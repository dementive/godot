#ifndef Colony_H
#define Colony_H

#include <godot_cpp/classes/object.hpp>

using namespace godot;

namespace GC {

class Colony : public Object {
	GDCLASS(Colony, Object);

private:
	uint8_t owner;
	uint32_t location;
	int population;
	Array structures;

	uint64_t id;
	inline static std::atomic<uint64_t> next_id = 0;

protected:
	static void _bind_methods();

public:
	Colony();
	~Colony();
};

} // namespace GC

#endif
