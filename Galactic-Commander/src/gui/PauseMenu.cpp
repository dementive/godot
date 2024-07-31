#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "PauseMenu.hpp"
#include "godot_cpp/classes/base_button.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "gui/SaveMenu.hpp"
#include <godot_cpp/classes/v_box_container.hpp>

using namespace godot;
using namespace GC;

void PauseMenu::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_resume_button_pressed"), &PauseMenu::_on_resume_button_pressed);
	ClassDB::bind_method(D_METHOD("_on_main_menu_button_pressed"), &PauseMenu::_on_main_menu_button_pressed);
	ClassDB::bind_method(D_METHOD("_on_quit_game_button_pressed"), &PauseMenu::_on_quit_game_button_pressed);
	ClassDB::bind_method(D_METHOD("_on_load_button_pressed"), &PauseMenu::_on_load_button_pressed);

	ADD_GROUP("Buttons", "button_");
	BIND_NODE_PATH_PROPERTY(button_vbox, PauseMenu, VBoxContainer)
	BIND_NODE_PATH_PROPERTY(button_resume, PauseMenu, BaseButton)
	BIND_NODE_PATH_PROPERTY(button_main_menu, PauseMenu, BaseButton)
	BIND_NODE_PATH_PROPERTY(button_quit, PauseMenu, BaseButton)
	BIND_NODE_PATH_PROPERTY(button_load, PauseMenu, BaseButton)
}

PauseMenu::PauseMenu() {}
PauseMenu::~PauseMenu() {}

void PauseMenu::resume() {
	set_visible(false);
	VBoxContainer *container_node = get_node<VBoxContainer>(button_vbox);
	container_node->set_visible(true);
	get_tree()->set_pause(false);
}

void PauseMenu::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::PROCESS_MODE_ALWAYS);
		BaseButton *resume_button_node = get_node<BaseButton>(button_resume);
		BaseButton *main_menu_button_node = get_node<BaseButton>(button_main_menu);
		BaseButton *quit_button_node = get_node<BaseButton>(button_quit);
		BaseButton *load_button_node = get_node<BaseButton>(button_load);

		if (resume_button_node != nullptr)
			resume_button_node->connect("pressed", Callable(this, "_on_resume_button_pressed"));

		if (main_menu_button_node != nullptr)
			main_menu_button_node->connect("pressed", Callable(this, "_on_main_menu_button_pressed"));

		if (quit_button_node != nullptr)
			quit_button_node->connect("pressed", Callable(this, "_on_quit_game_button_pressed"));

		if (load_button_node != nullptr)
			load_button_node->connect("pressed", Callable(this, "_on_load_button_pressed"));
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
