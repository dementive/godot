#include "godot_cpp/variant/dictionary.hpp"
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/shader.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <StellarBodyColors.hpp>
#include <Utils.hpp>

using namespace godot;

namespace GC {

enum StellarBodyMaterialType { M_STAR, M_TERRESTRIAL, M_ICE, M_LAVA, M_GAS, M_SAND, M_NO_ATMOSPHERE };

struct StellarBodyMaterial {
	StellarBodyMaterialType type;

	ShaderMaterial body;
	ShaderMaterial atmosphere;
	ShaderMaterial clouds;

	Dictionary body_params;
	Dictionary atmosphere_params;
	Dictionary cloud_params;
};

class StellarBodyMaterials {
private:
	Ref<Resource> body_shader = ResourceLoader::get_singleton()->load("res://gfx/shaders/body.gdshader");
	Ref<Resource> simple_body_shader = ResourceLoader::get_singleton()->load("res://gfx/shaders/simple_body.gdshader");
	Ref<Resource> atmosphere_shader = ResourceLoader::get_singleton()->load("res://gfx/shaders/atmosphere.gdshader");
	Ref<Resource> cloud_shader = ResourceLoader::get_singleton()->load("res://gfx/shaders/clouds.gdshader");

	void set_body_and_atmosphere_parms(StellarBodyMaterial &mats, Dictionary body_params, Dictionary atmosphere_params) {
		if (body_params.has("body_texture")) {
			mats.body.set_shader(simple_body_shader);
		} else {
			mats.body.set_shader(body_shader);
		}
		mats.atmosphere.set_shader(atmosphere_shader);

		Array body_keys = body_params.keys();
		for (int i = 0; i < body_params.size(); i++) {
			String key = body_keys[i];
			if (key == "noise" or key == "body_texture") { // Noise has to be loaded as a resource from a string as it isn't
														   // serializable, this is probably fuckin dumb and there's likely a
														   // better way to do this, oh well.
				mats.body.set_shader_parameter(key, ResourceLoader::get_singleton()->load(body_params[key]));
			} else {
				mats.body.set_shader_parameter(key, body_params[key]);
			}
		}

		Array atmosphere_keys = atmosphere_params.keys();
		for (int i = 0; i < atmosphere_params.size(); i++) {
			String key = atmosphere_keys[i];
			mats.atmosphere.set_shader_parameter(key, atmosphere_params[key]);
		}
	}

public:
	void save_params(StellarBodyMaterial &mats, String noise_texture, String body_texture = "", bool simple_body = false) {
		if (simple_body == false) {
			mats.body_params["emit"] = mats.body.get_shader_parameter("emit");
			mats.body_params["color_1"] = mats.body.get_shader_parameter("color_1");
			mats.body_params["color_1_treshold"] = mats.body.get_shader_parameter("color_1_treshold");
			mats.body_params["color_1_roughness"] = mats.body.get_shader_parameter("color_1_roughness");
			mats.body_params["color_1_emit"] = mats.body.get_shader_parameter("color_1_emit");
			mats.body_params["color_2"] = mats.body.get_shader_parameter("color_2");
			mats.body_params["color_2_treshold"] = mats.body.get_shader_parameter("color_2_treshold");
			mats.body_params["color_3"] = mats.body.get_shader_parameter("color_3");
			mats.body_params["color_3_treshold"] = mats.body.get_shader_parameter("color_3_treshold");
			mats.body_params["color_4"] = mats.body.get_shader_parameter("color_4");
			mats.body_params["color_4_treshold"] = mats.body.get_shader_parameter("color_4_treshold");
			mats.body_params["color_5"] = mats.body.get_shader_parameter("color_5");
			mats.body_params["color_5_treshold"] = mats.body.get_shader_parameter("color_5_treshold");
			mats.body_params["noise_gaseous"] = mats.body.get_shader_parameter("noise_gaseous");
			mats.body_params["noise_gaseous_speed"] = mats.body.get_shader_parameter("noise_gaseous_speed");
			mats.body_params["noise_scale"] = mats.body.get_shader_parameter("noise_scale");
			mats.body_params["noise"] =
					noise_texture; // Noise is stored as String because Resource isn't serializable with store_var.
		} else {
			mats.body_params["body_texture"] = body_texture;
			mats.body_params["use_color_mod"] = mats.body.get_shader_parameter("use_color_mod");
			mats.body_params["color_mod"] = mats.body.get_shader_parameter("color_mod");
			mats.body_params["brightness"] = mats.body.get_shader_parameter("brightness");
		}
		mats.atmosphere_params["color_1"] = mats.atmosphere.get_shader_parameter("color_1");
		mats.atmosphere_params["color_2"] = mats.atmosphere.get_shader_parameter("color_2");
		mats.atmosphere_params["alpha"] = mats.atmosphere.get_shader_parameter("alpha");
		mats.atmosphere_params["amount"] = mats.atmosphere.get_shader_parameter("amount");
		mats.atmosphere_params["intensity"] = mats.atmosphere.get_shader_parameter("intensity");
		mats.atmosphere_params["emit"] = mats.atmosphere.get_shader_parameter("emit");
	}

