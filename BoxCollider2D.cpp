#include "stdafx.h"
#include "BoxCollider2D.h"

CBoxCollider2D::CBoxCollider2D()
{
}

CBoxCollider2D::~CBoxCollider2D()
{

}


void CBoxCollider2D::SetColliderRect()
{
	m_rcCollider.left = LONG(m_vOffset.x - int(m_vSize.x * 0.5f));
	m_rcCollider.right = LONG(m_vOffset.x + int(m_vSize.x * 0.5f));
	m_rcCollider.top = LONG(m_vOffset.y - int(m_vSize.y * 0.5f));
	m_rcCollider.bottom = LONG(m_vOffset.y + int(m_vSize.y * 0.5f));
}

RECT CBoxCollider2D::GetColliderRect() const
{
	return m_rcCollider;
}

void CBoxCollider2D::SetSize(Vector2 vec)
{
	m_vSize = vec;
}

Vector2 CBoxCollider2D::GetSize() const
{
	return m_vSize;
}

void CBoxCollider2D::Init()
{
}

void CBoxCollider2D::Update()
{
}

void CBoxCollider2D::LateUpdate()
{
}

void CBoxCollider2D::Render(HDC hdc)
{
}

