// NOTE: Shader automatically converted from Godot Engine 4.2.2.stable's StandardMaterial3D.

shader_type spatial;
render_mode blend_mix,depth_draw_opaque,cull_back,diffuse_burley,specular_schlick_ggx;
uniform vec4 albedo : source_color = vec4(1,1,1,1);
uniform sampler2D texture_albedo : source_color,filter_linear_mipmap,repeat_enable;
uniform float point_size : hint_range(0,128);
uniform float roughness : hint_range(0,1);
uniform float specular : hint_range(0,1);
uniform float metallic : hint_range(0,1);
uniform sampler2D texture_normal : hint_roughness_normal,filter_linear_mipmap,repeat_enable;
uniform float normal_scale : hint_range(-16,16) = 1;

void fragment() {
	vec4 albedo_tex = texture(texture_albedo,UV);
	
	ALBEDO = albedo.rgb * albedo_tex.rgb;
	METALLIC = metallic;
	ROUGHNESS = roughness;
	SPECULAR = specular;
	NORMAL_MAP = texture(texture_normal,UV).rgb;
	NORMAL_MAP_DEPTH = normal_scale;
}
