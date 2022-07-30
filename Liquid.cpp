#include "stdafx.h"
#include "Liquid.h"

CLiquid::CLiquid()
{
}

CLiquid::~CLiquid()
{
}

void CLiquid::Init()
{
	CObject::Init(); // �θ�, �� CObject Init()���� ȣ���ؼ� transform�̶� collider �־��� 

	m_pTransform->SetOwnerObj(this);
	m_pTransform->SetPos(Vector2(PROJECILE_POS_X, PROJECILE_POS_Y));
	m_pTransform->SetSize(Vector2(PROJECILE_SIZE_X, PROJECILE_SIZE_Y));
	m_pTransform->SetAngle(NULL);

	m_pCollider->SetOwnerObj(this);
	m_pCollider->SetIsColliderType(COLLIDER_TYPE::BOX2D);
	m_pCollider->SetOffset(Vector2(PROJECILE_POS_X, PROJECILE_POS_Y));
	m_pCollider->SetSize(Vector2(PROJECILE_SIZE_X - int(PROJECILE_SIZE_X * 0.2f), PROJECILE_SIZE_Y - int(PROJECILE_SIZE_Y * 0.2f)));
	m_pCollider->SetIsActive(true);

	m_vLook = { -1, 0 };
	m_fSpeed = MOVEOBJ_SPEED;

	m_ObjectType = OBJECT_TYPE::M_ZOMBIE_LIQUID;
	m_ObjectState = OBJECT_STATE::IDLE;

}

void CLiquid::LateInit()
{
}

void CLiquid::Update()
{
}

void CLiquid::LateUpdate()
{
	if (m_pCollider->IsCollision())
	{
		switch (m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetObjectType())
		{
		case OBJECT_TYPE::M_PLAYER:
			CEventMgr::GetInst()->DeleteObject(this);
			break;
		}
	}
}

void CLiquid::Move()
{
}
