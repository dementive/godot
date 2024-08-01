#include "godot_cpp/classes/scene_tree.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "MainMenu.hpp"

using namespace godot;
using namespace GC;

void MainMenu::_bind_methods() {
	BIND_CALLBACK(MainMenu, on_new_game_pressed)
	BIND_CALLBACK(MainMenu, on_quit_pressed)

	ADD_GROUP("Buttons", "button_");
	BIND_NODE_PATH_PROPERTY(button_new_game, MainMenu, BaseButton)
	BIND_NODE_PATH_PROPERTY(button_quit, MainMenu, BaseButton)
}

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		CONNECT_CALLBACK(button_new_game, on_new_game_pressed)
		CONNECT_CALLBACK(button_quit, on_quit_pressed)
	}
}

void MainMenu::on_new_game_pressed() { get_tree()->change_scene_to_file("res://scenes/gui/loading_screen.tscn"); }

void MainMenu::on_quit_pressed() { get_tree()->quit(); }
