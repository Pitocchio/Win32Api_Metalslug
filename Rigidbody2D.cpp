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
	float fForce = m_vForce.Length();               // => ���� �� ���Ϳ��� ������ ���� ũ�⸦ ����(���� ����)

	// 1. ���� �ӵ� ���
	if (fForce != 0.f)
	{
		m_vForce.Normalize();						// => �� ���͸� ���� ���ͷ� �������(������ ����)

		float m_fAccel = fForce / m_fMass;			// => ���ӵ��� ũ�⸦ ����(�� / ����)        

		m_vAccel = m_vForce * m_fAccel;			    // => ���ӵ��� ����  (�ӵ� = �� + ����)
		
	}

	m_vAccel += m_vAccelA;                           // => for �߷� ����
	m_vVelocity += m_vAccel * DT;			         	// => �ӵ��� ����

	// 2. ������ ���� (�����¿� ���� �ݴ� ���������� ���ӵ� ������ Ī�Ѵ�, �� ��ü�� ���� �ƴ�)
	if (m_vVelocity.Length() != 0.f)               
	{
		Vector2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vector2 vFriction = vFricDir * m_fFricCoeff * DT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			m_vVelocity = Vector2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;           
		}
	}

	// 3. �ִ� �ӷ� ����
	if (m_vVelocity.Length() > m_fMaxSpeed)		
	{
		m_vVelocity.Normalize(); 
		m_vVelocity *= m_fMaxSpeed;
		// �������� ������� ������ �ƽ� ���ǵ� �����ָ� ��
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
