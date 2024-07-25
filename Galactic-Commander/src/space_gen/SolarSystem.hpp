#ifndef SolarSystem_H
#define SolarSystem_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/templates/vector.hpp>

#include "StellarBody.hpp"

namespace godot {

class SolarSystem : public Node3D {
	GDCLASS(SolarSystem, Node3D);

private:
	Vector<StellarBody *> stellar_bodies;
	uint8_t id;

protected:
	static void _bind_methods();

public:
	SolarSystem();
	~SolarSystem();

	Vector<StellarBody *> get_stellar_bodies();
	StellarBody *get_stellar_body(int index);
	void generate_solar_system(uint8_t system_id);

	void set_id(uint8_t new_id);
	uint8_t get_id();

	void serialize(Ref<FileAccess> file);
	void deserialize(Ref<FileAccess> file);
};

} //namespace godot

#endif
