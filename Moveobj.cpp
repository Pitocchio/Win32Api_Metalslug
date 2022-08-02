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
	m_pCollider = new CBoxCollider2D();
	AddComponent(COMPONENT_TYPE::BOXCOLLIDER2D, m_pCollider);

	m_pRigidbody = new CRigidbody2D();
	AddComponent(COMPONENT_TYPE::RIGIDBODY2D, m_pRigidbody);
}

void CMoveobj::Move()
{
}

