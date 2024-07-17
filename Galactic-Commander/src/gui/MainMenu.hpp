#ifndef MainMenu_H
#define MainMenu_H

#include <godot_cpp/classes/control.hpp>

namespace godot {

	class MainMenu : public Control {
		GDCLASS(MainMenu, Control);

	protected:
		static void _bind_methods();

	public:
		MainMenu();
		~MainMenu();

		void on_new_game_pressed();
	};

}

#endif
