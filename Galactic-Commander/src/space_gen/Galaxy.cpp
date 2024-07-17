#include <godot_cpp/classes/engine.hpp>

#include "Galaxy.hpp"
#include "SolarSystem.hpp"

using namespace godot;

void Galaxy::_bind_methods() {}
Galaxy::Galaxy() {
	if (!Engine::get_singleton()->is_editor_hint()) { // only run if we are not in the editor
		SolarSystem solar_system = SolarSystem();
		solar_system.generate_solar_system();
		solar_system.set_name("SolarSystem");
		add_child(&solar_system);
	}
}
Galaxy::~Galaxy() {}
