extends Object

func get_color(r: float, g: float, b: float, offset: float = 0.1) -> Color:
	return Color(
		randf_range(r-offset, r+offset),
		randf_range(g-offset, g+offset),
		randf_range(b-offset, b+offset)
	)

func get_color_html(html_color: String, offset: float = 0.1) -> Color:
	var color: Color = Color.html(html_color)
	color.r = randf_range(color.r-offset, color.r+offset)
	color.g = randf_range(color.g-offset, color.g+offset)
	color.b = randf_range(color.b-offset, color.b+offset)
	return color


func get_planet_color_array(c1: Color, c2: Color, c3: Color, c4: Color, c5: Color, c6: Color, c7: Color) -> PackedColorArray:
	# Colors 1-5 are the planet base color.
	# Colors 6-7 are the planet atmosphere color.
	var color_array: PackedColorArray = PackedColorArray()
	color_array.append(c1)
	color_array.append(c2)
	color_array.append(c3)
	color_array.append(c4)
	color_array.append(c5)
	color_array.append(c6)
	color_array.append(c7)
	return color_array

func get_base_color_array(c1: Color, c2: Color, c3: Color, c4: Color, c5: Color) -> PackedColorArray:
	# Colors 1-5 are the planet base color.
	var color_array: PackedColorArray = PackedColorArray()
	color_array.append(c1)
	color_array.append(c2)
	color_array.append(c3)
	color_array.append(c4)
	color_array.append(c5)
	return color_array

func get_lava_planet_colors() -> Array[PackedColorArray]:
	return [
		get_planet_color_array(
			get_color_html("d86a00", 0.175),
			get_color(0.89, 0.28, 0.25),
			get_color(0.68, 0.18, 0.27),
			get_color(0.32, 0.2, 0.25),
			get_color(0.24, 0.16, 0.21),
			get_color(0.16, 0.06, 0),
			get_color(1, 0.55, 0.15)
		),
		get_planet_color_array(
			get_color(1, 0.52, 0.2),
			get_color(0.89, 0.28, 0.25),
			get_color(0.68, 0.18, 0.27),
			get_color(0.32, 0.2, 0.25),
			get_color(0.24, 0.16, 0.21),
			get_color(0.6, 0.6, 0),
			get_color(0.95, 0.55, 0.15)
		)
	]

func get_sand_planet_colors() -> Array[PackedColorArray]:
	var regular_sand: PackedColorArray = get_planet_color_array(
			get_color_html("f2be6e"),
			get_color_html("c16d34"),
			get_color_html("4d3119"),
			get_color_html("efd6c6"),
			get_color_html("332921"),
			get_color_html("7a502d"),
			get_color_html("cf9363")
		)
	var darker_sand = regular_sand
	darker_sand[0] = get_color_html("362507")
	darker_sand[6] = get_color_html("94623a")

	return [
		get_planet_color_array(
			get_color(0.98, 0.88, 0.73),
			get_color(0.81, 0.65, 0.53),
			get_color(0.57, 0.38, 0.22),
			get_color(0.47, 0.32, 0.21),
			get_color(0.33, 0.27, 0.22),
			get_color(0.55, 0.39, 0.23),
			get_color(0.88, 0.68, 0.51)
		),
		regular_sand,
		darker_sand
	]

func get_terrestrial_planet_colors() -> Array[PackedColorArray]:
	return [
		get_planet_color_array(
			get_color_html("0072e2", 0.25),
			get_color(1, 0.94, 0.76, 0.2),
			get_color_html("f7e6cd", 0.15),
			get_color(0.27, 0.62, 0.42, 0.15),
			get_color(1, 1, 1),
			get_color(0, 0.12, 0.27),
			get_color(0.63, 0.78, 1)
		)
	]

