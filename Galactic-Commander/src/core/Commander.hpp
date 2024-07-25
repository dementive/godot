#ifndef Commander_H
#define Commander_H

#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/file_access.hpp>

#include "Types.hpp"

using namespace godot;

namespace GC {

enum DiplomaticRelation { PARTNERSHIP, ALLY, NEUTRAL, UNKNOWN, ENEMY };

class Commander : public CharacterBody3D {
	GDCLASS(Commander, CharacterBody3D);

private:
	ShipID active_ship;
	Array ships;
	Dictionary owned_stellar_bodies;
	Dictionary resources;
	Dictionary diplomatic_relations;
	Dictionary trade_routes;

	struct TradeRoute {
	    Commander* to;
	    Commander* from;

	    Array resources_to;
	    Array resources_from;
	};

	CommanderID id;
	inline static std::atomic<CommanderID> next_id = 0;

protected:
	static void _bind_methods();

public:
	Commander();
	~Commander();

	ShipID get_active_ship();
	void set_active_ship();

	Array get_ships();
	void add_ship(ShipID ship);
	void remove_ship(ShipID ship);

	Dictionary get_owned_stellar_bodies();
	void add_owned_stellar_body(StellarBodyID body);

	Dictionary get_resources();
	void set_resource(String resource_name);

	Dictionary get_diplomatic_relations();
	void set_diplomatic_relation(Commander* target, DiplomaticRelation new_relation);

	Dictionary get_trade_routes();
	void add_trade_route(Commander* target, TradeRoute new_route);
	bool has_trade_route_with(Commander* target);

	void set_id();
	void set_new_id(CommanderID new_id);
	CommanderID get_id();

	void serialize(Ref<FileAccess> file);
	Commander* deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
