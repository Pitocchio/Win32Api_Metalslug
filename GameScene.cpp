#include "stdafx.h"
#include "GameScene.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	{
		CScene::Update(); // �θ� ���� �ִ� ����Լ� ���

		//�����̽� ���� �� Scene ��ȯ
		if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::ENTER) == KEY_STATE::DOWN)
		{
			//CSceneMgr::GetInst()->ChangeScene(SCENE_TYPE::GAME);

			CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::TOOL);
		}
	}
}

void CGameScene::Enter()
{
	m_strFilePath = L"mapdata\\OriginData.bin";


	//// ������Ʈ �߰�

	CStage* pStage = new CStage(OBJECT_TYPE::S_GROUND);
	CEventMgr::GetInst()->CreateObject(pStage, OBJECT_TYPE::S_GROUND);

	CPlayer* pPlayer = new CPlayer();
	CEventMgr::GetInst()->CreateObject(pPlayer, OBJECT_TYPE::M_PLAYER);

	/*CProjectile* pLiquid = new CLiquid();
	CEventMgr::GetInst()->CreateObject(pLiquid, OBJECT_TYPE::M_ZOMBIE_LIQUID);*/

	//CGroundCollider* pGCol = new CGroundCollider();
	//CEventMgr::GetInst()->CreateObject(pGCol, OBJECT_TYPE::C_GROUNDCOLLIDER);


	// �浹 ���� ���� (���� ������ �浹 �˻縦 ������ ������Ʈ Ÿ�Ե�)

	//CCollisionMgr::GetInst()->CheckObjectType(OBJECT_TYPE::M_PLAYER, OBJECT_TYPE::C_GROUNDCOLLIDER);


	// Camera Look ����
	CCamera::GetInst()->SetLookAt(Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT*0.5f));


	// Map Object Data File Load
	LoadMapObj(m_strFilePath);


	
}

void CGameScene::Exit()
{
	// �浹 ���� ����
	CCollisionMgr::GetInst()->ResetObjectType();

	CObjectMgr::GetInst()->Release();

	/*for (vector <MAPOBJ*>::iterator iter = m_vecMapObj.begin(); iter != m_vecMapObj.end(); ++iter)
	{
		if ((*iter) != nullptr)
			delete* iter;
	}

	m_vecMapObj.clear();*/


}

void CGameScene::Render(HDC hdc)
{
	CObjectMgr::GetInst()->Render(hdc);
	//CMapLineMgr::GetInst()->Render(hdc);

	CMapObjMgr::GetInst()->Render(hdc);
}

void CGameScene::LoadMapObj(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	if (pFile == nullptr)
		return;

	LONG type = 0;
	POINT pt1 = {};
	POINT pt2 = {};
	
	while (feof(pFile) == 0)
	{
		fread(&type, sizeof(LONG), 1, pFile);
		fread(&pt1.x, sizeof(LONG), 1, pFile);
		fread(&pt1.y, sizeof(LONG), 1, pFile);
		fread(&pt2.x, sizeof(LONG), 1, pFile);
		fread(&pt2.y, sizeof(LONG), 1, pFile);

		if (feof(pFile) != 0)
			break;

		if (type == (UINT)OBJECT_TYPE::ML_LINE)
		{
			CMapLine* temp = new CMapLine(pt1, pt2);
			CMapObjMgr::GetInst()->AddMapLine(temp);
		}
		else
		{
			CMapCollider* temp = new CMapCollider(pt1, pt2, type);
			CMapObjMgr::GetInst()->AddMapCol(temp);
		}
	}

	cout << "\nFile Load Success!\n";

	fclose(pFile);
}