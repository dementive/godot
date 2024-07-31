#ifndef StellarBodyView_H
#define StellarBodyView_H

#include "godot_cpp/variant/node_path.hpp"
#include <godot_cpp/classes/panel_container.hpp>

#include "GuiMacros.hpp"

using namespace godot;

namespace GC {

class StellarBodyView : public PanelContainer {
	GDCLASS(StellarBodyView, PanelContainer);

protected:
	static void _bind_methods();

public:
	StellarBodyView();
	~StellarBodyView();

	GUI_NODE(close_button)
	GUI_NODE(title_label)
	GUI_NODE(orbit_distance_label)
	GUI_NODE(size_label)

	void _ready() override;

	void on_close_pressed();
	void set_data(String planet_name, float orbit_size, float stellar_body_size);
};

} //namespace GC

#endif
