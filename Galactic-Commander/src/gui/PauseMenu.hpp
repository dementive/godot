#ifndef PauseMenu_H
#define PauseMenu_H

#include <godot_cpp/classes/panel_container.hpp>

#include "GuiMacros.hpp"

using namespace godot;

namespace GC {

class PauseMenu : public PanelContainer {
	GDCLASS(PauseMenu, PanelContainer);

private:
	String save_file_name;

	void resume();

protected:
	static void _bind_methods();

public:
	PauseMenu();
	~PauseMenu();

	GUI_NODE(button_vbox)
	GUI_NODE(button_resume)
	GUI_NODE(button_main_menu)
	GUI_NODE(button_quit)
	GUI_NODE(button_load)

	void _ready() override;
	void _unhandled_input(const Ref<InputEvent> &event) override;

	void _on_resume_button_pressed();
	void _on_main_menu_button_pressed();
	void _on_quit_game_button_pressed();
	void _on_load_button_pressed();
};

} //namespace GC

#endif
