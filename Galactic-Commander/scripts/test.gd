extends Node3D
#
#func _ready():
	#var sphere_mesh = get_child(0).get_child(0)
	#var building_model = sphere_mesh.get_child(0).get_child(0).get_child(0)
	#var sphere_radius = sphere_mesh.mesh.radius
	#var sphere_size = sphere_radius * sphere_mesh.scale.x
#
	## Calculate the building's size using its bounding box
	#var building_aabb = building_model.get_aabb()
	#var building_size = building_aabb.size
#
	## Define the desired location on the sphere ( longitude, latitude )
	#var longitude = 0.5  # 0 to 1, 0 = -180°, 1 = 180°
	#var latitude = 0.3  # 0 to 1, 0 = -90°, 1 = 90°
#
	## Calculate the position on the sphere's surface
	#var theta = longitude * 2 * PI - PI
	#var phi = latitude * PI - PI / 2
	#var building_position = Vector3(
		#sphere_radius * sin(phi) * cos(theta),
		#sphere_radius * cos(phi) - building_size.y / 2,
		#sphere_radius * sin(phi) * sin(theta)
	#)
#
	## Calculate the rotation to align the building with the sphere's surface
	#var normal = building_position.normalized()
	#var up_vector = Vector3(0, 1, 0)
	#var rotation_axis = normal.cross(up_vector)
	#var rotation_angle = acos(normal.dot(up_vector))
	#var building_rotation = Quaternion(rotation_axis, rotation_angle)
#
	## Convert the Quaternion to a Basis
	#var building_basis = Basis(building_rotation)
#
	## Set the building's position and rotation
	#building_model.transform.origin = building_position
	#building_model.transform.basis = building_basis
