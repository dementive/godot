#ifndef StellarBody_H
#define StellarBody_H

#include "godot_cpp/classes/control.hpp"
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/templates/vector.hpp>

#include "godot_cpp/variant/vector3.hpp"
#include <StellarBodyMaterials.hpp>

#define VECTOR_FORWARD Vector3(0, 1, 0) // Used to compare to so we can check if the new position != this

using namespace godot;

namespace GC {

enum StellarBodyType { STAR, PLANET };

class StellarBody : public StaticBody3D {
	GDCLASS(StellarBody, StaticBody3D);

private:
	float planet_collision_size;
	bool has_atmosphere = false;
	Vector3 scale;
	Dictionary orbiting_bodies; // Dictionary<uint32_t, StellarBody*>
	Dictionary body_params;
	Dictionary atmosphere_params;
	Dictionary cloud_params;
	StellarBodyMaterialType material_type;
	StellarBodyType body_type;
	uint8_t solar_system_id;
	float orbit_size;

	uint8_t owner;
	bool is_habitable;
	Dictionary resources;
	Dictionary structures;

	uint32_t id;
	inline static std::atomic<uint32_t> next_id = 0;

protected:
	static void _bind_methods();

public:
	StellarBody();
	~StellarBody();

	void _input_event(Camera3D *camera, const Ref<InputEvent> &event, const Vector3 &position, const Vector3 &normal,
			int32_t shape_idx) override;
	void _mouse_exit() override;

	StellarBody *create_body(uint8_t system_id, StellarBodyType body_type, float distance_from_orbit_origin,
			StellarBodyMaterial materials, Vector3 body_scale, String body_name, bool atmosphere = true, uint32_t new_id = -1,
			Vector3 load_position = VECTOR_FORWARD);
	void generate_body(float distance_from_orbit_origin, StellarBodyMaterial materials, Vector3 planet_scale,
			bool has_atmosphere, Vector3 load_position);
	void add_body(StellarBody *body);
	void create_orbit(float orbit_size);

	void set_solar_system_id(uint8_t new_id);
	uint8_t get_solar_system_id();

	Control *get_planet_info_panel();
	Vector3 get_scale();

	void set_orbiting_bodies(Dictionary new_orbiting_bodies);
	Dictionary get_orbiting_bodies();

	StellarBodyType get_body_type();
	float get_orbit_size();

	void set_id();
	void set_new_id(uint32_t new_id);
	uint32_t get_id();

	void serialize(Ref<FileAccess> file);
	std::pair<StellarBody *, Array> deserialize(Ref<FileAccess> file);
};

} //namespace GC

#endif
