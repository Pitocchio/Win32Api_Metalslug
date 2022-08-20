#pragma once

class CInputMgr
{
	SINGLETONE(CInputMgr)

public: // Lifecycle
	void Init();
	void Update();

public: 
	void BlockInput();
	void UnblockInput();

	// Key Methods
	KEY_STATE GetKeyState(KEY_TYPE key) const;

	// Mouse Methods
	MOUSE_STATE GetMouseState(MOUSE_TYPE mouse) const;

	POINT GetMousePos() const { return m_ptMousePos; } 

private:

	// Key Variables
	vector<Key> m_vecKey;
	int m_arrKey[(int)KEY_TYPE::TYPEEND_KEY] =
	{	VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4,
		VK_NUMPAD5, VK_NUMPAD6,VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,

		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_SPACE, VK_ESCAPE, VK_RETURN,

		VK_CONTROL, VK_SHIFT,

		'Q', 'W', 'E', 'R', 'T', 'Y',
		'A', 'S', 'D', 'F',
		'Z', 'X', 'C', 'V',
		'U', 'I', 'O', 'P',
	};

	// Mouse Variables
	vector<Mouse> m_vecMouse;

	int m_arrMouse[(int)MOUSE_TYPE::TYPEEND_MOUSE] =
	{
		VK_LBUTTON, VK_MBUTTON, VK_RBUTTON
	};

	POINT m_ptMousePos;

	bool bBlock;
};

