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

		// �����̽� ���� �� Scene ��ȯ
		//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::SPACE) == KEY_STATE::KEY_DOWN)
		//{
		//	//CSceneMgr::GetInst()->ChangeScene(SCENE_TYPE::GAME);

		//	CEventMgr::GetInst()->ChangeScene(SCENE_TYPE::TOOL);
		//}
	}
}

void CGameScene::Enter()
{
	//// ������Ʈ �߰�
	CPlayer* pPlayer = new CPlayer();
	CEventMgr::GetInst()->CreateObject(pPlayer, OBJECT_TYPE::M_PLAYER);

	////CProjectile* pLiquid = new CLiquid();
	////CEventMgr::GetInst()->CreateObject(pLiquid, OBJECT_TYPE::M_ZOMBIE_LIQUID);

	//CGroundCollider* pGCol = new CGroundCollider();
	//CEventMgr::GetInst()->CreateObject(pGCol, OBJECT_TYPE::C_GROUNDCOLLIDER);


	//// �浹 ���� ���� (���� ������ �浹 �˻縦 ������ ������Ʈ Ÿ�Ե�)
	//

	//CCollisionMgr::GetInst()->CheckObjectType(OBJECT_TYPE::M_PLAYER, OBJECT_TYPE::C_GROUNDCOLLIDER);


}

void CGameScene::Exit()
{
	// �浹 ���� ����
	CCollisionMgr::GetInst()->ResetObjectType();

	CObjectMgr::GetInst()->Release();
}
