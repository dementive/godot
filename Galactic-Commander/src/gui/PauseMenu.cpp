#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "PauseMenu.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "gui/SaveMenu.hpp"

using namespace godot;
using namespace GC;

void PauseMenu::_bind_methods() {
	CALLBACKS(PauseMenu, _on_resume_button_pressed, _on_main_menu_button_pressed, _on_quit_game_button_pressed, _on_load_button_pressed)
	// BIND_CALLBACK(PauseMenu, _on_resume_button_pressed)
	// BIND_CALLBACK(PauseMenu, _on_main_menu_button_pressed)
	// BIND_CALLBACK(PauseMenu, _on_quit_game_button_pressed)
	// BIND_CALLBACK(PauseMenu, _on_load_button_pressed)

	ADD_GROUP("Buttons", "button_");
	//BIND_NODE_PATH_PROPERTY(button_resume, PauseMenu, BaseButton)
	//BIND_NODE_PATH_PROPERTY(button_main_menu, PauseMenu, BaseButton)
	//BIND_NODE_PATH_PROPERTY(button_quit, PauseMenu, BaseButton)
	//BIND_NODE_PATH_PROPERTY(button_load, PauseMenu, BaseButton)

	//BIND_WIDGETS(PauseMenu, button_load, BaseButton, button_quit, BaseButton, button_main_menu, BaseButton, button_resume, BaseButton)

	BIND_WIDGETS(PauseMenu, PAIR(button_load, BaseButton), PAIR(button_quit, BaseButton), PAIR(button_main_menu, BaseButton),
			PAIR(button_resume, BaseButton))
}

PauseMenu::PauseMenu() {}
PauseMenu::~PauseMenu() {}

void PauseMenu::resume() {
	set_visible(false);
	get_tree()->set_pause(false);
}

void PauseMenu::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::PROCESS_MODE_ALWAYS);

		CONNECT_CALLBACKS(PAIR(button_resume, _on_resume_button_pressed), PAIR(button_main_menu, _on_main_menu_button_pressed),
				PAIR(button_quit, _on_quit_game_button_pressed), PAIR(button_load, _on_load_button_pressed))
		//CONNECT_CALLBACK(button_resume, _on_resume_button_pressed)
		// CONNECT_CALLBACK(button_main_menu, _on_main_menu_button_pressed)
		// CONNECT_CALLBACK(button_quit, _on_quit_game_button_pressed)
		//CONNECT_CALLBACK(button_load, _on_load_button_pressed)
	} else {
		// CHECK_GUI_NODE(button_load)
		CHECK_WIDGETS(button_resume, button_main_menu, button_quit, button_load)
	}
}

void PauseMenu::_unhandled_input(const Ref<InputEvent> &event) {
	const InputEventKey *key_event = Object::cast_to<const InputEventKey>(*event);
	if (key_event and key_event->is_pressed() and key_event->get_keycode() == KEY_ESCAPE) {
		if (is_visible()) {
			resume();
		} else {
			set_visible(!is_visible());
			get_tree()->set_pause(!get_tree()->is_paused());
		}
	}
}

void PauseMenu::_on_resume_button_pressed() { resume(); }

void PauseMenu::_on_main_menu_button_pressed() {
	resume();
	get_tree()->change_scene_to_file("res://scenes/gui/main_menu.tscn");
}

void PauseMenu::_on_quit_game_button_pressed() { get_tree()->quit(); }

void PauseMenu::_on_load_button_pressed() {
	Ref<PackedScene> ref = ResourceLoader::get_singleton()->load("res://scenes/gui/save_menu.tscn");

	if (ref->can_instantiate()) {
		Node *node = ref->instantiate();

		SaveMenu *view = Object::cast_to<SaveMenu>(node);
		if (view != nullptr) {
			get_parent()->add_child(node);
			//queue_free();
			set_visible(false);
		}
	}
}
