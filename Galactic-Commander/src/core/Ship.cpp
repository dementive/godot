#include "Ship.hpp"

using namespace godot;
using namespace GC;

void Ship::_bind_methods() {}

Ship::Ship() {}
Ship::~Ship() {}

CommanderID Ship::get_owner() { return owner; }

void Ship::set_owner(CommanderID new_owner) { owner = new_owner; }

uint16_t Ship::get_attack() { return attack; }

void Ship::set_attack(uint16_t amount) { attack = amount; }

uint16_t Ship::get_defense() { return defense; }

void Ship::set_defense(uint16_t amount) { defense = amount; }

uint16_t Ship::get_speed() { return speed; }

void Ship::set_speed(uint16_t amount) { speed = amount; }

Dictionary Ship::get_required_resources() { return Dictionary(); }

void Ship::set_required_resource(GC::Resource new_resource) {}

void Ship::serialize(Ref<FileAccess> file) {}

Ship *Ship::deserialize(Ref<FileAccess> file) { return this; }
