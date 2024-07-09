extends CharacterBody3D

@export var max_speed = 20.0;
@export var acceleration = 20.0;
@export var rotation_speed = PI;
@export var enable_rotation = true;
@export var enable_movement = true;

@onready var ship_body : Node3D = $ShipBody;
const BACKWARD_RATIO = 0.5;
var fast_as_fuck: bool = true

var speed = 0;
var drift_direction = Vector3.FORWARD;
	

func _process(delta):
	if enable_rotation:
		# Rotate Player
		var relative_mouse = _get_relative_mouse();
		var player_basis = transform.basis;
		player_basis = player_basis.rotated(player_basis.x, relative_mouse.y * rotation_speed * delta);
		player_basis = player_basis.rotated(player_basis.y, -relative_mouse.x * rotation_speed * delta);
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

func _move_forward(delta):
	var forward = ship_body.global_transform.basis.z.normalized();
	if Input.is_action_pressed("ui_up"):
		speed = min(speed + acceleration * delta, max_speed);
	elif Input.is_action_pressed("ui_down"):
		speed = max(speed - acceleration * delta, -max_speed * BACKWARD_RATIO);
	else:
		speed -= speed * delta;
	
	velocity = forward * speed;
	if fast_as_fuck:
		velocity *= 100.0
	move_and_slide();

# Get a vector for the mouse relative to the center of the screen
# Range(-1, 1) negative is left/top positive is right/bottom
func _get_relative_mouse() -> Vector2:
	var viewport = get_viewport();
	var mouse_position = viewport.get_mouse_position();
	var center = viewport.size / 2.0;
	var mouse_direction = mouse_position - center;
	
	var size = max(viewport.size.x, viewport.size.y);
	return mouse_direction / size;

# Created by Ryan Remer
