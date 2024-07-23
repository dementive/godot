extends Node3D

# Define the desired location on the sphere ( longitude, latitude )
@export var longitude = 0.9  # 0 to 1, 0 = -180°, 1 = 180°
@export var latitude = 0.3  # 0 to 1, 0 = -90°, 1 = 90°

func _ready():
	var sphere_mesh = get_child(0).get_child(0)
	var building_model : MeshInstance3D = sphere_mesh.get_child(0)
	var model_scale = building_model.scale
	var sphere_radius = sphere_mesh.mesh.radius
	var sphere_size = sphere_radius * sphere_mesh.scale.x

	# Calculate the building's size using its bounding box
	var building_aabb = building_model.get_aabb()
	var building_size = building_aabb.size

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
	var tangent = Vector3(-sin(theta), 0, cos(theta)).normalized()  # Tangent vector
	var binormal = normal.cross(tangent)  # Binormal vector
	var building_basis = Basis(tangent, binormal, normal)

	# Set the building's position, rotation, and scale
	building_model.transform.origin = building_position
	building_model.transform.basis = building_basis
	building_model.scale = model_scale
	
	building_model.rotation.x = deg_to_rad(rad_to_deg(building_model.rotation.x) + 90.0)
