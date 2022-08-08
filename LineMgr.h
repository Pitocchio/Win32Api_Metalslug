#pragma once

class CLine;

class CLineMgr
{
	SINGLETONE(CLineMgr)

public:
	void Init();
	void Render(HDC hdc);
	void Release();
public:
	vector<CLine*> GetVecLine() { return m_pVecLine; }

private:
	vector<CLine*> m_pVecLine;
};

