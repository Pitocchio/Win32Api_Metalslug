#include "stdafx.h"
#include "Core.h"

CCore* CCore::m_pInst = nullptr;

void CCore::Init(HWND hWnd)
{
	// Window and Double Buffering Set
	m_RC = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	m_Hwnd = hWnd;
	m_Hdc = GetDC(m_Hwnd);
	AdjustWindowRect(&m_RC, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(hWnd, nullptr, 100, 100, (m_RC.right - m_RC.left), (m_RC.bottom - m_RC.top), 0);
	m_Hbitmap = CreateCompatibleBitmap(m_Hdc, m_RC.right, m_RC.bottom);
	m_Hbitdc = CreateCompatibleDC(m_Hdc);
	HBITMAP hOldbit = (HBITMAP)SelectObject(m_Hbitdc, m_Hbitmap);
	DeleteObject(hOldbit);

	// GDI Object set
	CreateBrushPen();

	// Manager Init
	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	CCamera::GetInst()->Init();
	CLineMgr::GetInst()->Init();
}

void CCore::Progress()
{
	// Manager Update
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();

	// Scene Update
	CSceneMgr::GetInst()->Update();

	

	// Collision Update
	//CCollisionMgr::GetInst()->Update();

	// Scene LateUpdate
	CCamera::GetInst()->Update();

	CSceneMgr::GetInst()->LateUpdate();

	/*if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::SPACE) == KEY_STATE::KEY_UP)
	{
		Vector2 Pos = CCamera::GetInst()->GetRealPos(Vector2(900.f, WINDOW_HEIGHT * 0.5f));
		CCamera::GetInst()->SetLookAt(Pos);
	}*/

	// Render
	Rectangle(m_Hbitdc, -1, -1, m_RC.right + 1, m_RC.bottom + 1);
	CSceneMgr::GetInst()->Render(m_Hbitdc);
	CLineMgr::GetInst()->Render(m_Hbitdc);

	BitBlt(m_Hdc, 0, 0, m_RC.right, m_RC.bottom, m_Hbitdc, 0, 0, SRCCOPY);

	// Event
	CEventMgr::GetInst()->Update();


}

void CCore::Release()
{
	// Release
	CSceneMgr::GetInst()->Release();
	CObjectMgr::GetInst()->Release();
	CResMgr::GetInst()->Release();
	CCamera::GetInst()->Release();
	CLineMgr::GetInst()->Release();

	// DestroyInst
	CTimeMgr::GetInst()->DestroyInst();
	CKeyMgr::GetInst()->DestroyInst();
	CSceneMgr::GetInst()->DestroyInst();
	CObjectMgr::GetInst()->DestroyInst();
	CEventMgr::GetInst()->DestroyInst();
	CCollisionMgr::GetInst()->DestroyInst();
	CResMgr::GetInst()->DestroyInst();
	CPathMgr::GetInst()->DestroyInst();
	CCamera::GetInst()->DestroyInst();
	CLineMgr::GetInst()->DestroyInst();

	// Delete GDI obj (except Hollow)
	for (int i = 0; i < (UINT)PEN_TYPE::TYPEEND_PEN; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

}

void CCore::CreateBrushPen()
{
	// Hollow Brush (윈도우 자체 제공이라 delete 필요 X)
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}


