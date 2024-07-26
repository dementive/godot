#include "Structure.hpp"

using namespace godot;
using namespace GC;

void Structure::_bind_methods() {}

Structure::Structure() {}
Structure::~Structure() {}

StructureID Structure::get_location() { return location; }

void Structure::serialize(Ref<FileAccess> file) {}
Structure *Structure::deserialize(Ref<FileAccess> file) { return this; }
