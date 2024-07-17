#include "StellarBody.hpp"

#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/sphere_shape3d.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "Orbit.hpp"
#include "godot_cpp/variant/string_name.hpp"
#include "godot_cpp/variant/vector3.hpp"

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
	set_name(body_name);
	if (body_type == STAR) {
		generate_body(distance_from_orbit_origin, materials, body_scale, atmosphere);
		create_orbit();
	} else if (body_type == PLANET) {
		generate_body(distance_from_orbit_origin, materials, body_scale, atmosphere);
	}
}

Control* StellarBody::get_planet_info_panel() {
	Array ui_panels = get_tree()->get_nodes_in_group("ui_panels");
	Control* panel = Object::cast_to<Control>(ui_panels[0]);
	return panel;
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
	float distance_from_star, StellarBodyMaterial materials, Vector3 planet_scale, bool has_atmosphere
) {
	if (distance_from_star > 0) {
		Vector3 position = get_position();
		position.x = distance_from_star;
		position.z = UtilityFunctions::randf_range(0, 10000);
		set_position(position);
	}

	SphereShape3D sphere_shape = SphereShape3D();
	sphere_shape.set_radius((planet_scale.x / 2) + planet_scale.x / 2.0);
	Ref<SphereShape3D> sphere_ref(&sphere_shape);
	shape_owner_add_shape(create_shape_owner(this), sphere_ref);

	MeshInstance3D mesh_instance = MeshInstance3D();
	SphereMesh sphere = SphereMesh();
	sphere.set_material(&materials.body);
	Ref<SphereMesh> instance_ref(&sphere);

	mesh_instance.set_mesh(instance_ref);
	mesh_instance.set_name(get_name() + StringName("Mesh"));
	mesh_instance.set_scale(planet_scale);

	if (has_atmosphere) {
		MeshInstance3D atmosphere_mesh = MeshInstance3D();

		SphereMesh a_sphere = SphereMesh();
		a_sphere.set_material(&materials.atmosphere);
		Ref<SphereMesh> a_sphere_ref(&a_sphere);
		atmosphere_mesh.set_mesh(a_sphere_ref);

		atmosphere_mesh.set_name(get_name() + StringName("AtmosphereMesh"));
		atmosphere_mesh.set_scale(Vector3(1.01, 1.01, 1.01));
		mesh_instance.add_child(&atmosphere_mesh);
	}

	add_child(&mesh_instance);
}