func get_gas_planet_colors() -> Array[PackedColorArray]:
	return [
		get_planet_color_array(
			get_color(0.78, 0.55, 0.23),
			get_color(0.56, 0.38, 0.30),
			get_color(0.83, 0.61, 0.49),
			get_color(0.65, 0.61, 0.53),
			get_color(0.25, 0.27, 0.21),
			get_color(0.4, 0.26, 0.2),
			get_color(0.76, 0.56, 0.47)
		),
		get_planet_color_array(
			get_color_html("8c9eb0"),
			get_color_html("596e98"),
			get_color_html("525b65"),
			get_color_html("4046ae"),
			get_color_html("404436"),
			get_color_html("003671"),
			get_color_html("005fcd"),
		),
		get_planet_color_array(
			get_color_html("47108a"),
			get_color_html("594998"),
			get_color_html("486d86"),
			get_color_html("4046ae"),
			get_color_html("320049"),
			get_color_html("003671"),
			get_color_html("4e035e"),
		),
		get_planet_color_array(
			get_color_html("bf7056"),
			get_color_html("90614d"),
			get_color_html("d39c7e"),
			get_color_html("a79c86"),
			get_color_html("70251e"),
			get_color_html("674127"),
			get_color_html("62222b"),
		),
		get_planet_color_array(
			get_color_html("50a088"),
			get_color_html("388043"),
			get_color_html("1e3770"),
			get_color_html("092a1b"),
			get_color_html("254d24"),
			get_color_html("315800"),
			get_color_html("5a9248"),
		)
	]

func get_ice_planet_colors() -> Array[PackedColorArray]:
	return [
		get_planet_color_array(
			get_color(0.31, 0.61, 0.78),
			get_color(0.47, 0.68, 0.81),
			get_color(0.62, 0.75, 0.83),
			get_color(0.93, 0.94, 0.97),
			get_color(0.82, 0.85, 0.89),
			get_color(0.11, 0.29, 0.38),
			get_color(0.63, 0.82, 0.94)
		),
		get_planet_color_array(
			get_color_html("1c4962"),
			get_color_html("4c7e9c"),
			get_color_html("6d94ad"),
			get_color_html("95a3d2"),
			get_color_html("dce2e9"),
			get_color(0.11, 0.29, 0.38),
			get_color(0.63, 0.82, 0.94)
		),
		get_planet_color_array(
			get_color_html("316878"),
			get_color_html("4c7e9c"),
			get_color_html("6d94ad"),
			get_color_html("ffffff"),
			get_color_html("161b22"),
			get_color(0.11, 0.29, 0.38),
			get_color(0.63, 0.82, 0.94)
		),
	]

func get_no_atmosphere_colors() -> Array[PackedColorArray]:
	return [
		get_base_color_array(
			get_color(0.19, 0.18, 0.18),
			get_color(0.58, 0.56, 0.55),
			get_color(0.85, 0.85, 0.84),
			get_color(0.94, 0.94, 0.94),
			get_color(0.76, 0.76, 0.74)
		),
		get_base_color_array(
			get_color_html("741905"),
			get_color_html("955f6b"),
			get_color_html("695557"),
			get_color_html("bf7356"),
			get_color_html("bd4b52")
		),
		get_base_color_array(
			get_color_html("2a2a2a"),
			get_color_html("715737"),
			get_color_html("4c3d2d"),
			get_color_html("623423"),
			get_color_html("4a161a")
		)
	]

func get_star_colors() -> Dictionary:
	return {
		# Red Dwarf Star
		"red": get_planet_color_array(
			get_color_html("a30016"),
			get_color_html("260000"),
			get_color_html("61001b"),
			get_color_html("870e00"),
			get_color_html("923300"),
			get_color_html("0b0b0b"),
			get_color_html("510700")
		),
		# Sun-like star
		"yellow": get_planet_color_array(
			get_color(0.44, 0.13, 0),
			get_color(1, 0.4, 0),
			get_color(1, 0.64, 0.25),
			get_color(1, 0.4, 0),
			get_color(1, 0.64, 0.25),
			get_color(0.44, 0.13, 0),
			get_color(1, 0.64, 0.25)
		),
		# White star
		"white": get_planet_color_array(
			get_color_html("ffffff"),
			get_color_html("9f9f9f"),
			get_color_html("1e1e1e"),
			get_color_html("e8e8e8"),
			get_color_html("ffe5db"),
			get_color_html("0b0b0b"),
			get_color_html("a3a3a3")
		),
		# Blue star
		"blue": get_planet_color_array(
			get_color(0.2, 0.2, 0.8),
			get_color(0.1, 0.1, 0.9),
			get_color(0.3, 0.3, 0.7),
			get_color(0.15, 0.15, 0.85),
			get_color(0.25, 0.25, 0.75),
			get_color(0.1, 0.1, 0.95),
			get_color(0.15, 0.15, 0.9)
		)
	}
