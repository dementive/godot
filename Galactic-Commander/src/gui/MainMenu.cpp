#include "godot_cpp/classes/scene_tree.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "MainMenu.hpp"

using namespace godot;
using namespace GC;

void MainMenu::_bind_methods() {
	ADD_GROUP("Buttons", "button_");
	CALLBACKS(MainMenu, on_new_game_pressed, on_quit_pressed)
	BIND_WIDGETS(MainMenu, PAIR(button_new_game, BaseButton), PAIR(button_quit, BaseButton))
}

MainMenu::MainMenu() {}
MainMenu::~MainMenu() {}

void MainMenu::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}

	if (p_what == NOTIFICATION_READY) {
		set_process_mode(Node::PROCESS_MODE_ALWAYS);
		CONNECT_CALLBACKS(PAIR(button_new_game, on_new_game_pressed), PAIR(button_quit, on_quit_pressed))
	}
}

void MainMenu::on_new_game_pressed() { get_tree()->change_scene_to_file("res://scenes/gui/loading_screen.tscn"); }

void MainMenu::on_quit_pressed() { get_tree()->quit(); }
