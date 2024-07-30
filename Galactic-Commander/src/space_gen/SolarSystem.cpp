#include "godot_cpp/variant/utility_functions.hpp"
#include <godot_cpp/core/class_db.hpp>

#include "SolarSystem.hpp"
#include "StellarBody.hpp"

using namespace godot;
using namespace GC;

SolarSystem::SolarSystem() {}
SolarSystem::~SolarSystem() {}
void SolarSystem::_bind_methods() {}

void SolarSystem::generate_solar_system() {
	game_object.set_id(this);
	Vector3 small_scale = Vector3(1500.0, 1500.0, 1500.0);
	Vector3 mid_scale = Vector3(2000.0, 2000.0, 2000.0);
	Vector3 big_scale = Vector3(3500.0, 3500.0, 3500.0);

	float star_size = UtilityFunctions::randf_range(5000, 10000);
	Vector3 star_scale = Vector3(star_size, star_size, star_size);
	StellarBodyMaterials *materials = new StellarBodyMaterials();

	float body_position = 0.0;

	StellarBody *star = memnew(StellarBody());

	star->create_body(game_object.get_id(), StellarBodyType(STAR), body_position, materials->get_star_material(star_size), star_scale, "Sun");
	add_child(star);

	body_position += star_scale.x * 2.5;

	StellarBody *lavatus = memnew(StellarBody());
	lavatus->create_body(game_object.get_id(), StellarBodyType(PLANET), body_position, materials->get_lava_material(), small_scale, "Lavatus");
	star->add_body(lavatus);

	body_position += small_scale.x * 10;

	StellarBody *sandicus = memnew(StellarBody());
	sandicus->create_body(game_object.get_id(), StellarBodyType(PLANET), body_position, materials->get_sand_material(), small_scale, "Sandicus");
	star->add_body(sandicus);

	body_position += small_scale.x * 12;

	StellarBody *earth = memnew(StellarBody());
	StellarBody *moon = memnew(StellarBody());

	earth->create_body(game_object.get_id(), StellarBodyType(PLANET), body_position, materials->get_terrestrial_material(), mid_scale, "Urth");
	moon->create_body(game_object.get_id(), StellarBodyType(PLANET), 250.0, materials->get_no_atmosphere_material(), small_scale, "Woon", false);

	earth->add_body(moon);
	earth->create_orbit(300.0);
	star->add_body(earth);

	body_position += mid_scale.x * 15;

	StellarBody *yupiter = memnew(StellarBody());
	yupiter->create_body(game_object.get_id(), StellarBodyType(PLANET), body_position, materials->get_gas_material(), big_scale, "Yupiter");
	star->add_body(yupiter);

	body_position += big_scale.x * 10;

	StellarBody *veptune = memnew(StellarBody());
	veptune->create_body(game_object.get_id(), StellarBodyType(PLANET), body_position, materials->get_ice_material(), mid_scale, "Veptune");
	star->add_body(veptune);

	stellar_bodies.push_back(star);
	stellar_bodies.push_back(lavatus);
	stellar_bodies.push_back(sandicus);
	stellar_bodies.push_back(earth);
	stellar_bodies.push_back(moon);
	stellar_bodies.push_back(yupiter);
	stellar_bodies.push_back(veptune);

	delete materials;
}

StellarBody *SolarSystem::get_stellar_body(int index) { return stellar_bodies[index]; }

Vector<StellarBody *> SolarSystem::get_stellar_bodies() { return stellar_bodies; }

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
	game_object.set_new_id(system_id, this);

	uint16_t bodies_in_solar_system = file->get_16();

	Array loaded_orbiting_bodies;
	loaded_orbiting_bodies.resize(bodies_in_solar_system); // Not resizing causes crash :(
	Dictionary loaded_stellar_bodies;

	for (int i = 0; i < bodies_in_solar_system; ++i) {
		StellarBody *body = memnew(StellarBody());

		if (body != nullptr) {
			Pair<StellarBody *, Array> new_body_data = body->deserialize(file);

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
