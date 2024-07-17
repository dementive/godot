extends Node
class_name Galaxy

func _ready():
	var solar_system : SolarSystem = SolarSystem.new()
	solar_system.generate_solar_system()
	add_child(solar_system)
