@tool
extends Resource

class_name PlanetNoise

@export var noise_map := FastNoiseLite.new() : set = set_noise_map
@export var amplitude := 1.0 : set = set_amplitude
@export var min_height := 0.0 : set = set_min_height
@export var use_first_layer_as_mask := false : set = set_first_layer_as_mask

func set_min_height(val):
	min_height = val
	emit_signal("changed")
	
func set_first_layer_as_mask(val):
	use_first_layer_as_mask = val
	emit_signal("changed")

func set_amplitude(val):
	amplitude = val
	emit_signal("changed")
	
func set_noise_map(val):
	noise_map = val
	emit_signal("changed")
	if noise_map != null and not noise_map.is_connected("changed", Callable(self, "on_data_changed")):
		noise_map.connect("changed", Callable(self, "on_data_changed"))

func on_data_changed():
	emit_signal("changed")
