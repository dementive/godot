extends Node3D

var SolarSystem = preload("res://scripts/space_gen/solar_system.gd").new()

func _ready():
	add_child(SolarSystem.generate_solar_system())
