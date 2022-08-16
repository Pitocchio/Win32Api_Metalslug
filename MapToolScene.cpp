#include "stdafx.h"
#include "MapToolScene.h"

CMapToolScene::CMapToolScene()
{
}

CMapToolScene::~CMapToolScene()
{
}

void CMapToolScene::Enter()
{
	CStage* pStage = new CStage(OBJECT_TYPE::S_GROUND);
	CEventMgr::GetInst()->CreateObject(pStage, OBJECT_TYPE::S_GROUND);

	CCamera::GetInst()->SetLookAt(Vector2(500, 2000));

	m_ptTemp1 = nullptr;
	m_ptTemp2 = nullptr;

	m_curDrawObj = OBJECT_TYPE::NONE;

	m_strFilePath = L"mapdata\\OriginData.bin"; // Origin Data! 변경금지!

	LoadMapObj(m_strFilePath); // 기존에 저장되어있던 파일 불러온다
}

void CMapToolScene::Update()
{
	CScene::Update(); // Base Method

	GetCurDrawObj();

	m_ptMousePos = CInputMgr::GetInst()->GetMousePos();

	if (CheckSceneChange()) // Check Scene Change
		return;

	ScrollMouse(); // Camera Moving by Mouse Position

	CreateMapObject();

	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::S) == KEY_STATE::DOWN)
		SaveMapObj(m_strFilePath);
}




void CMapToolScene::Render(HDC hdc)
{
	CObjectMgr::GetInst()->Render(hdc); // 일반 오브젝트 (스테이지)

	RenderLiveMapObj(hdc); // 지금 그리고 있는 맵 오브젝트(라인, 콜라이더 박스)

	RenderMapObj(hdc); // 현재 벡터에 저장된 맵 오브젝트(라인, 콜라이더 박스)

	RenderText(hdc); // 툴 관련 텍스트 
}

void CMapToolScene::Exit()
{
	CObjectMgr::GetInst()->Release();

	SaveMapObj(m_strFilePath);

	for (vector <MAPOBJ*>::iterator iter = m_vecMapObj.begin(); iter != m_vecMapObj.end(); ++iter)
	{
		if ((*iter) != nullptr)
				delete* iter;
	}

	m_vecMapObj.clear();
}

void CMapToolScene::ScrollMouse()
{
	Vector2 vCameraLookat = CCamera::GetInst()->GetLookAt();


	if ((-100.f <= m_ptMousePos.x && m_ptMousePos.x <= 15.f)
		&& (0.f <= m_ptMousePos.y && m_ptMousePos.y <= WINDOW_HEIGHT))
	{
		vCameraLookat.x -= MOUSE_SPEED * fDT;
	}
	else if ((WINDOW_WIDTH + 100.f >= m_ptMousePos.x && m_ptMousePos.x  >= WINDOW_WIDTH - 15.f)
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

bool CMapToolScene::CheckSceneChange()
{
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::ENTER) == KEY_STATE::DOWN)
	{
		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::GAME);
		return true;
	}
	else
	{
		return false;
	}
}

void CMapToolScene::CreateMapObject()
{
	Vector2 vClickPos = Vector2(int(CCamera::GetInst()->GetRealPos(Vector2(float(m_ptMousePos.x), float(m_ptMousePos.y))).x),
								int(CCamera::GetInst()->GetRealPos(Vector2(float(m_ptMousePos.x), float(m_ptMousePos.y))).y));

	if (CInputMgr::GetInst()->GetMouseState(MOUSE_TYPE::LBTN) == MOUSE_STATE::DOWN)
	{

		if (m_curDrawObj == OBJECT_TYPE::ML_LINE) // ML_LINE
			AddMapObject(vClickPos, OBJECT_TYPE::ML_LINE);
		else if (m_curDrawObj == OBJECT_TYPE::MC_CAMERA_FOLLOWPLAYERY) // MC_CAMERA_FOLLOWPLAYERY
			AddMapObject(vClickPos, OBJECT_TYPE::MC_CAMERA_FOLLOWPLAYERY);
		else if (m_curDrawObj == OBJECT_TYPE::MC_CAMERA_ROCK) // MC_CAMERA_ROCK
			AddMapObject(vClickPos, OBJECT_TYPE::MC_CAMERA_ROCK);
		else if (m_curDrawObj == OBJECT_TYPE::MC_PLAYER_LEFTMOVEROCK) // MC_PLAYER_LEFTMOVEROCK
			AddMapObject(vClickPos, OBJECT_TYPE::MC_PLAYER_LEFTMOVEROCK);
		else if (m_curDrawObj == OBJECT_TYPE::MC_ENEMY_SPAWNER) // MC_ENEMY_SPAWNER
			AddMapObject(vClickPos, OBJECT_TYPE::MC_ENEMY_SPAWNER);
	}

	if (CInputMgr::GetInst()->GetMouseState(MOUSE_TYPE::RBTN) == MOUSE_STATE::DOWN) // Back
	{
		if (!m_vecMapObj.empty())
		{
			cout << "Pop Data!\n";
			delete m_vecMapObj.back()->point1;
			delete m_vecMapObj.back()->point2;
			delete m_vecMapObj.back();
			m_vecMapObj.pop_back();

			PrintVector();
		}
	}
}

