#include "stdafx.h"
#include "AniToolScene1.h"

CAniToolScene1::CAniToolScene1()
	: m_ptTemp1(nullptr)
	, m_ptTemp2(nullptr)
	, m_pTex(nullptr)
{
}

CAniToolScene1::~CAniToolScene1()
{
}

void CAniToolScene1::Enter()
{
	CCamera::GetInst()->SetLookAt(Vector2(0.f, 0.f));
	m_Curbody = BODY_TYPE::TOP;
	m_wstrCurState = L"";
}

void CAniToolScene1::Update()
{
	m_ptMousePos = CInputMgr::GetInst()->GetMousePos();

	ScrollMouse();

	AddvecFrame();

	//AddvecBox();

	if (CheckSceneChange()) // Check Scene Change
		return;
}

void CAniToolScene1::Render(HDC hdc)
{
	// ============= BackGround ============= // 
	HBRUSH Hbrush = CreateSolidBrush(RGB(0, 0, 0));
	HGDIOBJ Holdbrush = SelectObject(hdc, Hbrush);
	Rectangle(hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc, Holdbrush);
	DeleteObject(Hbrush);




	// ============= BMP ============= // 

	if (m_pTex != nullptr)
	{
		int iWidth = (int)m_pTex->Width();
		int iHeight = (int)m_pTex->Height();

		Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vector2(0.f, 0.f));
		Vector2 t = CCamera::GetInst()->GetRenderPos(Vector2(iWidth, iHeight));

		TransparentBlt(hdc,
			int(vRenderPos.x),
			int(vRenderPos.y),
			iWidth, iHeight,
			m_pTex->GetDC(),
			0, 0, iWidth, iHeight,
			RGB(86, 177, 222));
	}


	// ============= Mouse Cross ============= // 
	PEN_TYPE ePen = PEN_TYPE::RED;
	SelectGDI pen(hdc, ePen);

	MoveToEx(hdc, (int)m_ptMousePos.x - 1000, (int)m_ptMousePos.y, nullptr);
	LineTo(hdc, (int)m_ptMousePos.x, (int)m_ptMousePos.y);

	MoveToEx(hdc, (int)m_ptMousePos.x, (int)m_ptMousePos.y, nullptr);
	LineTo(hdc, (int)m_ptMousePos.x + 1000, (int)m_ptMousePos.y);

	MoveToEx(hdc, m_ptMousePos.x, (int)m_ptMousePos.y - 1000, nullptr);
	LineTo(hdc, (int)m_ptMousePos.x, (int)m_ptMousePos.y);

	MoveToEx(hdc, m_ptMousePos.x, (int)m_ptMousePos.y, nullptr);
	LineTo(hdc, (int)m_ptMousePos.x, (int)m_ptMousePos.y + 1000);
	
	Render_vecBox(hdc);
	Render_CurBox(hdc);


	// ============= Text Info ============= // 
	RenderText(hdc);
}

void CAniToolScene1::Exit()
{

	for (vector <Frame*>::iterator iter = m_vecFrame.begin(); iter != m_vecFrame.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			delete (*iter)->point1;
			delete (*iter)->point2;
			delete* iter;
		}
	}

	m_vecBox.clear();

	delete m_pTex;
}

void CAniToolScene1::SetTexture(const wstring& _strKeyName, const wstring& _strFilePath)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(_strKeyName, _strFilePath);
}

void CAniToolScene1::ScrollMouse()
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

bool CAniToolScene1::CheckSceneChange()
{
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::ENTER) == KEY_STATE::DOWN)
	{
		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::ANITOOL2);
		return true;
	}
	else
		return false;
}


void CAniToolScene1::RenderText(HDC hdc)
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
}


void CAniToolScene1::SaveMapFrame(const wstring& _strRelativePath)
{
	// 상대경로를 현 함수의 인자로 받아 절대경로 세팅
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	wofstream ofs(strFilePath, ios::out | ios::trunc);
	for (vector <Frame*>::iterator iter = m_vecFrame.begin(); iter != m_vecFrame.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{

			ofs << (*iter)->State << endl
				<< (*iter)->Body << endl
				<< (*iter)->point1->x << endl
				<< (*iter)->point1->y << endl
				<< (*iter)->point2->x << endl
				<< (*iter)->point2->y << endl
				<< (*iter)->Pivot.x << endl
				<< (*iter)->Pivot.y << endl
				<< (*iter)->Duration << endl << endl;
		}
	}
	ofs.close();
}


