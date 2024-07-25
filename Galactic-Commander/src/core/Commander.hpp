#ifndef Commander_H
#define Commander_H

#include <godot_cpp/classes/character_body3d.hpp>

using namespace godot;

namespace GC {

class Commander : public CharacterBody3D {
	GDCLASS(Commander, CharacterBody3D);

protected:
	static void _bind_methods();

public:
	Commander();
	~Commander();
};

} // namespace GC

#endif
