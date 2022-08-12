#include "stdafx.h"
#include "TimeMgr.h"

CTimeMgr* CTimeMgr::m_pInst = nullptr;

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCount); // ���� CPU�� ƽ�� �޾ƿ´�
	QueryPerformanceFrequency(&m_llFrequency); 

	m_dDT = 0.;
	m_dAcc = 0.;
	m_iCallCount = 0;
	m_iFPS = 0;


	m_dTotalTime = 0.f;
	m_dLimit = 0.016f;
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// DT : ���������ӿ��� ���������� ���ű��� �ɸ� �ð�
	// ���� ������ ī���ð� ���� ������ ī���� ���� ���̸� ���� ��, �ð� ������ ��ȯ�ϱ� ���� m_llFrequency�� �������ش�)
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;


	++m_iCallCount;
	m_dAcc += m_dDT;
	if (m_dAcc >= 1.) // �����ð��� 1.f�ʰ� �Ǹ�
	{
		m_iFPS = m_iCallCount; // 1.f�� ������ ������ ȣ�� Ƚ��, �� �� 1�ʵ��� ����̳� ���ŵǾ����� => FPS
		m_dAcc = 0.;
		m_iCallCount = 0;
	}
}

bool CTimeMgr::LimitFPS(float _frame)
{
	//m_dTotalTime = 0.f;
	m_dLimit = 1.f / _frame;

	/*while (m_dTotalTime < m_dLimit)
	{
		QueryPerformanceCounter(&m_llCurCnt);
		m_dTotalTime += (double)(m_llCurCnt.QuadPart - m_llPrevCnt.QuadPart) / (double)m_llFrequency.QuadPart;
		m_llPrevCnt = m_llCurCnt;
	}*/

	QueryPerformanceCounter(&m_llCurCnt);
	m_dTotalTime += (double)(m_llCurCnt.QuadPart - m_llPrevCnt.QuadPart) / (double)m_llFrequency.QuadPart;
	m_llPrevCnt = m_llCurCnt;

	if (m_dTotalTime >= m_dLimit) // ����
	{
		m_dTotalTime = 0.f;

		return true;
	}
	else
	{
		return false;
	}
}









/*

FPS 60 ����

1�ʿ� 60�� ������ ���� => 16ms�� 1�� ���� 

��ŸŸ�� += ����Ÿ�� (FPS ���� ���� ���� ���� ��, �������ӿ� �����ϰ� ������ ���� �� �� �ɸ�����)


							=>  ��ŸŸ���� 16ms���� Ŀ���� �ȴٸ� ������ �����Ѵ�
								if (dt =>16ms)
								{

									update;

								} 

��� ������ ���Ѿ� �ұ��?!




*/
