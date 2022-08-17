#include "stdafx.h"
#include "AniToolScene2.h"

CAniToolScene2::CAniToolScene2()
{

}

CAniToolScene2::~CAniToolScene2()
{

}

void CAniToolScene2::Enter()
{
	// = L"mapdata\\OriginData.bin"; 

	CCamera::GetInst()->SetLookAt(Vector2(0.f, 0.f));

	//m_pAnimator = new CAnimator2D();
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\PISTOL_BASIC_MOVE_ST.bmp"); // 애니메이션 테스트 (애니메이션 파일 불러옴)
	//m_pAnimator->CreateAnimation(L"PISTOL_BASIC_MOVE_ST", m_pTex, Vector2(0.f, 0.f), Vector2(39.1f, 64.f), Vector2(39.1f, 0.f), 0.1f, 18);
	//m_pAnimator->PlayAnimation(L"PISTOL_BASIC_MOVE_ST", true);
}

void CAniToolScene2::Update()
{
	m_ptMousePos = CInputMgr::GetInst()->GetMousePos();


	if (CheckSceneChange()) // Check Scene Change
		return;

}



void CAniToolScene2::Render(HDC hdc)
{	
	POINT ptWest, ptEast, ptNorth, ptSouth, ptOrigin;

	ptOrigin = CCamera::GetInst()->GetRenderPos(POINT{ 0, 0 });
	ptWest = CCamera::GetInst()->GetRenderPos(POINT{ -100, 0 });
	ptEast = CCamera::GetInst()->GetRenderPos(POINT{ 100, 0 });
	ptNorth = CCamera::GetInst()->GetRenderPos(POINT{ 0, -100 });
	ptSouth = CCamera::GetInst()->GetRenderPos(POINT{ 0, 100 });

	// BackGround - Green
	HBRUSH Hbrush = CreateSolidBrush(RGB(0, 255, 0));
	HGDIOBJ Holdbrush = SelectObject(hdc, Hbrush);
	Rectangle(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc, Holdbrush);
	DeleteObject(Hbrush);

	// Cross 
	MoveToEx(hdc, ptWest.x, ptWest.y, nullptr);
	LineTo(hdc, ptEast.x, ptEast.y);
	MoveToEx(hdc, ptNorth.x, ptNorth.y, nullptr);
	LineTo(hdc, ptSouth.x, ptSouth.y);


	//Animator Render
	//m_pAnimator->Render(hdc);

	// Text Info
	RenderText(hdc);
}

void CAniToolScene2::Exit()
{
}



bool CAniToolScene2::CheckSceneChange()
{
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::ENTER) == KEY_STATE::DOWN)
	{
		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::MAPTOOL);
		return true;
	}
	else
	{
		return false;
	}
}

