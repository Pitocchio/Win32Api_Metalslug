#include "stdafx.h"
#include "Line.h"

CLine::CLine()
{
}

CLine::~CLine()
{
}

CLine::CLine(POINT _Src, POINT _Dst)
{
	m_tSrc.x = _Src.x;
	m_tSrc.y = _Src.y;

	m_tDst.x = _Dst.x;
	m_tDst.y = _Dst.y;
}

void CLine::Init()
{
	m_fDist = ((float)(m_tDst.y - m_tSrc.y) / (float)(m_tDst.x - m_tSrc.x));
	m_fIntercept = m_tDst.y - (m_tDst.x * m_fDist);
}



void CLine::Render(HDC hDC)
{
	PEN_TYPE ePen = PEN_TYPE::RED;

	SelectGDI pen(hDC, ePen);
	SelectGDI brush(hDC, BRUSH_TYPE::HOLLOW); // 임시객체(지역변수)기 때문에 나갈때 자동으로 소멸자 호출, 그때 다시 셀렉
	POINT tempSrc = CCamera::GetInst()->GetRenderPos(m_tSrc);
	POINT tempDst = CCamera::GetInst()->GetRenderPos(m_tDst);

	MoveToEx(hDC, tempSrc.x, tempSrc.y, nullptr);
	LineTo(hDC, tempDst.x, tempDst.y);
}

bool CLine::IsInLine(INFO& _tInfo)
{
	if (m_tSrc.x <= _tInfo.fX && m_tDst.x >= _tInfo.fX)
		return true;

	return false;
}

int CLine::LineCheck(INFO& _tInfo)
{
	if (m_fDist == 0)
	{
		if (_tInfo.fY >= (m_fDist * _tInfo.fX + m_fIntercept) - 50)
		{
			_tInfo.fY = (m_fDist * _tInfo.fX + m_fIntercept) - 50;
			return 1;
		}

		return 0;
	}

	for (float i = m_tSrc.x; i <= m_tDst.x; i += 0.5f)
	{
		if (abs(_tInfo.fX - i) <= 0.001f)
		{
			if (_tInfo.fY >= (m_fDist * i + m_fIntercept) - 50)
			{
				_tInfo.fY = (m_fDist * i + m_fIntercept) - 50;
				return 1;
			}
		}
	}

	return 0;
}
