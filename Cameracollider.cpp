#include "stdafx.h"
#include "Cameracollider.h"

CCameracollider::CCameracollider()
{
}

CCameracollider::~CCameracollider()
{
}

void CCameracollider::Init()
{
	//CObject::Init(); // �θ�, �� CObject Init()���� ȣ���ؼ� transform�̶� collider �־��� 

	//// Component - Transform
	//m_pTransform->SetOwnerObj(this);
	//m_pTransform->SetPos(Vector2(PLAYER_POS_X, PLAYER_POS_Y+300));
	//m_pTransform->SetSize(Vector2(PLAYER_SIZE_STAND_X+500, PLAYER_SIZE_STAND_Y));
	//m_pTransform->SetAngle(NULL);

	//// Component - Collider
	//m_pCollider->SetOwnerObj(this);
	//m_pCollider->SetIsColliderType(COLLIDER_TYPE::BOX2D);
	//m_pCollider->SetOffset(Vector2(PLAYER_POS_X, PLAYER_POS_Y + 300));
	//m_pCollider->SetSize(Vector2(PLAYER_SIZE_STAND_X + 500 - int((PLAYER_SIZE_STAND_X + 500) * 0.03f), PLAYER_SIZE_STAND_Y - int(PLAYER_SIZE_STAND_Y * 0.2f)));
	//m_pCollider->SetIsActive(true);
	 

}

void CCameracollider::LateInit()
{
}

void CCameracollider::Update()
{
}

void CCameracollider::LateUpdate()
{
}
