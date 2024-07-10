class_name PlanetGeneration
extends Node3D

var PlanetColors = preload("res://scripts/planet_colors.gd").new()
var PlanetMaterial = preload("res://scripts/planet_materials.gd").new()

var ice_colors: Array[PackedColorArray] = PlanetColors.get_ice_planet_colors()
var gas_colors: Array[PackedColorArray] = PlanetColors.get_gas_planet_colors()
var no_atmosphere_colors: Array[PackedColorArray] = PlanetColors.get_no_atmosphere_colors()
var terrestrial_colors: Array[PackedColorArray] = PlanetColors.get_terrestrial_planet_colors()
var sand_colors: Array[PackedColorArray] = PlanetColors.get_sand_planet_colors()
var lava_colors: Array[PackedColorArray] = PlanetColors.get_lava_planet_colors()
var star_colors: Dictionary = PlanetColors.get_star_colors()

func _ready():
	var small_scale = Vector3(1300.0, 1300.0, 1300.0)
	var mid_scale = Vector3(1500.0, 1500.0, 1500.0)
	var big_scale = Vector3(2000.0, 2000.0, 2000.0)
	
	var star_size: float = randf_range(3000, 6000)
	var star_material: Array[ShaderMaterial] 
	var star_scale = Vector3(star_size, star_size, star_size)
	
	# Star color is directly correlated with the star's mass
	if star_size < 3500:
		star_material= PlanetMaterial.get_star_material(star_colors["white"])
	elif star_size >= 3500 and star_size >= 4250:
		star_material = PlanetMaterial.get_star_material(star_colors["yellow"])
	elif star_size >= 4250 and star_size >= 5000:
		star_material = PlanetMaterial.get_star_material(star_colors["blue"])
	else:
		star_material = PlanetMaterial.get_star_material(star_colors["red"])
	
	var star: Node3D = generate_star(star_material, star_scale)
	star.add_child(
		generate_planet(8000.0, PlanetMaterial.get_lava_material(lava_colors.pick_random()), small_scale)
	)
	
	star.add_child(
		generate_planet(11000.0, PlanetMaterial.get_sand_material(sand_colors.pick_random()), small_scale)
	)
	star.add_child(
		generate_planet(18500.0, PlanetMaterial.get_terrestrial_material(terrestrial_colors.pick_random()), mid_scale)
	)
	star.add_child(
		generate_planet_no_atmosphere(25000.0, PlanetMaterial.get_no_atmosphere_material(no_atmosphere_colors.pick_random()), mid_scale)
	)
	star.add_child(
		generate_planet_no_atmosphere(31000.0, PlanetMaterial.get_no_atmosphere_material(no_atmosphere_colors.pick_random()), small_scale)
	)
	star.add_child(
		generate_planet(39000.0, PlanetMaterial.get_gas_material(gas_colors.pick_random()), big_scale)
	)
	star.add_child(
		generate_planet(53000.0, PlanetMaterial.get_ice_material(ice_colors.pick_random()), mid_scale)
	)

func generate_planet_no_atmosphere(
	distance_from_star: float,
	shader_material: ShaderMaterial,
	planet_scale: Vector3
	) -> StaticBody3D:
	# Planet that does not use the atmosphere shader
	var static_body: StaticBody3D = StaticBody3D.new()
	static_body.position.x = distance_from_star
	static_body.position.z = randf_range(0, 10000)
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	static_body.add_child(collision_shape)
	collision_shape.scale = planet_scale + Vector3(100, 100, 100)
	collision_shape.shape = SphereShape3D.new()
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	
	mesh_instance.mesh = SphereMesh.new()
	mesh_instance.mesh.set_material(shader_material)
	mesh_instance.scale = planet_scale
	
	static_body.add_child(mesh_instance)
	return static_body
	
func generate_planet(
	distance_from_star: float,
	materials: Array[ShaderMaterial],
	planet_scale: Vector3
	) -> StaticBody3D:
	var static_body: StaticBody3D = StaticBody3D.new()
	static_body.position.x = distance_from_star
	static_body.position.z = randf_range(0, 10000)
	
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	static_body.add_child(collision_shape)
	collision_shape.scale = planet_scale + Vector3(800, 800, 800)
	collision_shape.shape = SphereShape3D.new()
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
	
	mesh_instance.mesh = SphereMesh.new()
	atmosphere_mesh.mesh = SphereMesh.new()
	
	mesh_instance.mesh.set_material(materials[0])
	atmosphere_mesh.mesh.set_material(materials[1])
	
	mesh_instance.scale = planet_scale
	atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
	
	mesh_instance.add_child(atmosphere_mesh)
	static_body.add_child(mesh_instance)
	return static_body

func generate_star(
	materials: Array[ShaderMaterial],
	star_scale: Vector3
	) -> Node3D:
	# Star generation, same as generate_planet except stars do not move through space.
	var star_node: Node3D = Node3D.new()
	var static_body: StaticBody3D = StaticBody3D.new()
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	static_body.add_child(collision_shape)
	collision_shape.scale = star_scale + Vector3(1500, 1500, 1500)
	collision_shape.shape = SphereShape3D.new()
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
	star_node.set_script(load("res://scripts/orbit.gd"))
	
	mesh_instance.mesh = SphereMesh.new()
	atmosphere_mesh.mesh = SphereMesh.new()
	
	mesh_instance.mesh.set_material(materials[0])
	atmosphere_mesh.mesh.set_material(materials[1])
	
	mesh_instance.scale = star_scale
	atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
	
	mesh_instance.add_child(atmosphere_mesh)
	static_body.add_child(mesh_instance)
	star_node.add_child(static_body)
	add_child(star_node)
	return star_node
