#include "godot_cpp/classes/file_access.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/variant/string.hpp"
#include <godot_cpp/classes/object.hpp>

using namespace godot;

namespace GC {

/*
Implements a generic save game system using binary serialization as described here:
https://www.nightquestgames.com/godot-4-save-and-load-games-how-to-build-a-robust-system/
*/
class SaveManager : public Object {
	GDCLASS(SaveManager, Object);

private:
	Ref<FileAccess> file;
	String file_path;
	String password;

	~SaveManager() {};

protected:
	static void _bind_methods() {};

public:
	void init(String path, String input_password) {
		file_path = path;
		password = input_password;
	}

	void clear() {
		FileAccess file;
		String file_path;
		String password;
	}

	int open_file(FileAccess::ModeFlags access) {
		file = FileAccess::open_encrypted_with_pass(file_path, access, password);
		return file == nullptr ? FileAccess::get_open_error() : OK;
	}

	void close_file() { file->close(); }

	template <typename T> void serialize(T object) { object->serialize(file); }

	template <typename T> void deserialize(T object) { object->deserialize(file); }
};

/*

Example Usage:


// To understand this system you should first read this great article:
https://www.nightquestgames.com/godot-4-save-and-load-games-how-to-build-a-robust-system/
// First you'll need 2 functions that will init the saving and loading of your game similar to this:

void Galaxy::on_save(String file_name) {
	save_manager = memnew(SaveManager());
	save_manager->init(file_name, "12345");

	int status = save_manager->open_file(FileAccess::WRITE);
	if (status != OK) {
		UtilityFunctions::print("Error opening save file...");
		return;
	}

	save_manager->serialize(solar_system);
	save_manager->close_file();
}

void Galaxy::on_load(String file_name) {
	save_manager = memnew(SaveManager());
	save_manager->init(file_name, "12345");

	int status = save_manager->open_file(FileAccess::READ);
	if (status != OK) {
		UtilityFunctions::print("Error opening save file...");
		return;
	}

	solar_system->queue_free();

	SolarSystem *new_solar_system = memnew(SolarSystem());
	save_manager->deserialize(new_solar_system);
	add_child(new_solar_system);
	solar_system = new_solar_system;
	save_manager->close_file();
}

// Then in each and every game object you want to serialize and deserialize you will have to implement something like these
functions
// This might seem like a complicated example but you'll need to do something like this in order to properly recreate the
relationships between objects in your game

void SolarSystem::serialize(Ref<FileAccess> file) {
	file->store_64(game_object.id);
	file->store_16(get_stellar_bodies().size());
	for (int i = 0; i < get_stellar_bodies().size(); ++i) {
		StellarBody *body = get_stellar_bodies()[i];

		if (body != nullptr) {
			body->serialize(file);
		}
	}
}

void SolarSystem::deserialize(Ref<FileAccess> file) {
	uint64_t system_id = file->get_64();
	game_object.set_new_id(system_id);

	uint16_t bodies_in_solar_system = file->get_16();

	Array loaded_orbiting_bodies;
	loaded_orbiting_bodies.resize(bodies_in_solar_system); // Not resizing causes crash :(
	Dictionary loaded_stellar_bodies;

	for (int i = 0; i < bodies_in_solar_system; ++i) {
		StellarBody *body = memnew(StellarBody());

		if (body != nullptr) {
			std::pair<StellarBody *, Array> new_body_data = body->deserialize(file);

			if (new_body_data.first == nullptr) {
				continue;
			}

			// Save Stellar bodies in a Dictionary like this: Dictionary<uint32_t, StellarBody*>
			// This way we can iterate over the dictionary and assign the orbiting bodies to their parents from their ID.
			loaded_stellar_bodies[new_body_data.first->game_object.get_id()] = new_body_data.first;
			loaded_orbiting_bodies[i] = new_body_data.second;
		}
	}

	// Loop over all the loaded stellar bodies and assign orbiting bodies
	Array body_keys = loaded_stellar_bodies.keys();
	for (int i = 0; i < loaded_stellar_bodies.size(); i++) {
		Array orbiting_bodies = loaded_orbiting_bodies[i];

		if (orbiting_bodies.size() <= 0) {
			continue;
		}

		uint64_t body_id = body_keys[i];
		Variant body_variant = loaded_stellar_bodies[body_id];
		StellarBody *body = Object::cast_to<StellarBody>(body_variant);

		if (body == nullptr) {
			continue;
		}

		if (body->get_body_type() == STAR) {
			// Add star as child of solar system
			if (body->get_parent() == nullptr) {
				add_child(body);
			}
		}

		body->create_orbit(body->get_orbit_size());
		for (int i = 0; i < orbiting_bodies.size(); ++i) {
			uint64_t orbiting_body_id = orbiting_bodies[i];
			Variant orbiting_body_variant = loaded_stellar_bodies[orbiting_body_id];
			StellarBody *orbiting_body = Object::cast_to<StellarBody>(orbiting_body_variant);

			if (orbiting_body == nullptr) {
				continue;
			}

			body->add_body(orbiting_body);
		}
	}
}


// You probably noticed in the above functions they call the serialize and deserialize functions of the objects they contain
(StellarBodies are inside of SolarSystem so need to be loaded first and "bubbled up" to solar system)
// The StellarBody serialization looks like this:

void StellarBody::serialize(Ref<FileAccess> file) {
	// The order objects get serialized has to be the EXACT SAME as the order they are retrived in deserialize() or the data
	// won't be correct.

	file->store_var(get_position());
	file->store_pascal_string(get_name());
	file->store_8(material_type);
	file->store_8(body_type);
	file->store_64(game_object.id);
	file->store_64(location);
	file->store_float(scale.x); // Scale is actually a Vector3 but we can store just 1 float because all the values should
								// always be the same.
	file->store_var(has_atmosphere);
	file->store_var(orbiting_bodies.keys());
	file->store_float(orbit_size);

	file->store_var(body_params);
	if (material_type != M_NO_ATMOSPHERE) {
		file->store_var(atmosphere_params);
	}
	if (material_type == M_ICE or material_type == M_TERRESTRIAL) {
		file->store_var(cloud_params);
	}
}

std::pair<StellarBody *, Array> StellarBody::deserialize(Ref<FileAccess> file) {
	// The order objects get deserialized has to be the EXACT SAME as the order they are stored in serialize() or the data won't
	// be correct.
	StellarBodyMaterials *materials = new StellarBodyMaterials();

	Vector3 loaded_position = file->get_var();
	String body_name = file->get_pascal_string();
	uint8_t loaded_material_type = file->get_8();
	uint8_t loaded_body_type = file->get_8();
	uint64_t body_id = file->get_64();

	uint64_t system_id = file->get_64();
	float body_scale_f = file->get_float();
	Vector3 body_scale = Vector3(body_scale_f, body_scale_f, body_scale_f);
	bool body_has_atmosphere = file->get_var();
	Array orbiting_body_ids = file->get_var();
	orbit_size = file->get_float();

	Dictionary loaded_body_params = file->get_var();
	if (loaded_material_type == M_NO_ATMOSPHERE) {
		StellarBodyMaterial mats = materials->get_material_from_dict_no_atmosphere(loaded_body_params);
		create_body(system_id, StellarBodyType(loaded_body_type), 0.0, mats, body_scale, body_name, body_has_atmosphere,
				body_id, loaded_position);
	} else {
		Dictionary loaded_atmosphere_params = file->get_var();

		if (loaded_material_type == M_ICE or loaded_material_type == M_TERRESTRIAL) {
			Dictionary loaded_cloud_params = file->get_var();
			StellarBodyMaterial mats = materials->get_material_with_clouds_from_dict(
					loaded_body_params, loaded_atmosphere_params, loaded_cloud_params);
			create_body(system_id, StellarBodyType(loaded_body_type), 0.0, mats, body_scale, body_name, body_has_atmosphere,
					body_id, loaded_position);
		} else {
			StellarBodyMaterial mats = materials->get_material_from_dict(loaded_body_params, loaded_atmosphere_params);
			create_body(system_id, StellarBodyType(loaded_body_type), 0.0, mats, body_scale, body_name, body_has_atmosphere,
					body_id, loaded_position);
		}
	}

	delete materials;
	std::pair<StellarBody *, Array> out_pair(this, orbiting_body_ids);
	return out_pair;
}


That is all you'll need to fully implement a generic, extendable, and Tim Cain approved save game system
(https://youtu.be/S_gE99yeK6c?feature=shared).

*/

} //namespace GC
