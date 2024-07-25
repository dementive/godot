#ifndef Ship_H
#define Ship_H

#include <godot_cpp/classes/mesh_instance3d.hpp>

using namespace godot;

namespace GC {

class Ship : public MeshInstance3D {
	GDCLASS(Ship, MeshInstance3D);

private:
	Vector3 location;
	uint8_t attack;
	uint8_t defense;
	uint16_t speed;
	Array required_resources;

	uint32_t id;
	inline static std::atomic<uint32_t> next_id = 0;

protected:
	static void _bind_methods();

public:
	Ship();
	~Ship();
};

} // namespace GC

#endif
