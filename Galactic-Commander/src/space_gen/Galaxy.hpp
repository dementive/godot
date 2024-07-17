#ifndef Galaxy_H
#define Galaxy_H

#include <godot_cpp/classes/node.hpp>

namespace godot {

	/*
	The Galaxy.

	This is the root node of the game.
	*/
	class Galaxy : public Node {
		GDCLASS(Galaxy, Node);

	protected:
		static void _bind_methods();

	public:
		Galaxy();
		~Galaxy();
	};

}

#endif
