extends Object

var body_shader: Shader = load("res://gfx/shaders/body.gdshader")
var atmosphere_shader: Shader = load("res://gfx/shaders/atmosphere.gdshader")
var cloud_shader = load("res://gfx/shaders/clouds.gdshader")

func get_star_material(color: PackedColorArray) -> Array[ShaderMaterial]:
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	var atmosphere_shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = body_shader
	atmosphere_shader_mat.shader = atmosphere_shader
	
	shader_mat.set_shader_parameter("emit", 3.0)
	shader_mat.set_shader_parameter("color_1", color[0])
	shader_mat.set_shader_parameter("color_1_treshold", 0.4)
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", color[1])
	shader_mat.set_shader_parameter("color_2_treshold", 0.5)
	shader_mat.set_shader_parameter("color_3", color[2])
	shader_mat.set_shader_parameter("color_3_treshold", 0.6)
	shader_mat.set_shader_parameter("color_4", color[3])
	shader_mat.set_shader_parameter("color_4_treshold", 0.7)
	shader_mat.set_shader_parameter("color_5", color[4])
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", true)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.05)
	shader_mat.set_shader_parameter("noise_scale", 3.0)
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/star.tres"))
	
	atmosphere_shader_mat.set_shader_parameter("color_1", color[5])
	atmosphere_shader_mat.set_shader_parameter("color_2", color[6])
	atmosphere_shader_mat.set_shader_parameter("alpha", 0.55)
	atmosphere_shader_mat.set_shader_parameter("amount", 4.5)
	atmosphere_shader_mat.set_shader_parameter("intensity", 10.0)
	atmosphere_shader_mat.set_shader_parameter("emit", true)
	
	return [shader_mat, atmosphere_shader_mat]

func get_gas_material(color: PackedColorArray) -> Array[ShaderMaterial]:
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	var atmosphere_shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = body_shader
	atmosphere_shader_mat.shader = atmosphere_shader
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", color[0])
	shader_mat.set_shader_parameter("color_1_treshold", 0.422)
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", color[1])
	shader_mat.set_shader_parameter("color_2_treshold", 0.505)
	shader_mat.set_shader_parameter("color_3", color[2])
	shader_mat.set_shader_parameter("color_3_treshold", 0.529)
	shader_mat.set_shader_parameter("color_4", color[3])
	shader_mat.set_shader_parameter("color_4_treshold", 0.574)
	shader_mat.set_shader_parameter("color_5", color[4])
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", true)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", 1.425)
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_gaseous.tres"))

	atmosphere_shader_mat.set_shader_parameter("color_1", color[5])
	atmosphere_shader_mat.set_shader_parameter("color_2", color[6])
	atmosphere_shader_mat.set_shader_parameter("alpha", 0.8)
	atmosphere_shader_mat.set_shader_parameter("amount", 4.5)
	atmosphere_shader_mat.set_shader_parameter("intensity", 4.0)
	atmosphere_shader_mat.set_shader_parameter("emit", false)

	return [shader_mat, atmosphere_shader_mat]

