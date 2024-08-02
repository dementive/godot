#ifndef PauseMenu_H
#define PauseMenu_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/panel_container.hpp>

#include "utils/GuiMacros.hpp"

using namespace godot;

namespace GC {

class PauseMenu : public PanelContainer {
	GDCLASS(PauseMenu, PanelContainer)
	WIDGETS(button_resume, button_main_menu, button_quit, button_load)

private:
	String save_file_name;

	void resume();

protected:
	static void _bind_methods();

public:
	PauseMenu();
	~PauseMenu();

	void _notification(int p_what);
	void _unhandled_input(const Ref<InputEvent> &event) override;

	void open();

	void _on_resume_button_pressed();
	void _on_main_menu_button_pressed();
	void _on_quit_game_button_pressed();
	void _on_load_button_pressed();
};

} //namespace GC

#endif
