#include "godot_cpp/variant/packed_string_array.hpp"
#include <godot_cpp/classes/dir_access.hpp>

using namespace godot;

namespace GC {

inline PackedStringArray get_files_in_dir(String directory, String file_type) {
	// Returns array with full paths to files of a certain type in a directory
	Ref<DirAccess> dir = DirAccess::open(directory);
	PackedStringArray textures = dir->get_files();

	if (textures.size() == 0) {
		return textures;
	}

	PackedStringArray filtered_files;

	for (int i = 0; i < textures.size(); ++i) {
		String texture = textures[i];

		if (texture.ends_with(file_type)) {
			filtered_files.push_back(directory + "/" + texture);
		}
	}

	return filtered_files;
}

} //namespace GC