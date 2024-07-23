shader_type spatial;

uniform sampler2D body_texture;
uniform bool use_color_mod = false;
uniform vec3 color_mod : source_color;

uniform float brightness = 1.0;

void fragment() {
    vec4 color = texture(body_texture, UV);
	if (use_color_mod) {
		color *= vec4(color_mod, 1.0);	
	}
	color *= brightness;
    ALBEDO = color.rgb;
}
