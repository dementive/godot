#ifndef StellarBody_H
#define StellarBody_H

#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/static_body3d.hpp>

#include <StellarBodyMaterials.hpp>

namespace godot {

	enum StellarBodyType { STAR, PLANET };

	class StellarBody : public StaticBody3D {
		GDCLASS(StellarBody, StaticBody3D)

	private:
		float planet_collision_size;

	protected:
		static void _bind_methods();

	public:
		StellarBody();
		~StellarBody();

		std::vector<StellarBody*> orbiting_bodies;

		void _input_event(
			Camera3D* camera, const Ref<InputEvent>& event, const Vector3& position, const Vector3& normal, int32_t shape_idx
		) override;
		void _mouse_exit() override;

		void create_body(
			StellarBodyType body_type, float distance_from_orbit_origin, StellarBodyMaterial materials, Vector3 body_scale,
			String body_name, bool atmosphere = true
		);
		void add_body(StellarBody* body);
		void create_orbit(float orbit_size = 60000.0);
		void generate_body(float distance_from_star, StellarBodyMaterial materials, Vector3 planet_scale, bool has_atmosphere);
	};

}

#endif
