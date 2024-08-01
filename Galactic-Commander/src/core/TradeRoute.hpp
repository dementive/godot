#ifndef TradeRoute_H
#define TradeRoute_H

#include "godot_cpp/templates/hash_map.hpp"
#include <godot_cpp/variant/string.hpp>

#include "Resource.hpp"
#include "utils/Types.hpp"

using namespace godot;

namespace GC {

struct TradeRoute {
	CommanderID *to;
	CommanderID *from;

	HashMap<String, Resource *> resources_to;
	HashMap<String, Resource *> resources_from;
};

} //namespace GC

#endif