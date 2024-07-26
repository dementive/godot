#include <cstdint>

namespace GC {

/*
Struct that all GameObjects should have a member variable of so they can handle their unique ID's in a convenient way

Any class with a GameObject needs to have a public variable: "inline static StellarBodyID next_id = 0;"

Godot doesn't allow for multiple inheritance https://forum.godotengine.org/t/gdextension-multiple-inheritance/73755

but I need common functionality for a large number of the core classes in my game so this is my hacky way of doing it
*/
template <typename Derived> struct GameObject {
	uint64_t id;

	void set_id() {
		id = Derived::next_id;
		Derived::next_id++;
	}

	void set_new_id(uint64_t new_id) { id = new_id; }

	uint64_t get_id() { return id; }
};

} //namespace GC