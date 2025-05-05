extends Node2D

# TODO this should be the lookup texture NOT the province texture.
@export var voronoi_texture: Texture2D

func _ready():
	generate_borders()

func generate_borders():
	var image: Image = voronoi_texture.get_image()
	
	var width: int = image.get_width()
	var height: int = image.get_height()
	
	# Dictionary to collect border line segments by province pairs
	# Key: PackedColorArray (color1, color2) sorted by color
	# Value: Array of Vector2 pairs (start and end of edges)
	var borders = {}
	# Scan pixels comparing right and bottom neighbors to get edges
	for y in range(height):
		for x in range(width):
			var current_color: Color = image.get_pixel(x, y)
			
			# Compare right neighbor if exists
			if x + 1 < width:
				var right_color: Color = image.get_pixel(x + 1, y)
				if current_color != right_color:
					var key: PackedColorArray = [current_color, right_color]
					key.sort() # sort to prevent duplicates, I guess
					if not borders.has(key):
						borders[key] = Array()
					# Edge at vertical boundary between (x+1,y) and (x,y)
					# Border line segment coordinates are pixel edges, from (x+1,y) to (x+1,y+1)
					# Let's represent edges in image pixel space as Vector2 points (adjust as needed)
					# For vertical edge between pixels, line is from (x+1,y) to (x+1,y+1)
					borders[key].append([Vector2(x + 1, y), Vector2(x + 1, y + 1)])

			# Compare bottom neighbor if exists
			if y + 1 < height:
				var bottom_color: Color = image.get_pixel(x, y + 1)
				if current_color != bottom_color:
					var key: PackedColorArray = [current_color, bottom_color]
					key.sort()
					if not borders.has(key):
						borders[key] = Array()
					# Edge at horizontal boundary between (x,y+1) and (x,y)
					# Border line segment from (x, y+1) to (x+1, y+1)
					borders[key].append([Vector2(x, y + 1), Vector2(x + 1, y + 1)])
	
	# For each border between province pairs, create one mesh with all line segments
	for border_pair in borders.keys():
		var line_segments: Array = borders[border_pair]
		
		#var line_mesh: Mesh = create_mesh_from_segments(line_segments)
		var line_mesh: Mesh = create_mesh_with_width_from_segments(line_segments, 2.5)
		var border_mesh_instance: MeshInstance2D = MeshInstance2D.new()
		border_mesh_instance.mesh = line_mesh
		
		# Determine province colors from key string
		#var c1 = Color(border_pair[0])
		#var c2 = Color(border_pair[1])
		
		# Get correct material based on the kind of border it is
		# var material = determine_material(c1, c2)
		# if material:
		#     border_mesh_instance.material_override = material
		
		%Map.call_deferred(&"add_child", border_mesh_instance)

# Creates a single mesh from multiple line segments
func create_mesh_from_segments(segments: Array) -> Mesh:
	var st: SurfaceTool = SurfaceTool.new()
	st.begin(Mesh.PRIMITIVE_LINES)
	for seg in segments:
		st.add_vertex(Vector3(seg[0].x, seg[0].y, 0))
		st.add_vertex(Vector3(seg[1].x, seg[1].y, 0))
	return st.commit()

func create_mesh_with_width_from_segments(segments: Array, width: float) -> Mesh:
	var st = SurfaceTool.new()
	st.begin(Mesh.PRIMITIVE_TRIANGLES)
	
	var half_w = width * 0.5
	
	for seg in segments:
		var start = seg[0]
		var end = seg[1]
		var dir = (end - start).normalized()
		var perp = Vector2(-dir.y, dir.x)
		
		var v0 = start + perp * half_w
		var v1 = start - perp * half_w
		var v2 = end - perp * half_w
		var v3 = end + perp * half_w
		
		# Triangle 1
		st.add_vertex(Vector3(v0.x, v0.y, 0))
		st.add_vertex(Vector3(v1.x, v1.y, 0))
		st.add_vertex(Vector3(v2.x, v2.y, 0))
		
		# Triangle 2
		st.add_vertex(Vector3(v2.x, v2.y, 0))
		st.add_vertex(Vector3(v3.x, v3.y, 0))
		st.add_vertex(Vector3(v0.x, v0.y, 0))
	
	return st.commit()
