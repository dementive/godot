extends Node3D
class_name Planet

func generate_planet_no_atmosphere(
	distance_from_star: float,
	shader_material: ShaderMaterial,
	planet_scale: Vector3
	) -> StaticBody3D:
	# Planet that does not use the atmosphere shader
	var static_body: StaticBody3D = StaticBody3D.new()
	static_body.position.x = distance_from_star
	static_body.position.z = randf_range(0, 10000)
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	static_body.add_child(collision_shape)
	collision_shape.scale = planet_scale + Vector3(100, 100, 100)
	collision_shape.shape = SphereShape3D.new()
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	
	mesh_instance.mesh = SphereMesh.new()
	mesh_instance.mesh.set_material(shader_material)
	mesh_instance.scale = planet_scale
	
	static_body.add_child(mesh_instance)
	return static_body
	
func generate_planet(
	distance_from_star: float,
	materials: Array[ShaderMaterial],
	planet_scale: Vector3
	) -> StaticBody3D:
	var static_body: StaticBody3D = StaticBody3D.new()
	static_body.position.x = distance_from_star
	static_body.position.z = randf_range(0, 10000)
	
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	static_body.add_child(collision_shape)
	collision_shape.scale = planet_scale + Vector3(800, 800, 800)
	collision_shape.shape = SphereShape3D.new()
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
	
	mesh_instance.mesh = SphereMesh.new()
	atmosphere_mesh.mesh = SphereMesh.new()
	
	mesh_instance.mesh.set_material(materials[0])
	atmosphere_mesh.mesh.set_material(materials[1])
	
	mesh_instance.scale = planet_scale
	atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
	
	mesh_instance.add_child(atmosphere_mesh)
	static_body.add_child(mesh_instance)
	return static_body

func generate_star(
	materials: Array[ShaderMaterial],
	star_scale: Vector3
	) -> Node3D:
	# Star generation, same as generate_planet except stars do not move through space.
	var star_node: Node3D = Node3D.new()
	var static_body: StaticBody3D = StaticBody3D.new()
	var collision_shape: CollisionShape3D = CollisionShape3D.new()
	static_body.add_child(collision_shape)
	collision_shape.scale = star_scale + Vector3(1500, 1500, 1500)
	collision_shape.shape = SphereShape3D.new()
	
	var mesh_instance: MeshInstance3D = MeshInstance3D.new()
	var atmosphere_mesh: MeshInstance3D = MeshInstance3D.new()
	star_node.set_script(load("res://scripts/space_gen/orbit.gd"))
	
	mesh_instance.mesh = SphereMesh.new()
	atmosphere_mesh.mesh = SphereMesh.new()
	
	mesh_instance.mesh.set_material(materials[0])
	atmosphere_mesh.mesh.set_material(materials[1])
	
	mesh_instance.scale = star_scale
	atmosphere_mesh.scale = Vector3(1.01, 1.01, 1.01)
	
	mesh_instance.add_child(atmosphere_mesh)
	static_body.add_child(mesh_instance)
	star_node.add_child(static_body)
	return star_node
