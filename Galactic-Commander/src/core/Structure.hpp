#ifndef Structure_H
#define Structure_H

#include "godot_cpp/templates/hash_map.hpp"
#include "godot_cpp/templates/vector.hpp"
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

#include "GameObject.hpp"
#include "Types.hpp"

using namespace godot;

namespace GC {

class Structure : public MeshInstance3D {
	GDCLASS(Structure, MeshInstance3D);

private:
	StellarBodyID location;

	Vector<String> required_resources;
	HashMap<String, uint64_t> resource_usage;
	uint64_t required_pops;
	bool is_orbital_structure;

protected:
	static void _bind_methods();

public:
	Structure();
	~Structure();

	inline static std::atomic<StructureID> next_id = 0;
	inline static HashMap<uint64_t, Structure *> map = HashMap<uint64_t, Structure *>();
	GameObject<Structure> game_object;

	StructureID get_location();

	void serialize(Ref<FileAccess> file);
	Structure *deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
