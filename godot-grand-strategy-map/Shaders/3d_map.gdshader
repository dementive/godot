shader_type spatial;
render_mode cull_back, depth_draw_never, depth_test_disabled;

//#define SHOW_PROVINCE_MAP
//#define SHOW_LOOKUP_TEXTURE

uniform sampler2D texture_albedo : source_color, filter_linear;
uniform sampler2D lookup_texture : source_color, filter_nearest;
uniform sampler2D color_texture : source_color, filter_nearest;
uniform vec4 selected_area: source_color;

bool is_same_color(vec3 a, vec3 b) {
	vec3 diff = abs(a - b);
	return  diff.r < 0.000001 &&  diff.g < 0.000001 &&  diff.b < 0.000001;
}

void fragment() {
	vec4 lookup_uv = texture(lookup_texture, UV);
	ALBEDO = texture(color_texture, vec2(lookup_uv.x, lookup_uv.y)).rgb;

	for(int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			vec4 check_color = texture(lookup_texture, vec2(UV.x + (1024.0 * float(i)), UV.y  + (1024.0 * float(j))));
			if(!is_same_color(check_color.rgb, lookup_uv.rgb)){
				ALBEDO = vec3(1.0);
			}
		}
	}

	//For selected area
	if(is_same_color(lookup_uv.rgb, selected_area.rgb)){
		ALBEDO = vec3(1.0);
	}

#ifdef SHOW_PROVINCE_MAP
	vec4 albedo_tex = texture(texture_albedo, UV);
	ALBEDO = albedo_tex.rgb;
#endif

#ifdef SHOW_LOOKUP_TEXTURE
	ALBEDO = lookup_uv.rgb;
#endif

}
