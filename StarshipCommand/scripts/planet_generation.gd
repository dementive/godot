class_name PlanetGeneration
extends Node3D

func _ready():
	var small_scale = Vector3(1300.0, 1300.0, 1300.0)
	var mid_scale = Vector3(1500.0, 1500.0, 1500.0)
	var big_scale = Vector3(2000.0, 2000.0, 2000.0)
	var massive_scale = Vector3(3500.0, 3500.0, 3500.0)
	
	var star: Node3D = generate_star(get_star_material(), get_star_material(), massive_scale)
	star.add_child(
		generate_planet(6000.0, get_lava_material(), get_lava_atmosphere_material(), small_scale)
	)
	star.add_child(
		generate_planet(11000.0, get_sand_material(), get_sand_atmosphere_material(), small_scale)
	)
	star.add_child(
		generate_planet(18500.0, get_terrestrial_material(), get_terrestrial_atmosphere_material(), mid_scale)
	)
	star.add_child(
		generate_planet_no_atmosphere(25000.0, get_no_atmosphere_material(), mid_scale)
	)
	star.add_child(
		generate_planet_no_atmosphere(31000.0, get_no_atmosphere_material(), small_scale)
	)
	star.add_child(
		generate_planet(39000.0, get_gas_material(), get_gas_atmosphere_material(), big_scale)
	)
	star.add_child(
		generate_planet_no_atmosphere(48000.0, get_ice_material(), mid_scale)
	)

