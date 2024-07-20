#include "godot_cpp/variant/string_name.hpp"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/sphere_shape3d.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "Orbit.hpp"
#include "StellarBody.hpp"

using namespace godot;

StellarBody::StellarBody() {}
StellarBody::~StellarBody() {}
void StellarBody::_bind_methods() {}

void StellarBody::create_body(
	StellarBodyType body_type, float distance_from_orbit_origin, StellarBodyMaterial materials, Vector3 body_scale,
	String body_name, bool atmosphere
) {
	// This code should be in the constructor but this isn't possible currently
	// https://github.com/godotengine/godot-cpp/issues/953

	// Save shader params so StellarBody can be serialized.
	cloud_params = materials.cloud_params;
	body_params = materials.body_params;
	atmosphere_params = materials.atmosphere_params;
	type = materials.type;

	set_name(body_name);
	if (body_type == STAR) {
		generate_body(distance_from_orbit_origin, materials, body_scale, atmosphere);
		create_orbit();
	} else if (body_type == PLANET) {
		generate_body(distance_from_orbit_origin, materials, body_scale, atmosphere);
	}
}

void StellarBody::_input_event(
	Camera3D* camera, const Ref<InputEvent>& event, const Vector3& position, const Vector3& normal, int32_t shape_idx
) {
	if (event->is_class("InputEventMouseButton")) {
		InputEventMouseButton* input_event_mouse_button = static_cast<InputEventMouseButton*>(*event);
		if (input_event_mouse_button->is_pressed() && input_event_mouse_button->get_button_index() == MOUSE_BUTTON_LEFT) {
			Control* panel = get_planet_info_panel();
			if (panel) {
				panel->set_visible(true);
				panel->get_node<Label>("PlanetNameLabel")->set_text(get_name());
			}
		}
	}
}

void StellarBody::_mouse_exit() {
	Control* panel = get_planet_info_panel();
	if (panel) {
		panel->set_visible(false);
	}
}

void StellarBody::create_orbit(float orbit_size) {
	Orbit* orbit = memnew(Orbit());
	orbit->set_max_orbit_size(orbit_size);
	orbit->set_name(get_name() + StringName("Orbit"));
	add_child(orbit);
}

void StellarBody::add_body(StellarBody* body) {
	orbiting_bodies.push_back(body);
	add_child(body);
}

void StellarBody::generate_body(
	float distance_from_star, StellarBodyMaterial materials, Vector3 body_scale, bool body_has_atmosphere
) {
	if (distance_from_star > 0) {
		Vector3 position = get_position();
		position.x = distance_from_star;
		position.z = UtilityFunctions::randf_range(0, 10000);
		set_position(position);
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
	add_child(&mesh_instance); // Be careful this is the first child so it doesn't break get_mesh()
}

void StellarBody::serialize(Ref<FileAccess> file) {
	// To recreate these objects all we need is the parameters to the generate_body function to get saved.
	// Also if there are orbiting bodies we have to save that as the orbit needs to be reacreated with create_orbit()

	// float distance_from_star, StellarBodyMaterial materials, Vector3 body_scale, bool body_has_atmosphere

	Vector3 position = get_position();
	file->store_float(position.x);
	file->store_8(type);
	file->store_float(scale.x); // Scale is actually a Vector3 but we can store just 1 float because all the values should always be the same.
	file->store_var(has_atmosphere);

	if (type == M_ICE or type == M_TERRESTRIAL) {
		file->store_var(cloud_params);
	}
	if (type != M_NO_ATMOSPHERE) {
		file->store_var(atmosphere_params);
	}
	file->store_var(body_params);
}

void StellarBody::deserialize(Ref<FileAccess> file) {
	// The order objects get deserialized has to be the EXACT SAME as the order they are stored in serialize()
	StellarBodyMaterials* materials = new StellarBodyMaterials();

	float x_pos = file->get_float();
	UtilityFunctions::print("Position: ", x_pos);

	uint8_t body_type = file->get_8();
	UtilityFunctions::print("Body Type: ", body_type);

	float body_scale_f = file->get_float();
	Vector3 body_scale = Vector3(body_scale_f, body_scale_f, body_scale_f);
	UtilityFunctions::print("Body Scale: ", body_scale);

	bool body_has_atmosphere = file->get_var();
	UtilityFunctions::print("Atmosphere: ", body_has_atmosphere);

	Dictionary b_params = file->get_var();
	UtilityFunctions::print("Body params: ", b_params);
	if (body_type == M_NO_ATMOSPHERE) {
		StellarBodyMaterial mats = materials->get_material_from_dict_no_atmosphere(b_params);
	} else {
		Dictionary a_params = file->get_var();
		UtilityFunctions::print("Atmosphere params: ", a_params);

		if (body_type == M_ICE or body_type == M_TERRESTRIAL) {
			Dictionary c_params = file->get_var();
			UtilityFunctions::print("Cloud params: ", c_params);
			StellarBodyMaterial mats = materials->get_material_with_clouds_from_dict(b_params, a_params, c_params);
		} else {
			StellarBodyMaterial mats = materials->get_material_from_dict(b_params, a_params);
		}
	}
	UtilityFunctions::print("\n\n");
	delete materials;
}

Control* StellarBody::get_planet_info_panel() {
	Array ui_panels = get_tree()->get_nodes_in_group("ui_panels");
	Control* panel = Object::cast_to<Control>(ui_panels[0]);
	return panel;
}

Vector3 StellarBody::get_scale() {
	return scale;
}

MeshInstance3D* StellarBody::get_mesh() {
	return Object::cast_to<MeshInstance3D>(get_child(0));
}
