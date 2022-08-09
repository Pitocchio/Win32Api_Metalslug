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

	double m_dDT; // ������ ������ �ð� ��
	double m_dAcc; //1�� üũ�� ���� ���� �ð�
	UINT m_iCallCount; // �ʴ� ȣ�� Ƚ�� üũ
	UINT m_iFPS; // �ʴ� ȣ�� Ƚ��

	

};

