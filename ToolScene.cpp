#include "stdafx.h"
#include "ToolScene.h"

CToolScene::CToolScene()
{
}

CToolScene::~CToolScene()
{
}

void CToolScene::Update()
{
	CScene::Update(); // �θ� ���� �ִ� ����Լ� ���

	// �����̽� ���� �� Scene ��ȯ
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::SPACE) == KEY_STATE::KEY_DOWN)
	{
		//CSceneMgr::GetInst()->ChangeScene(SCENE_TYPE::GAME);

		CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::GAME);
	}
}

void CToolScene::Enter()
{
}

void CToolScene::Exit()
{
	CObjectMgr::GetInst()->Release();
}
