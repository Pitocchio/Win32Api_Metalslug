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
	// ���� (Y������ / X������) : ����� �� ������, ������ �� ������
	m_fDist = ((float)(m_tDst.y - m_tSrc.y) / (float)(m_tDst.x - m_tSrc.x)); 
	
	// y ���� (������ y��� ������ ���� y��ǥ Ȥ�� x = 0�� ���� y��)
	m_fIntercept = m_tDst.y - (m_tDst.x * m_fDist); 

	/*
		������ ������ : y = mx + n
		����(m) = (y2 - y1) / (x2 - x1)
		y����(n) = y - mx
	*/
}



void CMapLine::Render(HDC hDC)
{
	PEN_TYPE ePen = PEN_TYPE::RED;

	SelectGDI pen(hDC, ePen);
	SelectGDI brush(hDC, BRUSH_TYPE::HOLLOW); // �ӽð�ü(��������)�� ������ ������ �ڵ����� �Ҹ��� ȣ��, �׶� �ٽ� ����
	POINT tempSrc = CCamera::GetInst()->GetRenderPos(m_tSrc);
	POINT tempDst = CCamera::GetInst()->GetRenderPos(m_tDst);

	MoveToEx(hDC, tempSrc.x, tempSrc.y, nullptr);
	LineTo(hDC, tempDst.x, tempDst.y);
}

// �÷��̾��� X�������� ���� ���ο� ��ġ�� �ִ°�
bool CMapLine::IsInLine(INFO& _tInfo) 
{
	if (m_tSrc.x <= _tInfo.fX && m_tDst.x >= _tInfo.fX)
		return true;

	return false;
}


int CMapLine::LineCheck(INFO& _tInfo)
{
	if (m_fDist == 0) // ���Ⱑ 0�̶��
	{
		if (_tInfo.fY >= (m_fDist * _tInfo.fX + m_fIntercept) - 50) // ���� �÷��̾� y�������� (y���� - 50)���� ũ�ų� ���ٸ�
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
