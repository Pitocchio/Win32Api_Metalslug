#include "stdafx.h"
#include "TimeMgr.h"

CTimeMgr* CTimeMgr::m_pInst = nullptr;

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCount); // 현재 CPU의 틱을 받아온다
	QueryPerformanceFrequency(&m_llFrequency); 

	m_dDT = 0.;
	m_dAcc = 0.;
	m_iCallCount = 0;
	m_iFPS = 0;
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// DT : 이전프레임에서 현재프레임 갱신까지 걸린 시간
	// 이전 프레임 카운팅과 현재 프레임 카운팅 값의 차이를 구한 뒤, 시간 단위로 변환하기 위해 m_llFrequency로 나누어준다)
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;


	++m_iCallCount;
	m_dAcc += m_dDT;
	if (m_dAcc >= 1.) // 누적시간이 1.f초가 되면
	{
		m_iFPS = m_iCallCount; // 1.f초 동안의 누적된 호출 횟수, 즉 약 1초동안 몇번이나 갱신되었는지 => FPS
		m_dAcc = 0.;
		m_iCallCount = 0;
	}
}

void CTimeMgr::LimitFPS()
{
	m_dDT_test = 0.f;

	while (m_dDT_test < 16.f)
	{
		QueryPerformanceCounter(&m_lltest);
		m_dAT_test = (float)m_lltest.QuadPart / (double)m_llFrequency.QuadPart;

		m_dDT_test += m_dAT_test;
	}

	//cout << m_dDT_test << endl;

}







// 지금 내 거에서는 델타타임이 알파타임 역할 중


/*

FPS 60 고정

1초에 60번 프레임 갱신 => 16ms당 1번 갱신 

델타타임 += 알파타임 (FPS 제한 없이 게임 돌릴 시, 한프레임에 시작하고 끝날때 까지 몇 초 걸리는지)


							=>  델타타임이 16ms보다 커지게 된다면 로직을 실행한다
								if (dt =>16ms)
								{

									update;

								} 

어떻게 고정을 시켜야 할까요?!




*/
