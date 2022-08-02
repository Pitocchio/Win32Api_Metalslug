#include "stdafx.h"
#include "Collider2D.h"

UINT CCollider2D::g_iNextID = 0;

CCollider2D::CCollider2D()
	:m_pOwnerObj(nullptr)
	,m_iID(g_iNextID++)
	,m_iCollision(0)
{
}

CCollider2D::CCollider2D(const CCollider2D& origin)
	: m_pOwnerObj(nullptr)
	, m_ColliderType(origin.m_ColliderType)
	, m_iCollision(origin.m_iCollision)
	, m_vOffset(origin.m_vOffset)
	, m_bActive(origin.m_bActive)
	, m_iID(g_iNextID++)
{
	
	
}

CCollider2D::~CCollider2D()
{
}


void CCollider2D::SetOwnerObj(CObject* obj)
{
	m_pOwnerObj = obj;
}

CObject* CCollider2D::GetOwnerObj()
{
	return m_pOwnerObj;
}

CCollider2D* CCollider2D::GetOtherObjCol()
{
	return m_pOtherObjCol;
}



void CCollider2D::SetOffset(Vector2 vec)
{
	m_vOffset = vec;
}

Vector2 CCollider2D::GetOffset() const
{
	return m_vOffset;
}



bool CCollider2D::IsCollision() const
{
	return m_iCollision > 0;
}

void CCollider2D::SetIsColliderType(COLLIDER_TYPE type)
{
	m_ColliderType = type;
}

COLLIDER_TYPE CCollider2D::GetIsColliderType() const
{
	return m_ColliderType;
}

void CCollider2D::SetIsActive(bool b)
{
	m_bActive = b;
}

bool CCollider2D::IsActive()
{
	return m_bActive;
}

void CCollider2D::OnCollision(CCollider2D* pOther)
{
}

void CCollider2D::OnCollisionEnter(CCollider2D* pOther)
{
	++m_iCollision;
	m_pOtherObjCol = pOther;

}

void CCollider2D::OnCollisionExit(CCollider2D* pOther)
{
	--m_iCollision;
}

void CCollider2D::Init()
{
}

void CCollider2D::Update()
{
}

void CCollider2D::LateUpdate()
{
}

void CCollider2D::Render(HDC hdc)
{
}
