extends Object
class_name MapLoader

const DIM = 255
var state_uvs : Dictionary
var owned_arr: PackedColorArray
var look_up_image : Image

# Load provinces.png and states data and then create a lookup image from the data
func load_map() -> void:
	var states: Dictionary = {}
	
	var config: ConfigFile = ConfigFile.new()
	if config.load("res://Assets/states_cache.cfg") != OK: return

	for section in config.get_sections():
		var map_color: Color = config.get_value(section, "color", Color(0,0,0))
		map_color = Color8(int(map_color.r), int(map_color.g), int(map_color.b))
		var owner_color: Color = config.get_value(section, "owner_color", Color(0,0,0))
		owner_color = Color8(int(owner_color.r), int(owner_color.g), int(owner_color.b))

		var province_id = section.to_int()
		states[map_color] = province_id
		
		owned_arr.push_back(owner_color)
		var color := Color(
			float(int(province_id) % DIM) / (DIM - 1),
			floor(float(province_id) / DIM) / (DIM - 1),
			0.0
		)
		state_uvs[color] =  province_id
	
	#Load provinces.png
	var province_image := preload("res://Assets/provinces.png").get_image()
	var image_dimensions: Vector2i = province_image.get_size()

	# Create lookup texture
	look_up_image = Image.create_empty(province_image.get_width(), province_image.get_height(), false, Image.FORMAT_RGF);

	for x in range(image_dimensions.x):
		for y in range(image_dimensions.y):
			var province_id = states[province_image.get_pixel(x, y)];
			var color = Color(
				(float(province_id % DIM)/ (DIM - 1)),
				(floor(float(province_id)/DIM) / (DIM - 1)),
				0.0
			);
			look_up_image.set_pixel(x, y, color);

	#look_up_image.save_exr("res://Assets/lookup.exr")

# Get the color texture used for 'map modes'
func get_color_texture() -> ImageTexture:
	var owner_map : Image = Image.create_empty(
		DIM,
		DIM,
		false,
		Image.FORMAT_RGBAF
	)
	for province_id in range(state_uvs.size()):
		var uv = Vector2(float(int(province_id) % DIM), floor(float(province_id) / DIM))
		owner_map.set_pixel(uv.x, uv.y, owned_arr[province_id])

	return ImageTexture.create_from_image(owner_map)

func get_lookup_texture() -> ImageTexture:
	return ImageTexture.create_from_image(look_up_image)

func get_lookup_image() -> Image:
	return look_up_image

func get_state_uvs() -> Dictionary:
	return state_uvs
