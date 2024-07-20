#include "Galaxy.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Galaxy::_bind_methods() {
	ClassDB::bind_method(D_METHOD("on_save"), &Galaxy::on_save);
	ClassDB::bind_method(D_METHOD("on_load"), &Galaxy::on_load);
}

Galaxy::Galaxy() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		solar_system = memnew(SolarSystem());
		solar_system->generate_solar_system();
		solar_system->set_name("SolarSystem");
		add_child(solar_system);

		save_manager = memnew(SaveManager());
		save_manager->init("user://test.sav", "12345");
	}
}

Galaxy::~Galaxy() {}

SaveManager* Galaxy::get_save_manager() {
	return save_manager;
}

SolarSystem* Galaxy::get_solar_system() {
	return solar_system;
}

void Galaxy::on_save() {
	int status = save_manager->open_file(FileAccess::WRITE);
	if (status != OK) {
		UtilityFunctions::print("Error opening save file...");
		return;
	}
	for (int i = 0; i < solar_system->get_stellar_bodies().size(); ++i) {
		StellarBody* body = solar_system->get_stellar_bodies()[i];

		if (body != nullptr) {
			save_manager->serialize(body);
		}
	}
	save_manager->close_file();
}

void Galaxy::on_load() {
	int status = save_manager->open_file(FileAccess::READ);
	if (status != OK) {
		UtilityFunctions::print("Error opening save file...");
		return;
	}

	for (int i = 0; i < solar_system->get_stellar_bodies().size(); ++i) {
		StellarBody* body = solar_system->get_stellar_bodies()[i];

		if (body != nullptr) {
			save_manager->deserialize(body);
		}
	}
	save_manager->close_file();
}
