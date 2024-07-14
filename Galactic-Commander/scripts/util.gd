
static func get_sphere_volume(r: float) -> float:
	return PI * r * r * r * 4.0 / 3.0


static func find_node_by_type(parent: Node, klass):
	for i in parent.get_child_count():
		var child = parent.get_child(i)
		if is_instance_of(child, klass):
			return child
		var res = find_node_by_type(child, klass)
		if res != null:
			return res
	return null


static func find_parent_by_type(node: Node, klass):
	while node.get_parent() != null:
		node = node.get_parent()
		if is_instance_of(node, klass):
			return node
	return null


static func format_integer_with_commas(n: int) -> String:
	if n < 0:
		return "-" + format_integer_with_commas(-n)
	if n < 1000:
		return str(n)
	if n < 1000000:
		return str(n / 1000, ",", str(n % 1000).pad_zeros(3))
	if n < 10000000000:
		return str(n / 1000000, ",", 
			str((n / 1000) % 10000000).pad_zeros(3), ",", 
			str(n % 1000).pad_zeros(3))
	push_error("Number too big for shitty function")
	assert(false)
	return "<error>"


static func ray_intersects_sphere(
	ray_origin: Vector3, ray_dir: Vector3, center: Vector3, radius: float) -> bool:
	
	var t := (center - ray_origin).dot(ray_dir)
	if t < 0.0:
		return false
	var p := ray_origin + ray_dir * t
	var y := (center - p).length()
	return y <= radius
