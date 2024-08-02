#include "Colony.hpp"

using namespace godot;
using namespace GC;

void Colony::_bind_methods() {}

Colony::Colony() {}
Colony::~Colony() {}

void Colony::create_colony(CommanderID colony_owner, StellarBodyID colony_location, uint64_t colony_population) {
	owner = colony_owner;
	location = colony_location;
	population = colony_population;

	set_id(this);
}

CommanderID Colony::get_owner() { return owner; }

void Colony::set_owner(CommanderID new_owner) { owner = new_owner; }

StellarBodyID Colony::get_location() { return location; }

uint64_t Colony::get_population() { return population; }

void Colony::add_population(uint64_t amount) { population += amount; }

Vector<StructureID> Colony::get_structures() { return structures; }

void Colony::add_structure(StructureID new_structure) {
	// structures[new_structure] = get_structure_from_id(new_structure);
}

void Colony::serialize(Ref<FileAccess> file) {}

Colony *Colony::deserialize(Ref<FileAccess> file) { return this; }
