#ifndef Structure_H
#define Structure_H

#include "StellarBody.hpp"
#include <godot_cpp/classes/mesh_instance3d.hpp>

using namespace godot;

namespace GC {

class Structure : public MeshInstance3D {
	GDCLASS(Structure, MeshInstance3D);

private:
	StellarBody *location;

	Array required_resources;
	Array resource_usage;
	uint64_t required_pops;

	uint64_t id;
	inline static std::atomic<uint64_t> next_id = 0;

protected:
	static void _bind_methods();

public:
	Structure();
	~Structure();
};

} // namespace GC

#endif