func get_lava_atmosphere_material() -> ShaderMaterial:
	var shader: Shader = load("res://gfx/shaders/atmosphere.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader

	shader_mat.set_shader_parameter("color_1", Color(0.168627, 0.0627451, 0))
	shader_mat.set_shader_parameter("color_2", Color(1, 0.521569, 0.156863))
	shader_mat.set_shader_parameter("alpha", 0.3)
	shader_mat.set_shader_parameter("amount", 5.366)
	shader_mat.set_shader_parameter("intensity", 0.167)
	shader_mat.set_shader_parameter("emit", true)

	return shader_mat

func get_sand_atmosphere_material() -> ShaderMaterial:
	var shader: Shader = load("res://gfx/shaders/atmosphere.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader

	shader_mat.set_shader_parameter("color_1", Color(0.572549, 0.380392, 0.223529))
	shader_mat.set_shader_parameter("color_2", Color(0.882353, 0.670588, 0.505882))
	shader_mat.set_shader_parameter("alpha", 0.513)
	shader_mat.set_shader_parameter("amount", 4.5)
	shader_mat.set_shader_parameter("intensity", 4.0)
	shader_mat.set_shader_parameter("emit", false)

	return shader_mat
	
func get_terrestrial_atmosphere_material() -> ShaderMaterial:
	var shader: Shader = load("res://gfx/shaders/atmosphere.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader

	shader_mat.set_shader_parameter("color_1", Color(0, 0.12, 0.27))
	shader_mat.set_shader_parameter("color_2", Color(0.63, 0.78, 1))
	shader_mat.set_shader_parameter("alpha", 0.3)
	shader_mat.set_shader_parameter("amount", 4.5)
	shader_mat.set_shader_parameter("intensity", 4.0)
	shader_mat.set_shader_parameter("emit", false)

	return shader_mat
	
func get_gas_atmosphere_material() -> ShaderMaterial:
	var shader: Shader = load("res://gfx/shaders/atmosphere.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader

	shader_mat.set_shader_parameter("color_1", Color(0.4, 0.258824, 0.2))
	shader_mat.set_shader_parameter("color_2", Color(0.764706, 0.560784, 0.470588))
	shader_mat.set_shader_parameter("alpha", 0.8)
	shader_mat.set_shader_parameter("amount", 4.5)
	shader_mat.set_shader_parameter("intensity", 4.0)
	shader_mat.set_shader_parameter("emit", false)

	return shader_mat

func get_star_atmosphere_material() -> ShaderMaterial:
	var shader: Shader = load("res://gfx/shaders/atmosphere.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader

	shader_mat.set_shader_parameter("color_1", Color(0.435294, 0.129412, 0, 1))
	shader_mat.set_shader_parameter("color_2", Color(1, 0.639216, 0.25098, 1))
	shader_mat.set_shader_parameter("alpha", 0.55)
	shader_mat.set_shader_parameter("amount", 4.5)
	shader_mat.set_shader_parameter("intensity", 10.0)
	shader_mat.set_shader_parameter("emit", true)

	return shader_mat

func get_star_material() -> ShaderMaterial:
	var shader = load("res://gfx/shaders/body.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader
	
	shader_mat.set_shader_parameter("emit", 3.0)
	shader_mat.set_shader_parameter("color_1", Color(0.435294, 0.129412, 0, 1))
	shader_mat.set_shader_parameter("color_1_treshold", 0.4)
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", Color(1, 0.403922, 0, 1))
	shader_mat.set_shader_parameter("color_2_treshold", 0.5)
	shader_mat.set_shader_parameter("color_3", Color(1, 0.639216, 0.25098, 1))
	shader_mat.set_shader_parameter("color_3_treshold", 0.6)
	shader_mat.set_shader_parameter("color_4", Color(1, 0.403922, 0, 1))
	shader_mat.set_shader_parameter("color_4_treshold", 0.7)
	shader_mat.set_shader_parameter("color_5", Color(1, 0.639216, 0.25098, 1))
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", true)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.05)
	shader_mat.set_shader_parameter("noise_scale", 3.0)
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/star.tres"))
	
	return shader_mat

func get_gas_material() -> ShaderMaterial:
	var shader = load("res://gfx/shaders/body.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", Color(0.784314, 0.545098, 0.227451))
	shader_mat.set_shader_parameter("color_1_treshold", 0.422)
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", Color(0.564706, 0.380392, 0.301961))
	shader_mat.set_shader_parameter("color_2_treshold", 0.505)
	shader_mat.set_shader_parameter("color_3", Color(0.827451, 0.611765, 0.494118))
	shader_mat.set_shader_parameter("color_3_treshold", 0.529)
	shader_mat.set_shader_parameter("color_4", Color(0.654902, 0.611765, 0.52549))
	shader_mat.set_shader_parameter("color_4_treshold", 0.574)
	shader_mat.set_shader_parameter("color_5", Color(0.25098, 0.266667, 0.211765))
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", true)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", 1.425)
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_gaseous.tres"))

	return shader_mat

func get_terrestrial_material() -> ShaderMaterial:
	var shader = load("res://gfx/shaders/body.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", Color(0.17, 0.55, 1))
	shader_mat.set_shader_parameter("color_1_treshold", 0.54)
	shader_mat.set_shader_parameter("color_1_roughness", 0.1)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", Color(1, 0.94, 0.76))
	shader_mat.set_shader_parameter("color_2_treshold", 0.56)
	shader_mat.set_shader_parameter("color_3", Color(0.34, 0.74, 0.5))
	shader_mat.set_shader_parameter("color_3_treshold", 0.6)
	shader_mat.set_shader_parameter("color_4", Color(0.27, 0.62, 0.42))
	shader_mat.set_shader_parameter("color_4_treshold", 0.7)
	shader_mat.set_shader_parameter("color_5", Color(1, 1, 1, 1))
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", 1.0)
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_terrestrial.tres"))

	return shader_mat

func get_sand_material() -> ShaderMaterial:
	var shader = load("res://gfx/shaders/body.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", Color(0.984314, 0.882353, 0.733333))
	shader_mat.set_shader_parameter("color_1_treshold", 0.51)
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", Color(0.807843, 0.647059, 0.533333))
	shader_mat.set_shader_parameter("color_2_treshold", 0.659)
	shader_mat.set_shader_parameter("color_3", Color(0.572549, 0.380392, 0.223529))
	shader_mat.set_shader_parameter("color_3_treshold", 0.72)
	shader_mat.set_shader_parameter("color_4", Color(0.470588, 0.321569, 0.215686))
	shader_mat.set_shader_parameter("color_4_treshold", 0.764)
	shader_mat.set_shader_parameter("color_5", Color(0.32549, 0.266667, 0.219608))
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", 1.283)
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_sand.tres"))

	return shader_mat

func get_lava_material() -> ShaderMaterial:
	var shader = load("res://gfx/shaders/body.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", Color(1, 0.537255, 0.2))
	shader_mat.set_shader_parameter("color_1_treshold", 0.253)
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", true)
	shader_mat.set_shader_parameter("color_2", Color(0.901961, 0.270588, 0.223529))
	shader_mat.set_shader_parameter("color_2_treshold", 0.303)
	shader_mat.set_shader_parameter("color_3", Color(0.678431, 0.184314, 0.270588))
	shader_mat.set_shader_parameter("color_3_treshold", 0.402)
	shader_mat.set_shader_parameter("color_4", Color(0.321569, 0.2, 0.247059))
	shader_mat.set_shader_parameter("color_4_treshold", 0.653)
	shader_mat.set_shader_parameter("color_5", Color(0.239216, 0.160784, 0.211765))
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", 1.0)
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_lava.tres"))

	return shader_mat

func get_ice_material() -> ShaderMaterial:
	var shader = load("res://gfx/shaders/body.gdshader")
	var cloud_shader = load("res://gfx/shaders/clouds.gdshader")
	var noise_texture = load("res://gfx/noises/planet_ice.tres")
	
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	var cloud_shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader
	cloud_shader_mat.shader = cloud_shader

	cloud_shader_mat.set_shader_parameter("speed", 0.005)
	cloud_shader_mat.set_shader_parameter("brightness", 0.728)
	cloud_shader_mat.set_shader_parameter("threshold", 1.102)
	cloud_shader_mat.set_shader_parameter("fluffiness", 0.376)
	cloud_shader_mat.set_shader_parameter("noise_texture", noise_texture)

	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", Color(0.309804, 0.611765, 0.784314))
	shader_mat.set_shader_parameter("color_1_treshold", 0.287)
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", Color(0.470588, 0.678431, 0.807843))
	shader_mat.set_shader_parameter("color_2_treshold", 0.374)
	shader_mat.set_shader_parameter("color_3", Color(0.615686, 0.745098, 0.831373))
	shader_mat.set_shader_parameter("color_3_treshold", 0.472)
	shader_mat.set_shader_parameter("color_4", Color(0.92549, 0.937255, 0.972549))
	shader_mat.set_shader_parameter("color_4_treshold", 0.573)
	shader_mat.set_shader_parameter("color_5", Color(0.819608, 0.847059, 0.886275))
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", 1.0)
	shader_mat.set_shader_parameter("noise", noise_texture)
	
	shader_mat.next_pass = cloud_shader_mat
	return shader_mat

func get_no_atmosphere_material() -> ShaderMaterial:
	var shader = load("res://gfx/shaders/body.gdshader")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = shader
	
	shader_mat.set_shader_parameter("emit", randf_range(0.0, 2.0))
	shader_mat.set_shader_parameter("color_1", Color(randf_range(0.0, 0.7), randf_range(0.0, 0.7), randf_range(0.0, 0.7)))
	shader_mat.set_shader_parameter("color_1_treshold", 0.257)
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", Color(randf_range(0.0, 0.7), randf_range(0.0, 0.7), randf_range(0.0, 0.7)))
	shader_mat.set_shader_parameter("color_2_treshold", 0.332)
	shader_mat.set_shader_parameter("color_3", Color(randf_range(0.0, 0.7), randf_range(0.0, 0.7), randf_range(0.0, 0.7)))
	shader_mat.set_shader_parameter("color_3_treshold", 0.44)
	shader_mat.set_shader_parameter("color_4", Color(randf_range(0.0, 0.7), randf_range(0.0, 0.7), randf_range(0.0, 0.7)))
	shader_mat.set_shader_parameter("color_4_treshold", 0.638)
	shader_mat.set_shader_parameter("color_5", Color(randf_range(0.0, 0.7), randf_range(0.0, 0.7), randf_range(0.0, 0.7)))
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", 1.0)
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_no_atmosphere.tres"))

	return shader_mat

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
	#mesh_instance.position.x = offset
	
	static_body.add_child(mesh_instance)
	return static_body
	
func generate_planet(
	distance_from_star: float,
	shader_material: ShaderMaterial,
	atmosphere_material: ShaderMaterial,
	planet_scale: Vector3
	) -> StaticBody3D:
	var static_body: StaticBody3D = StaticBody3D.new()
	static_body.position.x = distance_from_star
	static_body.position.z = randf_range(0, 10000)
	
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	static_body.add_child(collision_shape)
	collision_shape.scale = planet_scale + Vector3(100, 100, 100)
	collision_shape.shape = SphereShape3D.new()
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
	
	mesh_instance.mesh = SphereMesh.new()
	atmosphere_mesh.mesh = SphereMesh.new()
	
	mesh_instance.mesh.set_material(shader_material)
	atmosphere_mesh.mesh.set_material(atmosphere_material)
	
	mesh_instance.scale = planet_scale
	atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
	
	mesh_instance.add_child(atmosphere_mesh)
	static_body.add_child(mesh_instance)
	return static_body

func generate_star(
	shader_material: ShaderMaterial,
	atmosphere_material: ShaderMaterial,
	star_scale: Vector3
	) -> Node3D:
	# Star generation, same as generate_planet except stars do not move through space.
	var star_node: Node3D = Node3D.new()
	var static_body: StaticBody3D = StaticBody3D.new()
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	static_body.add_child(collision_shape)
	collision_shape.scale = star_scale + Vector3(200, 200, 200)
	collision_shape.shape = SphereShape3D.new()
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
	star_node.set_script(load("res://scripts/orbit.gd"))
	
	mesh_instance.mesh = SphereMesh.new()
	atmosphere_mesh.mesh = SphereMesh.new()
	
	mesh_instance.mesh.set_material(shader_material)
	atmosphere_mesh.mesh.set_material(atmosphere_material)
	
	mesh_instance.scale = star_scale
	atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
	
	mesh_instance.add_child(atmosphere_mesh)
	static_body.add_child(mesh_instance)
	star_node.add_child(static_body)
	add_child(star_node)
	return star_node
