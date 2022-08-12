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
	CInputMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	CCamera::GetInst()->Init();
}

void CCore::Progress()
{
	// Limit FPS
	if (CTimeMgr::GetInst()->LimitFPS(LIMIT_FPS))
	{
		// Manager Update
		CTimeMgr::GetInst()->Update();
		CInputMgr::GetInst()->Update();

		// Scene Update
		CSceneMgr::GetInst()->Update();

	
		//Collision Update
		//CCollisionMgr::GetInst()->Update();

		// Scene LateUpdate
		CCamera::GetInst()->Update();

		CSceneMgr::GetInst()->LateUpdate();

		/*if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::SPACE) == KEY_STATE::UP)
		{
			Vector2 Pos = CCamera::GetInst()->GetRealPos(Vector2(900.f, WINDOW_HEIGHT * 0.5f));
			CCamera::GetInst()->SetLookAt(Pos);
		}*/

		// Render
		Rectangle(m_Hbitdc, -1, -1, m_RC.right + 1, m_RC.bottom + 1);
		CSceneMgr::GetInst()->Render(m_Hbitdc);
		//CMapLineMgr::GetInst()->Render(m_Hbitdc);

		BitBlt(m_Hdc, 0, 0, m_RC.right, m_RC.bottom, m_Hbitdc, 0, 0, SRCCOPY);

		// Event
		CEventMgr::GetInst()->Update();
	}

}

void CCore::Release()
{
	// Release
	CSceneMgr::GetInst()->Release();
	CObjectMgr::GetInst()->Release();
	CResMgr::GetInst()->Release();
	CCamera::GetInst()->Release();
	CMapObjMgr::GetInst()->Release();

	// DestroyInst
	CTimeMgr::GetInst()->DestroyInst();
	CInputMgr::GetInst()->DestroyInst();
	CSceneMgr::GetInst()->DestroyInst();
	CCamera::GetInst()->DestroyInst();
	CObjectMgr::GetInst()->DestroyInst();
	CEventMgr::GetInst()->DestroyInst();
	CCollisionMgr::GetInst()->DestroyInst();
	CResMgr::GetInst()->DestroyInst();
	CPathMgr::GetInst()->DestroyInst();
	CMapObjMgr::GetInst()->DestroyInst();

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
	int iLineWidth = 2;

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, iLineWidth, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, iLineWidth, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, iLineWidth, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, iLineWidth, RGB(255, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::ORANGE] = CreatePen(PS_SOLID, iLineWidth, RGB(255, 165, 0));
	m_arrPen[(UINT)PEN_TYPE::PURPLE] = CreatePen(PS_SOLID, iLineWidth, RGB(255, 255, 0));



}


