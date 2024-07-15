extends Node3D
class_name SolarSystem

var PlanetColors = preload("res://scripts/space_gen/planet_colors.gd").new()
var PlanetMaterial = preload("res://scripts/space_gen/planet_materials.gd").new()

var ice_colors: Array[PackedColorArray] = PlanetColors.get_ice_planet_colors()
var gas_colors: Array[PackedColorArray] = PlanetColors.get_gas_planet_colors()
var no_atmosphere_colors: Array[PackedColorArray] = PlanetColors.get_no_atmosphere_colors()
var terrestrial_colors: Array[PackedColorArray] = PlanetColors.get_terrestrial_planet_colors()
var sand_colors: Array[PackedColorArray] = PlanetColors.get_sand_planet_colors()
var lava_colors: Array[PackedColorArray] = PlanetColors.get_lava_planet_colors()

var _bodies : Array

func _init(system_name: String):
	set_name(system_name)
	generate_solar_system()

func get_stellar_body_count() -> int:
	return len(_bodies)

func get_stellar_body(idx: int) -> StaticBody3D:
	return _bodies[idx]

func generate_solar_system():
	var small_scale = Vector3(1300.0, 1300.0, 1300.0)
	var mid_scale = Vector3(1500.0, 1500.0, 1500.0)
	var big_scale = Vector3(2000.0, 2000.0, 2000.0)
	
	var star_size: float = randf_range(3000, 6000)
	var star_scale = Vector3(star_size, star_size, star_size)
	
	var star : StellarBody = StellarBody.new(StellarBody.type.STAR, 0.0, PlanetMaterial.get_star_material(star_size), star_scale, "Sun")
	add_child(star)
	
	var lavatus : StellarBody = StellarBody.new(StellarBody.type.PLANET, 8000.0, PlanetMaterial.get_lava_material(lava_colors.pick_random()), small_scale, "Lavatus")
	star.add_body(lavatus)
	
	var sandicus : StellarBody = StellarBody.new(StellarBody.type.PLANET, 11000.0, PlanetMaterial.get_sand_material(sand_colors.pick_random()), small_scale, "Sandicus")
	star.add_body(sandicus)
	
	var earth : StellarBody = StellarBody.new(StellarBody.type.PLANET, 18500.0, PlanetMaterial.get_terrestrial_material(terrestrial_colors.pick_random()), mid_scale, "Earth")
	var moon : StellarBody = StellarBody.new(StellarBody.type.PLANET, 400.0, PlanetMaterial.get_no_atmosphere_material(no_atmosphere_colors.pick_random()), small_scale, "Moon", false)
	earth.add_body(moon)
	earth.create_orbit(500.0)
	
	star.add_body(earth)

	var yupiter : StellarBody = StellarBody.new(StellarBody.type.PLANET, 39000.0, PlanetMaterial.get_gas_material(gas_colors.pick_random()), big_scale, "Yupiter")
	star.add_body(yupiter)
	
	var veptune : StellarBody = StellarBody.new(StellarBody.type.PLANET, 53000.0, PlanetMaterial.get_ice_material(ice_colors.pick_random()), mid_scale, "Veptune")
	star.add_body(veptune)

	for body in get_children():
		if body is StellarBody:
			_bodies.append(body)
