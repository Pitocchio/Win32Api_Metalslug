#pragma once

class CMapLine;

class CMapLineMgr
{
	SINGLETONE(CMapLineMgr)

public:
	void Init();
	void Render(HDC hdc);
	void Release();
public:
	vector<CMapLine*> GetVecLine() { return m_pVecLine; }

private:
	vector<CMapLine*> m_pVecLine;
	//void LoadMapObj(const wstring& _strKry, const wstring& _strRelativePath);
};

