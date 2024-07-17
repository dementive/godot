#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/classes/shader_material.hpp>
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
			if (star_size < 3500) {
				color = star_colors["white"];
			} else if (star_size >= 3500 and star_size >= 4250) {
				color = star_colors["yellow"];
			} else if (star_size >= 4250 and star_size >= 5000) {
				color = star_colors["blue"];
			} else {
				color = star_colors["red"];
			}

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

		StellarBodyMaterial get_terrestrial_material() {
			StellarBodyMaterial mats;
			mats.body.set_shader(body_shader);
			mats.atmosphere.set_shader(atmosphere_shader);
			Array color = StellarBodyColors::get_terrestrial_planet_colors();

			Ref<Resource> noise_texture = ResourceLoader::get_singleton()->load("res://gfx/noises/planet_terrestrial.tres");
			ShaderMaterial cloud_shader_mat = ShaderMaterial();
			cloud_shader_mat.set_shader(cloud_shader);

			cloud_shader_mat.set_shader_parameter("speed", 0.005);
			cloud_shader_mat.set_shader_parameter("brightness", 0.728);
			cloud_shader_mat.set_shader_parameter("threshold", 1.102);
			cloud_shader_mat.set_shader_parameter("fluffiness", 0.376);
			cloud_shader_mat.set_shader_parameter("noise_texture", noise_texture);

			mats.body.set_shader_parameter("emit", 0.0);
			mats.body.set_shader_parameter("color_1", color[0]);
			mats.body.set_shader_parameter("color_1_treshold", UtilityFunctions::randf_range(0.51, 0.59));
			mats.body.set_shader_parameter("color_1_roughness", 0.9);
			mats.body.set_shader_parameter("color_1_emit", false);
			mats.body.set_shader_parameter("color_2", color[1]);
			mats.body.set_shader_parameter("color_2_treshold", 0.56);
			mats.body.set_shader_parameter("color_3", color[2]);
			mats.body.set_shader_parameter("color_3_treshold", 0.6);
			mats.body.set_shader_parameter("color_4", color[3]);
			mats.body.set_shader_parameter("color_4_treshold", 0.7);
			mats.body.set_shader_parameter("color_5", color[4]);
			mats.body.set_shader_parameter("color_5_treshold", 1.0);
			mats.body.set_shader_parameter("noise_gaseous", false);
			mats.body.set_shader_parameter("noise_gaseous_speed", 0.0025);
			mats.body.set_shader_parameter("noise_scale", UtilityFunctions::randf_range(1.0, 1.75));
			mats.body.set_shader_parameter("noise", noise_texture);

			mats.atmosphere.set_shader_parameter("color_1", color[5]);
			mats.atmosphere.set_shader_parameter("color_2", color[6]);
			mats.atmosphere.set_shader_parameter("alpha", 0.3);
			mats.atmosphere.set_shader_parameter("amount", 4.5);
			mats.atmosphere.set_shader_parameter("intensity", 4.0);
			mats.atmosphere.set_shader_parameter("emit", false);

			mats.atmosphere.set_next_pass(&cloud_shader_mat);
			return mats;
		}

		StellarBodyMaterial get_ice_material() {
			StellarBodyMaterial mats;
			mats.body.set_shader(body_shader);
			mats.atmosphere.set_shader(atmosphere_shader);
			Array color = StellarBodyColors::get_ice_planet_colors();

			Ref<Resource> noise_texture = ResourceLoader::get_singleton()->load("res://gfx/noises/planet_ice.tres");
			ShaderMaterial cloud_shader_mat = ShaderMaterial();
			cloud_shader_mat.set_shader(cloud_shader);

			cloud_shader_mat.set_shader_parameter("speed", 0.005);
			cloud_shader_mat.set_shader_parameter("brightness", 0.728);
			cloud_shader_mat.set_shader_parameter("threshold", 1.102);
			cloud_shader_mat.set_shader_parameter("fluffiness", 0.376);
			cloud_shader_mat.set_shader_parameter("noise_texture", noise_texture);

			mats.body.set_shader_parameter("emit", 0.0);
			mats.body.set_shader_parameter("color_1", color[0]);
			mats.body.set_shader_parameter("color_1_treshold", UtilityFunctions::randf_range(0.287, 0.5));
			mats.body.set_shader_parameter("color_1_roughness", 0.0);
			mats.body.set_shader_parameter("color_1_emit", false);
			mats.body.set_shader_parameter("color_2", color[1]);
			mats.body.set_shader_parameter("color_2_treshold", UtilityFunctions::randf_range(0.374, 0.45));
			mats.body.set_shader_parameter("color_3", color[2]);
			mats.body.set_shader_parameter("color_3_treshold", UtilityFunctions::randf_range(0.425, 0.525));
			mats.body.set_shader_parameter("color_4", color[3]);
			mats.body.set_shader_parameter("color_4_treshold", UtilityFunctions::randf_range(0.553, 0.583));
			mats.body.set_shader_parameter("color_5", color[4]);
			mats.body.set_shader_parameter("color_5_treshold", UtilityFunctions::randf_range(0.6, 1.0));
			mats.body.set_shader_parameter("noise_gaseous", false);
			mats.body.set_shader_parameter("noise_gaseous_speed", 0.0025);
			mats.body.set_shader_parameter("noise_scale", UtilityFunctions::randf_range(1.0, 2.3));
			mats.body.set_shader_parameter("noise", noise_texture);

			mats.atmosphere.set_shader_parameter("color_1", color[5]);
			mats.atmosphere.set_shader_parameter("color_2", color[6]);
			mats.atmosphere.set_shader_parameter("alpha", 0.5);
			mats.atmosphere.set_shader_parameter("amount", 4.0);
			mats.atmosphere.set_shader_parameter("intensity", 2.0);
			mats.atmosphere.set_shader_parameter("emit", true);

			mats.atmosphere.set_next_pass(&cloud_shader_mat);
			return mats;
		}

		StellarBodyMaterial get_lava_material() {
			StellarBodyMaterial mats;
			mats.body.set_shader(body_shader);
			mats.atmosphere.set_shader(atmosphere_shader);

			Array color = StellarBodyColors::get_lava_planet_colors();

			mats.body.set_shader_parameter("emit", 0.0);
			mats.body.set_shader_parameter("color_1", color[0]);
			mats.body.set_shader_parameter("color_1_treshold", UtilityFunctions::randf_range(0.253, 0.3));
			mats.body.set_shader_parameter("color_1_roughness", 0.0);
			mats.body.set_shader_parameter("color_1_emit", true);
			mats.body.set_shader_parameter("color_2", color[1]);
			mats.body.set_shader_parameter("color_2_treshold", UtilityFunctions::randf_range(0.3, 0.4));
			mats.body.set_shader_parameter("color_3", color[2]);
			mats.body.set_shader_parameter("color_3_treshold", 0.402);
			mats.body.set_shader_parameter("color_4", color[3]);
			mats.body.set_shader_parameter("color_4_treshold", UtilityFunctions::randf_range(0.525, 0.653));
			mats.body.set_shader_parameter("color_5", color[4]);
			mats.body.set_shader_parameter("color_5_treshold", 1.0);
			mats.body.set_shader_parameter("noise_gaseous", false);
			mats.body.set_shader_parameter("noise_gaseous_speed", 0.0025);
			mats.body.set_shader_parameter("noise_scale", UtilityFunctions::randf_range(1.0, 1.75));
			mats.body.set_shader_parameter("noise", ResourceLoader::get_singleton()->load("res://gfx/noises/planet_lava.tres"));

			mats.atmosphere.set_shader_parameter("color_1", color[5]);
			mats.atmosphere.set_shader_parameter("color_2", color[6]);
			mats.atmosphere.set_shader_parameter("alpha", 0.3);
			mats.atmosphere.set_shader_parameter("amount", 5.366);
			mats.atmosphere.set_shader_parameter("intensity", 0.167);
			mats.atmosphere.set_shader_parameter("emit", true);

			return mats;
		}

		StellarBodyMaterial get_gas_material() {
			StellarBodyMaterial mats;
			mats.body.set_shader(body_shader);
			mats.atmosphere.set_shader(atmosphere_shader);
			Array color = StellarBodyColors::get_gas_planet_colors();

			mats.body.set_shader_parameter("emit", 0.0);
			mats.body.set_shader_parameter("color_1", color[0]);
			mats.body.set_shader_parameter("color_1_treshold", UtilityFunctions::randf_range(0.39, 0.43));
			mats.body.set_shader_parameter("color_1_roughness", 0.0);
			mats.body.set_shader_parameter("color_1_emit", false);
			mats.body.set_shader_parameter("color_2", color[1]);
			mats.body.set_shader_parameter("color_2_treshold", 0.505);
			mats.body.set_shader_parameter("color_3", color[2]);
			mats.body.set_shader_parameter("color_3_treshold", 0.529);
			mats.body.set_shader_parameter("color_4", color[3]);
			mats.body.set_shader_parameter("color_4_treshold", UtilityFunctions::randf_range(0.574, 0.615));
			mats.body.set_shader_parameter("color_5", color[4]);
			mats.body.set_shader_parameter("color_5_treshold", 1.0);
			mats.body.set_shader_parameter("noise_gaseous", true);
			mats.body.set_shader_parameter("noise_gaseous_speed", UtilityFunctions::randf_range(0.0022, 0.0029));
			mats.body.set_shader_parameter("noise_scale", UtilityFunctions::randf_range(1.425, 2.0));
			mats.body.set_shader_parameter(
				"noise", ResourceLoader::get_singleton()->load("res://gfx/noises/planet_gaseous.tres")
			);

			mats.atmosphere.set_shader_parameter("color_1", color[5]);
			mats.atmosphere.set_shader_parameter("color_2", color[6]);
			mats.atmosphere.set_shader_parameter("alpha", UtilityFunctions::randf_range(0.6, 0.8));
			mats.atmosphere.set_shader_parameter("amount", 4.5);
			mats.atmosphere.set_shader_parameter("intensity", 4.0);
			mats.atmosphere.set_shader_parameter("emit", false);

			return mats;
		}

		StellarBodyMaterial get_sand_material() {
			StellarBodyMaterial mats;
			mats.body.set_shader(body_shader);
			mats.atmosphere.set_shader(atmosphere_shader);
			Array color = StellarBodyColors::get_sand_planet_colors();

			mats.body.set_shader_parameter("emit", 0.0);
			mats.body.set_shader_parameter("color_1", color[0]);
			mats.body.set_shader_parameter("color_1_treshold", UtilityFunctions::randf_range(0.425, 0.51));
			mats.body.set_shader_parameter("color_1_roughness", 0.0);
			mats.body.set_shader_parameter("color_1_emit", false);
			mats.body.set_shader_parameter("color_2", color[1]);
			mats.body.set_shader_parameter("color_2_treshold", UtilityFunctions::randf_range(0.57, 0.659));
			mats.body.set_shader_parameter("color_3", color[2]);
			mats.body.set_shader_parameter("color_3_treshold", UtilityFunctions::randf_range(0.69, 0.72));
			mats.body.set_shader_parameter("color_4", color[3]);
			mats.body.set_shader_parameter("color_4_treshold", 0.764);
			mats.body.set_shader_parameter("color_5", color[4]);
			mats.body.set_shader_parameter("color_5_treshold", 1.0);
			mats.body.set_shader_parameter("noise_gaseous", false);
			mats.body.set_shader_parameter("noise_gaseous_speed", 0.0025);
			mats.body.set_shader_parameter("noise_scale", UtilityFunctions::randf_range(1.283, 1.8));
			mats.body.set_shader_parameter("noise", ResourceLoader::get_singleton()->load("res://gfx/noises/planet_sand.tres"));

			mats.atmosphere.set_shader_parameter("color_1", color[5]);
			mats.atmosphere.set_shader_parameter("color_2", color[6]);
			mats.atmosphere.set_shader_parameter("alpha", 0.513);
			mats.atmosphere.set_shader_parameter("amount", 4.5);
			mats.atmosphere.set_shader_parameter("intensity", 4.0);
			mats.atmosphere.set_shader_parameter("emit", false);

			return mats;
		}

		StellarBodyMaterial get_no_atmosphere_material() {
			StellarBodyMaterial mats;
			mats.body.set_shader(body_shader);
			Array color = StellarBodyColors::get_no_atmosphere_colors();

			mats.body.set_shader_parameter("emit", 0.0);
			mats.body.set_shader_parameter("color_1", color[0]);
			mats.body.set_shader_parameter("color_1_treshold", UtilityFunctions::randf_range(0.25, 0.42));
			mats.body.set_shader_parameter("color_1_roughness", 0.0);
			mats.body.set_shader_parameter("color_1_emit", false);
			mats.body.set_shader_parameter("color_2", color[1]);
			mats.body.set_shader_parameter("color_2_treshold", UtilityFunctions::randf_range(0.33, 1.0));
			mats.body.set_shader_parameter("color_3", color[2]);
			mats.body.set_shader_parameter("color_3_treshold", 0.44);
			mats.body.set_shader_parameter("color_4", color[3]);
			mats.body.set_shader_parameter("color_4_treshold", UtilityFunctions::randf_range(0.3, 0.5));
			mats.body.set_shader_parameter("color_5", color[4]);
			mats.body.set_shader_parameter("color_5_treshold", 1.0);
			mats.body.set_shader_parameter("noise_gaseous", false);
			mats.body.set_shader_parameter("noise_gaseous_speed", 0.0025);
			mats.body.set_shader_parameter("noise_scale", UtilityFunctions::randf_range(1.0, 2.3));
			mats.body.set_shader_parameter(
				"noise", ResourceLoader::get_singleton()->load("res://gfx/noises/planet_no_atmosphere.tres")
			);

			return mats;
		}
	};
} // namespace godot
