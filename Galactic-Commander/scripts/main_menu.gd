extends Button

func _ready():
	connect("pressed", Callable(self, "_on_button_pressed"))

func _on_button_pressed():
	var loading_screen = load("res://scenes/loading_screen.tscn")
	get_tree().change_scene_to_packed(loading_screen)
