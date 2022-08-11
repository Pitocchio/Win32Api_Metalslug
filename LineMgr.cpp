#include "stdafx.h"
#include "LineMgr.h"

CMapLineMgr* CMapLineMgr::m_pInst = nullptr;


void CMapLineMgr::Init()
{
	

	m_pVecLine.emplace_back(new CMapLine({ 0, 1000 }, { 500, 1000 }));
	m_pVecLine.emplace_back(new CMapLine({ 500, 1000 }, { 1000, 900 }));
	m_pVecLine.emplace_back(new CMapLine({ 1000, 900 }, { 1200, 900 }));
	m_pVecLine.emplace_back(new CMapLine({ 1200, 900 }, { 1400, 1000 }));
	m_pVecLine.emplace_back(new CMapLine({ 1400, 1000 }, { 1600, 800 }));
	m_pVecLine.emplace_back(new CMapLine({ 1600, 800 }, { 2000, 800 }));

	for (int i = 0; i < m_pVecLine.size(); ++i)
	{
		m_pVecLine[i]->Init();
	}
}

void CMapLineMgr::Render(HDC hdc)
{
	for (int i = 0; i < m_pVecLine.size(); ++i)
	{
		m_pVecLine[i]->Render(hdc);
	}
}

void CMapLineMgr::Release()
{
	for (auto& line : m_pVecLine)
		delete line;
}
