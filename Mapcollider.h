#pragma once
class CMapCollider
{
public:
	CMapCollider();
	~CMapCollider();
	CMapCollider(POINT _LeftTop, POINT _RightBottom, UINT _ObjType);

public:
	void Init();
	void Render(HDC hDC);

public:


private:
	POINT m_ptLeftTop;
	POINT m_ptRightBottom;
	
	OBJECT_TYPE m_Objtype;

};

