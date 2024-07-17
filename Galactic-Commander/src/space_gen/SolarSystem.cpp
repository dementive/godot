#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>

#include "SolarSystem.hpp"
#include "StellarBody.hpp"

using namespace godot;

SolarSystem::SolarSystem() {}
SolarSystem::~SolarSystem() {}

void SolarSystem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("generate_solar_system"), &SolarSystem::generate_solar_system);
}

void SolarSystem::generate_solar_system() {
	Vector3 small_scale = Vector3(1300.0, 1300.0, 1300.0);
	Vector3 mid_scale = Vector3(1500.0, 1500.0, 1500.0);
	Vector3 big_scale = Vector3(2000.0, 2000.0, 2000.0);

	float star_size = UtilityFunctions::randf_range(3000, 6000);
	Vector3 star_scale = Vector3(star_size, star_size, star_size);

	StellarBody star = StellarBody();
	star.create_body(StellarBodyType(STAR), 0.0, materials.get_star_material(star_size), star_scale, "Sun");

	add_child(&star);
}

int SolarSystem::get_stellar_body_count() {
	return stellar_bodies.size();
}

StellarBody* SolarSystem::get_stellar_body(int index) {
	return stellar_bodies[index];
}
