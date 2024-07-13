extends Node3D

var PlanetColors = preload("res://scripts/space_gen/planet_colors.gd").new()
var PlanetMaterial = preload("res://scripts/space_gen/planet_materials.gd").new()
var Planet = preload("res://scripts/space_gen/planet.gd").new()

var ice_colors: Array[PackedColorArray] = PlanetColors.get_ice_planet_colors()
var gas_colors: Array[PackedColorArray] = PlanetColors.get_gas_planet_colors()
var no_atmosphere_colors: Array[PackedColorArray] = PlanetColors.get_no_atmosphere_colors()
var terrestrial_colors: Array[PackedColorArray] = PlanetColors.get_terrestrial_planet_colors()
var sand_colors: Array[PackedColorArray] = PlanetColors.get_sand_planet_colors()
var lava_colors: Array[PackedColorArray] = PlanetColors.get_lava_planet_colors()
var star_colors: Dictionary = PlanetColors.get_star_colors()

func generate_solar_system() -> Node3D:
	var small_scale = Vector3(1300.0, 1300.0, 1300.0)
	var mid_scale = Vector3(1500.0, 1500.0, 1500.0)
	var big_scale = Vector3(2000.0, 2000.0, 2000.0)
	
	var star_size: float = randf_range(3000, 6000)
	var star_material: Array[ShaderMaterial] 
	var star_scale = Vector3(star_size, star_size, star_size)
	
	# Star color is directly correlated with the star's mass
	if star_size < 3500:
		star_material= PlanetMaterial.get_star_material(star_colors["red"])
	elif star_size >= 3500 and star_size >= 4250:
		star_material = PlanetMaterial.get_star_material(star_colors["red"])
	elif star_size >= 4250 and star_size >= 5000:
		star_material = PlanetMaterial.get_star_material(star_colors["red"])
	else:
		star_material = PlanetMaterial.get_star_material(star_colors["red"])
	
	var star: Node3D = Planet.generate_star(star_material, star_scale)
	star.add_child(
		Planet.generate_planet(8000.0, PlanetMaterial.get_lava_material(lava_colors.pick_random()), small_scale)
	)
	
	star.add_child(
		Planet.generate_planet(11000.0, PlanetMaterial.get_sand_material(sand_colors.pick_random()), small_scale)
	)
	star.add_child(
		Planet.generate_planet(18500.0, PlanetMaterial.get_terrestrial_material(terrestrial_colors.pick_random()), mid_scale)
	)
	star.add_child(
		Planet.generate_planet_no_atmosphere(25000.0, PlanetMaterial.get_no_atmosphere_material(no_atmosphere_colors.pick_random()), mid_scale)
	)
	star.add_child(
		Planet.generate_planet_no_atmosphere(31000.0, PlanetMaterial.get_no_atmosphere_material(no_atmosphere_colors.pick_random()), small_scale)
	)
	star.add_child(
		Planet.generate_planet(39000.0, PlanetMaterial.get_gas_material(gas_colors.pick_random()), big_scale)
	)
	star.add_child(
		Planet.generate_planet(53000.0, PlanetMaterial.get_ice_material(ice_colors.pick_random()), mid_scale)
	)

	add_child(star)
	
	return self
