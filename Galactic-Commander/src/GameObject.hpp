#include <cstdint>

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

namespace GC {

/*
Struct that all GameObjects should have a member variable of so they can handle their unique ID's in a convenient way

The ID's allow for easy deserialization of the core Nodes in a game and also enable O(1) access of objects everywhere in the
game via ID -> object pointer hash maps.

Any class with a GameObject needs to have a public variable: "inline static uint64_t next_id = 0;"

Godot doesn't allow for multiple inheritance https://forum.godotengine.org/t/gdextension-multiple-inheritance/73755

but I need common functionality for a large number of the core classes in my game so this is my hacky way of doing it
*/
template <typename Derived> struct GameObject {
	uint64_t id;

	// Used to automatically generate a unique ID for an instance of a GameObject.
	// This MUST be called when a game object is constructed or it will not get an ID.
	void set_id() {
		id = Derived::next_id;
		Derived::next_id++;
	}

	// Used to set a game object ID, should only be used when deserializing GameObject.
	void set_new_id(uint64_t new_id) { id = new_id; }

	// Get the unique ID for this GameObject.
	uint64_t get_id() { return id; }
};

} //namespace GC

#endif