extends Node2D

@onready var map = %Map
@onready var label = %Label

var loader: MapLoader

func _ready() -> void:
	loader = MapLoader.new()
	loader.load_map()
	map.material.set_shader_parameter('color_texture', loader.get_color_texture())
	map.material.set_shader_parameter('lookup_texture', loader.get_lookup_texture())

func _on_control_gui_input(event):
	if event is InputEventMouseButton:
		var mouse_event = event as InputEventMouseButton
		
		if !mouse_event.is_pressed(): return

		var click_position = (mouse_event.position - map.global_position) / map.global_scale
		var state_color = loader.get_lookup_image().get_pixelv(click_position)
		var state_id  = loader.get_state_uvs().get(state_color)
		if state_id:
			label.set_text(str( state_id))
			map.material.set_shader_parameter('selected_area', state_color)
