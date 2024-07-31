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
	get_child(1).set_visible(true)
	get_tree().paused = false

func _on_main_menu_button_pressed():
	visible = false
	get_child(1).set_visible(true)
	get_tree().paused = false
	get_tree().change_scene_to_file("res://scenes/gui/main_menu.tscn")

func _on_quit_game_button_pressed():
	get_tree().quit()

func _on_load_button_pressed():
	get_child(0).set_text("Save/Load")
	get_child(1).set_visible(false)
	get_child(2).set_visible(true)
	#get_tree().get_root().get_node("Galaxy").on_load("user://saves/000_1.save")

var save_file_name : String

func _on_line_edit_text_submitted(new_text):
	save_file_name = new_text

func _on_save_game_button_pressed():
	var save_file = "user://saves/" + save_file_name + ".save"
	if not FileAccess.file_exists(save_file):
		print("CREATING: ", save_file)
		FileAccess.open(save_file, FileAccess.WRITE)
	get_tree().get_root().get_node("Galaxy").on_save(save_file)
	
	get_child(0).set_text("Paused")
	get_child(1).set_visible(true)
	get_child(2).set_visible(false)


func _on_load_game_button_pressed():
	var save_file = "user://saves/" + save_file_name + ".save"
	get_tree().get_root().get_node("Galaxy").on_load(save_file)
	
	get_child(0).set_text("Paused")
	get_child(1).set_visible(true)
	get_child(2).set_visible(false)

func create_new_save_file() -> String:
	var save_files : PackedStringArray = get_save_files()
	var counter : int = 1
	var found_available_count : bool = false
	var file_name : String
	
	while found_available_count == false:
		file_name = "user://000_%s.save" % counter
		found_available_count = false if save_files.has(file_name) else true
		counter += 1

	return file_name

func open_save_dir() -> DirAccess:
	var path = "user://saves"
	if not DirAccess.dir_exists_absolute(path):
		DirAccess.make_dir_absolute(path)
	
	return DirAccess.open(path)

func get_save_files() -> PackedStringArray:
	var dir : DirAccess = open_save_dir()
	
	var files : PackedStringArray = dir.get_files()
	
	if files.size() == 0:
		return files
		
	var filtered_files : PackedStringArray = []
	
	for file in files:
		if file.ends_with(".save"):
			filtered_files.append(file)
	
	return filtered_files
