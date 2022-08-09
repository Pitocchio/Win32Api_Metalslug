#include "stdafx.h"
#include "ToolScene.h"

CToolScene::CToolScene()
{
}

CToolScene::~CToolScene()
{
}

void CToolScene::Enter()
{
	CStage* pStage = new CStage(OBJECT_TYPE::S_GROUND);
	CEventMgr::GetInst()->CreateObject(pStage, OBJECT_TYPE::S_GROUND);

	CCamera::GetInst()->SetLookAt(Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));

	
}

void CToolScene::Update()
{
	CScene::Update(); // Base Method

	if (CheckSceneChange()) // Check Scene Change
		return;

	ScrollMouse(); // Camera Moving by Mouse Position

	AddMapObject();

	
}

void CToolScene::Render(HDC hdc)
{
	CObjectMgr::GetInst()->Render(hdc);

	// Text - FPS
	SetTextAlign(hdc, TA_LEFT);

	TCHAR tch1[128] = {};
	swprintf_s(tch1, L"FPS : %.2f ",
		float(FPS));
	TextOut(hdc, 0, 0, tch1, _tcslen(tch1));

	// Text - DT
	TCHAR tch2[128] = {};
	swprintf_s(tch2, L"DT : %f ", DT);
	TextOut(hdc, 0, 15, tch2, _tcslen(tch2));


	// Text - World Cursor
	TCHAR tch3[128] = {};
	Vector2 temp1 = CCamera::GetInst()->GetRealPos(Vector2(m_pointMousePos.x, m_pointMousePos.y));
	swprintf_s(tch3, L"World Cursor Pos : %d, %d ", int(temp1.x), int(temp1.y));
	TextOut(hdc, 0, 30, tch3, _tcslen(tch3));


	// Text - Local Cursor
	TCHAR tch4[128] = {};
	swprintf_s(tch4, L"Local Cursor Pos : %d, %d ", m_pointMousePos.x, m_pointMousePos.y);
	TextOut(hdc, 0, 45, tch4, _tcslen(tch4));


	// Text - Info
	TCHAR tch5[256] = {};
	swprintf_s(tch5, L"['Q'  +  Mouse Click] : Line Point");
	TextOut(hdc, 0, 75, tch5, _tcslen(tch5));
	TCHAR tch6[256] = {};
	swprintf_s(tch6, L"['W' +  Mouse Click] : CameraCollider Y+");
	TextOut(hdc, 0, 90, tch6, _tcslen(tch6));
	TCHAR tch7[256] = {};
	swprintf_s(tch7, L"['E'  +  Mouse Click] : CameraCollider Y-");
	TextOut(hdc, 0, 105, tch7, _tcslen(tch7));
	TCHAR tch8[256] = {};
	swprintf_s(tch8, L"['R'  +  Mouse Click] : Camera Rock");
	TextOut(hdc, 0, 120, tch8, _tcslen(tch8));
	
}

void CToolScene::Exit()
{
	CObjectMgr::GetInst()->Release();
}

void CToolScene::ScrollMouse()
{
	GetCursorPos(&m_pointMousePos);
	ScreenToClient(CCore::GetInst()->GetMainHwnd(), &m_pointMousePos);

	Vector2 vTempPos = CCamera::GetInst()->GetLookAt();

	if ((-100.f <= m_pointMousePos.x && m_pointMousePos.x <= 15.f) 
		&& (0.f <= m_pointMousePos.y && m_pointMousePos.y <= WINDOW_HEIGHT))
	{
		vTempPos.x -= 300000.f * fDT;
	}
	else if ((WINDOW_WIDTH + 100.f >= m_pointMousePos.x && m_pointMousePos.x  >= WINDOW_WIDTH - 15.f)
		&& (0.f <= m_pointMousePos.y && m_pointMousePos.y <= WINDOW_HEIGHT))
	{
		vTempPos.x += 300000.f * fDT;
	}
	else if ((-100.f <= m_pointMousePos.y && m_pointMousePos.y <= 15.f) // Up
		&& (0.f <= m_pointMousePos.x && m_pointMousePos.x <= WINDOW_WIDTH))
	{
		vTempPos.y -= 300000.f * fDT;
	}
	else if ((WINDOW_HEIGHT + 100.f >= m_pointMousePos.y && m_pointMousePos.y >= WINDOW_HEIGHT - 15.f)
		&& (0.f <= m_pointMousePos.x && m_pointMousePos.x <= WINDOW_WIDTH))
	{
		vTempPos.y += 300000.f * fDT;
	}

	CCamera::GetInst()->SetLookAt(vTempPos);
}

bool CToolScene::CheckSceneChange()
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::ENTER) == KEY_STATE::KEY_DOWN)
	{
		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::GAME);
		return true;
	}
	else
	{
		return false;
	}
}

void CToolScene::AddMapObject()
{
	
	Vector2 vClickPos = Vector2(CCamera::GetInst()->GetRealPos(Vector2(m_pointMousePos.x, m_pointMousePos.y)).x,
								CCamera::GetInst()->GetRealPos(Vector2(m_pointMousePos.x, m_pointMousePos.y)).y);

	//mouse_event()
	//GetCursor()

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::Q) == KEY_STATE::KEY_HOLD) // Line Point
	{
		if (VK_LBUTTON)
		{
			cout << "Q\n";
		}

	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::W) == KEY_STATE::KEY_HOLD) // Camera - Y up
	{
		if (VK_LBUTTON)
		{
			cout << "W\n";
		}

	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::E) == KEY_STATE::KEY_HOLD) // Camera - Y down
	{
		if (VK_LBUTTON)
		{
			cout << "E\n";
		}

	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::R) == KEY_STATE::KEY_HOLD) // Camera - Rock
	{
		if (VK_LBUTTON)
		{
			cout << "R\n";
		}

	}

	

}

