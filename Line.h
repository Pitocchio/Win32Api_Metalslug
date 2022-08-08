#pragma once
class CLine
{

public:
	CLine();
	~CLine();
	CLine(POINT _Src, POINT _Dst);

public:
	void Init();
	void Render(HDC hDC);

public:
	bool IsInLine(INFO& _tInfo);
	int LineCheck(INFO& _tInfo);
	float Get_Dist() { return m_fDist; }

private:
	POINT m_tSrc;
	POINT m_tDst;
	float m_fDist;
	float m_fIntercept;

};