func get_terrestrial_material(color: PackedColorArray) -> Array[ShaderMaterial]:
	var noise_texture = load("res://gfx/noises/planet_terrestrial.tres")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	var cloud_shader_mat: ShaderMaterial = ShaderMaterial.new()
	var atmosphere_shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = body_shader
	cloud_shader_mat.shader = cloud_shader
	atmosphere_shader_mat.shader = atmosphere_shader

	cloud_shader_mat.set_shader_parameter("speed", 0.005)
	cloud_shader_mat.set_shader_parameter("brightness", 0.728)
	cloud_shader_mat.set_shader_parameter("threshold", 1.102)
	cloud_shader_mat.set_shader_parameter("fluffiness", 0.376)
	cloud_shader_mat.set_shader_parameter("noise_texture", noise_texture)
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", color[0])
	shader_mat.set_shader_parameter("color_1_treshold", randf_range(0.51, 0.59))
	shader_mat.set_shader_parameter("color_1_roughness", 0.1)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", color[1])
	shader_mat.set_shader_parameter("color_2_treshold", 0.56)
	shader_mat.set_shader_parameter("color_3", color[2])
	shader_mat.set_shader_parameter("color_3_treshold", 0.6)
	shader_mat.set_shader_parameter("color_4", color[3])
	shader_mat.set_shader_parameter("color_4_treshold", 0.7)
	shader_mat.set_shader_parameter("color_5", color[4])
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", randf_range(1.0, 1.75))
	shader_mat.set_shader_parameter("noise", noise_texture)

	atmosphere_shader_mat.set_shader_parameter("color_1", color[5])
	atmosphere_shader_mat.set_shader_parameter("color_2", color[6])
	atmosphere_shader_mat.set_shader_parameter("alpha", 0.3)
	atmosphere_shader_mat.set_shader_parameter("amount", 4.5)
	atmosphere_shader_mat.set_shader_parameter("intensity", 4.0)
	atmosphere_shader_mat.set_shader_parameter("emit", false)

	shader_mat.next_pass = cloud_shader_mat
	return [shader_mat, atmosphere_shader_mat]

func get_sand_material(color: PackedColorArray) -> Array[ShaderMaterial]:
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	var atmosphere_shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = body_shader
	atmosphere_shader_mat.shader = atmosphere_shader
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", color[0])
	shader_mat.set_shader_parameter("color_1_treshold", randf_range(0.425, 0.51))
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", color[1])
	shader_mat.set_shader_parameter("color_2_treshold", randf_range(0.57, 0.659))
	shader_mat.set_shader_parameter("color_3", color[2])
	shader_mat.set_shader_parameter("color_3_treshold", randf_range(0.69, 0.72))
	shader_mat.set_shader_parameter("color_4", color[3])
	shader_mat.set_shader_parameter("color_4_treshold", 0.764)
	shader_mat.set_shader_parameter("color_5", color[4])
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", randf_range(1.283, 1.8))
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_sand.tres"))
	
	atmosphere_shader_mat.set_shader_parameter("color_1", color[5])
	atmosphere_shader_mat.set_shader_parameter("color_2", color[6])
	atmosphere_shader_mat.set_shader_parameter("alpha", 0.513)
	atmosphere_shader_mat.set_shader_parameter("amount", 4.5)
	atmosphere_shader_mat.set_shader_parameter("intensity", 4.0)
	atmosphere_shader_mat.set_shader_parameter("emit", false)

	return [shader_mat, atmosphere_shader_mat]

func get_lava_material(color: PackedColorArray) -> Array[ShaderMaterial]:
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	var atmosphere_shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = body_shader
	atmosphere_shader_mat.shader = atmosphere_shader
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", color[0])
	shader_mat.set_shader_parameter("color_1_treshold", randf_range(0.253, 0.3))
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", true)
	shader_mat.set_shader_parameter("color_2", color[1])
	shader_mat.set_shader_parameter("color_2_treshold", randf_range(0.3, 0.4))
	shader_mat.set_shader_parameter("color_3", color[2])
	shader_mat.set_shader_parameter("color_3_treshold", 0.402)
	shader_mat.set_shader_parameter("color_4", color[3])
	shader_mat.set_shader_parameter("color_4_treshold", randf_range(0.525, 0.653))
	shader_mat.set_shader_parameter("color_5", color[4])
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", randf_range(1.0, 1.75))
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_lava.tres"))

	atmosphere_shader_mat.set_shader_parameter("color_1", color[5])
	atmosphere_shader_mat.set_shader_parameter("color_2", color[6])
	atmosphere_shader_mat.set_shader_parameter("alpha", 0.3)
	atmosphere_shader_mat.set_shader_parameter("amount", 5.366)
	atmosphere_shader_mat.set_shader_parameter("intensity", 0.167)
	atmosphere_shader_mat.set_shader_parameter("emit", true)

	return [shader_mat, atmosphere_shader_mat]

