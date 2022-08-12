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

	bool LimitFPS(float _frame);

	

private: // Variables

	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_dDT; // ������ ������ �ð� ��
	double m_dAcc; //1�� üũ�� ���� ���� �ð�
	UINT m_iCallCount; // �ʴ� ȣ�� Ƚ�� üũ
	UINT m_iFPS; // �ʴ� ȣ�� Ƚ��



	// Frame
	LARGE_INTEGER m_llCurCnt;
	LARGE_INTEGER m_llPrevCnt;

	double m_dTotalTime;
	double m_dLimit;
};

