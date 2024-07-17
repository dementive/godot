#ifndef SolarSystem_H
#define SolarSystem_H

#include <godot_cpp/classes/node3d.hpp>

#include "StellarBody.hpp"

namespace godot {

	class SolarSystem : public Node3D {
		GDCLASS(SolarSystem, Node3D)

	private:
		Array ice_colors = StellarBodyColors::get_ice_planet_colors();
		Array gas_colors = StellarBodyColors::get_gas_planet_colors();
		Array no_atmosphere_colors = StellarBodyColors::get_no_atmosphere_colors();
		Array terrestrial_colors = StellarBodyColors::get_terrestrial_planet_colors();
		Array sand_colors = StellarBodyColors::get_sand_planet_colors();
		StellarBodyMaterials materials = StellarBodyMaterials();

		std::vector<StellarBody*> stellar_bodies;

	protected:
		static void _bind_methods();

	public:
		SolarSystem();
		~SolarSystem();

		int get_stellar_body_count();
		StellarBody* get_stellar_body(int index);
		void generate_solar_system();
	};

}

#endif
