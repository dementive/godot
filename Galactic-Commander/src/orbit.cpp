#include "orbit.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/static_body3d.hpp> // TODO - replace StaticBody3D with StellarBody
#include "godot_cpp/core/math.hpp"

using namespace godot;

void GCOrbit::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_max_orbit_size"), &GCOrbit::get_max_orbit_size);
	ClassDB::bind_method(D_METHOD("set_max_orbit_size", "orbit_size"), &GCOrbit::set_max_orbit_size);
	ClassDB::add_property("GCOrbit", PropertyInfo(Variant::FLOAT, "max_orbit_size"), "set_max_orbit_size", "get_max_orbit_size");
}

GCOrbit::GCOrbit() {
	max_orbit_size = 60000.0;
}

GCOrbit::~GCOrbit() {}

void GCOrbit::_physics_process(double delta) {
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

void GCOrbit::set_max_orbit_size(const float orbit_size) {
	max_orbit_size = Math::max(orbit_size, 0.01f);
}

double GCOrbit::get_max_orbit_size() const {
	return max_orbit_size;
}
