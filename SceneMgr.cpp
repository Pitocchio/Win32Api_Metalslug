#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInst = nullptr;

void CSceneMgr::Init()
{
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CToolScene;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetSceneType(SCENE_TYPE::TOOL);

	m_arrScene[(UINT)SCENE_TYPE::GAME] = new CGameScene; // 모든 Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::GAME]->SetSceneType(SCENE_TYPE::GAME);


	/*m_arrScene[(UINT)SCENE_TYPE::CHARACTER] = new CCharacterScene;
	m_arrScene[(UINT)SCENE_TYPE::GAME] = new CGameScene;
	m_arrScene[(UINT)SCENE_TYPE::OUTTRO] = new COuttroScene;*/

	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::TOOL]; // 현재 Scene 지정
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pCurScene->LateUpdate();
}

void CSceneMgr::Render(HDC hdc)
{
	m_pCurScene->Render(hdc);
}

void CSceneMgr::Release()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::TYPEEND_SCENE; ++i)
	{
		if (m_arrScene[i] != nullptr)
			delete m_arrScene[i];
	}
}

void CSceneMgr::ChangeScene(SCENE_TYPE scene)
{
	m_pCurScene->Exit();

	m_pCurScene = m_arrScene[(UINT)scene];

	m_pCurScene->Enter();
}
