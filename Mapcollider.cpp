#include "stdafx.h"
#include "Mapcollider.h"

CMapcollider::CMapcollider()
{
}

CMapcollider::~CMapcollider()
{
}

void CMapcollider::Init()
{
	m_pCollider = new CLineCollider2D();
	AddComponent(COMPONENT_TYPE::LINECOLLIDER2D, m_pCollider);
}
