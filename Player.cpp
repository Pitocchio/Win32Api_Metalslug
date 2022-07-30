#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
	
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	CObject::Init(); // �θ�, �� CObject Init()���� ȣ���ؼ� transform�̶� collider �־��� 

	m_pTransform->SetOwnerObj(this);
	m_pTransform->SetPos(Vector2(PLAYER_POS_X, PLAYER_POS_Y));
	m_pTransform->SetSize(Vector2(PLAYER_SIZE_STAND_X, PLAYER_SIZE_STAND_Y));
	m_pTransform->SetAngle(NULL);

	m_pCollider->SetOwnerObj(this);
	m_pCollider->SetIsColliderType(COLLIDER_TYPE::BOX2D);
	m_pCollider->SetOffset(Vector2(PLAYER_POS_X, PLAYER_POS_Y));
	m_pCollider->SetSize(Vector2(PLAYER_SIZE_STAND_X-int(PLAYER_SIZE_STAND_X * 0.2f), PLAYER_SIZE_STAND_Y- int(PLAYER_SIZE_STAND_Y * 0.2f)));
	m_pCollider->SetIsActive(true);

	m_vLook = { 0, 0 };
	m_fSpeed = MOVEOBJ_SPEED;

	m_ObjectState = OBJECT_STATE::IDLE;
	m_ObjectType = OBJECT_TYPE::M_PLAYER;

	m_curWeapon = ATTACKOBJ_WEAPON_TYPE::BASICGUN;
	m_iLife = 3;

	m_iBulletCount = 1000;
	m_iGrenadeCount = 10;

}

void CPlayer::LateInit()
{
}

void CPlayer::Update()
{
	Move();

	// � �������� ���� Ÿ�� �� �޾Ƽ� �׿� �´� ���� ���� ex Į, ��, ����ź
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::Z) == KEY_STATE::KEY_HOLD)
		Attack();
}

void CPlayer::LateUpdate()
{
	if (m_pCollider->IsCollision())
	{
		switch (m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetObjectType())
		{
		// ��� ó��
		case OBJECT_TYPE::M_ZOMBIE_LIQUID:
			CEventMgr::GetInst()->DeleteObject(this);
			break;
		case OBJECT_TYPE::M_REBEL_GRENADE:
			CEventMgr::GetInst()->DeleteObject(this);
			break;
		// ���� �̺�Ʈ �� ���� �ʿ�
		}
	}
}

void CPlayer::Move()
{
	map<COMPONENT_TYPE, CComponent*>::iterator iter = m_mapComponent.find(COMPONENT_TYPE::TRANSFORM2D);

	Vector2 vTemp = m_pTransform->GetPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_HOLD)
	{
		m_vLook = { -1, 0 };
		vTemp.x += (m_vLook.x * m_fSpeed) * CTimeMgr::GetInst()->GetDeltatime();
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_HOLD)
	{
		m_vLook = { 1, 0 };
		vTemp.x += (m_vLook.x * m_fSpeed) * CTimeMgr::GetInst()->GetDeltatime();
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::UP) == KEY_STATE::KEY_HOLD)
	{
		m_vLook = { 0, -1 };
		vTemp.y += (m_vLook.y * m_fSpeed) * CTimeMgr::GetInst()->GetDeltatime();
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::DOWN) == KEY_STATE::KEY_HOLD)
	{
		m_vLook = { 0, 1 };
		vTemp.y += (m_vLook.y * m_fSpeed) * CTimeMgr::GetInst()->GetDeltatime();
	}

	m_pTransform->SetPos(vTemp);
	m_pCollider->SetOffset(vTemp);

	// Ʈ������ �����ǰ� �ݶ��̴� �������� ������ ���� ���̴� ���� ���� �־��ش�
}

void CPlayer::Attack()
{
	// �Ѿ� �߻�
}