	StellarBodyMaterial get_material_with_clouds_from_dict(
			Dictionary body_params, Dictionary atmosphere_params, Dictionary cloud_params) {
		StellarBodyMaterial mats;
		set_body_and_atmosphere_parms(mats, body_params, atmosphere_params);

		mats.clouds.set_shader(cloud_shader);
		Array cloud_keys = cloud_params.keys();
		for (int i = 0; i < cloud_params.size(); i++) {
			String key = cloud_keys[i];
			if (key == "noise_texture") {
				mats.clouds.set_shader_parameter(key, ResourceLoader::get_singleton()->load(cloud_params[key]));
			} else {
				mats.clouds.set_shader_parameter(key, cloud_params[key]);
			}
		}

		if (body_params.has("body_texture")) {
			// Check if the simple body shader is being used
			save_params(mats, body_params["noise"], body_params["body_texture"], true);
		} else {
			save_params(mats, body_params["noise"]);
		}

		mats.atmosphere.set_next_pass(&mats.clouds);
		return mats;
	}

	StellarBodyMaterial get_material_from_dict(Dictionary body_params, Dictionary atmosphere_params) {
		StellarBodyMaterial mats;

		set_body_and_atmosphere_parms(mats, body_params, atmosphere_params);

		if (body_params.has("body_texture")) {
			save_params(mats, body_params["noise"], body_params["body_texture"], true);
		} else {
			save_params(mats, body_params["noise"]);
		}

		return mats;
	}

	StellarBodyMaterial get_material_from_dict_no_atmosphere(Dictionary body_params) {
		StellarBodyMaterial mats;
		mats.body.set_shader(body_shader);

		Array body_keys = body_params.keys();
		for (int i = 0; i < body_params.size(); i++) {
			String key = body_keys[i];
			if (key == "noise") {
				mats.body.set_shader_parameter(key, ResourceLoader::get_singleton()->load(body_params[key]));
			} else {
				mats.body.set_shader_parameter(key, body_params[key]);
			}
		}

		if (body_params.has("body_texture")) {
			save_params(mats, body_params["noise"], body_params["body_texture"], true);
		} else {
			save_params(mats, body_params["noise"]);
		}
		return mats;
	}

	StellarBodyMaterial get_star_material(int star_size) {
		StellarBodyMaterial mats;
		PackedColorArray color;
		String noise = "res://gfx/noises/star.tres";
		Dictionary star_colors = StellarBodyColors::get_star_colors();

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
		mats.body.set_shader_parameter("noise", ResourceLoader::get_singleton()->load(noise));

		mats.atmosphere.set_shader_parameter("color_1", color[5]);
		mats.atmosphere.set_shader_parameter("color_2", color[6]);
		mats.atmosphere.set_shader_parameter("alpha", 0.55);
		mats.atmosphere.set_shader_parameter("amount", 4.5);
		mats.atmosphere.set_shader_parameter("intensity", 10.0);
		mats.atmosphere.set_shader_parameter("emit", true);

		mats.type = M_STAR;
		save_params(mats, noise);
		return mats;
	}

