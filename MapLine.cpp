#include "stdafx.h"
#include "MapLine.h"

CMapLine::CMapLine()
	:m_tSrc{}
	,m_tDst{}
	,m_fDist(0.f)
	, m_fIntercept(0.f)
	,m_Objtype(OBJECT_TYPE::ML_LINE)
{
}

CMapLine::~CMapLine()
{
}

CMapLine::CMapLine(POINT _Src, POINT _Dst)
{
	m_tSrc.x = _Src.x;
	m_tSrc.y = _Src.y;

	m_tDst.x = _Dst.x;
	m_tDst.y = _Dst.y;

	m_fDist = 0.f;
	m_fIntercept = 0.f;

	m_Objtype = OBJECT_TYPE::ML_LINE;
}

void CMapLine::Init()
{
	// 기울기 (Y증가량 / X증가량) : 양수일 때 오르막, 음수일 때 내리막
	m_fDist = ((float)(m_tDst.y - m_tSrc.y) / (float)(m_tDst.x - m_tSrc.x)); 
	
	// y 절편 (직선이 y축과 만나는 점의 y좌표 혹은 x = 0일 때의 y값)
	m_fIntercept = m_tDst.y - (m_tDst.x * m_fDist); 

	/*
		직선의 방정식 : y = mx + n
		기울기(m) = (y2 - y1) / (x2 - x1)
		y절편(n) = y - mx
	*/
}



void CMapLine::Render(HDC hDC)
{
	PEN_TYPE ePen = PEN_TYPE::RED;

	SelectGDI pen(hDC, ePen);
	SelectGDI brush(hDC, BRUSH_TYPE::HOLLOW); // 임시객체(지역변수)기 때문에 나갈때 자동으로 소멸자 호출, 그때 다시 셀렉
	POINT tempSrc = CCamera::GetInst()->GetRenderPos(m_tSrc);
	POINT tempDst = CCamera::GetInst()->GetRenderPos(m_tDst);

	MoveToEx(hDC, tempSrc.x, tempSrc.y, nullptr);
	LineTo(hDC, tempDst.x, tempDst.y);
}

// 플레이어의 X포지션이 현재 라인에 위치해 있는가
bool CMapLine::IsInLine(INFO& _tInfo) 
{
	if (m_tSrc.x <= _tInfo.fX && m_tDst.x >= _tInfo.fX)
		return true;

	return false;
}


int CMapLine::LineCheck(INFO& _tInfo)
{
	if (m_fDist == 0) // 기울기가 0이라면
	{
		if (_tInfo.fY >= (m_fDist * _tInfo.fX + m_fIntercept) - 50) // 현재 플레이어 y포지션이 (y절편 - 50)보다 크거나 같다면
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
