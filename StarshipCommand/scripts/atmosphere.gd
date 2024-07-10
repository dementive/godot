extends MeshInstance3D

# Define the maximum distance at which the object should be rendered
const MAX_RENDER_DISTANCE = 3000.0

func _process(delta):
	var camera: Camera3D = get_viewport().get_camera_3d()
	if camera == null:
		return
	
	# Calculate the distance between the camera and this object
	var distance = camera.global_transform.origin.distance_to(global_transform.origin)
	
	#print(distance)
	# Check if the object is within the render distance
	if distance <= MAX_RENDER_DISTANCE:
		print("OBJECT IN RENDER DISTANCE!!!")
		visible = true
	else:
		visible = false
