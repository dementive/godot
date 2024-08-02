#ifndef LoadingScreen_H
#define LoadingScreen_H

#include <godot_cpp/classes/control.hpp>

#include "utils/GuiMacros.hpp"

using namespace godot;

namespace GC {

class LoadingScreen : public Control {
	GDCLASS(LoadingScreen, Control)

private:
	Array progress;
	String scene_to_load = "res://scenes/game.tscn";

protected:
	static void _bind_methods();

public:
	LoadingScreen();
	~LoadingScreen();

	GUI_NODE(label_progress)

	void _ready() override;
	void _process(const double p_delta) override;
};

} //namespace GC

#endif
