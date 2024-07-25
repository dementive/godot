#ifndef Commander_H
#define Commander_H

#include "core/Ship.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/character_body3d.hpp>

using namespace godot;

namespace GC {

enum DiplomaticRelation { PARTNERSHIP, ALLY, NEUTRAL, UNKNOWN, ENEMY };

struct TradeRoute {
	uint32_t to;
	uint32_t from;

	Array resources_to;
	Array resources_from;
};

class Commander : public CharacterBody3D {
	GDCLASS(Commander, CharacterBody3D);

private:
	Ship active_ship;
	Array ships;
	Vector3 location;

	Dictionary owned_stellar_bodies;
	Dictionary resources;
	Dictionary diplomatic_relations;
	Dictionary trade_routes;

	uint8_t id;
	inline static std::atomic<uint8_t> next_id = 0;

protected:
	static void _bind_methods();

public:
	Commander();
	~Commander();
};

} // namespace GC

#endif
