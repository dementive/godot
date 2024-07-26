#ifndef SolarSystem_H
#define SolarSystem_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/templates/vector.hpp>

#include "StellarBody.hpp"
#include <Types.hpp>

using namespace godot;

namespace GC {

class SolarSystem : public Node3D {
	GDCLASS(SolarSystem, Node3D);

private:
	Vector<StellarBody *> stellar_bodies;
	SolarSystemID id;

protected:
	static void _bind_methods();

public:
	SolarSystem();
	~SolarSystem();

	Vector<StellarBody *> get_stellar_bodies();
	StellarBody *get_stellar_body(int index);
	void generate_solar_system(SolarSystemID system_id);

	void set_id(SolarSystemID new_id);
	SolarSystemID get_id();

	void serialize(Ref<FileAccess> file);
	void deserialize(Ref<FileAccess> file);
};

} //namespace GC

#endif