void CMapToolScene::AddMapObject(Vector2 vClickPos, OBJECT_TYPE type)
{
	if (m_ptTemp2 == nullptr)
	{
		if (m_ptTemp1 == nullptr) // (X, X)
		{
			m_ptTemp1 = new POINT{ LONG(vClickPos.x), LONG(vClickPos.y) }; // (O, X)


			// 라인일 경우 꼭짓점 맞춰주는 센스
			if (m_curDrawObj == OBJECT_TYPE::ML_LINE)
			{
				double dis = 111.f;
				double tempdis = 0.f;

				for (vector <MAPOBJ*>::iterator iter = m_vecMapObj.begin(); iter != m_vecMapObj.end(); ++iter)
				{
					tempdis = sqrt(pow((*iter)->point1->x - m_ptTemp1->x, 2) + pow((*iter)->point1->y - m_ptTemp1->y, 2));
					if (tempdis < 25.f)
					{
						if (dis > tempdis)
						{
							dis = tempdis;

							*m_ptTemp1 = *((*iter)->point1);
						}
					}

					tempdis = sqrt(pow((*iter)->point2->x - m_ptTemp1->x, 2) + pow((*iter)->point2->y - m_ptTemp1->y, 2));
					if (tempdis < 25.f)
					{
						if (dis > tempdis)
						{
							dis = tempdis;

							*m_ptTemp1 = *((*iter)->point2);
						}
					}
				}
			}
		}
		else // (O, X)
		{
			m_ptTemp2 = new POINT{ LONG(vClickPos.x), LONG(vClickPos.y) }; // (O, O)

			MAPOBJ* temp = new MAPOBJ{ m_ptTemp1, m_ptTemp2, (UINT)type };

			m_vecMapObj.push_back(temp);

			m_ptTemp1 = nullptr;
			m_ptTemp2 = nullptr;
			//cout << "Add Success!\n";

			PrintVector();
		}
	}
}

void CMapToolScene::PrintVector()
{
	cout << "\n====================================\n";
	cout << "\n* Vector Data Print *\n\n";
	for (vector <MAPOBJ*>::iterator iter = m_vecMapObj.begin(); iter != m_vecMapObj.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			cout << "(UINT)OBJTYPE : " << (UINT)(*iter)->Coltype << endl;
			printf("POINT 1 : X : %d, Y : %d\nPOINT 2 : X : %d, Y : %d\n\n", (*iter)->point1->x, (*iter)->point1->y, (*iter)->point2->x, (*iter)->point2->y);
		}
	}
	cout << "====================================\n";
}

void CMapToolScene::SaveMapObj(const wstring& _strRelativePath)
{
	// 상대경로를 현 함수의 인자로 받아 절대경로 세팅
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 파일 포인터 생성 
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	if (pFile == nullptr)
		return;

	for (vector <MAPOBJ*>::iterator iter = m_vecMapObj.begin(); iter != m_vecMapObj.end(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			fwrite(&((*iter)->Coltype), sizeof(UINT), 1, pFile);
			fwrite(&((*iter)->point1->x), sizeof(LONG), 1, pFile);
			fwrite(&((*iter)->point1->y), sizeof(LONG), 1, pFile);
			fwrite(&((*iter)->point2->x), sizeof(LONG), 1, pFile);
			fwrite(&((*iter)->point2->y), sizeof(LONG), 1, pFile);
		}
	}

	cout << "\nFile Save Success!\n";

	fclose(pFile);
}

//void CToolScene::LoadMapObj(const wstring& _strRelativePath)
//{
//	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
//	strFilePath += _strRelativePath;
//
//	FILE* pFile = nullptr;
//
//	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
//	if (pFile == nullptr)
//		return;
//
//	
//	
//
//	LONG test = 0;
//	
//	
//	while (feof(pFile) == 0)
//	{
//		fread(&test, sizeof(LONG), 1, pFile);
//
//		if (feof(pFile) != 0)
//			break;
//
//		cout << test << endl;
//	}
//
//
//	cout << "\nFile Load Success!\n";
//
//	fclose(pFile);
//}


