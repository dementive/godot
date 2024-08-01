#ifndef MainMenu_H
#define MainMenu_H

#include <godot_cpp/classes/control.hpp>

#include "utils/GuiMacros.hpp"

using namespace godot;

namespace GC {

class MainMenu : public Control {
	GDCLASS(MainMenu, Control);

protected:
	static void _bind_methods();

public:
	MainMenu();
	~MainMenu();

	WIDGETS(button_new_game, button_quit)

	void _notification(int p_what);
	void on_new_game_pressed();
	void on_quit_pressed();
};

} //namespace GC

#endif
