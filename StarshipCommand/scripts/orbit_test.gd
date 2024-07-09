extends Node3D

@export var rotation_speed = 0.5

func _physics_process(delta):
	get_child(0).global_rotation.y = 0
	rotate_y(deg_to_rad(float(rotation_speed)))