void CAniToolScene1::AddvecFrame()
{
	Vector2 vClickPos = Vector2(int(CCamera::GetInst()->GetRealPos(Vector2(float(m_ptMousePos.x), float(m_ptMousePos.y))).x),
		int(CCamera::GetInst()->GetRealPos(Vector2(float(m_ptMousePos.x), float(m_ptMousePos.y))).y));

	if (CInputMgr::GetInst()->GetMouseState(MOUSE_TYPE::LBTN) == MOUSE_STATE::DOWN)
	{
		if (m_ptTemp2 == nullptr)
		{
			if (m_ptTemp1 == nullptr) // (X, X)
			{
				m_ptTemp1 = new POINT{ LONG(vClickPos.x), LONG(vClickPos.y) }; // (O, X)

				if (m_ptTemp1->x < 0) // x값이 음수일 경우 에러를 방지하기 위해, 0으로 강제 세팅 
					m_ptTemp1->x = 0;

			}
			else // (O, X)
			{
				m_ptTemp2 = new POINT{ LONG(vClickPos.x), LONG(vClickPos.y) }; // (O, O)

				Frame* temp = new Frame{ m_wstrCurState, UINT(m_Curbody), m_ptTemp1, m_ptTemp2, Vector2(0.f, 0.f), 0.1f };
				m_vecFrame.push_back(temp);

				m_ptTemp1 = nullptr;
				m_ptTemp2 = nullptr;

				Print_vecFrame();
			}
		}
	}

	if (CInputMgr::GetInst()->GetMouseState(MOUSE_TYPE::RBTN) == MOUSE_STATE::DOWN) // Back
	{
		if (!m_vecFrame.empty())
		{
			cout << "Pop Data!\n";
			delete m_vecFrame.back()->point1;
			delete m_vecFrame.back()->point2;
			delete m_vecFrame.back();

			m_vecFrame.pop_back();

			Print_vecFrame();
		}
	}

}


void CAniToolScene1::Print_vecFrame()
{
	cout << "\n====================================\n";
	cout << "\n* Vector Data Print *\n\n";
	for (vector <Frame*>::iterator iter = m_vecFrame.begin(); iter != m_vecFrame.end(); ++iter)
	{
		/*if ((*iter) != nullptr)
		{
			printf("POINT 1 : X : %d, Y : %d\nPOINT 2 : X : %d, Y : %d\n\n", (*iter)->point1->x, (*iter)->point1->y, (*iter)->point2->x, (*iter)->point2->y);
		}*/

		if ((*iter) != nullptr)
		{
			cout << "STATE : ";
			wcout << (*iter)->State << endl;

			cout << "BODY : " << (UINT)(*iter)->Body << endl;

			cout << "POINT1 : " << (*iter)->point1->x << "  " << (*iter)->point1->y << endl;
			cout << "POINT2 : " << (*iter)->point2->x << "  " << (*iter)->point2->y << endl;
			cout << "PIVOT : " << (*iter)->Pivot.x << "  " << (*iter)->Pivot.y << endl;
			cout << "Duration : " << (*iter)->Duration << endl << endl;

		}
	}
	cout << "====================================\n";
}

void CAniToolScene1::Render_vecBox(HDC hdc)
{
	for (vector <Frame*>::iterator iter = m_vecFrame.begin(); iter != m_vecFrame.end(); ++iter)
	{
		PEN_TYPE ePen;
		if ((*iter)->Body == UINT(BODY_TYPE::TOP))
			ePen = PEN_TYPE::GREEN;
		else
			ePen = PEN_TYPE::BLUE;

		SelectGDI pen(hdc, ePen);
		SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW);

		POINT tempSrc = CCamera::GetInst()->GetRenderPos(*(*iter)->point1);
		POINT tempDst = CCamera::GetInst()->GetRenderPos(*(*iter)->point2);

		Rectangle(hdc, tempSrc.x, tempSrc.y, tempDst.x, tempDst.y);
	}
}

void CAniToolScene1::Render_CurBox(HDC hdc)
{
	if (m_ptTemp1 != nullptr)
	{
		if (m_ptTemp2 == nullptr)
		{
		
			PEN_TYPE ePen;
			if (m_Curbody == BODY_TYPE::TOP)
				ePen = PEN_TYPE::GREEN;
			else
				ePen = PEN_TYPE::BLUE;

			SelectGDI pen(hdc, ePen);
			SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW);

			POINT tempSrc = CCamera::GetInst()->GetRenderPos(*m_ptTemp1);
			POINT tempDst = CInputMgr::GetInst()->GetMousePos();

			Rectangle(hdc, tempSrc.x, tempSrc.y, tempDst.x, tempDst.y);
			
		}
	}
}



