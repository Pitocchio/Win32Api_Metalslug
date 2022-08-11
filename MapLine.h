#pragma once


class CMapLine
{

public:
	CMapLine();
	~CMapLine();
	CMapLine(POINT _Src, POINT _Dst);

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
	OBJECT_TYPE m_Objtype;

};

