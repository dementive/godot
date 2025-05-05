extends Camera3D

var loader: MapLoader
@onready var map: MeshInstance3D = %MapMesh

func _ready() -> void:
	loader = MapLoader.new()
	loader.load_map()
	map.get_mesh().surface_get_material(0).set_shader_parameter('color_texture', loader.get_color_texture())
	map.get_mesh().surface_get_material(0).set_shader_parameter('lookup_texture', loader.get_lookup_texture())

func _physics_process(delta: float) -> void:
	if Input.is_action_just_pressed(&"ui_select"):
		var mouse_position := get_viewport().get_mouse_position()
		var origin = project_ray_origin(mouse_position)
		var direction = project_ray_normal(mouse_position)

		var distance: float = -origin.y/direction.y
		var xz_pos: Vector3 = origin + direction * distance
		var pos = Vector3(xz_pos.x, 1.0, xz_pos.z)
		var click_position: Vector2i = Vector2i(pos.x, pos.z)

		var state_color = loader.get_lookup_image().get_pixelv(click_position)
		var state_id  = loader.get_state_uvs().get(state_color)
		
		if state_id:
			map.get_mesh().surface_get_material(0).set_shader_parameter('selected_area', state_color.linear_to_srgb())