func get_ice_material(color: PackedColorArray) -> Array[ShaderMaterial]:
	var noise_texture = load("res://gfx/noises/planet_ice.tres")
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	var cloud_shader_mat: ShaderMaterial = ShaderMaterial.new()
	var atmosphere_shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = body_shader
	cloud_shader_mat.shader = cloud_shader
	atmosphere_shader_mat.shader = atmosphere_shader

	cloud_shader_mat.set_shader_parameter("speed", 0.005)
	cloud_shader_mat.set_shader_parameter("brightness", 0.728)
	cloud_shader_mat.set_shader_parameter("threshold", 1.102)
	cloud_shader_mat.set_shader_parameter("fluffiness", 0.376)
	cloud_shader_mat.set_shader_parameter("noise_texture", noise_texture)

	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", color[0])
	shader_mat.set_shader_parameter("color_1_treshold", randf_range(0.287, 0.5))
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", color[1])
	shader_mat.set_shader_parameter("color_2_treshold", randf_range(0.374, 0.45))
	shader_mat.set_shader_parameter("color_3", color[2])
	shader_mat.set_shader_parameter("color_3_treshold", randf_range(0.425, 0.525))
	shader_mat.set_shader_parameter("color_4", color[3])
	shader_mat.set_shader_parameter("color_4_treshold", randf_range(0.553, 0.583))
	shader_mat.set_shader_parameter("color_5", color[4])
	shader_mat.set_shader_parameter("color_5_treshold", randf_range(0.6, 1.0))
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", randf_range(1.0, 2.3))
	shader_mat.set_shader_parameter("noise", noise_texture)
	
	atmosphere_shader_mat.set_shader_parameter("color_1", color[5])
	atmosphere_shader_mat.set_shader_parameter("color_2", color[6])
	atmosphere_shader_mat.set_shader_parameter("alpha", 0.5)
	atmosphere_shader_mat.set_shader_parameter("amount", 4.5)
	atmosphere_shader_mat.set_shader_parameter("intensity", 4.0)
	atmosphere_shader_mat.set_shader_parameter("emit", true)
	
	shader_mat.next_pass = cloud_shader_mat
	return [shader_mat, atmosphere_shader_mat]

func get_no_atmosphere_material(color: PackedColorArray) -> ShaderMaterial:
	var shader_mat: ShaderMaterial = ShaderMaterial.new()
	shader_mat.shader = body_shader
	
	shader_mat.set_shader_parameter("emit", 0.0)
	shader_mat.set_shader_parameter("color_1", color[0])
	shader_mat.set_shader_parameter("color_1_treshold", randf_range(0.25, 0.42))
	shader_mat.set_shader_parameter("color_1_roughness", 0.0)
	shader_mat.set_shader_parameter("color_1_emit", false)
	shader_mat.set_shader_parameter("color_2", color[1])
	shader_mat.set_shader_parameter("color_2_treshold", randf_range(0.33, 1.0))
	shader_mat.set_shader_parameter("color_3", color[2])
	shader_mat.set_shader_parameter("color_3_treshold", 0.44)
	shader_mat.set_shader_parameter("color_4", color[3])
	shader_mat.set_shader_parameter("color_4_treshold", randf_range(0.3, 0.5))
	shader_mat.set_shader_parameter("color_5", color[4])
	shader_mat.set_shader_parameter("color_5_treshold", 1.0)
	shader_mat.set_shader_parameter("noise_gaseous", false)
	shader_mat.set_shader_parameter("noise_gaseous_speed", 0.0025)
	shader_mat.set_shader_parameter("noise_scale", randf_range(1.0, 2.3))
	shader_mat.set_shader_parameter("noise", load("res://gfx/noises/planet_no_atmosphere.tres"))

	return shader_mat