void CAniToolScene2::RenderText(HDC hdc)
{
	SetTextAlign(hdc, TA_LEFT);
	
	// Basic Top
	// FPS
	TCHAR tch[128] = {};
	swprintf_s(tch, L"FPS : %.2f ", float(FPS));
	TextOut(hdc, 1, 0, tch, (int)_tcslen(tch));
	// DT
	swprintf_s(tch, L"DT : %f ", DT);
	TextOut(hdc, 1, 20, tch, (int)_tcslen(tch));
	// CAMERA LOOK AT
	swprintf_s(tch, L"CAMERA LOOK AT : %.4f, %.4f ", CCamera::GetInst()->GetLookAt().x, CCamera::GetInst()->GetLookAt().y);
	TextOut(hdc, 1, 40, tch, (int)_tcslen(tch));
	// Text - World Cursor
	Vector2 temp1 = CCamera::GetInst()->GetRealPos(Vector2(m_ptMousePos.x, m_ptMousePos.y));
	swprintf_s(tch, L"World Cursor Pos : %d, %d ", int(temp1.x), int(temp1.y));
	TextOut(hdc, 1, 60, tch, (int)_tcslen(tch));
	// Text - Local Cursor
	swprintf_s(tch, L"Local Cursor Pos : %d, %d ", m_ptMousePos.x, m_ptMousePos.y);
	TextOut(hdc, 1, 80, tch, (int)_tcslen(tch));




	// Animation Left
	// Name
	swprintf_s(tch, L"Ani Name(State) : ");
	TextOut(hdc, 1, 160, tch, (int)_tcslen(tch));

	// 상체 or 하체
	swprintf_s(tch, L"Control Ani : ");
	TextOut(hdc, 1, 180, tch, (int)_tcslen(tch));

	// 상체 인덱스
	swprintf_s(tch, L"Top Idx : ");
	TextOut(hdc, 1, 200, tch, (int)_tcslen(tch));

	// 상체 피벗
	swprintf_s(tch, L"Top Pivot : ");
	TextOut(hdc, 1, 220, tch, (int)_tcslen(tch));

	// 하체 인덱스
	swprintf_s(tch, L"Bot Idx : ");
	TextOut(hdc, 1, 240, tch, (int)_tcslen(tch));

	// 하체 피벗
	swprintf_s(tch, L"Top Pivot : ");
	TextOut(hdc, 1, 260, tch, (int)_tcslen(tch));

	// 프레임 시간
	swprintf_s(tch, L"Frame Time : ");
	TextOut(hdc, 1, 280, tch, (int)_tcslen(tch));

	// 반복 여부
	swprintf_s(tch, L"Repeat : ");
	TextOut(hdc, 1, 300, tch, (int)_tcslen(tch));




	swprintf_s(tch, L"Num 2, 4, 6, 8 : Animation Move (5px)");
	TextOut(hdc, 1, 400, tch, (int)_tcslen(tch));
	
	swprintf_s(tch, L"Num 2, 4, 6, 8 + Ctrl: Animation Move (1px)");
	TextOut(hdc, 1, 420, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Ctrl : Choice Top or Bottom");
	TextOut(hdc, 1, 440, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Shift : LR Flip");
	TextOut(hdc, 1, 460, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Enter : Play Toggle(On/Off)");
	TextOut(hdc, 1, 480, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"LEFT_KEY : Prev State");
	TextOut(hdc, 1, 500, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"RIGHT_KEY : Next State");
	TextOut(hdc, 1, 520, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"UP_KEY : Frame Time 0.01second + ");
	TextOut(hdc, 1, 540, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"DOWN_KEY : Frame Time 0.01second - ");
	TextOut(hdc, 1, 560, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"S : Save");
	TextOut(hdc, 1, 580, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"L : Load");
	TextOut(hdc, 1, 600, tch, (int)_tcslen(tch));
}


void CAniToolScene2::ScrollMouse()
{
	Vector2 vCameraLookat = CCamera::GetInst()->GetLookAt();


	if ((-100.f <= m_ptMousePos.x && m_ptMousePos.x <= 15.f)
		&& (0.f <= m_ptMousePos.y && m_ptMousePos.y <= WINDOW_HEIGHT))
	{
		vCameraLookat.x -= MOUSE_SPEED * fDT;
	}
	else if ((WINDOW_WIDTH + 100.f >= m_ptMousePos.x && m_ptMousePos.x >= WINDOW_WIDTH - 15.f)
		&& (0.f <= m_ptMousePos.y && m_ptMousePos.y <= WINDOW_HEIGHT))
	{
		vCameraLookat.x += MOUSE_SPEED * fDT;
	}
	else if ((-100.f <= m_ptMousePos.y && m_ptMousePos.y <= 15.f) // Up
		&& (0.f <= m_ptMousePos.x && m_ptMousePos.x <= WINDOW_WIDTH))
	{
		vCameraLookat.y -= MOUSE_SPEED * fDT;
	}
	else if ((WINDOW_HEIGHT + 100.f >= m_ptMousePos.y && m_ptMousePos.y >= WINDOW_HEIGHT - 15.f)
		&& (0.f <= m_ptMousePos.x && m_ptMousePos.x <= WINDOW_WIDTH))
	{
		vCameraLookat.y += MOUSE_SPEED * fDT;
	}

	CCamera::GetInst()->SetLookAt(vCameraLookat);
}
