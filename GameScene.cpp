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
		CScene::Update(); // 부모가 갖고 있는 멤버함수 사용

		// 스페이스 누를 시 Scene 변환
		//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::SPACE) == KEY_STATE::KEY_DOWN)
		//{
		//	//CSceneMgr::GetInst()->ChangeScene(SCENE_TYPE::GAME);

		//	CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::TOOL);
		//}
	}
}

void CGameScene::Enter()
{
	//// 오브젝트 추가
	CPlayer* pPlayer = new CPlayer();
	CEventMgr::GetInst()->CreateObject(pPlayer, OBJECT_TYPE::M_PLAYER);

	////CProjectile* pLiquid = new CLiquid();
	////CEventMgr::GetInst()->CreateObject(pLiquid, OBJECT_TYPE::M_ZOMBIE_LIQUID);

	//CGroundCollider* pGCol = new CGroundCollider();
	//CEventMgr::GetInst()->CreateObject(pGCol, OBJECT_TYPE::C_GROUNDCOLLIDER);


	//// 충돌 지정 설정 (현재 씬에서 충돌 검사를 진행할 오브젝트 타입들)
	//

	//CCollisionMgr::GetInst()->CheckObjectType(OBJECT_TYPE::M_PLAYER, OBJECT_TYPE::C_GROUNDCOLLIDER);


}

void CGameScene::Exit()
{
	// 충돌 지정 해제
	CCollisionMgr::GetInst()->ResetObjectType();

	CObjectMgr::GetInst()->Release();
}
