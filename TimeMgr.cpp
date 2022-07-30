#include "stdafx.h"
#include "TimeMgr.h"

CTimeMgr* CTimeMgr::m_pInst = nullptr;

void CTimeMgr::Init()
{
	QueryPerformanceFrequency(&m_liPeriodFrequency);
	QueryPerformanceCounter(&m_liLastTime);
	m_fDeltaTime = 0.0f;
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_liCurTime);
	m_fDeltaTime = (float)(m_liCurTime.QuadPart - m_liLastTime.QuadPart) / m_liPeriodFrequency.QuadPart;
	m_liLastTime = m_liCurTime;
}

float CTimeMgr::GetDeltatime() const
{
	return m_fDeltaTime;
}