void CMapToolScene::LoadMapObj(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	if (pFile == nullptr)
		return;

	LONG type = 0;
	/*POINT pt1 = {};
	POINT pt2 = {};*/

	while (feof(pFile) == 0)
	{
		POINT* pt1 = new POINT{};
		POINT* pt2 = new POINT{};

		fread(&type, sizeof(LONG), 1, pFile);
		fread(&pt1->x, sizeof(LONG), 1, pFile);
		fread(&pt1->y, sizeof(LONG), 1, pFile);
		fread(&pt2->x, sizeof(LONG), 1, pFile);
		fread(&pt2->y, sizeof(LONG), 1, pFile);
	/*	fread(&type, sizeof(LONG), 1, pFile);
		fread(&pt1.x, sizeof(LONG), 1, pFile);
		fread(&pt1.y, sizeof(LONG), 1, pFile);
		fread(&pt2.x, sizeof(LONG), 1, pFile);
		fread(&pt2.y, sizeof(LONG), 1, pFile);*/

		if (feof(pFile) != 0)
			break;

		MAPOBJ* temp = new MAPOBJ{ pt1, pt2, (UINT)type };
		m_vecMapObj.push_back(temp);
	}

	cout << "\nFile Load Success!\n";

	fclose(pFile);
}

void CMapToolScene::RenderText(HDC hdc)
{
	// Text - FPSs
	SetTextAlign(hdc, TA_LEFT);

	TCHAR tch1[128] = {};
	swprintf_s(tch1, L"FPS : %.2f ",
		float(FPS));
	TextOut(hdc, 0, 0, tch1, (int)_tcslen(tch1));

	// Text - DT
	TCHAR tch2[128] = {};
	swprintf_s(tch2, L"DT : %f ", DT);
	TextOut(hdc, 0, 15, tch2, (int)_tcslen(tch2));


	// Text - World Cursor
	TCHAR tch3[128] = {};
	Vector2 temp1 = CCamera::GetInst()->GetRealPos(Vector2(m_ptMousePos.x, m_ptMousePos.y));
	swprintf_s(tch3, L"World Cursor Pos : %d, %d ", int(temp1.x), int(temp1.y));
	TextOut(hdc, 0, 30, tch3, (int)_tcslen(tch3));


	// Text - Local Cursor
	TCHAR tch4[128] = {};
	swprintf_s(tch4, L"Local Cursor Pos : %d, %d ", m_ptMousePos.x, m_ptMousePos.y);
	TextOut(hdc, 0, 45, tch4, (int)_tcslen(tch4));


	// Text - Info
	TCHAR tch45[256] = {};
	swprintf_s(tch45, L"=============  Map Tool Control =============");
	TextOut(hdc, 0, 75, tch45, (int)_tcslen(tch45));

	TCHAR tch5[256] = {};
	swprintf_s(tch5, L"[Q] : Line Point");
	TextOut(hdc, 0, 90, tch5, (int)_tcslen(tch5));

	TCHAR tch6[256] = {};
	swprintf_s(tch6, L"[W] : Collider CameraFollowPlayerY");
	TextOut(hdc, 0, 105, tch6, (int)_tcslen(tch6));

	TCHAR tch7[256] = {};
	swprintf_s(tch7, L"[E] : Collider PlayerLeftMoveLock");
	TextOut(hdc, 0, 120, tch7, (int)_tcslen(tch7));

	TCHAR tch8[256] = {};
	swprintf_s(tch8, L"[R] : Collider CameraRock");
	TextOut(hdc, 0, 135, tch8, (int)_tcslen(tch8));

	TCHAR tch9[256] = {};
	swprintf_s(tch9, L"[T] : Collider MonsterSpawn");
	TextOut(hdc, 0, 150, tch9, (int)_tcslen(tch9));

	TCHAR tch13[256] = {};
	swprintf_s(tch13, L"[Y] : NONE");
	TextOut(hdc, 0, 165, tch13, (int)_tcslen(tch13));

	TCHAR tch10[256] = {};
	swprintf_s(tch10, L"[RightClick] : Back");
	TextOut(hdc, 0, 180, tch10, (int)_tcslen(tch10));

	TCHAR tch11[256] = {};
	swprintf_s(tch11, L"[S] : Save");
	TextOut(hdc, 0, 195, tch11, (int)_tcslen(tch11));

	TCHAR tch12[256] = {};
	swprintf_s(tch12, L"=========================================");
	TextOut(hdc, 0, 210, tch12, (int)_tcslen(tch12));



}

