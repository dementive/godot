#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/rich_text_label.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include <godot_cpp/classes/engine.hpp>

#include "StellarBodyView.hpp"

using namespace godot;
using namespace GC;

void StellarBodyView::_bind_methods() {
	ADD_GROUP("Buttons", "button_");
	ADD_GROUP("Labels", "label_");

	CALLBACKS(StellarBodyView, on_close_pressed)
	BIND_WIDGETS(StellarBodyView, PAIR(button_close, BaseButton), PAIR(label_title, Label), PAIR(label_orbit_distance, RichTextLabel),
			PAIR(label_size, RichTextLabel))
}

StellarBodyView::StellarBodyView() {}

StellarBodyView::~StellarBodyView() {}

void StellarBodyView::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}

	if (p_what == NOTIFICATION_READY) {
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
