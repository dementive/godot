extends Node3D

var SolarSystem = preload("res://scripts/solar_system.gd").new()

func _ready():
	add_child(SolarSystem.generate_solar_system())
