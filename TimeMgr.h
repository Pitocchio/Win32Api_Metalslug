#pragma once
class CTimeMgr
{
	SINGLETONE(CTimeMgr)

public: // Lifecycle
	void Init();
	void Update();

public: // Methods
	float GetDeltatime() const ;

private: // Variables
	LARGE_INTEGER m_liPeriodFrequency;
	LARGE_INTEGER m_liCurTime;
	LARGE_INTEGER m_liLastTime;
	float m_fDeltaTime;
};

