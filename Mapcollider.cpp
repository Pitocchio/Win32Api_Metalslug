#include "stdafx.h"
#include "MapCollider.h"

CMapCollider::CMapCollider()
	:m_ptLeftTop{}
	,m_ptRightBottom{}
	,m_Objtype(OBJECT_TYPE::NONE)
{
}

CMapCollider::~CMapCollider()
{
}

CMapCollider::CMapCollider(POINT _LeftTop, POINT _RightBottom, UINT _ObjType)
{
	m_ptLeftTop = _LeftTop;
	m_ptRightBottom = _RightBottom;

	m_Objtype = OBJECT_TYPE(_ObjType);
}

void CMapCollider::Init()
{
}

void CMapCollider::Render(HDC hDC)
{
	PEN_TYPE ePen = PEN_TYPE::NONE;

	switch (UINT(m_Objtype))
	{
	case UINT(OBJECT_TYPE::MC_CAMERA_FOLLOWPLAYERY):
		ePen = PEN_TYPE::ORANGE;
		break;
	case UINT(OBJECT_TYPE::MC_CAMERA_ROCK):
		ePen = PEN_TYPE::PURPLE;
		break;
	case UINT(OBJECT_TYPE::MC_PLAYER_LEFTMOVEROCK):
		ePen = PEN_TYPE::BLUE;
		break;
	case UINT(OBJECT_TYPE::MC_ENEMY_SPAWNER):
		ePen = PEN_TYPE::GREEN;
		break;
	default:
		break;
	}

	SelectGDI pen(hDC, ePen);
	SelectGDI brush(hDC, BRUSH_TYPE::HOLLOW);

	POINT tempSrc = CCamera::GetInst()->GetRenderPos(m_ptLeftTop);
	POINT tempDst = CCamera::GetInst()->GetRenderPos(m_ptRightBottom);

	Rectangle(hDC, tempSrc.x, tempSrc.y, tempDst.x, tempDst.y);
}
