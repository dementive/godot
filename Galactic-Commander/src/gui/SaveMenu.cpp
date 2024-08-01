#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/line_edit.hpp>

#include "Galaxy.hpp"
#include "SaveMenu.hpp"
#include "godot_cpp/classes/file_access.hpp"
#include "godot_cpp/classes/input_event_key.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/window.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;
using namespace GC;

void SaveMenu::_bind_methods() {
	ADD_GROUP("Buttons", "button_");
	ADD_GROUP("EditBoxes", "edit_");

	CALLBACKS(SaveMenu, on_save_pressed, on_load_pressed)
	BIND_WIDGETS(SaveMenu, PAIR(button_save, BaseButton), PAIR(button_load, BaseButton), PAIR(edit_name, LineEdit))
}

SaveMenu::SaveMenu() {}
SaveMenu::~SaveMenu() {}

void SaveMenu::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}

	if (p_what == NOTIFICATION_READY) {
		set_process_mode(Node::PROCESS_MODE_ALWAYS);
		CONNECT_CALLBACKS(PAIR(button_load, on_load_pressed), PAIR(button_save, on_save_pressed))
	}
}

void SaveMenu::_unhandled_input(const Ref<InputEvent> &event) {
	if (!is_visible())
		return;
	const InputEventKey *key_event = Object::cast_to<const InputEventKey>(*event);
	if (key_event and key_event->is_pressed() and key_event->get_keycode() == KEY_ESCAPE) {
		set_visible(false);
		get_tree()->set_pause(false);
	}
}

void SaveMenu::on_save_pressed() {
	LineEdit *edit_node = get_node<LineEdit>(edit_name);
	String save_file = "user://saves/" + edit_node->get_text() + ".save";

	if (!FileAccess::file_exists(save_file)) {
		UtilityFunctions::print("Creating new save file: ", save_file);
		FileAccess::open(save_file, FileAccess::WRITE);
	}
	get_tree()->get_root()->get_node<Galaxy>("Galaxy")->on_save(save_file);
	get_tree()->set_pause(false);
	queue_free(); // hmm...
}

void SaveMenu::on_load_pressed() {
	LineEdit *edit_node = get_node<LineEdit>(edit_name);
	String save_file = "user://saves/" + edit_node->get_text() + ".save";

	get_tree()->get_root()->get_node<Galaxy>("Galaxy")->on_load(save_file);
	get_tree()->set_pause(false);
	queue_free(); // hmm..
}
