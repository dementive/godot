@tool
extends Resource
class_name PlanetData

@export var radius := 5 : set = set_radius
@export var resolution := 25 : set = set_resolution
@export var noise_map := FastNoiseLite.new() : set = set_noise_map
@export var amplitude := 1.0 : set = set_amplitude
@export var min_height := 0.0 : set = set_min_height

func set_min_height(val):
	min_height = val
	emit_signal("changed")

func set_radius(val):
	radius = val
	emit_signal("changed")

func set_resolution(val):
	resolution = val
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

func point_on_planet(point_on_sphere : Vector3) -> Vector3:
	var elevation = noise_map.get_noise_3dv(point_on_sphere)
	elevation = elevation + 1 / 2.0 * amplitude
	elevation = max(0.0, elevation - min_height)
	return point_on_sphere * radius * (elevation+1.0)
