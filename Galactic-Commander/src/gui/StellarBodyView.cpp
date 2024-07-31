#include "godot_cpp/classes/base_button.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/rich_text_label.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include <godot_cpp/classes/engine.hpp>

#include "StellarBodyView.hpp"

using namespace godot;
using namespace GC;

void StellarBodyView::_bind_methods() {
	ClassDB::bind_method(D_METHOD("on_close_pressed"), &StellarBodyView::on_close_pressed);

	BIND_NODE_PATH_PROPERTY(close_button, StellarBodyView, BaseButton)
	BIND_NODE_PATH_PROPERTY(title_label, StellarBodyView, Label)
	BIND_NODE_PATH_PROPERTY(orbit_distance_label, StellarBodyView, RichTextLabel)
	BIND_NODE_PATH_PROPERTY(size_label, StellarBodyView, RichTextLabel)
}

StellarBodyView::StellarBodyView() {}

StellarBodyView::~StellarBodyView() {}

void StellarBodyView::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		BaseButton *button_node = get_node<BaseButton>(close_button);

		if (button_node != nullptr)
			button_node->connect("pressed", Callable(this, "on_close_pressed"));
	}
}

void StellarBodyView::on_close_pressed() { queue_free(); }

void StellarBodyView::set_data(String planet_name, float orbit_size, float stellar_body_size) {
	Label *label_node = get_node<Label>(title_label);
	if (label_node != nullptr)
		label_node->set_text(planet_name);

	RichTextLabel *orbit_label_node = get_node<RichTextLabel>(orbit_distance_label);
	if (orbit_label_node != nullptr)
		orbit_label_node->set_text(vformat("%0.2f", orbit_size));

	RichTextLabel *size_label_node = get_node<RichTextLabel>(size_label);
	if (size_label_node != nullptr)
		size_label_node->set_text(vformat("%0.2f", stellar_body_size));
}
