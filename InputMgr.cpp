#include "stdafx.h"
#include "InputMgr.h"

CInputMgr* CInputMgr::m_pInst = nullptr;



void CInputMgr::Init()
{
	// Key
	for (int i = 0; i < (int)KEY_TYPE::TYPEEND_KEY; ++i)
	{
		m_vecKey.push_back(Key{ KEY_STATE::NONE, false });
	}

	// Mouse
	for (int i = 0; i < (int)MOUSE_TYPE::TYPEEND_MOUSE; ++i)
	{
		m_vecMouse.push_back(Mouse{ MOUSE_STATE::NONE, false });
	}

	bBlock = false;
}


void CInputMgr::Update()
{
	if (!bBlock)
	{
		HWND hwnd;
		
		hwnd = GetFocus(); // 현재 이 윈도우가 포커싱 되어있는지 여부를 bool 값으로 반환

		if (hwnd)
		{

			// Key
			for (int i = 0; i < (int)KEY_TYPE::TYPEEND_KEY; ++i)
			{
				if (GetAsyncKeyState(m_arrKey[i]) & 0x8000)
				{
					if (m_vecKey[i].bPrev)
						m_vecKey[i].state = KEY_STATE::HOLD;
					else
						m_vecKey[i].state = KEY_STATE::DOWN;

					m_vecKey[i].bPrev = true;
				}
				else
				{
					if (m_vecKey[i].bPrev)
						m_vecKey[i].state = KEY_STATE::UP;
					else
						m_vecKey[i].state = KEY_STATE::NONE;

					m_vecKey[i].bPrev = false;
				}
			}


			// Mouse

			GetCursorPos(&m_ptMousePos);
			ScreenToClient(CCore::GetInst()->GetMainHwnd(), &m_ptMousePos);


			for (int i = 0; i < (int)MOUSE_TYPE::TYPEEND_MOUSE; ++i)
			{
				if (GetAsyncKeyState(m_arrMouse[i]) & 0x8000)
				{
					if (m_vecMouse[i].bPrev)
						m_vecMouse[i].state = MOUSE_STATE::HOLD;
					else
						m_vecMouse[i].state = MOUSE_STATE::DOWN;

					m_vecMouse[i].bPrev = true;
				}
				else
				{
					if (m_vecMouse[i].bPrev)
						m_vecMouse[i].state = MOUSE_STATE::UP;
					else
						m_vecMouse[i].state = MOUSE_STATE::NONE;

					m_vecMouse[i].bPrev = false;
				}
			}
		}
	}
	else
	{
		int k = 9099;
	}
}

void CInputMgr::BlockInput()
{
	m_ptMousePos = POINT{0,0};
	bBlock = true; 
}

void CInputMgr::UnblockInput()
{
	bBlock = false;
}
KEY_STATE CInputMgr::GetKeyState(KEY_TYPE key) const
{
	return m_vecKey[(int)key].state;
}

MOUSE_STATE CInputMgr::GetMouseState(MOUSE_TYPE mouse) const
{
	return m_vecMouse[(int)mouse].state;
}




/*

사용 방법
if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::SPACE) == KEY_STATE::DOWN)
		cout << "SPACE 입력!";

*/








