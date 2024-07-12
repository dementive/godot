@tool
extends Resource
class_name PlanetData

@export var radius := 5 : set = set_radius
@export var resolution := 25 : set = set_resolution
@export var planet_noise : Array[PlanetNoise] :
	set(val):
		planet_noise = val
		emit_changed()
		for n in planet_noise:
			if n != null and not n.is_connected("changed", on_data_changed):
				n.connect("changed", on_data_changed)

@export var biomes : Array[PlanetBiome] :
	set(val):
		biomes = val
		emit_changed()
		for i in range(biomes.size()):
			if biomes[i] == null:
				biomes[i] = PlanetBiome.new()
			if not biomes[i].is_connected("changed", on_data_changed):
				biomes[i].connect("changed", on_data_changed)

var min_height = 99999.0
var max_height = 0.0

func set_radius(val):
	radius = val
	emit_signal("changed")

func set_resolution(val):
	resolution = val
	emit_signal("changed")

func on_data_changed():
	emit_signal("changed")

func point_on_planet(point_on_sphere : Vector3) -> Vector3:
	var elevation : float = 0.0
	var base_elevation = 0.0
	if planet_noise.size() > 0:
		base_elevation = (planet_noise[0].noise_map.get_noise_3dv((point_on_sphere*100.0)))
		base_elevation = base_elevation + 1 / 2.0 * planet_noise[0].amplitude
		base_elevation = max(0.0, base_elevation - planet_noise[0].min_height)
	for n in planet_noise:
		var mask = 1.0
		if n.use_first_layer_as_mask:
			mask = base_elevation
		var level_elevation = n.noise_map.get_noise_3dv(point_on_sphere*100.0)
		level_elevation = level_elevation + 1 / 2.0 * n.amplitude
		level_elevation = max(0.0, level_elevation - n.min_height) * mask
		elevation += level_elevation
	return point_on_sphere * radius * (elevation+1.0)

func update_biome_texture() -> ImageTexture:
	var image_texture : ImageTexture
	var dynamic_image : Image
	
	var height : int = biomes.size()
	if height > 0:
		var data : PackedByteArray
		var width : int = biomes[0].gradient.width
		for b in biomes:
			data.append_array(b.gradient.get_image().get_data())
		
		dynamic_image = Image.create_from_data(width, height, false, Image.FORMAT_RGBA8, data)
		image_texture = ImageTexture.create_from_image(dynamic_image)
		image_texture.resource_name = "Biome Texture"

	return image_texture

func biome_percent_from_point(point_on_unit_sphere : Vector3) -> float:
	var height_percent : float = (point_on_unit_sphere.y + 1.0) / 2.0
	var biome_index : float = 0.0
	var num_biome : float = biomes.size()
	for i in range(num_biome):
		if biomes[i].start_height < height_percent:
			biome_index = i
		else:
			break
		
	return biome_index / max(1.0, num_biome - 1.0)
