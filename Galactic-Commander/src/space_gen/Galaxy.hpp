#ifndef Galaxy_H
#define Galaxy_H

#include <godot_cpp/classes/node.hpp>
#include "SaveManager.hpp"
#include <SolarSystem.hpp>

namespace godot {

	/*
	The Galaxy.

	This is the root node of the game.
	*/
	class Galaxy : public Node {
		GDCLASS(Galaxy, Node);

	private:
		SaveManager* save_manager;
		SolarSystem* solar_system;

	protected:
		static void _bind_methods();

	public:
		Galaxy();
		~Galaxy();

		SaveManager* get_save_manager();
		SolarSystem* get_solar_system();

		void on_save();
		void on_load();
	};

}

#endif
