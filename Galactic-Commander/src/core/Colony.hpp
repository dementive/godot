#ifndef Colony_H
#define Colony_H

#include "godot_cpp/templates/hash_map.hpp"
#include "godot_cpp/templates/vector.hpp"
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/object.hpp>

#include "Types.hpp"
#include <GameObject.hpp>

using namespace godot;

namespace GC {

class Colony : public Object {
	GDCLASS(Colony, Object);

private:
	CommanderID owner;
	StellarBodyID location;
	uint64_t population;
	Vector<StructureID> structures;

protected:
	static void _bind_methods();

public:
	Colony();
	~Colony();

	inline static std::atomic<ColonyID> next_id = 0;
	inline static HashMap<uint64_t, Colony *> map = HashMap<uint64_t, Colony *>();
	GameObject<Colony> game_object;

	void create_colony(CommanderID owner, StellarBodyID location, uint64_t population = 500);

	CommanderID get_owner();
	void set_owner(CommanderID new_owner);

	StellarBodyID get_location();

	uint64_t get_population();
	void add_population(uint64_t amount);

	Vector<StructureID> get_structures();
	void add_structure(StructureID new_structure);

	void serialize(Ref<FileAccess> file);
	Colony *deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
