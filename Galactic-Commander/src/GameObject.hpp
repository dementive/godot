#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "godot_cpp/templates/hash_map.hpp"
#include <cstdint>
// ^^^ Used for GAME_OBJECT don't remove clangd is wrong.

namespace GC {

/*
Struct that all GameObjects should have a member variable of so they can handle their unique ID's in a convenient way

The ID's allow for easy deserialization of the core Nodes in a game and also enable O(1) access of objects everywhere in the
game via ID -> object pointer hash maps.

Any class with a GameObject needs to have 2 public variables:
inline static std::atomic<uint64_t> next_id = 0;
inline static HashMap<uint64_t, Derived*> map = HashMap<uint64_t, Derived*>();

Godot doesn't allow for multiple inheritance https://forum.godotengine.org/t/gdextension-multiple-inheritance/73755

but I need common functionality for a large number of the core classes in my game so this is my hacky way of doing it
*/

// Call GAME_OBJECT(ClassName) in the public: block of the class to make a GameObject
#define GAME_OBJECT(m_class)                                                                                                                                   \
public:                                                                                                                                                        \
	inline static std::atomic<uint64_t> next_id = 0;                                                                                                           \
	inline static HashMap<uint64_t, m_class *> map = HashMap<uint64_t, m_class *>();                                                                           \
	uint64_t id;                                                                                                                                               \
	void set_id(m_class *object) {                                                                                                                             \
		id = m_class::next_id;                                                                                                                                 \
		m_class::next_id++;                                                                                                                                    \
		m_class::map[id] = object;                                                                                                                             \
	}                                                                                                                                                          \
	void set_new_id(uint64_t new_id, m_class *object) {                                                                                                        \
		id = new_id;                                                                                                                                           \
		m_class::map[id] = object;                                                                                                                             \
	}                                                                                                                                                          \
	uint64_t get_id() { return id; }                                                                                                                           \
	void remove_id(uint64_t id_to_remove) { m_class::map.erase(id_to_remove); }

} //namespace GC

#endif