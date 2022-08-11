#pragma once

class CFrameMgr
{
	SINGLETONE(CFrameMgr)

public:
	void Init();
	void Update();

public:
	void LimitFrame();

private:

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; // 프레임 사이의 시간 값
	double m_dAcc; //1초 체크를 위한 누적 시간

	double m_dAT;
	double m_dDT;


};

