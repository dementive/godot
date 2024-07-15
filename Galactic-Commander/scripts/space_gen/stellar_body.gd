extends StaticBody3D
class_name StellarBody

enum type {STAR, PLANET}
var planet_collision_size = 800.0
var orbiting_bodies : Array[StellarBody]
@onready var info_panel = get_tree().root.get_node("GameWorld").get_node("HUD").get_node("PlanetInfoPanel")

func _init(
		body_type: type,
		distance_from_orbit_origin: float,
		materials: Array[ShaderMaterial],
		body_scale: Vector3,
		body_name: String,
		atmosphere=true
	):
	set_name(body_name)
	if body_type == type.STAR:
		planet_collision_size = 1500.0
		generate_body(distance_from_orbit_origin, materials, body_scale, atmosphere)
		create_orbit()
	elif body_type == type.PLANET:
		generate_body(distance_from_orbit_origin, materials, body_scale, atmosphere)

func _input_event(camera: Camera3D, event: InputEvent, position: Vector3, normal: Vector3, shape_idx: int):
	if event is InputEventMouseButton and event.pressed:
		if event.button_index == MOUSE_BUTTON_LEFT:
			on_click()

func on_click():
	info_panel.visible = true
	var label : Label = info_panel.get_node("PlanetNameLabel")
	label.set_text(get_name())
	
func _mouse_exit():
	info_panel.visible = false

func add_body(body: StellarBody):
	add_child(body)
	orbiting_bodies.append(body)
	get_parent()

func create_orbit(orbit_size=60000.0):
	var orbit : GCOrbit = GCOrbit.new()
	orbit.set_max_orbit_size(orbit_size)
	orbit.set_name("Orbit")
	add_child(orbit)

func generate_body(
		distance_from_star: float,
		materials: Array[ShaderMaterial],
		planet_scale: Vector3,
		has_atmosphere: bool
	):
	if distance_from_star > 0:
		self.position.x = distance_from_star
		self.position.z = randf_range(0, 10000)

	var sphere_shape = SphereShape3D.new()
	sphere_shape.radius = (max(planet_scale.x, planet_scale.y, planet_scale.z) / 2) + planet_collision_size
	self.shape_owner_add_shape(self.create_shape_owner(self), sphere_shape)
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	mesh_instance.mesh = SphereMesh.new()
	mesh_instance.set_name(name + "Mesh")
	mesh_instance.mesh.set_material(materials[0])
	mesh_instance.scale = planet_scale
	
	if has_atmosphere:
		var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
		atmosphere_mesh.mesh = SphereMesh.new()
		atmosphere_mesh.set_name(name + "AtmosphereMesh")
		atmosphere_mesh.mesh.set_material(materials[1])
		atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
		mesh_instance.add_child(atmosphere_mesh)

	self.add_child(mesh_instance)
