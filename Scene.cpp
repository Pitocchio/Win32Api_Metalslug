#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{

}

void CScene::Update()
{
	CObjectMgr::GetInst()->Update();
}

void CScene::LateUpdate()
{
	CObjectMgr::GetInst()->LateUpdate();
}

void CScene::Render(HDC hdc)
{
	CObjectMgr::GetInst()->Render(hdc);
}
