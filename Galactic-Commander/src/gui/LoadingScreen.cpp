#include <godot_cpp/classes/engine.hpp>

#include "LoadingScreen.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;
using namespace GC;

void LoadingScreen::_bind_methods() {
	ADD_GROUP("Labels", "label_");
	BIND_NODE_PATH(LoadingScreen, label_progress, Label)
}

LoadingScreen::LoadingScreen() {}

LoadingScreen::~LoadingScreen() {}

void LoadingScreen::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		ResourceLoader::get_singleton()->load_threaded_request(scene_to_load);
	} else {
		CHECK_GUI_NODE(label_progress)
	}
}

void LoadingScreen::_process(const double p_delta) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		ResourceLoader::ThreadLoadStatus scene_load_status = ResourceLoader::get_singleton()->load_threaded_get_status(scene_to_load, progress);

		Label *progress_label_node = get_node<Label>(label_progress);
		progress_label_node->set_text(String::num_int64(Math::floor(float(progress[0]) * 100)) + "%");

		if (scene_load_status == ResourceLoader::THREAD_LOAD_LOADED) {
			Ref<PackedScene> new_scene = ResourceLoader::get_singleton()->load_threaded_get(scene_to_load);
			get_tree()->change_scene_to_packed(new_scene);
		}
	}
}
