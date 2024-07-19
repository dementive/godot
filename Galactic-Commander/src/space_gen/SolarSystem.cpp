#include "SolarSystem.hpp"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "StellarBody.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

SolarSystem::SolarSystem() {}
SolarSystem::~SolarSystem() {}
void SolarSystem::_bind_methods() {}

void SolarSystem::generate_solar_system() {
	Vector3 small_scale = Vector3(1300.0, 1300.0, 1300.0);
	Vector3 mid_scale = Vector3(1500.0, 1500.0, 1500.0);
	Vector3 big_scale = Vector3(2000.0, 2000.0, 2000.0);

	float star_size = UtilityFunctions::randf_range(3000, 6000);
	Vector3 star_scale = Vector3(star_size, star_size, star_size);

	StellarBody* star = memnew(StellarBody());
	star->create_body(StellarBodyType(STAR), 0.0, materials.get_star_material(star_size), star_scale, "Sun");
	add_child(star);

	StellarBody* lavatus = memnew(StellarBody());
	lavatus->create_body(StellarBodyType(PLANET), 8000.0, materials.get_lava_material(), small_scale, "Lavatus");
	star->add_body(lavatus);

	StellarBody* sandicus = memnew(StellarBody());
	sandicus->create_body(StellarBodyType(PLANET), 11000.0, materials.get_sand_material(), small_scale, "Sandicus");
	star->add_body(sandicus);

	StellarBody* earth = memnew(StellarBody());
	StellarBody* moon = memnew(StellarBody());

	earth->create_body(StellarBodyType(PLANET), 18500.0, materials.get_terrestrial_material(), mid_scale, "Urth");
	moon->create_body(StellarBodyType(PLANET), 250.0, materials.get_no_atmosphere_material(), small_scale, "Woon", false);

	earth->add_body(moon);
	earth->create_orbit(300.0);
	star->add_body(earth);

	StellarBody* yupiter = memnew(StellarBody());
	yupiter->create_body(StellarBodyType(PLANET), 39000.0, materials.get_gas_material(), big_scale, "Yupiter");
	star->add_body(yupiter);

	StellarBody* veptune = memnew(StellarBody());
	veptune->create_body(StellarBodyType(PLANET), 53000.0, materials.get_ice_material(), mid_scale, "Veptune");
	star->add_body(veptune);

	stellar_bodies.push_back(star);
	stellar_bodies.push_back(lavatus);
	stellar_bodies.push_back(sandicus);
	stellar_bodies.push_back(earth);
	stellar_bodies.push_back(moon);
	stellar_bodies.push_back(yupiter);
	stellar_bodies.push_back(veptune);
}

int SolarSystem::get_stellar_body_count() {
	return stellar_bodies.size();
}

StellarBody* SolarSystem::get_stellar_body(int index) {
	return stellar_bodies[index];
}
