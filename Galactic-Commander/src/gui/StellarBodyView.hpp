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

	WIDGETS(button_close, label_title, label_orbit_distance, label_size)

	void _notification(int p_what);
	void on_close_pressed();
	void set_data(String planet_name, float orbit_size, float stellar_body_size);
};

} //namespace GC

#endif
