#include "Orbit.hpp"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "StellarBody.hpp"
#include "godot_cpp/core/math.hpp"

using namespace godot;
using namespace GC;

const real_t MIN_ROTATION_SPEED = 0.00001f;
const real_t MAX_ROTATION_SPEED = 0.003f;

void Orbit::_bind_methods() {
	// ClassDB::bind_method(D_METHOD("get_max_orbit_size"), &Orbit::get_max_orbit_size);
	// ClassDB::bind_method(D_METHOD("set_max_orbit_size", "orbit_size"), &Orbit::set_max_orbit_size);
	// ClassDB::add_property("Orbit", PropertyInfo(Variant::FLOAT, "max_orbit_size"), "set_max_orbit_size",
	// "get_max_orbit_size");
}

Orbit::Orbit() {}
Orbit::~Orbit() {}

void Orbit::_physics_process(double delta) {
	StellarBody *parent = Object::cast_to<StellarBody>(get_parent());
	if (parent == nullptr) {
		return;
	}

	Array body_keys = parent->get_orbiting_bodies().keys();
	for (int i = 0; i < parent->get_orbiting_bodies().size(); i++) {
		uint32_t key = body_keys[i];
		Variant body_variant = parent->get_orbiting_bodies()[key];
		StellarBody *body = Object::cast_to<StellarBody>(body_variant);

		if (body == nullptr) {
			return;
		}

		float normalized_distance = Math::clamp(body->get_position().x / get_max_orbit_size(), 0.0, 1.0);
		float rotation_speed = Math::lerp(MIN_ROTATION_SPEED, MAX_ROTATION_SPEED, normalized_distance);
		parent->rotate_y(Math::deg_to_rad(rotation_speed));
	}
}

void Orbit::set_max_orbit_size(const float orbit_size) { max_orbit_size = Math::max(orbit_size, 0.01f); }

double Orbit::get_max_orbit_size() const { return max_orbit_size; }
