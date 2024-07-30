#ifndef Resource_H
#define Resource_H

#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

namespace GC {

enum ResourceType { RESEARCH, MINERAL, ENERGY, GOODS };

// Remove and make 4 abstractions.
struct Resource {
	String name;
	float value;
	float growth;
	ResourceType type;
};

} //namespace GC

#endif