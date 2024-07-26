#ifndef Colony_H
#define Colony_H

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/object.hpp>

using namespace godot;
#include "Types.hpp"

namespace GC {

class Colony : public Object {
	GDCLASS(Colony, Object);

private:
	CommanderID owner;
	StellarBodyID location;
	uint64_t population;
	Dictionary structures;

	ColonyID id;
	inline static std::atomic<ColonyID> next_id = 0;

protected:
	static void _bind_methods();

public:
	Colony();
	~Colony();

	void create_colony(CommanderID owner, StellarBodyID location, uint64_t population = 500);

	CommanderID get_owner();
	void set_owner(CommanderID new_owner);

	StellarBodyID get_location();

	uint64_t get_population();
	void add_population(uint64_t amount);

	Dictionary get_structures();
	void add_structure(StructureID new_structure);

	void set_id();
	void set_new_id(ColonyID new_id);
	ColonyID get_id();

	void serialize(Ref<FileAccess> file);
	Colony *deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
