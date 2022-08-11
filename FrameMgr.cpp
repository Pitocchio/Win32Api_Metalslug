#include "stdafx.h"
#include "FrameMgr.h"

CFrameMgr* CFrameMgr::m_pInst = nullptr;

void CFrameMgr::Update()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency); 

}





void CFrameMgr::Update()
{
}

void CFrameMgr::LimitFrame()
{
}
