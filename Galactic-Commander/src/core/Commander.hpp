#ifndef Commander_H
#define Commander_H

#include <godot_cpp/classes/character_body3d.hpp>

namespace godot {

class Commander : public CharacterBody3D {
	GDCLASS(Commander, CharacterBody3D);

protected:
	static void _bind_methods();

public:
	Commander();
	~Commander();
};

} // namespace godot

#endif
