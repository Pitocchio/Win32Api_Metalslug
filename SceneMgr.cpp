#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInst = nullptr;

void CSceneMgr::Init()
{
	m_arrScene[(UINT)SCENE_TYPE::ANITOOL] = new CAniToolScene;
	m_arrScene[(UINT)SCENE_TYPE::ANITOOL]->SetSceneType(SCENE_TYPE::ANITOOL);

	m_arrScene[(UINT)SCENE_TYPE::MAPTOOL] = new CMapToolScene;
	m_arrScene[(UINT)SCENE_TYPE::MAPTOOL]->SetSceneType(SCENE_TYPE::MAPTOOL);

	m_arrScene[(UINT)SCENE_TYPE::GAME] = new CGameScene; 
	m_arrScene[(UINT)SCENE_TYPE::GAME]->SetSceneType(SCENE_TYPE::GAME);


	// 현재 Scene 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::ANITOOL]; 
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