	StellarBodyMaterial get_terrestrial_material() {
		StellarBodyMaterial mats;
		String noise = "res://gfx/noises/planet_terrestrial.tres";

		mats.body.set_shader(simple_body_shader);
		mats.atmosphere.set_shader(atmosphere_shader);
		mats.clouds.set_shader(cloud_shader);

		Array color = StellarBodyColors::get_terrestrial_planet_colors();
		Ref<Resource> noise_texture = ResourceLoader::get_singleton()->load(noise);

		Dictionary cloud_parameters;
		cloud_parameters["speed"] = 0.005;
		cloud_parameters["brightness"] = 0.728;
		cloud_parameters["threshold"] = 1.102;
		cloud_parameters["fluffiness"] = 0.376;
		cloud_parameters["noise_texture"] = noise;
		mats.cloud_params = cloud_parameters; // DO NOT change this, setting the paramters for clouds any other way doesn't work
											  // for some dumbass reason

		mats.clouds.set_shader_parameter("speed", cloud_parameters["speed"]);
		mats.clouds.set_shader_parameter("brightness", cloud_parameters["brightness"]);
		mats.clouds.set_shader_parameter("threshold", cloud_parameters["threshold"]);
		mats.clouds.set_shader_parameter("fluffiness", cloud_parameters["fluffiness"]);
		mats.clouds.set_shader_parameter("noise_texture", noise_texture);

		Array all_textures = GC::get_files_in_dir("res://gfx/planet_textures/Grassland", ".png");
		Array jungle_textures = GC::get_files_in_dir("res://gfx/planet_textures/Jungle", ".png");
		Array marshy_textures = GC::get_files_in_dir("res://gfx/planet_textures/Marshy", ".png");
		Array tundra_textures = GC::get_files_in_dir("res://gfx/planet_textures/Tundra", ".png");
		Array sandy_textures = GC::get_files_in_dir("res://gfx/planet_textures/Sandy", ".png");

		all_textures.append_array(jungle_textures);
		all_textures.append_array(marshy_textures);
		all_textures.append_array(tundra_textures);
		all_textures.append_array(sandy_textures);

		String texture = all_textures.pick_random();

		mats.body.set_shader_parameter("body_texture", ResourceLoader::get_singleton()->load(texture));
		mats.body.set_shader_parameter("brightness", 0.75);

		mats.atmosphere.set_shader_parameter("color_1", color[5]);
		mats.atmosphere.set_shader_parameter("color_2", color[6]);
		mats.atmosphere.set_shader_parameter("alpha", 0.3);
		mats.atmosphere.set_shader_parameter("amount", 4.5);
		mats.atmosphere.set_shader_parameter("intensity", 4.0);
		mats.atmosphere.set_shader_parameter("emit", false);

		mats.atmosphere.set_next_pass(&mats.clouds);
		mats.type = M_TERRESTRIAL;
		save_params(mats, noise, texture, true);
		return mats;
	}

