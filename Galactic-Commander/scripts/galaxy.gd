extends Node
class_name Galaxy

var solar_system : SolarSystem = SolarSystem.new("SolarSystem")

func _ready():
	add_child(solar_system)
