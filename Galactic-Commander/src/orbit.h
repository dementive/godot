#ifndef GCOrbit_H
#define GCOrbit_H

#include <godot_cpp/classes/node3d.hpp>


namespace godot {

/*
Orbit Node to attach to a StellarBody in a solar system

All StellarBody's that are children of the parent node of a GCOrbit node will orbit the parent.
*/
class GCOrbit : public Node3D {
	GDCLASS(GCOrbit, Node3D)

private:
	float max_orbit_size;

protected:
	static void _bind_methods();
	
public:
	GCOrbit();
	~GCOrbit();

	void _physics_process(double delta) override;

	void set_max_orbit_size(const float orbit_size);
	double get_max_orbit_size() const;
};

}

#endif