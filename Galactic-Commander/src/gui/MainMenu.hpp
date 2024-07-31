#ifndef MainMenu_H
#define MainMenu_H

#include <godot_cpp/classes/control.hpp>

#include "GuiMacros.hpp"

using namespace godot;

namespace GC {

class MainMenu : public Control {
	GDCLASS(MainMenu, Control);

protected:
	static void _bind_methods();

public:
	MainMenu();
	~MainMenu();

	GUI_NODE(button_new_game)
	GUI_NODE(button_quit)

	void _ready() override;

	void on_new_game_pressed();
	void on_quit_pressed();
};

} //namespace GC

#endif
