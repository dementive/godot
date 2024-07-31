
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "Galaxy.hpp"
#include "Orbit.hpp"
#include "SolarSystem.hpp"
#include "StellarBody.hpp"
#include "core/Colony.hpp"
#include "core/Commander.hpp"
#include "core/Ship.hpp"
#include "core/Structure.hpp"
#include "gui/MainMenu.hpp"
#include "gui/LoadingScreen.hpp"
#include "gui/StellarBodyView.hpp"
#include "register_types.hpp"

using namespace godot;
using namespace GC;

void initialize_galactic_commander_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<Orbit>();
	ClassDB::register_class<StellarBody>();
	ClassDB::register_class<SolarSystem>();
	ClassDB::register_class<Galaxy>();

	ClassDB::register_class<MainMenu>();
	ClassDB::register_class<LoadingScreen>();
	ClassDB::register_class<StellarBodyView>();

	ClassDB::register_class<SaveManager>();

	ClassDB::register_class<Commander>();
	ClassDB::register_class<Structure>();
	ClassDB::register_class<Colony>();
	ClassDB::register_class<Ship>();
}

void uninitialize_galactic_commander_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT galactic_commander_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library,
		GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_galactic_commander_module);
	init_obj.register_terminator(uninitialize_galactic_commander_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
