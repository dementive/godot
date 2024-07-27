#ifndef SolarSystem_H
#define SolarSystem_H

#include "godot_cpp/templates/hash_map.hpp"
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

protected:
	static void _bind_methods();

public:
	SolarSystem();
	~SolarSystem();

	inline static std::atomic<SolarSystemID> next_id = 0;
	inline static HashMap<uint64_t, SolarSystem *> map = HashMap<uint64_t, SolarSystem *>();
	GameObject<SolarSystem> game_object;

	Vector<StellarBody *> get_stellar_bodies();
	StellarBody *get_stellar_body(int index);
	void generate_solar_system();

	void serialize(Ref<FileAccess> file);
	void deserialize(Ref<FileAccess> file);
};

} //namespace GC

#endif
