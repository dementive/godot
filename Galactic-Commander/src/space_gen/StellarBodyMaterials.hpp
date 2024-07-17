#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <StellarBodyColors.hpp>

namespace godot {

struct StellarBodyMaterial {
    ShaderMaterial body;
    ShaderMaterial atmosphere;
};

class StellarBodyMaterials {

private:
	Ref<Resource> body_shader = ResourceLoader::get_singleton()->load("res://gfx/shaders/body.gdshader");
	Ref<Resource> atmosphere_shader = ResourceLoader::get_singleton()->load("res://gfx/shaders/atmosphere.gdshader");
	Ref<Resource> cloud_shader = ResourceLoader::get_singleton()->load("res://gfx/shaders/clouds.gdshader");
	std::map<std::string, PackedColorArray> star_colors = StellarBodyColors::get_star_colors();

public:

	StellarBodyMaterial get_star_material(int star_size) {
		StellarBodyMaterial mats;
		PackedColorArray color;

		mats.body.set_shader(body_shader);
		mats.atmosphere.set_shader(atmosphere_shader);

		// Star coloor is directly correlated with the star's mass
		if (star_size < 3500) color = star_colors["white"];
		else if (star_size >= 3500 and star_size >= 4250) color = star_colors["yellow"];
		else if (star_size >= 4250 and star_size >= 5000) color = star_colors["blue"];
		else color = star_colors["red"];

		mats.body.set_shader_parameter("emit", 3.0);
		mats.body.set_shader_parameter("color_1", color[0]);
		mats.body.set_shader_parameter("color_1_treshold", 0.4);
		mats.body.set_shader_parameter("color_1_roughness", 0.0);
		mats.body.set_shader_parameter("color_1_emit", false);
		mats.body.set_shader_parameter("color_2", color[1]);
		mats.body.set_shader_parameter("color_2_treshold", 0.5);
		mats.body.set_shader_parameter("color_3", color[2]);
		mats.body.set_shader_parameter("color_3_treshold", 0.6);
		mats.body.set_shader_parameter("color_4", color[3]);
		mats.body.set_shader_parameter("color_4_treshold", 0.7);
		mats.body.set_shader_parameter("color_5", color[4]);
		mats.body.set_shader_parameter("color_5_treshold", 1.0);
		mats.body.set_shader_parameter("noise_gaseous", true);
		mats.body.set_shader_parameter("noise_gaseous_speed", UtilityFunctions::randf_range(0.04, 0.06));
		mats.body.set_shader_parameter("noise_scale", UtilityFunctions::randf_range(3.0, 5.5));
		mats.body.set_shader_parameter("noise", ResourceLoader::get_singleton()->load("res://gfx/noises/star.tres"));

		mats.atmosphere.set_shader_parameter("color_1", color[5]);
		mats.atmosphere.set_shader_parameter("color_2", color[6]);
		mats.atmosphere.set_shader_parameter("alpha", 0.55);
		mats.atmosphere.set_shader_parameter("amount", 4.5);
		mats.atmosphere.set_shader_parameter("intensity", 10.0);
		mats.atmosphere.set_shader_parameter("emit", true);

		return mats;
	}

};
}