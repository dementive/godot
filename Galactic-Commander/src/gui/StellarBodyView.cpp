#include "godot_cpp/classes/base_button.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include <godot_cpp/classes/engine.hpp>

#include "StellarBodyView.hpp"

using namespace godot;
using namespace GC;

void StellarBodyView::_bind_methods() {
	ClassDB::bind_method(D_METHOD("on_close_pressed"), &StellarBodyView::on_close_pressed);

	ClassDB::bind_method(D_METHOD("get_close_button"), &StellarBodyView::get_close_button);
	ClassDB::bind_method(D_METHOD("set_close_button", "button"), &StellarBodyView::set_close_button);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "close_button", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "BaseButton"),
			"set_close_button", "get_close_button");
}

StellarBodyView::StellarBodyView() {}

StellarBodyView::~StellarBodyView() {}

void StellarBodyView::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		BaseButton *button_node = get_node<BaseButton>(close_button);
		if (button_node != nullptr) button_node->connect("pressed", Callable(this, "on_close_pressed"));
	}
}

void StellarBodyView::on_close_pressed() { set_visible(false); }

NodePath StellarBodyView::get_close_button() const { return close_button; }

void StellarBodyView::set_close_button(NodePath button_path) { close_button = button_path; }
