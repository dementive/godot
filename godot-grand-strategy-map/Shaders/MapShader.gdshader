shader_type canvas_item;

uniform sampler2D lookup_texture : source_color, filter_nearest;
uniform sampler2D color_texture : source_color, filter_nearest;
uniform vec4 selected_area : source_color;

bool is_same_color(vec3 a, vec3 b) {
	vec3 diff = abs(a - b);
	return  diff.r < 0.000001 &&  diff.g < 0.000001 &&  diff.b < 0.000001;
}

void fragment() {
	vec4 lookup_uv = texture(lookup_texture, UV);
	COLOR = texture(color_texture, vec2(lookup_uv.x, lookup_uv.y));

	//For selected area
	if(is_same_color(lookup_uv.rgb, selected_area.rgb)){
		COLOR = vec4(1.0);
	}
}