#include "stdafx.h"
#include "MapObjMgr.h"

CMapObjMgr* CMapObjMgr::m_pInst = nullptr;


void CMapObjMgr::Init()
{
	
}

void CMapObjMgr::Render(HDC hdc)
{
	
	for (vector<CMapLine*>::iterator iter = m_pVecLine.begin(); iter != m_pVecLine.end(); ++iter)
	{
		(*iter)->Render(hdc);
	}

	for (vector<CMapCollider*>::iterator iter = m_pVecCol.begin(); iter != m_pVecCol.end(); ++iter)
	{
		(*iter)->Render(hdc);
	}

}

void CMapObjMgr::Release()
{
	for (auto& line : m_pVecLine)
		delete line;
}

void CMapObjMgr::AddMapLine(CMapLine* _Line)
{
	if (_Line != nullptr)
	{
		m_pVecLine.push_back(_Line);
		_Line->Init();
	}

}

void CMapObjMgr::AddMapCol(CMapCollider* _Col)
{
	if (_Col != nullptr)
	{
		m_pVecCol.push_back(_Col);
		_Col->Init();
	}
}
