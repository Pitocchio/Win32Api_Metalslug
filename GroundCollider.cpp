#include "stdafx.h"
#include "GroundCollider.h"

CGroundCollider::CGroundCollider()
{
}

CGroundCollider::~CGroundCollider()
{
}

void CGroundCollider::Init()
{
	CObject::Init(); // �θ�, �� CObject Init()���� ȣ���ؼ� transform�̶� collider �־��� 
	CMapcollider::Init();

	// Component - Transform
	m_pTransform->SetOwnerObj(this);
	m_pTransform->SetPos(Vector2(PLAYER_POS_X-300.f, PLAYER_POS_Y+300.f));
	m_pTransform->SetSize(Vector2(0.f, 0.f));
	m_pTransform->SetAngle(NULL);

	// Component - Collider
	m_pCollider->SetOwnerObj(this);
	m_pCollider->SetIsColliderType(COLLIDER_TYPE::LINE2D);
	m_pCollider->SetOffset(Vector2(0.f, 0.f));
	m_pCollider->SetIsActive(true);



	m_ObjectType = OBJECT_TYPE::C_GROUNDCOLLIDER;



	// ������ ���� ����Ʈ�� ���� ����Ʈ ����
	m_vStartPoint = m_pTransform->GetPos(); // ���� ����Ʈ = Transform Position
	m_vEndPoint = Vector2(m_vStartPoint.x + 800, m_vStartPoint.y);


	dynamic_cast<CLineCollider2D*>(m_pCollider)->SetStartPoint(m_vStartPoint);
	dynamic_cast<CLineCollider2D*>(m_pCollider)->SetEndPoint(m_vEndPoint);
}

void CGroundCollider::LateInit()
{
}

void CGroundCollider::Update()
{
}

void CGroundCollider::LateUpdate()
{
}
