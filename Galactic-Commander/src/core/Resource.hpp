#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

namespace GC {

enum ResourceType { RESEARCH, MINERAL, ENERGY, GOODS };

struct Resource {
	String name;
	float value;
	Array sub_resources;
	float growth;
	ResourceType type;
};

struct SubResource {
	String name;
	float value;
	float growth;
};

} //namespace GC
