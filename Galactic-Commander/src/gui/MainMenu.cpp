#include "MainMenu.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/label_settings.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/core/memory.hpp"

using namespace godot;

void MainMenu::_bind_methods() {
	ClassDB::bind_method(D_METHOD("on_new_game_pressed"), &MainMenu::on_new_game_pressed);
}

MainMenu::MainMenu() {
	if (!Engine::get_singleton()->is_editor_hint()) {

		// Create widgets
		Label* game_title = memnew(Label());
		LabelSettings* game_title_settings = memnew(LabelSettings());

		// Set widget properties
		game_title_settings->set_font_size(55);
		game_title->set_text("Galactic Commander");
		game_title->set_label_settings(game_title_settings);
		add_child(game_title);

		Button* new_game_button = memnew(Button());
		new_game_button->set_text("New Game");
		new_game_button->set_size(Vector2(142, 41));
		add_child(new_game_button);

		// Set widget layouts
		set_anchors_and_offsets_preset(LayoutPreset(PRESET_FULL_RECT), LayoutPresetMode(PRESET_MODE_MINSIZE));
		game_title->set_anchors_and_offsets_preset(LayoutPreset(PRESET_CENTER_TOP), LayoutPresetMode(PRESET_MODE_MINSIZE));
		new_game_button->set_anchors_and_offsets_preset(LayoutPreset(PRESET_CENTER), LayoutPresetMode(PRESET_MODE_KEEP_SIZE));

		// Connect callbacks
		new_game_button->connect("pressed", { this, "on_new_game_pressed" });
	}
}

MainMenu::~MainMenu() {}

void MainMenu::on_new_game_pressed() {
	get_tree()->change_scene_to_file("res://scenes/loading_screen.tscn");
}
