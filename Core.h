#pragma once
class CCore
{
	SINGLETONE(CCore);

public: // LifeCycle
	void Init(HWND hWnd);
	void Progress();
	void Release();

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_Hwnd; }
	HDC GetMainDC() { return m_Hdc; }
	RECT GetMainRect() { return m_RC; }
	HBRUSH GetBrush(BRUSH_TYPE type) { return m_arrBrush[(UINT)type]; }
	HPEN GetPen(PEN_TYPE type) { return m_arrPen[(UINT)type]; }


private: // Variables
	RECT m_RC;
	HWND m_Hwnd;
	HDC m_Hdc;

	HBITMAP m_Hbitmap;
	HDC m_Hbitdc;

	// 자주 사용할 GDI OBJECT
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::TYPEEND_BRUSH];
	HPEN m_arrPen[(UINT)PEN_TYPE::TYPEEND_PEN];

	HWND m_Hdlg;


};

