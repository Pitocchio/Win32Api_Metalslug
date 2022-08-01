#include "stdafx.h"
#include "Rigidbody2D.h"

CRigidbody2D::CRigidbody2D()
	: m_bActive(true)
	, m_fMass (1.f)
	, m_fFricCoeff(100.f)
	, m_fMaxSpeed(100.f)
{
}

CRigidbody2D::~CRigidbody2D()
{
}

void CRigidbody2D::Init()
{
}

void CRigidbody2D::Update()
{
}

void CRigidbody2D::LateUpdate()
{
}

void CRigidbody2D::Render(HDC hdc)
{
}

void CRigidbody2D::InitForce()
{
	m_vForce = Vector2(0.0f, 0.0f);
}

void CRigidbody2D::AddForce(Vector2 force)
{
	m_vForce += force;
}

void CRigidbody2D::CalVelocity()
{
	float fForce = m_vForce.Length();   // => 기존 힘 벡터에서 순수한 힘의 크기를 구함(벡터 길이)

	if (fForce != 0.f)
	{
		m_vForce.Normalize();						// => 힘 벡터를 단위 벡터로 만들어줌(벡터의 방향)

		float m_fAccel = fForce / m_fMass;			// => 가속도의 크기를 구함(힘 / 질량)        

		m_vAccel = m_vForce * m_fAccel;			    // => 가속도를 구함  (속도 = 힘 + 방향)

		m_vVelocity += m_vAccel * DT;				// => 속도를 구함
	}

	//if (m_vVelocity.Length() != 0.f)                 // => 마찰력에 의한 반대방향으로의 가속도 적용
	//{
	//	Vector2 vFricDir = -m_vVelocity;
	//	vFricDir.Normalize();

	//	Vector2 vFriction = vFricDir * m_fFricCoeff * DT;
	//	if (m_vVelocity.Length() <= vFriction.Length())
	//	{
	//		// 마찰 가속도가 본래 속도보다 더 큰 경우
	//		m_vVelocity = Vector2(0.f, 0.f);
	//	}
	//	else
	//	{
	//		m_vVelocity += vFriction;           
	//	}
	//}

	//if (m_vVelocity.Length() > m_fMaxSpeed)		// => 최대속도 제한
	//{
	//	m_vVelocity.Normalize(); 
	//	m_vVelocity *= m_fMaxSpeed;
	//}
}

void CRigidbody2D::SetMass(float mass)
{
	m_fMass = mass;
}

float CRigidbody2D::GetMass() const
{
	return m_fMass;
}

float CRigidbody2D::GetSpeed() 
{
	return m_vVelocity.Length();
}

void CRigidbody2D::SetVelocity(Vector2 velocity)
{
	m_vVelocity = velocity;
}

void CRigidbody2D::AddVelocity(Vector2 velocity)
{
	m_vVelocity += velocity;
}

Vector2 CRigidbody2D::GetVelocity()
{
	return m_vVelocity;
}

void CRigidbody2D::SetMaxSpeed(float speed)
{
	m_fMaxSpeed = speed;
}
