extends StaticBody3D
class_name StellarBody

enum type {STAR, PLANET}

var orbiting_bodies : Array[StellarBody]

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
		generate_star(materials, body_scale)
		create_orbit()
	elif body_type == type.PLANET:
		generate_planet(distance_from_orbit_origin, materials, body_scale, atmosphere)

func add_body(body: StellarBody):
	add_child(body)
	orbiting_bodies.append(body)
	get_parent()

func create_orbit(orbit_size=60000.0,):
	var orbit : GCOrbit = GCOrbit.new()
	orbit.set_max_orbit_size(orbit_size)
	orbit.set_name("Orbit")
	add_child(orbit)
	
func generate_planet(
		distance_from_star: float,
		materials: Array[ShaderMaterial],
		planet_scale: Vector3,
		atmosphere: bool
	):
	self.position.x = distance_from_star
	self.position.z = randf_range(0, 10000)
	
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	self.add_child(collision_shape)
	collision_shape.scale = planet_scale + Vector3(800, 800, 800)
	collision_shape.shape = SphereShape3D.new()
	collision_shape.set_name(name + "CollisionShape")
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	mesh_instance.mesh = SphereMesh.new()
	mesh_instance.set_name(name + "Mesh")
	mesh_instance.mesh.set_material(materials[0])
	mesh_instance.scale = planet_scale
	
	if atmosphere:
		var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
		atmosphere_mesh.mesh = SphereMesh.new()
		atmosphere_mesh.set_name(name + "AtmosphereMesh")
		atmosphere_mesh.mesh.set_material(materials[1])
		atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
		mesh_instance.add_child(atmosphere_mesh)

	self.add_child(mesh_instance)

func generate_star(
	materials: Array[ShaderMaterial],
	star_scale: Vector3
	):
	# Star generation, same as generate_planet except stars do not move through space.
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	self.add_child(collision_shape)
	collision_shape.scale = star_scale + Vector3(1500, 1500, 1500)
	collision_shape.shape = SphereShape3D.new()
	collision_shape.set_name(name + "CollisionShape")
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
	
	mesh_instance.mesh = SphereMesh.new()
	atmosphere_mesh.mesh = SphereMesh.new()
	mesh_instance.set_name(name + "Mesh")
	atmosphere_mesh.set_name(name + "AtmosphereMesh")
	
	mesh_instance.mesh.set_material(materials[0])
	atmosphere_mesh.mesh.set_material(materials[1])
	
	mesh_instance.scale = star_scale
	atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
	
	mesh_instance.add_child(atmosphere_mesh)
	self.add_child(mesh_instance)
