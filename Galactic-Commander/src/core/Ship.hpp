#ifndef Ship_H
#define Ship_H

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

#include "GameObject.hpp"
#include "Resource.hpp"
#include "Types.hpp"

using namespace godot;

namespace GC {

class Ship : public MeshInstance3D {
	GDCLASS(Ship, MeshInstance3D);

private:
	CommanderID owner;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	Dictionary required_resources;

protected:
	static void _bind_methods();

public:
	Ship();
	~Ship();

	inline static ShipID next_id = 0;
	GameObject<Ship> game_object;

	CommanderID get_owner();
	void set_owner(CommanderID new_owner);

	uint16_t get_attack();
	void set_attack(uint16_t amount);

	uint16_t get_defense();
	void set_defense(uint16_t amount);

	uint16_t get_speed();
	void set_speed(uint16_t amount);

	Dictionary get_required_resources();
	void set_required_resource(GC::Resource new_resource);

	void serialize(Ref<FileAccess> file);
	Ship *deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