void CMapToolScene::RenderMapObj(HDC hdc)
{
	for (vector <MAPOBJ*>::iterator iter = m_vecMapObj.begin(); iter != m_vecMapObj.end(); ++iter)
	{
		if ((*iter)->Coltype == UINT(OBJECT_TYPE::ML_LINE))
		{
			PEN_TYPE ePen = PEN_TYPE::RED;

			SelectGDI pen(hdc, ePen);
			SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW);


			POINT tempSrc = CCamera::GetInst()->GetRenderPos(*(*iter)->point1);
			POINT tempDst = CCamera::GetInst()->GetRenderPos(*(*iter)->point2);

			MoveToEx(hdc, tempSrc.x, tempSrc.y, nullptr);
			LineTo(hdc, tempDst.x, tempDst.y);
		}
		else
		{
			PEN_TYPE ePen = PEN_TYPE::NONE;
		
			switch ((*iter)->Coltype)
			{
				case UINT(OBJECT_TYPE::MC_CAMERA_FOLLOWPLAYERY):
					ePen = PEN_TYPE::ORANGE;
					break;
				case UINT(OBJECT_TYPE::MC_CAMERA_ROCK):
					ePen = PEN_TYPE::PURPLE;
					break;
				case UINT(OBJECT_TYPE::MC_PLAYER_LEFTMOVEROCK):
					ePen = PEN_TYPE::BLUE;
					break;
				case UINT(OBJECT_TYPE::MC_ENEMY_SPAWNER):
					ePen = PEN_TYPE::GREEN;
					break;
				default:
					break;
			}

			SelectGDI pen(hdc, ePen);
			SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW);

			POINT tempSrc = CCamera::GetInst()->GetRenderPos(*(*iter)->point1);
			POINT tempDst = CCamera::GetInst()->GetRenderPos(*(*iter)->point2);

			Rectangle(hdc, tempSrc.x, tempSrc.y, tempDst.x, tempDst.y);
		}
	}

}

void CMapToolScene::RenderLiveMapObj(HDC hdc)
{

	if (m_ptTemp1 != nullptr)
	{
		if (m_ptTemp2 == nullptr)
		{
			if (m_curDrawObj == OBJECT_TYPE::ML_LINE)
			{
				PEN_TYPE ePen;

				POINT tempSrc = CCamera::GetInst()->GetRenderPos(*m_ptTemp1);
				POINT tempDst = CInputMgr::GetInst()->GetMousePos();
				
				float angle = ((float)(tempDst.y - tempSrc.y) / (float)(tempDst.x - tempSrc.x));

				if (angle == 0.f)
					ePen = PEN_TYPE::GREEN;
				else
					ePen = PEN_TYPE::RED;

				SelectGDI pen(hdc, ePen);
				SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW);

				MoveToEx(hdc, tempSrc.x, tempSrc.y, nullptr);
				LineTo(hdc, tempDst.x, tempDst.y);
			}
			else
			{
				PEN_TYPE ePen = PEN_TYPE::GREEN;

				SelectGDI pen(hdc, ePen);
				SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW);

				POINT tempSrc = CCamera::GetInst()->GetRenderPos(*m_ptTemp1);
				POINT tempDst = CInputMgr::GetInst()->GetMousePos();

				Rectangle(hdc, tempSrc.x, tempSrc.y, tempDst.x, tempDst.y);
			}
		}
	}
}

void CMapToolScene::GetCurDrawObj()
{

	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::Q) == KEY_STATE::DOWN) // ML_LINE
	{
		m_curDrawObj = OBJECT_TYPE::ML_LINE;
	}
	else if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::W) == KEY_STATE::DOWN) // MC_CAMERA_FOLLOWPLAYERY
	{
		m_curDrawObj = OBJECT_TYPE::MC_CAMERA_FOLLOWPLAYERY;
	}
	else if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::E) == KEY_STATE::DOWN) // MC_CAMERA_ROCK
	{
		m_curDrawObj = OBJECT_TYPE::MC_CAMERA_ROCK;
	}
	else if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::R) == KEY_STATE::DOWN) // MC_PLAYER_LEFTMOVEROCK
	{
		m_curDrawObj = OBJECT_TYPE::MC_PLAYER_LEFTMOVEROCK;
	}
	else if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::T) == KEY_STATE::DOWN) // MC_ENEMY_SPAWNER
	{
		m_curDrawObj = OBJECT_TYPE::MC_ENEMY_SPAWNER;
	}
	else if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::Y) == KEY_STATE::DOWN) // MC_ENEMY_SPAWNER
	{
		m_curDrawObj = OBJECT_TYPE::NONE;
	}
}



