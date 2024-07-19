extends CharacterBody3D

@export var max_speed = 20.0;
@export var acceleration = 20.0;
@export var rotation_speed = PI;
@export var enable_rotation = true;
@export var enable_movement = true;
enum MODE {SHIP, MAP}
@export var camera_mode = MODE.SHIP

@onready var ship_body : Node3D = $ShipBody;
const BACKWARD_RATIO = 0.5;

var speed = 0;
var drift_direction = Vector3.FORWARD;

func switch_camera_mode():
	var camera = get_viewport().get_camera_3d()
	if camera_mode == MODE.MAP:
		find_child("ShipBody").set_scale(Vector3(25,25,25))
		find_child("GPUParticles").visible = false
		get_tree().get_root().get_node("GameWorld/HUD/Crosshair").visible = false
		set_rotation(Vector3(0,0,0))
		camera.set_position(Vector3(0, 6500, 0))
		camera.set_rotation_degrees(Vector3(-50, 180, 0))
	elif camera_mode == MODE.SHIP:
		find_child("ShipBody").set_scale(Vector3(1,1,1))
		find_child("GPUParticles").visible = true
		get_tree().get_root().get_node("GameWorld/HUD/Crosshair").visible = true
		camera.set_position(Vector3(0, 5.466, -24.284))
		camera.set_far(60000)
		camera.set_rotation_degrees(Vector3(0, 180, 0))

func _process(delta):
	var viewport = get_viewport()
	var mouse_position = viewport.get_mouse_position()
	var is_mouse_inside = mouse_position.x >= 0 and mouse_position.y >= 0 and mouse_position.x <= viewport.size.x and mouse_position.y <= viewport.size.y
	if !is_mouse_inside:
		return
	
	if camera_mode == MODE.SHIP:
		if enable_rotation:
			# Rotate Player
			var relative_mouse = _get_relative_mouse();
			var player_basis = transform.basis;
			player_basis = player_basis.rotated(basis.x, relative_mouse.y * rotation_speed * delta);
			player_basis = player_basis.rotated(basis.y, -relative_mouse.x * rotation_speed * delta);
			player_basis = player_basis.orthonormalized();
			transform.basis = player_basis;
			
			# Rotate Ship
			var ship_basis = Basis.IDENTITY;
			var ship_scale = ship_body.scale;
			ship_basis = ship_basis.rotated(Vector3.UP, -relative_mouse.x * rotation_speed / 2.0);
			ship_basis = ship_basis.rotated(Vector3.RIGHT, relative_mouse.y * rotation_speed);
			ship_basis = ship_basis.rotated(ship_basis.z, relative_mouse.x * rotation_speed);
			ship_basis = ship_basis.orthonormalized();
			ship_body.basis = ship_basis;
			ship_body.scale = ship_scale;
		
		if enable_movement:
			_move_forward(delta);
	
	if camera_mode == MODE.MAP:
		_move_on_map()
	
func _move_forward(delta):
	var forward = ship_body.global_transform.basis.z.normalized();
	if Input.is_action_pressed("ui_up"):
		speed = min(speed + acceleration * delta, max_speed);
	elif Input.is_action_pressed("ui_down"):
		speed = max(speed - acceleration * delta, -max_speed * BACKWARD_RATIO);
	else:
		speed -= speed * delta;
	
	velocity = forward * speed;
	
	velocity *= 150
	
	move_and_slide();
	
var right_click_pressed = false
var initial_mouse_y = 0
var rotation_sensitivity = 0.1 # Adjust this value to change rotation speed

func _move_on_map():
	var camera = get_viewport().get_camera_3d()
	var camera_position = camera.get_position()
	
	var MAP_MOVE_AMOUNT = camera_position.y / 25
	var MOUSE_MOVE_AMOUNT = 750
	
	if Input.is_action_pressed("ui_up"):
		camera_position.z += MAP_MOVE_AMOUNT
	if Input.is_action_pressed("ui_down"):
		camera_position.z -= MAP_MOVE_AMOUNT
	if Input.is_action_pressed("ui_right"):
		camera_position.x -= MAP_MOVE_AMOUNT
	if Input.is_action_pressed("ui_left"):
		camera_position.x += MAP_MOVE_AMOUNT

	var new_y_pos: float
	if Input.is_action_just_released("mouse_up"):
		new_y_pos = max(camera_position.y - MOUSE_MOVE_AMOUNT, 3150)
		camera_position.y = new_y_pos
	if Input.is_action_just_released("mouse_down"):
		new_y_pos = max(camera_position.y + MOUSE_MOVE_AMOUNT, 3150)
		camera_position.y = new_y_pos

	# TODO - Figure out how to get it to tilt like pdx camera...
	## Detect right click press and release
	#var viewport = get_viewport()
	#if Input.is_action_just_pressed("mouse_right_click"):
		#right_click_pressed = true
		#initial_mouse_y = _get_relative_mouse().y
	#elif Input.is_action_just_released("mouse_right_click"):
		#right_click_pressed = false
	#
	## Adjust camera rotation based on mouse movement while right-clicking
	#if right_click_pressed:
		#print("RIGHT CLICK PRESSED!!!")
		#var current_mouse_y = _get_relative_mouse().y
		#var delta_y = initial_mouse_y - current_mouse_y
		#camera.rotation.x += delta_y * rotation_sensitivity
		##initial_mouse_y = current_mouse_y # Update initial Y position for next frame

	camera.set_position(camera_position)




# Get a vector for the mouse relative to the center of the screen
# Range(-1, 1) negative is left/top positive is right/bottom
func _get_relative_mouse() -> Vector2:
	var viewport = get_viewport();
	var mouse_position = viewport.get_mouse_position();
	var center = viewport.size / 2.0;
	var mouse_direction = mouse_position - center;
	
	var size = max(viewport.size.x, viewport.size.y);
	return mouse_direction / size;


func _on_camera_button_pressed():
	if camera_mode == MODE.SHIP:
		camera_mode = MODE.MAP
	elif camera_mode == MODE.MAP:
		camera_mode = MODE.SHIP
	switch_camera_mode()
