#include "SolarSystem.hpp"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "StellarBody.hpp"

using namespace godot;

SolarSystem::SolarSystem() {
	Vector3 small_scale = Vector3(1300.0, 1300.0, 1300.0);
	Vector3 mid_scale = Vector3(1500.0, 1500.0, 1500.0);
	Vector3 big_scale = Vector3(2000.0, 2000.0, 2000.0);

	float star_size = UtilityFunctions::randf_range(3000, 6000);
	Vector3 star_scale = Vector3(star_size, star_size, star_size);

	StellarBody star = StellarBody();
	star.create_body(StellarBodyType(STAR), 0.0, materials.get_star_material(star_size), star_scale, "Sun");
	add_child(&star);

	StellarBody lavatus = StellarBody();
	lavatus.create_body(StellarBodyType(PLANET), 8000.0, materials.get_lava_material(), small_scale, "Lavatus");
	star.add_body(&lavatus);

	StellarBody sandicus = StellarBody();
	sandicus.create_body(StellarBodyType(PLANET), 11000.0, materials.get_sand_material(), small_scale, "Sandicus");
	star.add_body(&sandicus);

	StellarBody earth = StellarBody();
	StellarBody moon = StellarBody();

	earth.create_body(StellarBodyType(PLANET), 18500.0, materials.get_terrestrial_material(), mid_scale, "Urth");
	moon.create_body(StellarBodyType(PLANET), 400.0, materials.get_no_atmosphere_material(), small_scale, "Woon", false);

	earth.add_body(&moon);
	earth.create_orbit(500.0);
	star.add_body(&earth);

	StellarBody yupiter = StellarBody();
	yupiter.create_body(StellarBodyType(PLANET), 39000.0, materials.get_gas_material(), big_scale, "Yupiter");
	star.add_body(&yupiter);

	StellarBody veptune = StellarBody();
	veptune.create_body(StellarBodyType(PLANET), 53000.0, materials.get_ice_material(), mid_scale, "Veptune");
	star.add_body(&veptune);

	for (int i = 0; i < get_child_count(); ++i) {
		godot::StellarBody* child = Object::cast_to<StellarBody>(get_child(i));
		if (child) {
			stellar_bodies.push_back(child);
		}
	}
}
SolarSystem::~SolarSystem() {}
void SolarSystem::_bind_methods() {}

int SolarSystem::get_stellar_body_count() {
	return stellar_bodies.size();
}

StellarBody* SolarSystem::get_stellar_body(int index) {
	return stellar_bodies[index];
}
