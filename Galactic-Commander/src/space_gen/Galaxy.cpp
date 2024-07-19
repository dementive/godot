#include "Galaxy.hpp"

#include <godot_cpp/classes/engine.hpp>

#include "SolarSystem.hpp"

using namespace godot;

void Galaxy::_bind_methods() {}

Galaxy::Galaxy() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		SolarSystem* solar_system = memnew(SolarSystem());
		solar_system->generate_solar_system();
		solar_system->set_name("SolarSystem");
		add_child(solar_system);
	}
}

Galaxy::~Galaxy() {}
