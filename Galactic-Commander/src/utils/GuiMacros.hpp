#include "godot_cpp/classes/base_button.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
// NOTE: These includes ^^^ are needed. clangd says they aren't used but it is wrong.

#include "ForEachMacro.hpp"

namespace GC {

#define ERROR_INFO vformat("[%s:%s]: ", __FILE__, __LINE__)

// Create a NodePath member with m_name and also create it's getter and setter functions.
#define GUI_NODE(m_name)                                                                                                                             \
	NodePath m_name;                                                                                                                                 \
	NodePath get_##m_name() const { return m_name; }                                                                                                 \
	void set_##m_name(NodePath path) { m_name = path; };

// Bind a NodePath member with m_name, m_type, and m_hint_type. Binds this member variable and it's getter/setter so it is
// selectable in the editor. Should be used alongside GUI_NODE
// TODO - REMOVE THIS
#define BIND_NODE_PATH_PROPERTY(m_name, m_type, m_hint_type)                                                                                         \
	ClassDB::bind_method(D_METHOD("get_" #m_name), &m_type::get_##m_name);                                                                           \
	ClassDB::bind_method(D_METHOD("set_" #m_name, #m_name), &m_type::set_##m_name);                                                                  \
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, #m_name, PROPERTY_HINT_NODE_PATH_VALID_TYPES, #m_hint_type), "set_" #m_name, "get_" #m_name);

// Binds this member variable and it's getter/setter so it is selectable in the editor. Should be used alongside GUI_NODE
#define BIND_NODE_PATH(m_type, m_name, m_hint_type)                                                                                                  \
	ClassDB::bind_method(D_METHOD("get_" #m_name), &m_type::get_##m_name);                                                                           \
	ClassDB::bind_method(D_METHOD("set_" #m_name, #m_name), &m_type::set_##m_name);                                                                  \
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, #m_name, PROPERTY_HINT_NODE_PATH_VALID_TYPES, #m_hint_type), "set_" #m_name, "get_" #m_name);

// Bind a simple callback method with no args. Make sure to also use CONNECT_CALLBACK in _ready so the method will actually run.
#define BIND_CALLBACK(m_class, m_method) ClassDB::bind_method(D_METHOD(#m_method), &m_class::m_method);

// Connect pressed signal callback of a button to a method
#define CONNECT_CALLBACK(m_button_path, m_method)                                                                                                    \
	BaseButton *m_method = get_node<BaseButton>(m_button_path);                                                                                      \
	m_method->connect("pressed", Callable(this, #m_method));

// Macro to check to make sure if a GUI_NODE is defined that it is also set in the editor so the game doesn't crash because you forgot to set
// the path. If you use this for each GUI_NODE nullptr checks when using get_node on the NodePath won't be needed as there will be a 100% chance the
// node will be valid since you set it directly in the editor and it lets you know if any are missing.
#define CHECK_GUI_NODE(m_name)                                                                                                                       \
	if (m_name.is_empty())                                                                                                                           \
		UtilityFunctions::printerr(                                                                                                                  \
				ERROR_INFO, #m_name, " NodePath has not been connected in the inspector dock of the editor! This will cause crashes.");

#define WIDGETS(...) FOR_EACH(GUI_NODE, __VA_OPT__(__VA_ARGS__, ))

// TODO - CHECK_WIDGETS should be inside of WIDGETS somehow. Could maybe create a custom _ready notification function to run it...hmmm....
#define CHECK_WIDGETS(...) FOR_EACH(CHECK_GUI_NODE, __VA_OPT__(__VA_ARGS__, ))

#define CALLBACKS(m_class, ...) FOR_EACH_TWO(BIND_CALLBACK, m_class, __VA_OPT__(__VA_ARGS__, ))

#define BIND_WIDGETS(m_class, ...) FOR_EACH_THREE(BIND_NODE_PATH, m_class, __VA_OPT__(__VA_ARGS__, ))

#define CONNECT_CALLBACKS(...) FOR_EACH_TWO_ARGS(CONNECT_CALLBACK, __VA_OPT__(__VA_ARGS__, ))

} //namespace GC