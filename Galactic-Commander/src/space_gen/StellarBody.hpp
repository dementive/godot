#ifndef StellarBody_H
#define StellarBody_H

#include "godot_cpp/classes/control.hpp"
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/templates/vector.hpp>
#include "godot_cpp/classes/mesh_instance3d.hpp"

#include "godot_cpp/variant/vector3.hpp"
#include <StellarBodyMaterials.hpp>

namespace godot {

	enum StellarBodyType { STAR, PLANET };

	class StellarBody : public StaticBody3D {
		GDCLASS(StellarBody, StaticBody3D);

	private:
		float planet_collision_size;
		bool has_atmosphere = false;
		Vector3 scale;
		Dictionary body_params;
		Dictionary atmosphere_params;
		Dictionary cloud_params;
		StellarBodyMaterialType type;
		uint8_t solar_system_id;

	protected:
		static void _bind_methods();

	public:
		StellarBody();
		~StellarBody();

		Vector<StellarBody*> orbiting_bodies;

		void _input_event(
			Camera3D* camera, const Ref<InputEvent>& event, const Vector3& position, const Vector3& normal, int32_t shape_idx
		) override;
		void _mouse_exit() override;

		void create_body(
			uint8_t system_id, StellarBodyType body_type, float distance_from_orbit_origin, StellarBodyMaterial materials, Vector3 body_scale,
			String body_name, bool atmosphere = true
		);
		void add_body(StellarBody* body);
		void create_orbit(float orbit_size = 60000.0);
		void generate_body(float distance_from_star, StellarBodyMaterial materials, Vector3 planet_scale, bool has_atmosphere);

		void set_solar_system_id(uint8_t new_id);
		uint8_t get_solar_system_id();

		Control* get_planet_info_panel();
		Vector3 get_scale();
		MeshInstance3D* get_mesh();

		void serialize(Ref<FileAccess> file);
		void deserialize(Ref<FileAccess> file);
	};

}

#endif