	StellarBodyMaterial get_ice_material() {
		StellarBodyMaterial mats;
		String noise = "res://gfx/noises/planet_ice.tres";

		mats.body.set_shader(body_shader);
		mats.atmosphere.set_shader(atmosphere_shader);
		mats.clouds.set_shader(cloud_shader);

		Array color = StellarBodyColors::get_ice_planet_colors();
		Ref<Resource> noise_texture = ResourceLoader::get_singleton()->load(noise);

		Dictionary cloud_parameters;
		cloud_parameters["speed"] = 0.005;
		cloud_parameters["brightness"] = 0.728;
		cloud_parameters["threshold"] = 1.102;
		cloud_parameters["fluffiness"] = 0.376;
		cloud_parameters["noise_texture"] = noise;
		mats.cloud_params = cloud_parameters;

		mats.clouds.set_shader_parameter("speed", cloud_parameters["speed"]);
		mats.clouds.set_shader_parameter("brightness", cloud_parameters["brightness"]);
		mats.clouds.set_shader_parameter("threshold", cloud_parameters["threshold"]);
		mats.clouds.set_shader_parameter("fluffiness", cloud_parameters["fluffiness"]);
		mats.clouds.set_shader_parameter("noise_texture", noise_texture);

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

		mats.atmosphere.set_next_pass(&mats.clouds);
		mats.type = M_ICE;
		save_params(mats, noise);
		return mats;
	}

	StellarBodyMaterial get_lava_material() {
		StellarBodyMaterial mats;
		String noise = "res://gfx/noises/planet_lava.tres";

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
		mats.body.set_shader_parameter("noise", ResourceLoader::get_singleton()->load(noise));

		mats.atmosphere.set_shader_parameter("color_1", color[5]);
		mats.atmosphere.set_shader_parameter("color_2", color[6]);
		mats.atmosphere.set_shader_parameter("alpha", 0.3);
		mats.atmosphere.set_shader_parameter("amount", 5.366);
		mats.atmosphere.set_shader_parameter("intensity", 0.167);
		mats.atmosphere.set_shader_parameter("emit", true);

		mats.type = M_LAVA;
		save_params(mats, noise);
		return mats;
	}

	StellarBodyMaterial get_gas_material() {
		StellarBodyMaterial mats;
		String noise = "res://gfx/noises/planet_gaseous.tres";

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
		mats.body.set_shader_parameter("noise", ResourceLoader::get_singleton()->load(noise));

		mats.atmosphere.set_shader_parameter("color_1", color[5]);
		mats.atmosphere.set_shader_parameter("color_2", color[6]);
		mats.atmosphere.set_shader_parameter("alpha", UtilityFunctions::randf_range(0.6, 0.8));
		mats.atmosphere.set_shader_parameter("amount", 4.5);
		mats.atmosphere.set_shader_parameter("intensity", 4.0);
		mats.atmosphere.set_shader_parameter("emit", false);

		mats.type = M_GAS;
		save_params(mats, noise);
		return mats;
	}

	StellarBodyMaterial get_sand_material() {
		StellarBodyMaterial mats;

		Array planet_textures = GC::get_files_in_dir("res://gfx/planet_textures/Arid", ".png");
		String texture = planet_textures.pick_random();

		mats.body.set_shader(simple_body_shader);
		mats.atmosphere.set_shader(atmosphere_shader);

		mats.body.set_shader_parameter("body_texture", ResourceLoader::get_singleton()->load(texture));
		mats.body.set_shader_parameter("brightness", 0.75);

		mats.atmosphere.set_shader_parameter("color_1", StellarBodyColors::get_color_html("958736"));
		mats.atmosphere.set_shader_parameter("color_2", StellarBodyColors::get_color_html("958736"));
		mats.atmosphere.set_shader_parameter("alpha", 0.513);
		mats.atmosphere.set_shader_parameter("amount", 4.5);
		mats.atmosphere.set_shader_parameter("intensity", 4.0);
		mats.atmosphere.set_shader_parameter("emit", false);

		mats.type = M_SAND;
		save_params(mats, "", texture, true);
		return mats;
	}

	StellarBodyMaterial get_no_atmosphere_material() {
		StellarBodyMaterial mats;
		String noise = "res://gfx/noises/planet_no_atmosphere.tres";

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
		mats.body.set_shader_parameter("noise", ResourceLoader::get_singleton()->load(noise));

		mats.type = M_NO_ATMOSPHERE;
		save_params(mats, noise);
		return mats;
	}
};
} //namespace GC
