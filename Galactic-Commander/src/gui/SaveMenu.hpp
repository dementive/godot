#ifndef SaveMenu_H
#define SaveMenu_H

#include <godot_cpp/classes/panel_container.hpp>

#include "utils/GuiMacros.hpp"

using namespace godot;

namespace GC {

class SaveMenu : public PanelContainer {
	GDCLASS(SaveMenu, PanelContainer);

protected:
	static void _bind_methods();

public:
	SaveMenu();
	~SaveMenu();

	WIDGETS(button_save, button_load, edit_name)

	void _notification(int p_what);
	void _unhandled_input(const Ref<InputEvent> &event) override;

	void on_save_pressed();
	void on_load_pressed();
};

} //namespace GC

#endif
