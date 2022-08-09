#include "stdafx.h"
#include "TimeMgr.h"

CTimeMgr* CTimeMgr::m_pInst = nullptr;

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);


	m_dDT = 0.;
	m_dAcc = 0.;
	m_iCallCount = 0;
	m_iFPS = 0;
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� ������ ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	// ���� ī��Ʈ ���� ���� ������ ���� (������ ����� ����)
	m_llPrevCount = m_llCurCount;

	++m_iCallCount;
	m_dAcc += m_dDT;

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

	}
}
