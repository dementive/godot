extends Node3D

# Define the desired location on the sphere ( longitude, latitude )
@export var longitude = 0.4  # 0 to 1, 0 = -180°, 1 = 180°
@export var latitude = 0.9  # 0 to 1, 0 = -90°, 1 = 90°

func _ready():
	var sphere_mesh = get_child(0).get_child(0)
	var building_model : MeshInstance3D = sphere_mesh.get_child(0)
	var model_scale = building_model.scale
	var sphere_radius = sphere_mesh.mesh.radius

	# Calculate the position on the sphere's surface
	var theta = longitude * 2 * PI - PI
	var phi = latitude * PI - PI / 2
	var building_position = Vector3(
		sphere_radius * sin(phi) * cos(theta),
		sphere_radius * cos(phi),
		sphere_radius * sin(phi) * sin(theta)
	)

	# Calculate the rotation to align the building with the sphere's surface
	var normal = building_position.normalized()
	var tangent = Vector3(-sin(theta), 0, cos(theta)).normalized()
	var binormal = normal.cross(tangent)
	var building_basis = Basis(tangent, binormal, normal)

	# Set the building's position, rotation, and scale
	building_model.transform.origin = building_position
	building_model.transform.basis = building_basis
	building_model.scale = model_scale
	
	# No idea why I have to do this but without it the rotation is broken...
	var adjustment = 0
	if latitude > 0.5:
		adjustment = -90.0
	else:
		adjustment = 90.0
	
	building_model.rotation.x = deg_to_rad(rad_to_deg(building_model.rotation.x) + adjustment)
