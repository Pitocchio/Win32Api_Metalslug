#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInst = nullptr;

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY_TYPE::TYPEEND_KEY; ++i)
	{
		m_vecKey.push_back(Key{ KEY_STATE::KEY_NONE, false });
	}
}

void CKeyMgr::Update()
{
	for (int i = 0; i < (int)KEY_TYPE::TYPEEND_KEY; ++i)
	{

		if (GetAsyncKeyState(m_arrVK[i]) & 0x8000)
		{
			if (m_vecKey[i].bPrev)
				m_vecKey[i].state = KEY_STATE::KEY_HOLD;
			else
				m_vecKey[i].state = KEY_STATE::KEY_DOWN;

			m_vecKey[i].bPrev = true;
		}
		else
		{
			if (m_vecKey[i].bPrev)
				m_vecKey[i].state = KEY_STATE::KEY_UP;
			else
				m_vecKey[i].state = KEY_STATE::KEY_NONE;

			m_vecKey[i].bPrev = false;
		}
	}
}

KEY_STATE CKeyMgr::GetKeyState(KEY_TYPE key) const
{
	return m_vecKey[(int)key].state;
}

/*

사용 방법
if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::SPACE) == KEY_STATE::KEY_DOWN)
		cout << "SPACE 입력!";

*/

