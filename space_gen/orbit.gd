# Node to attach to the object in a solar system
# Makes it so all it's children that are StaticBody3D's can orbit this node.

extends Node3D
class_name GDOrbit

var MAX_ORBIT_SIZE = 60000.0

func lerp(a, b, t):
	return (1 - t) * a + t * b

func _physics_process(_delta):
	var parent = get_parent()
	if not parent is StellarBody:
		return

	for child in parent.orbiting_bodies:
		var normalized_distance = clamp(child.position.x / MAX_ORBIT_SIZE, 0.0, 1.0)
		var rotation_speed = lerp(0.00001, 0.003, normalized_distance)
		parent.rotate_y(deg_to_rad(float(rotation_speed)))
