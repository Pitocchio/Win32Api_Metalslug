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

	m_pAnimator = new CAnimator2D();


	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\PISTOL_BASIC_MOVE_ST.bmp"); // 애니메이션 테스트 (애니메이션 파일 불러옴)
	//m_pAnimator->CreateAnimation(L"PISTOL_BASIC_MOVE_ST", m_pTex, Vector2(0.f, 0.f), Vector2(39.1f, 64.f), Vector2(39.1f, 0.f), 0.1f, 18);
	//m_pAnimator->PlayAnimation(L"PISTOL_BASIC_MOVE_ST", true);
}

void CAniToolScene2::Update()
{
	//m_ptMousePos = CInputMgr::GetInst()->GetMousePos();

	if (m_pAnimator != nullptr)
		EditFrm();

	if (m_pAnimator != nullptr)
		m_pAnimator->Update();

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
	m_pAnimator->Render(hdc);

	// Text Info
	RenderText(hdc);
}

void CAniToolScene2::Exit()
{

	for (vector <Frm*>::iterator iter = m_vecFrm.begin(); iter != m_vecFrm.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete* iter;
		}
	}

	m_vecFrm.clear();

	delete m_pTex;
}



bool CAniToolScene2::CheckSceneChange()
{
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::F1) == KEY_STATE::DOWN)
	{
		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::ANITOOL1);
		return true;
	}
	else if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::F2) == KEY_STATE::DOWN)
	{
		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::ANITOOL2);
		return true;
	}
	else if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::F3) == KEY_STATE::DOWN)
	{
		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::MAPTOOL);
		return true;
	}
	else if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::F4) == KEY_STATE::DOWN)
	{
		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::GAME);
		return true;
	}
	else
		return false;
}

void CAniToolScene2::EditFrm()
{
	CAnimation2D* pCurAni = m_pAnimator->GetCurAni();

	if (pCurAni == nullptr)
		return;

	int k = 0;


	Vector2 vPivot (0,0);

	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::NUM2) == KEY_STATE::HOLD)
	{
		/*if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::CTRL) == KEY_STATE::HOLD)
			vPivot.y = 1;
		else
			vPivot.y = 5;*/
		vPivot.y = 0.5;
		pCurAni->SetPivot(vPivot);

	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::NUM4) == KEY_STATE::HOLD)
	{
		/*if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::CTRL) == KEY_STATE::HOLD)
			vPivot.x = -1;
		else
			vPivot.x = -5;*/
		vPivot.x = -0.5;
		pCurAni->SetPivot(vPivot);

	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::NUM6) == KEY_STATE::HOLD)
	{
		/*if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::CTRL) == KEY_STATE::HOLD)
			vPivot.x = 1;
		else
			vPivot.x = 5;*/
		vPivot.x = 0.5;
		pCurAni->SetPivot(vPivot);

	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::NUM8) == KEY_STATE::HOLD)
	{
		/*if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::CTRL) == KEY_STATE::HOLD)
			vPivot.y = -1;
		else
			vPivot.y = -5;*/
		vPivot.y = -0.5;
		pCurAni->SetPivot(vPivot);
	}



	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::CTRL) == KEY_STATE::DOWN)
	{
		pCurAni->SetCurBody();
	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::SHIFT) == KEY_STATE::DOWN)
	{
		pCurAni->FlipX();
	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::ENTER) == KEY_STATE::DOWN)
	{

		pCurAni->PlayAniToggle();
	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::DOWN)
	{
		pCurAni->PlusMinusFrm(-1);
	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::DOWN)
	{
		pCurAni->PlusMinusFrm(1);
	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::DOWN) == KEY_STATE::DOWN)
	{
		float fTime = -0.05f;
		pCurAni->SetFrmTime(fTime);
	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::UP) == KEY_STATE::DOWN)
	{
		float fTime = 0.05f;
		pCurAni->SetFrmTime(fTime);
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
	//swprintf_s(tch, L"CAMERA LOOK AT : %.4f, %.4f ", CCamera::GetInst()->GetLookAt().x, CCamera::GetInst()->GetLookAt().y);
	//TextOut(hdc, 1, 40, tch, (int)_tcslen(tch));
	// Text - World Cursor
	Vector2 temp1 = CCamera::GetInst()->GetRealPos(Vector2(m_ptMousePos.x, m_ptMousePos.y));
	//swprintf_s(tch, L"World Cursor Pos : %d, %d ", int(temp1.x), int(temp1.y));
	//TextOut(hdc, 1, 60, tch, (int)_tcslen(tch));
	// Text - Local Cursor
	//swprintf_s(tch, L"Local Cursor Pos : %d, %d ", m_ptMousePos.x, m_ptMousePos.y);
	//TextOut(hdc, 1, 80, tch, (int)_tcslen(tch));



	swprintf_s(tch, L"Num 2, 4, 6, 8 : Animation Move (5px)");
	TextOut(hdc, 1, 420, tch, (int)_tcslen(tch));

	/*swprintf_s(tch, L"Num 2, 4, 6, 8 + Ctrl: Animation Move (1px)");
	TextOut(hdc, 1, 420, tch, (int)_tcslen(tch));*/

	swprintf_s(tch, L"Ctrl : Choice Top or Bottom");
	TextOut(hdc, 1, 440, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Shift : LR Flip");
	TextOut(hdc, 1, 460, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Enter : Play Toggle(On/Off)");
	TextOut(hdc, 1, 480, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"LEFT_KEY : Prev Frame");
	TextOut(hdc, 1, 500, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"RIGHT_KEY : Next Frame");
	TextOut(hdc, 1, 520, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"UP_KEY : Frame Time 0.01second + ");
	TextOut(hdc, 1, 540, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"DOWN_KEY : Frame Time 0.01second - ");
	TextOut(hdc, 1, 560, tch, (int)_tcslen(tch));

}


void CAniToolScene2::CreateAnimation(const wstring& _strKeyName, const wstring& _strTexPath, const wstring& _strDataPath)
{
	m_pAnimator->SetTexture(_strKeyName, _strTexPath);
	m_pAnimator->SetData(_strDataPath);
	m_pAnimator->CreateAnimation();
	m_pAnimator->PlayFirstAnimation();
	//m_pAnimator->SetCurAnimation(L"TARMA_PISTOL_BASIC_MOVE_ST");
}

void CAniToolScene2::SaveAnimation(const wstring& _strFilePath)
{
	m_pAnimator->Save(_strFilePath);
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
