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
	CObject::Init(); // 부모, 즉 CObject Init()먼저 호출해서 transform이랑 collider 넣어줌 
	CMoveobj::Init();

	// Component - Transform
	m_pTransform->SetOwnerObj(this);
	m_pTransform->SetPos(Vector2(PLAYER_POS_X, PLAYER_POS_Y));
	m_pTransform->SetSize(Vector2(PLAYER_SIZE_STAND_X, PLAYER_SIZE_STAND_Y));
	m_pTransform->SetAngle(NULL);

	// Component - Collider
	m_pCollider->SetOwnerObj(this);
	m_pCollider->SetIsColliderType(COLLIDER_TYPE::BOX2D);
	m_pCollider->SetOffset(Vector2(PLAYER_POS_X, PLAYER_POS_Y));
	m_pCollider->SetSize(Vector2(PLAYER_SIZE_STAND_X-int(PLAYER_SIZE_STAND_X * 0.2f), PLAYER_SIZE_STAND_Y- int(PLAYER_SIZE_STAND_Y * 0.2f)));
	m_pCollider->SetIsActive(true);

	// Component - Rigidbody
	m_pRigidbody->SetMass(1.f);


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
	m_pRigidbody->CalVelocity();

	Move();

	// 어떤 어택인지 어택 타입 값 받아서 그에 맞는 어택 구현 ex 칼, 총, 수류탄
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::Z) == KEY_STATE::KEY_HOLD)
		Attack();
}

void CPlayer::LateUpdate()
{



	if (m_pCollider->IsCollision())
	{
		switch (m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetObjectType())
		{
		// 사망 처리

		// LineCollider



		// MoveObj
		case OBJECT_TYPE::M_ZOMBIE_LIQUID:
			CEventMgr::GetInst()->DeleteObject(this);
			break;
		case OBJECT_TYPE::M_REBEL_GRENADE:
			CEventMgr::GetInst()->DeleteObject(this);
			break;

		
		}
	}



	m_pRigidbody->InitForce(); 
}

void CPlayer::Move()
{
	//Vector2 vTemp = m_pTransform->GetPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_HOLD)
	{
		//m_vLook = { -1, 0 };
		//vTemp.x += (m_vLook.x * m_fSpeed) * DT;
		m_pRigidbody->AddForce(MyVector2(-200.f, 0.f));
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_HOLD)
	{
		m_pRigidbody->AddForce(MyVector2(200.f, 0.f));

		//m_vLook = { 1, 0 };
		//vTemp.x += (m_vLook.x * m_fSpeed) * DT;
	}
	
	// 이동 방향
	Vector2 vDir = m_pRigidbody->GetVelocity();
	vDir.Normalize();

	// 이동 속력
	float fSpeed = m_pRigidbody->GetVelocity().Length();

	// 다른 컴포넌트 적용
	Vector2 vPos = m_pTransform->GetPos();
	vPos += vDir * fSpeed * DT;

	m_pTransform->SetPos(vPos);
	m_pCollider->SetOffset(vPos);

	//m_pTransform->SetPos(vTemp);
	//m_pCollider->SetOffset(vTemp);

	// 트랜스폼 포지션과 콜라이더 오프셋은 어차피 같은 값이니 같은 값을 넣어준다
}

void CPlayer::Attack()
{
	// 총알 발사
}
