// Macros that make it easy to write UI code for Godot 4 entirely in a C++ GDExtension while developing the actual UI layout in the godot editor.
// Does this in a safe way without having to use gdscript or write hundreds of lines of boilerplate code like you normally do in a GDExtension.
// Any node in your UI that needs interaction with code gets registered as a GUI_NODE and then you can simply use BIND_NODE_PATH to bind that GUI_NODE to godot.

#include "godot_cpp/classes/base_button.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
// NOTE: These includes ^^^ are needed. clangd says they aren't used but it is wrong.
#include <godot_cpp/classes/engine.hpp>

#include "ForEachMacro.hpp"

namespace GC {

#define ERROR_INFO vformat("[%s:%s]: ", __FILE__, __LINE__)

/*
	Create a NodePath member with m_name and also create it's getter and setter functions.
	Using NodePath allows the use of get_node to get the path
	Since it is set via the editor the NodePath will always be valid and the editor will also auto update the path if the node is moved around the scene tree.
	So using a GUI_NODE alongside CHECK_GUI_NODE will effectively make it so using get_node will never return null and will always return the correct node.
*/
#define GUI_NODE(m_name)                                                                                                                                       \
	NodePath m_name;                                                                                                                                           \
	NodePath get_##m_name() const { return m_name; }                                                                                                           \
	void set_##m_name(NodePath path) { m_name = path; };

// Binds this member variable and it's getter/setter so it is selectable in the editor. Should be used alongside GUI_NODE
#define BIND_NODE_PATH(m_type, m_name, m_hint_type)                                                                                                            \
	ClassDB::bind_method(D_METHOD("get_" #m_name), &m_type::get_##m_name);                                                                                     \
	ClassDB::bind_method(D_METHOD("set_" #m_name, #m_name), &m_type::set_##m_name);                                                                            \
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, #m_name, PROPERTY_HINT_NODE_PATH_VALID_TYPES, #m_hint_type), "set_" #m_name, "get_" #m_name);

// Bind a simple callback method with no args. Make sure to also use CONNECT_CALLBACK in _ready so the method will actually run.
#define BIND_CALLBACK(m_class, m_method) ClassDB::bind_method(D_METHOD(#m_method), &m_class::m_method);

// Connect pressed signal callback of a button to a method
#define CONNECT_CALLBACK(m_button_path, m_method)                                                                                                              \
	BaseButton *m_method = get_node<BaseButton>(m_button_path);                                                                                                \
	m_method->connect("pressed", Callable(this, #m_method));

// Macro to check to make sure if a GUI_NODE is defined that it is also set in the editor so the game doesn't crash because you forgot to set
// the path. If you use this for each GUI_NODE nullptr checks when using get_node on the NodePath won't be needed as there will be a 100% chance the
// node will be valid since you set it directly in the editor and it lets you know if any are missing.
#define CHECK_GUI_NODE(m_name)                                                                                                                                 \
	if (m_name.is_empty())                                                                                                                                     \
		UtilityFunctions::printerr(ERROR_INFO, #m_name, " NodePath has not been connected in the inspector dock of the editor! This will cause crashes.");

/*
	Define the widgets in this node that have scripted behavior such as callbacks or any UI element that gets updated with code.
	Creates NodePath parameters with getters and setters for the class given the parameters name.
	Also creates a _ready function that checks if the NodePaths have properly been added to the editor and warns you for safety.
	If you need another _ready function for your class use _notification instead of _ready!
*/
#define WIDGETS(...)                                                                                                                                           \
	void _ready() override {                                                                                                                                   \
		if (Engine::get_singleton()->is_editor_hint())                                                                                                         \
			FOR_EACH(CHECK_GUI_NODE, __VA_OPT__(__VA_ARGS__, ))                                                                                                \
	}                                                                                                                                                          \
	FOR_EACH(GUI_NODE, __VA_OPT__(__VA_ARGS__, ))

/*
	Bind a callback function with no arguments to godot.

	Make sure to also call CONNECT_CALLBACKS in a NOTIFICATION_READY notification so the callback signals actually get created.
	Otherwise they just won't do anything and it'll fucking suck to debug :)

	Note that these 2 calls result in the same code:

	BIND_CALLBACK(PauseMenu, _on_resume_button_pressed)
	BIND_CALLBACK(PauseMenu, _on_main_menu_button_pressed)
	BIND_CALLBACK(PauseMenu, _on_quit_game_button_pressed)
	BIND_CALLBACK(PauseMenu, _on_load_button_pressed)

	CALLBACKS(PauseMenu, _on_resume_button_pressed, _on_main_menu_button_pressed, _on_quit_game_button_pressed, _on_load_button_pressed)
*/
#define CALLBACKS(m_class, ...) FOR_EACH_TWO(BIND_CALLBACK, m_class, __VA_OPT__(__VA_ARGS__, ))

/*
	Bind the getter and setter functions of a widget to a new editor property.
	Also takes in the class of the widget as an argument so PROPERTY_HINT_NODE_PATH_VALID_TYPES can be used to only allow selection of valid NodePath's

	You have to be very careful with these, if you type the callback function name wrong it just won't work but clangd and the compiler might not tell you.
	Then it will crash when you call in in game, ClassDB::bind_method kinda just works like that, so don't make typos :)

	Note that these 2 calls result in the same code:

	BIND_NODE_PATH(PauseMenu, button_quit, BaseButton)
	BIND_NODE_PATH(PauseMenu, button_load, BaseButton)

	BIND_WIDGETS(PauseMenu, PAIR(button_load, BaseButton), PAIR(button_quit, BaseButton))
*/
#define BIND_WIDGETS(m_class, ...) FOR_EACH_THREE(BIND_NODE_PATH, m_class, __VA_OPT__(__VA_ARGS__, ))

/*
Connect the pressed signal of a button to callback functions

Note that these 3 different calls all result in the same code:

CONNECT_CALLBACK(button_resume, _on_resume_button_pressed)
CONNECT_CALLBACK(button_main_menu, _on_main_menu_button_pressed)

CONNECT_CALLBACKS(PAIR(button_resume, _on_resume_button_pressed), PAIR(button_main_menu, _on_main_menu_button_pressed))

CONNECT_CALLBACKS(button_resume, _on_resume_button_pressed, button_main_menu, _on_main_menu_button_pressed)
*/
// TODO - Make it so this can be optionally automatically called in WIDGETS so it doesn't have to be hooked up seperately.
// Probably the way to do this is to pass the widget and it's callback in to WIDGETS as a PAIR and then checking if a PAIR is found in the FOR_EACH.
#define CONNECT_CALLBACKS(...) FOR_EACH_TWO_ARGS(CONNECT_CALLBACK, __VA_OPT__(__VA_ARGS__, ))

} //namespace GC