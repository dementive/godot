extends Node2D

@onready var mapImage = $MapTexture

# Called when the node enters the scene tree for the first time.
func _ready():
	load_regions()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func load_regions():
	var image = mapImage.get_texture().get_image()
	var pixel_colors = get_pixel_colors(image)
	var regions = import_file("res://map_data/regions.json")
	print(regions)
	for color in regions:
		var region = load("res://Scenes/region.tscn").instantiate()
		region.region_name = regions[color]
		region.set_name(color)
		get_node("Regions").add_child(region)
		
		var polygons = get_polygons(image, color, pixel_colors)
		
		for polygon in polygons:
			var region_collision = CollisionPolygon2D.new()
			var region_polygon = Polygon2D.new()
			
			region_collision.polygon = polygon
			region_polygon.polygon = polygon

			region.add_child(region_collision)
			region.add_child(region_polygon)
		
func get_pixel_colors(image):
	var pixel_colors = {}
	for y in range(image.get_height()):
		for x in range(image.get_width()):
			var pixel_color = "#" + str(image.get_pixel(int(x), int(y)).to_html(false))
			if pixel_color not in pixel_colors:
				pixel_colors[pixel_color] = []
			pixel_colors[pixel_color].append(Vector2(x,y))

	return pixel_colors

func get_polygons(image, color, pixel_colors):
	var target_image = Image.create(image.get_size().x, image.get_size().y, false, Image.FORMAT_RGBA8)
	for value in pixel_colors[color]:
		target_image.set_pixel(value.x, value.y, "#ffffff")
	
	var bitmap = BitMap.new()
	bitmap.create_from_image_alpha(target_image)
	var polygons = bitmap.opaque_to_polygons(Rect2(Vector2(0,0), bitmap.get_size()), 0.1)
	return polygons

func import_file(filepath):
	var file = FileAccess.open(filepath, FileAccess.READ)
	if file != null:
		return JSON.parse_string(file.get_as_text().replace("_", " "))
	else:
		print("Failed to open file: ", filepath)
		return null
