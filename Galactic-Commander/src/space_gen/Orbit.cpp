#include "Orbit.hpp"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "StellarBody.hpp"
#include "godot_cpp/core/math.hpp"

using namespace godot;

void Orbit::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_max_orbit_size"), &Orbit::get_max_orbit_size);
	ClassDB::bind_method(D_METHOD("set_max_orbit_size", "orbit_size"), &Orbit::set_max_orbit_size);
	ClassDB::add_property("Orbit", PropertyInfo(Variant::FLOAT, "max_orbit_size"), "set_max_orbit_size", "get_max_orbit_size");
}

Orbit::Orbit() {
	max_orbit_size = 60000.0;
}

Orbit::~Orbit() {}

void Orbit::_physics_process(double delta) {
	// StellarBody* parent = Object::cast_to<StellarBody>(get_parent());
	// if (!parent) {
	// 	return;
	// }

	// for (auto& body : parent->orbiting_bodies) {
	// 	if (!body) {
	// 		continue;
	// 	}

	// 	float normalized_distance = Math::clamp(body->get_position().x / get_max_orbit_size(), 0.0, 1.0);
	// 	float rotation_speed = Math::lerp(0.00001f, 0.003f, normalized_distance);
	// 	parent->rotate_y(Math::deg_to_rad(rotation_speed));
	// }
	StaticBody3D* parent = Object::cast_to<StaticBody3D>(get_parent());
	if (!parent) return;

	TypedArray<Node> children = parent->get_children();
	for (int i = 0; i < children.size(); ++i)
	{
		StaticBody3D* child = Object::cast_to<StaticBody3D>(children[i]);
		if (!child) continue;
		
		float normalized_distance = Math::clamp(child->get_position().x / get_max_orbit_size(), 0.0, 1.0);
		float rotation_speed = Math::lerp(0.00001f, 0.003f, normalized_distance);
		parent->rotate_y(Math::deg_to_rad(rotation_speed));
	}
}

void Orbit::set_max_orbit_size(const float orbit_size) {
	max_orbit_size = Math::max(orbit_size, 0.01f);
}

double Orbit::get_max_orbit_size() const {
	return max_orbit_size;
}
