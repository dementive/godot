#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/rich_text_label.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include <godot_cpp/classes/engine.hpp>

#include "StellarBodyView.hpp"

using namespace godot;
using namespace GC;

void StellarBodyView::_bind_methods() {
	BIND_CALLBACK(StellarBodyView, on_close_pressed)

	ADD_GROUP("Buttons", "button_");
	BIND_NODE_PATH_PROPERTY(button_close, StellarBodyView, BaseButton)

	ADD_GROUP("Labels", "label_");
	BIND_NODE_PATH_PROPERTY(label_title, StellarBodyView, Label)
	BIND_NODE_PATH_PROPERTY(label_orbit_distance, StellarBodyView, RichTextLabel)
	BIND_NODE_PATH_PROPERTY(label_size, StellarBodyView, RichTextLabel)
}

StellarBodyView::StellarBodyView() {}

StellarBodyView::~StellarBodyView() {}

void StellarBodyView::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		CONNECT_CALLBACK(button_close, on_close_pressed)
	}
}

void StellarBodyView::on_close_pressed() { queue_free(); }

void StellarBodyView::set_data(String planet_name, float orbit_size, float stellar_body_size) {
	Label *label_node = get_node<Label>(label_title);
	label_node->set_text(planet_name);

	RichTextLabel *orbit_label_node = get_node<RichTextLabel>(label_orbit_distance);
	orbit_label_node->set_text(vformat("%0.2f", orbit_size));

	RichTextLabel *size_label_node = get_node<RichTextLabel>(label_size);
	size_label_node->set_text(vformat("%0.2f", stellar_body_size));
}
