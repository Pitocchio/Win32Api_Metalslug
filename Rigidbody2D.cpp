#include "stdafx.h"
#include "Rigidbody2D.h"

CRigidbody2D::CRigidbody2D()
	: m_bActive(true)
	, m_fMass (1.f)
	, m_fFricCoeff(100.f)
	, m_fMaxSpeed(200.f)
	, m_bGround(false)
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
	float fForce = m_vForce.Length();               // => 기존 힘 벡터에서 순수한 힘의 크기를 구함(벡터 길이)

	// 1. 현재 속도 계산
	if (fForce != 0.f)
	{
		m_vForce.Normalize();						// => 힘 벡터를 단위 벡터로 만들어줌(벡터의 방향)

		float m_fAccel = fForce / m_fMass;			// => 가속도의 크기를 구함(힘 / 질량)        

		m_vAccel = m_vForce * m_fAccel;			    // => 가속도를 구함  (속도 = 힘 + 방향)
		
	}

	m_vAccel += m_vAccelA;                           // => for 중력 구현
	m_vVelocity += m_vAccel * DT;			         	// => 속도를 구함

	// 2. 마찰력 적용 (마찰력에 의한 반대 방향으로의 가속도 정도로 칭한다, 이 자체가 힘은 아님)
	if (m_vVelocity.Length() != 0.f)               
	{
		Vector2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vector2 vFriction = vFricDir * m_fFricCoeff * DT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = Vector2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;           
		}
	}

	// 3. 최대 속력 제한
	if (m_vVelocity.Length() > m_fMaxSpeed)		
	{
		m_vVelocity.Normalize(); 
		m_vVelocity *= m_fMaxSpeed;
		// 단위벡터 만들어준 다음에 맥스 스피드 곱해주면 끝
	}
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

void CRigidbody2D::ApplyGravity()
{
	SetAccelAlpha(Vector2(0.f, 800.f));
}

void CRigidbody2D::SetGround(bool b)
{
	m_bGround = b;
}

bool CRigidbody2D::IsGround()
{
	if (m_bGround)
		return true;
	return false;
}

void CRigidbody2D::InitAccel()
{
	m_vAccel = Vector2(0.0f, 0.0f);
}

void CRigidbody2D::InitAccelAlpha()
{
	m_vAccelA = Vector2(0.0f, 0.0f);
}

void CRigidbody2D::SetAccelAlpha(Vector2 accel)
{
	m_vAccelA = accel;
}
