#include "godot_cpp/classes/file_access.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/variant/string.hpp"
#include <godot_cpp/classes/object.hpp>

using namespace godot;

namespace GC {

class SaveManager : public Object {
	GDCLASS(SaveManager, Object);

private:
	Ref<FileAccess> file;
	String file_path;
	String password;

	~SaveManager() {};

protected:
	static void _bind_methods() {};

public:
	void init(String path, String input_password) {
		file_path = path;
		password = input_password;
	}

	void clear() {
		FileAccess file;
		String file_path;
		String password;
	}

	int open_file(FileAccess::ModeFlags access) {
		file = FileAccess::open_encrypted_with_pass(file_path, access, password);
		return file == nullptr ? FileAccess::get_open_error() : OK;
	}

	void close_file() { file->close(); }

	template <typename T> void serialize(T object) { object->serialize(file); }

	template <typename T> void deserialize(T object) { object->deserialize(file); }
};

} //namespace GC
