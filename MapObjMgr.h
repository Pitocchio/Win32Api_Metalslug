#pragma once

class CMapLine;
class CMapCollider;

class CMapObjMgr
{
	SINGLETONE(CMapObjMgr)

public: // Lifecycle
	void Init();
	void Render(HDC hdc);
	void Release();


public: // Methods

	// Line
	vector<CMapLine*> GetVecLine() { return m_pVecLine; }
	vector<CMapCollider*> GetVecCol() { return m_pVecCol; }

	void AddMapLine(CMapLine* _Line);
	void AddMapCol(CMapCollider* _Col);



private: // Variables

	// Line
	vector<CMapLine*> m_pVecLine;
	vector<CMapCollider*> m_pVecCol;
};

