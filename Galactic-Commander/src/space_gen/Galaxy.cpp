#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <godot_cpp/classes/engine.hpp>

#include "Galaxy.hpp"
#include "utils/Types.hpp"

using namespace godot;
using namespace GC;

void Galaxy::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("on_save"), &Galaxy::on_save);
	//ClassDB::bind_method(D_METHOD("on_load"), &Galaxy::on_load);
	ClassDB::bind_method(D_METHOD("on_save", "file_name"), &Galaxy::on_save);
	ClassDB::bind_method(D_METHOD("on_load", "file_name"), &Galaxy::on_load);
}

Galaxy::Galaxy() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		solar_system = memnew(SolarSystem());
		solar_system->generate_solar_system();
		solar_system->set_name("SolarSystem");
		add_child(solar_system);
	}
}

Galaxy::~Galaxy() {}

SaveManager *Galaxy::get_save_manager() { return save_manager; }

SolarSystem *Galaxy::get_solar_system() { return solar_system; }

void Galaxy::on_save(String file_name) {
	save_manager = memnew(SaveManager());
	save_manager->init(file_name, "12345");

	int status = save_manager->open_file(FileAccess::WRITE);
	if (status != OK) {
		UtilityFunctions::print("Error opening save file...");
		return;
	}

	save_manager->serialize(solar_system);
	save_manager->close_file();
}

void Galaxy::on_load(String file_name) {
	save_manager = memnew(SaveManager());
	save_manager->init(file_name, "12345");

	int status = save_manager->open_file(FileAccess::READ);
	if (status != OK) {
		UtilityFunctions::print("Error opening save file...");
		return;
	}

	solar_system->queue_free();

	SolarSystem *new_solar_system = memnew(SolarSystem());
	save_manager->deserialize(new_solar_system);
	add_child(new_solar_system);
	solar_system = new_solar_system;
	save_manager->close_file();
}
