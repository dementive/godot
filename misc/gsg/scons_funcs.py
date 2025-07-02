import os

# Ideally this file would be in the gsg repo but the python environment scons runs in makes it impossible to import it there.

# Enable C++23
def set_cpp_standard(env):
	if not env.msvc:
		env["CXXFLAGS"].remove("-std=gnu++17")
		env["CXXFLAGS"].insert(0, "-std=gnu++23")
	else:
		env["CXXFLAGS"].remove("/std:c++17")
		env["CXXFLAGS"].insert(0, "/std:c++23")
		env["CXXFLAGS"].insert(0, "/Zc:preprocessor")

def enable_all_warnings(env):
	if env.debug_features:
		env.Append(
			CXXFLAGS=[
				"-Wall",
				"-Wextra",
				"-Wshadow",
				# Disable warnings from GDCLASS stuff
				"-Wno-unused-parameter",
			]
		)


		if using_clang(env):
			env.Append(CXXFLAGS=["-glldb"])
			env.Append(CXXFLAGS=["-Wimplicit-fallthrough", "-Wno-deprecated-volatile", "-Wno-missing-designated-field-initializers",])
			env.Append(CXXFLAGS=["-pedantic", "-Wno-nested-anon-types", "-Wno-gnu-anonymous-struct", "-Wno-extra-semi"])
			env.Append(CPPDEFINES=["_LIBCPP_REMOVE_TRANSITIVE_INCLUDES"])

		if using_gcc(env):
			env.Append(
				CXXFLAGS=["-Wno-volatile"]
			)

def set_flecs_defines(env):
	env.Append(CPPDEFINES=[
		"FLECS_CUSTOM_BUILD",
		"FLECS_CPP", "FLECS_CPP_NO_AUTO_REGISTRATION", "FLECS_CPP_NO_ENUM_REFLECTION",
		# "FLECS_PARSER", "FLECS_SCRIPT",
		"FLECS_SYSTEM", "FLECS_TIMER", "FLECS_PIPELINE", "FLECS_META",
		"FLECS_STATS", "FLECS_LOG"
	])
	if env.debug_features:
		env.Append(CPPDEFINES=["FLECS_KEEP_ASSERT", "FLECS_NO_ALWAYS_INLINE"])

def find_header_dirs():
	hpp_dirs = set()
	for root, _, files in os.walk("."):
		if any(file.endswith(".hpp") or file.endswith(".h") for file in files):
			hpp_dirs.add(root)
	return list(hpp_dirs)

def find_cpp_files(env):
	sources = []
	for dirpath, _, _ in os.walk("."):
		cpp_files = env.Glob(os.path.join(dirpath, "*.cpp"))
		sources.extend(cpp_files)
	return env.Flatten(sources)

def using_clang(env):
	return "clang" in os.path.basename(env["CC"])

def using_gcc(env):
	return "gcc" in os.path.basename(env["CC"])
