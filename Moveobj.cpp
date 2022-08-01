#include "stdafx.h"
#include "Moveobj.h"


CMoveobj::CMoveobj()
{
}

CMoveobj::~CMoveobj()
{
}


void CMoveobj::Init()
{
	m_pRigidbody = new CRigidbody2D();
	AddComponent(COMPONENT_TYPE::RIGIDBODY2D, m_pRigidbody);
}

void CMoveobj::Move()
{
}

