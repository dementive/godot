#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/sphere_shape3d.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "Orbit.hpp"
#include "StellarBody.hpp"

using namespace godot;
using namespace GC;

StellarBody::StellarBody() {}
StellarBody::~StellarBody() {}
void StellarBody::_bind_methods() {}

StellarBody *StellarBody::create_body(uint8_t system_id, StellarBodyType stellar_body_type, float distance_from_orbit_origin,
		StellarBodyMaterial materials, Vector3 body_scale, String body_name, bool atmosphere, uint32_t new_id,
		Vector3 load_position) {
	// This code should be in the constructor but this isn't possible currently
	// https://github.com/godotengine/godot-cpp/issues/953

	cloud_params = materials.cloud_params;
	body_params = materials.body_params;
	atmosphere_params = materials.atmosphere_params;
	body_type = stellar_body_type;
	material_type = materials.type;

	if (new_id == -1) {
		set_id();
	} else {
		set_new_id(new_id);
	}
	set_solar_system_id(system_id);
	set_name(body_name);

	if (body_type == STAR) {
		generate_body(distance_from_orbit_origin, materials, body_scale, atmosphere, load_position);
		if (new_id == -1) {
			create_orbit(60000); // SolarSystem::deserisalize() handles creating the orbit when loading
		}
	} else if (body_type == PLANET) {
		generate_body(distance_from_orbit_origin, materials, body_scale, atmosphere, load_position);
	}

	return this;
}

void StellarBody::generate_body(float distance_from_orbit_origin, StellarBodyMaterial materials, Vector3 body_scale,
		bool body_has_atmosphere, Vector3 load_position) {
	if (distance_from_orbit_origin > 0 and load_position == VECTOR_FORWARD) {
		Vector3 position = get_position();
		position.x = distance_from_orbit_origin;
		position.z = UtilityFunctions::randf_range(0, 10000);
		set_position(position);
	} else {
		set_position(load_position);
	}

	SphereShape3D sphere_shape = SphereShape3D();
	sphere_shape.set_radius((body_scale.x / 2) + body_scale.x / 2.0);
	Ref<SphereShape3D> sphere_ref(&sphere_shape);
	shape_owner_add_shape(create_shape_owner(this), sphere_ref);

	MeshInstance3D mesh_instance = MeshInstance3D();
	SphereMesh sphere = SphereMesh();
	sphere.set_material(&materials.body);
	Ref<SphereMesh> instance_ref(&sphere);

	mesh_instance.set_mesh(instance_ref);
	mesh_instance.set_scale(body_scale);

	if (body_has_atmosphere) {
		has_atmosphere = true;
		MeshInstance3D atmosphere_mesh = MeshInstance3D();

		SphereMesh a_sphere = SphereMesh();
		a_sphere.set_material(&materials.atmosphere);
		Ref<SphereMesh> a_sphere_ref(&a_sphere);
		atmosphere_mesh.set_mesh(a_sphere_ref);

		atmosphere_mesh.set_scale(Vector3(1.01, 1.01, 1.01));
		mesh_instance.add_child(&atmosphere_mesh);
	}

	scale = body_scale;
	add_child(&mesh_instance);
}

void StellarBody::_input_event(
		Camera3D *camera, const Ref<InputEvent> &event, const Vector3 &position, const Vector3 &normal, int32_t shape_idx) {
	if (event->is_class("InputEventMouseButton")) {
		InputEventMouseButton *input_event_mouse_button = static_cast<InputEventMouseButton *>(*event);
		if (input_event_mouse_button->is_pressed() && input_event_mouse_button->get_button_index() == MOUSE_BUTTON_LEFT) {
			Control *panel = get_planet_info_panel();
			if (panel) {
				panel->set_visible(true);
				panel->get_node<Label>("PlanetNameLabel")->set_text(get_name());
			}
		}
	}
}

void StellarBody::_mouse_exit() {
	Control *panel = get_planet_info_panel();
	if (panel) {
		panel->set_visible(false);
	}
}

void StellarBody::create_orbit(float new_orbit_size) {
	Orbit *orbit = memnew(Orbit());
	orbit_size = new_orbit_size;
	orbit->set_max_orbit_size(orbit_size);
	add_child(orbit);
}

void StellarBody::add_body(StellarBody *body) {
	orbiting_bodies[body->get_id()] = body;
	add_child(body);
}

void StellarBody::serialize(Ref<FileAccess> file) {
	// The order objects get serialized has to be the EXACT SAME as the order they are retrived in deserialize() or the data
	// won't be correct.

	file->store_var(get_position());
	file->store_pascal_string(get_name());
	file->store_8(material_type);
	file->store_8(body_type);
	file->store_32(id);
	file->store_8(solar_system_id);
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
	uint32_t body_id = file->get_32();
	uint8_t system_id = file->get_8();
	float body_scale_f = file->get_float();
	Vector3 body_scale = Vector3(body_scale_f, body_scale_f, body_scale_f);
	bool body_has_atmosphere = file->get_var();
	Array orbiting_body_ids = file->get_var();
	orbit_size = file->get_float();

	Dictionary b_params = file->get_var();
	if (loaded_material_type == M_NO_ATMOSPHERE) {
		StellarBodyMaterial mats = materials->get_material_from_dict_no_atmosphere(b_params);
		create_body(system_id, StellarBodyType(body_type), 0.0, mats, body_scale, body_name, body_has_atmosphere, body_id,
				loaded_position);
	} else {
		Dictionary a_params = file->get_var();

		if (loaded_material_type == M_ICE or loaded_material_type == M_TERRESTRIAL) {
			Dictionary c_params = file->get_var();
			StellarBodyMaterial mats = materials->get_material_with_clouds_from_dict(b_params, a_params, c_params);
			create_body(system_id, StellarBodyType(body_type), 0.0, mats, body_scale, body_name, body_has_atmosphere, body_id,
					loaded_position);
		} else {
			StellarBodyMaterial mats = materials->get_material_from_dict(b_params, a_params);
			create_body(system_id, StellarBodyType(body_type), 0.0, mats, body_scale, body_name, body_has_atmosphere, body_id,
					loaded_position);
		}
	}

	delete materials;
	std::pair<StellarBody *, Array> out_pair(this, orbiting_body_ids);
	return out_pair;
}

Control *StellarBody::get_planet_info_panel() {
	Array ui_panels = get_tree()->get_nodes_in_group("ui_panels");
	Control *panel = Object::cast_to<Control>(ui_panels[0]);
	return panel;
}

Vector3 StellarBody::get_scale() { return scale; }

void StellarBody::set_solar_system_id(uint8_t new_id) { solar_system_id = new_id; }

uint8_t StellarBody::get_solar_system_id() { return solar_system_id; }

void StellarBody::set_id() {
	id = next_id;
	StellarBody::next_id++;
}

void StellarBody::set_new_id(uint32_t new_id) { id = new_id; }

uint32_t StellarBody::get_id() { return id; }

void StellarBody::set_orbiting_bodies(Dictionary new_orbiting_bodies) { orbiting_bodies = new_orbiting_bodies; }
Dictionary StellarBody::get_orbiting_bodies() { return orbiting_bodies; }

StellarBodyType StellarBody::get_body_type() { return body_type; }

float StellarBody::get_orbit_size() { return orbit_size; }
