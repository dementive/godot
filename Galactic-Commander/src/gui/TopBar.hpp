#ifndef TopBar_H
#define TopBar_H

#include <godot_cpp/classes/h_box_container.hpp>

#include "utils/GuiMacros.hpp"

using namespace godot;

namespace GC {

class TopBar : public HBoxContainer {
	GDCLASS(TopBar, HBoxContainer)
	WIDGETS(button_menu, button_ledger)

protected:
	static void _bind_methods();

public:
	TopBar();
	~TopBar();

	void _notification(int p_what);
	void on_menu_pressed();
	void on_ledger_pressed();
};

} //namespace GC

#endif
