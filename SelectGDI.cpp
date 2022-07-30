#include "stdafx.h"
#include "SelectGDI.h"


SelectGDI::SelectGDI(HDC hdc, PEN_TYPE pentype)
	: m_hDC(hdc)
	, hDefaultBrush(nullptr)
	, hDefaultPen(nullptr)
{
	HPEN hPen = CCore::GetInst()->GetPen(pentype);
	hDefaultPen = (HPEN)SelectObject(hdc, hPen);
}

SelectGDI::SelectGDI(HDC hdc, BRUSH_TYPE brushtype)
	: m_hDC(hdc)
	, hDefaultBrush(nullptr)
	, hDefaultPen(nullptr)
{
	HBRUSH hBrush = CCore::GetInst()->GetBrush(brushtype);
	hDefaultBrush = (HBRUSH)SelectObject(hdc, hBrush);
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, hDefaultPen);
	SelectObject(m_hDC, hDefaultBrush);
}
