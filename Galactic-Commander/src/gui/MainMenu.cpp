#include "godot_cpp/classes/base_button.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "MainMenu.hpp"

using namespace godot;
using namespace GC;

void MainMenu::_bind_methods() {
	ClassDB::bind_method(D_METHOD("on_new_game_pressed"), &MainMenu::on_new_game_pressed);
	ClassDB::bind_method(D_METHOD("on_quit_pressed"), &MainMenu::on_quit_pressed);

	ADD_GROUP("Buttons", "button_");
	BIND_NODE_PATH_PROPERTY(button_new_game, MainMenu, BaseButton)
	BIND_NODE_PATH_PROPERTY(button_quit, MainMenu, BaseButton)
}

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		BaseButton *new_game_button_node = get_node<BaseButton>(button_new_game);
		BaseButton *quit_button_node = get_node<BaseButton>(button_quit);

		if (new_game_button_node != nullptr)
			new_game_button_node->connect("pressed", Callable(this, "on_new_game_pressed"));

		if (quit_button_node != nullptr)
			quit_button_node->connect("pressed", Callable(this, "on_quit_pressed"));
	}
}

void MainMenu::on_new_game_pressed() { get_tree()->change_scene_to_file("res://scenes/gui/loading_screen.tscn"); }

void MainMenu::on_quit_pressed() { get_tree()->quit(); }
