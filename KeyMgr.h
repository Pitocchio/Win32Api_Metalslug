#pragma once

class CKeyMgr
{
	SINGLETONE(CKeyMgr)

public: // Lifecycle
	void Init();
	void Update();

public: // Methods
	KEY_STATE GetKeyState(KEY_TYPE key) const;

private: // Variables
	vector<Key> m_vecKey;

	int m_arrVK[(int)KEY_TYPE::TYPEEND_KEY] =
	{
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 
		VK_SPACE, VK_ESCAPE, VK_RETURN,
		'Q', 'W', 'E', 'R',
		'A', 'S', 'D', 'F',
		'Z', 'X', 'C', 'V',
		'U', 'I', 'O', 'P',
	};
};

