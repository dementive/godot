#include "Commander.hpp"

using namespace godot;
using namespace GC;

void Commander::_bind_methods() {}

Commander::Commander() {}
Commander::~Commander() {}

ShipID Commander::get_active_ship() { return active_ship; }
void Commander::set_active_ship(ShipID new_ship) { active_ship = new_ship; }

Dictionary Commander::get_ships() { return ships; }

void Commander::add_ship(ShipID new_ship) {
	// ships[new_ship] = get_ship_from_id(new_ship);
}

void Commander::remove_ship(ShipID ship_to_remove) {
	// structures[new_structure] = get_structure_from_id(new_structure);
}

Dictionary Commander::get_owned_stellar_bodies() { return owned_stellar_bodies; }

void Commander::add_owned_stellar_body(StellarBodyID body) {}

Dictionary Commander::get_resources() { return resources; }

void Commander::set_resource(String resource_name) {}

Dictionary Commander::get_diplomatic_relations() { return diplomatic_relations; }

void Commander::set_diplomatic_relation(Commander *target, DiplomaticRelation new_relation) {}

Dictionary Commander::get_trade_routes() { return trade_routes; }

void Commander::add_trade_route(Commander *target, TradeRoute new_route) {}

bool Commander::has_trade_route_with(Commander *target) { return true; }

void Commander::serialize(Ref<FileAccess> file) {}

Commander *Commander::deserialize(Ref<FileAccess> file) { return this; }
