#ifndef Ship_H
#define Ship_H

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

#include "Resource.hpp"
#include "Types.hpp"

using namespace godot;

namespace GC {

#pragma once
class Commander;

class Ship : public MeshInstance3D {
	GDCLASS(Ship, MeshInstance3D);

private:
	CommanderID owner;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	Dictionary required_resources;

	ShipID id;
	inline static std::atomic<ShipID> next_id = 0;

protected:
	static void _bind_methods();

public:
	Ship();
	~Ship();

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

	void set_id();
	void set_new_id(ShipID new_id);
	ShipID get_id();

	void serialize(Ref<FileAccess> file);
	Ship *deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
