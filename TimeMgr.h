#pragma once
class CTimeMgr
{
	SINGLETONE(CTimeMgr)

public: // Lifecycle
	void Init();
	void Update();

public: // Methods
	float GetfDT() const { return (float)m_dDT; }
	double GetDT() const { return m_dDT; }
	UINT GetFPS() const { return m_iFPS; }

private: // Variables
	/*LARGE_INTEGER m_liPeriodFrequency;
	LARGE_INTEGER m_liCurTime;
	LARGE_INTEGER m_liLastTime;
	float m_fDeltaTime;*/

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; // 프레임 사이의 시간 값
	double m_dAcc; //1초 체크를 위한 누적 시간
	UINT m_iCallCount; // 초당 호출 횟수 체크
	UINT m_iFPS; // 초당 호출 횟수

	

};

