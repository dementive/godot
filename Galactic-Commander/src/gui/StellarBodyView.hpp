#ifndef StellarBodyView_H
#define StellarBodyView_H

#include <godot_cpp/classes/panel_container.hpp>

#include "utils/GuiMacros.hpp"

using namespace godot;

namespace GC {

class StellarBodyView : public PanelContainer {
	GDCLASS(StellarBodyView, PanelContainer);

protected:
	static void _bind_methods();

public:
	StellarBodyView();
	~StellarBodyView();

	GUI_NODE(button_close)
	GUI_NODE(label_title)
	GUI_NODE(label_orbit_distance)
	GUI_NODE(label_size)

	void _ready() override;

	void on_close_pressed();
	void set_data(String planet_name, float orbit_size, float stellar_body_size);
};

} //namespace GC

#endif
