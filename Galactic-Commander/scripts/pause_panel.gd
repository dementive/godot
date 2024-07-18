extends Panel

func _ready():
	set_process_mode(Node.PROCESS_MODE_ALWAYS)

func _unhandled_input(event):
	if event is InputEventKey:
		if event.pressed and event.keycode == KEY_ESCAPE:
			visible = !visible
			get_tree().paused = !get_tree().is_paused()

func _on_resume_button_pressed():
	visible = false
	get_tree().paused = false

func _on_main_menu_button_pressed():
	visible = false
	get_tree().paused = false
	get_tree().change_scene_to_file("res://scenes/main_menu.tscn")

func _on_quit_game_button_pressed():
	get_tree().quit()
