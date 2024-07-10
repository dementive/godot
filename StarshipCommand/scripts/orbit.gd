# Script to attach to the star in a solar system so all it's children can orbit it.

extends Node3D

const SOLAR_SYSTEM_MAX_SIZE = 50000.0

func lerp(a, b, t):
	return (1 - t) * a + t * b

func _physics_process(_delta):
	for child in get_children():
		if not child is StaticBody3D:
			continue
		child.global_rotation.y = 0
		var normalized_distance = clamp(child.position.x / SOLAR_SYSTEM_MAX_SIZE, 0.0, 1.0)
		var rotation_speed = lerp(0.00001, 0.003, normalized_distance)
		rotate_y(deg_to_rad(float(rotation_speed)))
