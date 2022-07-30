#pragma once

class SelectGDI
{
public:
	SelectGDI(HDC hdc, PEN_TYPE pentype);
	SelectGDI(HDC hdc, BRUSH_TYPE brushtype);
	~SelectGDI();

private:
	HPEN hDefaultPen;
	HBRUSH hDefaultBrush;
	HDC m_hDC;


};

