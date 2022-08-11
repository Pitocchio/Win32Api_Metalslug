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

	double m_dDT; // ������ ������ �ð� ��
	double m_dAcc; //1�� üũ�� ���� ���� �ð�

	double m_dAT;
	double m_dDT;


};

