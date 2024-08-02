#include "godot_cpp/classes/scene_tree.hpp"

#include "TopBar.hpp"

using namespace godot;
using namespace GC;

void TopBar::_bind_methods() {
	ADD_GROUP("Buttons", "button_");
	CALLBACKS(TopBar, on_menu_pressed, on_ledger_pressed)
	BIND_WIDGETS(TopBar, PAIR(button_menu, BaseButton), PAIR(button_ledger, BaseButton))
}

TopBar::TopBar() {}
TopBar::~TopBar() {}

void TopBar::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}

	if (p_what == NOTIFICATION_READY) {
		CONNECT_CALLBACKS(PAIR(button_menu, on_menu_pressed), PAIR(button_ledger, on_ledger_pressed))
	}
}

void TopBar::on_menu_pressed() { UtilityFunctions::print("Menu pressed!"); }

void TopBar::on_ledger_pressed() {}
