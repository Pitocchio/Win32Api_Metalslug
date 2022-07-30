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
	CScene::Update(); // 부모가 갖고 있는 멤버함수 사용

	// 스페이스 누를 시 Scene 변환
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
