namespace GC {

// Create a NodePath member with m_name and also create it's getter and setter functions.
#define GUI_NODE(m_name)                                                                                                                             \
	NodePath m_name;                                                                                                                                 \
	NodePath get_##m_name() const { return m_name; }                                                                                                 \
	void set_##m_name(NodePath path) { m_name = path; };

// Bind a NodePath member with m_name, m_type, and m_hint_type. Binds this member variable and it's getter/setter so it is
// selectable in the editor. Should be used alongside GUI_NODE
#define BIND_NODE_PATH_PROPERTY(m_name, m_type, m_hint_type)                                                                                         \
	ClassDB::bind_method(D_METHOD("get_" #m_name), &m_type::get_##m_name);                                                                           \
	ClassDB::bind_method(D_METHOD("set_" #m_name, #m_name), &m_type::set_##m_name);                                                                  \
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, #m_name, PROPERTY_HINT_NODE_PATH_VALID_TYPES, #m_hint_type), "set_" #m_name, "get_" #m_name);

} //namespace GC