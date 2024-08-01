#ifndef Ship_H
#define Ship_H

#include "godot_cpp/templates/vector.hpp"
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

#include "GameObject.hpp"
#include "utils/Types.hpp"

using namespace godot;

namespace GC {

class Ship : public MeshInstance3D {
	GDCLASS(Ship, MeshInstance3D);
	GAME_OBJECT(Ship)

private:
	CommanderID owner;
	uint16_t attack;
	uint16_t defense;
	uint16_t speed;
	Vector<String> required_resources;

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

	Vector<String> get_required_resources();
	void set_required_resource(String new_resource);

	void serialize(Ref<FileAccess> file);
	Ship *deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
