# Attach this script to the star in a solar system so all it's children can orbit it.

extends Node3D

func lerp(a, b, t):
	return (1 - t) * a + t * b

func _physics_process(delta):
	for child in get_children():
		if not child is StaticBody3D:
			continue
		child.global_rotation.y = 0
		var normalized_distance = clamp(child.position.x / 8000.0, 0.0, 1.0)
		var rotation_speed = lerp(0.0001, 0.02, normalized_distance)
		rotate_y(deg_to_rad(float(rotation_speed)))
