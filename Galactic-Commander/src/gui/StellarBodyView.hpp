#ifndef StellarBodyView_H
#define StellarBodyView_H

#include "godot_cpp/variant/node_path.hpp"
#include <godot_cpp/classes/control.hpp>

using namespace godot;

namespace GC {

class StellarBodyView : public Control {
	GDCLASS(StellarBodyView, Control);

private:
	NodePath close_button;

protected:
	static void _bind_methods();

public:
	StellarBodyView();
	~StellarBodyView();

	void _ready() override;

	NodePath get_close_button() const;
	void set_close_button(NodePath button_path);
	void on_close_pressed();
};

} //namespace GC

#endif
