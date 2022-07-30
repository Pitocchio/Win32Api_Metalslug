#include "stdafx.h"
#include "Transform2D.h"

CTransform2D::CTransform2D()
	:m_pOwnerObj(nullptr)

{
}

CTransform2D::~CTransform2D()
{
}

void CTransform2D::Init()
{
}

void CTransform2D::Update()
{
}

void CTransform2D::LateUpdate()
{
}

void CTransform2D::Render(HDC hdc)
{
}

void CTransform2D::SetOwnerObj(CObject* obj)
{
	m_pOwnerObj = obj;
}

void CTransform2D::SetPos(Vector2 vec)
{
	m_vPos = vec;
}

Vector2 CTransform2D::GetPos() const
{
	return m_vPos;
}

void CTransform2D::SetSize(Vector2 vec)
{
	m_vSize = vec;
}

Vector2 CTransform2D::GetSize() const
{
	return m_vSize;
}

void CTransform2D::SetAngle(float angle)
{
	m_fAngle = angle;
}

float CTransform2D::GetAngle() const
{
	return m_fAngle;
}

void CTransform2D::SetIsActive(bool b)
{
	m_bActive = b;
}

bool CTransform2D::GetIsActive()
{
	return m_bActive;
}
