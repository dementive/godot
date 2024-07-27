#ifndef Commander_H
#define Commander_H

#include "godot_cpp/templates/hash_map.hpp"
#include "godot_cpp/templates/vector.hpp"
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include "GameObject.hpp"
#include "Resource.hpp"
#include "TradeRoute.hpp"
#include "Types.hpp"

using namespace godot;

namespace GC {

enum DiplomaticRelation { PARTNERSHIP, ALLY, NEUTRAL, UNKNOWN, ENEMY };

class Commander : public CharacterBody3D {
	GDCLASS(Commander, CharacterBody3D);

private:
	ShipID active_ship;
	Vector<ShipID> ships;
	Vector<StellarBodyID> owned_stellar_bodies;
	HashMap<String, GC::Resource *> resources;
	HashMap<CommanderID, DiplomaticRelation> diplomatic_relations;
	Vector<TradeRoute> trade_routes;

protected:
	static void _bind_methods();

public:
	Commander();
	~Commander();

	inline static std::atomic<CommanderID> next_id = 0;
	inline static HashMap<uint64_t, Commander *> map = HashMap<uint64_t, Commander *>();
	GameObject<Commander> game_object;

	ShipID get_active_ship();
	void set_active_ship(ShipID new_ship);

	Vector<ShipID> get_ships();
	void add_ship(ShipID new_ship);
	void remove_ship(ShipID ship_to_remove);

	Vector<StellarBodyID> get_owned_stellar_bodies();
	void add_owned_stellar_body(StellarBodyID body);

	HashMap<String, GC::Resource *> get_resources();
	void set_resource(String resource_name);

	HashMap<CommanderID, DiplomaticRelation> get_diplomatic_relations();
	void set_diplomatic_relation(Commander *target, DiplomaticRelation new_relation);

	Vector<TradeRoute> get_trade_routes();
	void add_trade_route(Commander *target, TradeRoute new_route);
	bool has_trade_route_with(Commander *target);

	void serialize(Ref<FileAccess> file);
	Commander *deserialize(Ref<FileAccess> file);
};

} // namespace GC

#endif
