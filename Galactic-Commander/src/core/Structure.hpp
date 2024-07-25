#ifndef Structure_H
#define Structure_H

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/file_access.hpp>

#include "Types.hpp"

using namespace godot;

namespace GC {

class Structure : public MeshInstance3D {
	GDCLASS(Structure, MeshInstance3D);

private:
	StellarBodyID location;

	Array required_resources;
	Array resource_usage;
	uint64_t required_pops;
	bool is_orbital_structure;

	StructureID id;
	inline static std::atomic<StructureID> next_id = 0;

protected:
	static void _bind_methods();

public:
	Structure();
	~Structure();

	StructureID get_location();

	void set_id();
	void set_new_id(StructureID new_id);
	StructureID get_id();

	void serialize(Ref<FileAccess> file);
	Structure* deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
