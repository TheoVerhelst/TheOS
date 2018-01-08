#ifndef KEY_HPP
#define KEY_HPP

/// Enumeration of all keys on a standard US QWERTY keyboard, plus some extra keys,
/// such as a key on the left of the Z key.
enum class Key
{
	Unknown = 0, ///< Unhandled key
	A,           ///< The A key
	B,           ///< The B key
	C,           ///< The C key
	D,           ///< The D key
	E,           ///< The E key
	F,           ///< The F key
	G,           ///< The G key
	H,           ///< The H key
	I,           ///< The I key
	J,           ///< The J key
	K,           ///< The K key
	L,           ///< The L key
	M,           ///< The M key
	N,           ///< The N key
	O,           ///< The O key
	P,           ///< The P key
	Q,           ///< The Q key
	R,           ///< The R key
	S,           ///< The S key
	T,           ///< The T key
	U,           ///< The U key
	V,           ///< The V key
	W,           ///< The W key
	X,           ///< The X key
	Y,           ///< The Y key
	Z,           ///< The Z key
	LeftOfZ,     ///< The key at left of the Z key, not always present on US QWERTY keyboards
	Num0,        ///< The 0 key
	Num1,        ///< The 1 key
	Num2,        ///< The 2 key
	Num3,        ///< The 3 key
	Num4,        ///< The 4 key
	Num5,        ///< The 5 key
	Num6,        ///< The 6 key
	Num7,        ///< The 7 key
	Num8,        ///< The 8 key
	Num9,        ///< The 9 key
	Escape,      ///< The escape key
	LControl,    ///< The left control key
	LShift,      ///< The left shift key
	LAlt,        ///< The left alt key
	LSystem,     ///< The left OS specific key
	RControl,    ///< The right control key
	RShift,      ///< The right shift key
	RAlt,        ///< The right alt key
	RSystem,     ///< The right OS specific key
	Menu,        ///< The menu key
	LBracket,    ///< The [ key
	RBracket,    ///< The ] key
	SemiColon,   ///< The ; key
	Comma,       ///< The , key
	Period,      ///< The . key
	Quote,       ///< The ' key
	Slash,       ///< The / key
	BackSlash,   ///< The \ key
	BackTick,    ///< The ` key
	Equal,       ///< The = key
	Dash,        ///< The - key
	Space,       ///< The space key
	Return,      ///< The return key
	BackSpace,   ///< The backspace key
	Tab,         ///< The tabulation key
	CapsLock,    ///< The caps lock key
	PageUp,      ///< The page up key
	PageDown,    ///< The page down key
	ScrollLock,  ///< The scroll lock key,
	End,         ///< The end key
	Home,        ///< The home key
	Insert,      ///< The insert key
	Delete,      ///< The delete key
	PrintScreen, ///< The print screen key
	Left,        ///< The left arrow key
	Right,       ///< The right arrow key
	Up,          ///< The up arrow key
	Down,        ///< The Down arrow key
	Numpad0,     ///< The numpad 0 key
	Numpad1,     ///< The numpad 1 key
	Numpad2,     ///< The numpad 2 key
	Numpad3,     ///< The numpad 3 key
	Numpad4,     ///< The numpad 4 key
	Numpad5,     ///< The numpad 5 key
	Numpad6,     ///< The numpad 6 key
	Numpad7,     ///< The numpad 7 key
	Numpad8,     ///< The numpad 8 key
	Numpad9,     ///< The numpad 9 key
	NumpadLock,  ///< The numpad lock key
	NumpadPeriod,///< The numpad . key
	NumpadReturn,///< The numpad return key
	Add,         ///< The + key
	Subtract,    ///< The - key
	Multiply,    ///< The * key
	Divide,      ///< The / key
	F1,          ///< The F1 key
	F2,          ///< The F2 key
	F3,          ///< The F3 key
	F4,          ///< The F4 key
	F5,          ///< The F5 key
	F6,          ///< The F6 key
	F7,          ///< The F7 key
	F8,          ///< The F8 key
	F9,          ///< The F9 key
	F10,         ///< The F10 key
	F11,         ///< The F11 key
	F12,         ///< The F12 key
	F13,         ///< The F13 key
	F14,         ///< The F14 key
	F15,         ///< The F15 key
	Pause,       ///< The pause key
	KeyNumber    ///< The total number of keyboard keys
};

struct KeyEvent
{
	Key key;
	bool pressed;
};



#endif // KEY_HPP
