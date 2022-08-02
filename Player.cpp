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
	dynamic_cast<CBoxCollider2D*>(m_pCollider)->SetSize(Vector2(PLAYER_SIZE_STAND_X-int(PLAYER_SIZE_STAND_X * 0.2f), PLAYER_SIZE_STAND_Y- int(PLAYER_SIZE_STAND_Y * 0.2f)));
	m_pCollider->SetIsActive(true);

	// Component - Rigidbody
	m_pRigidbody->SetMass(1.f);
	m_pRigidbody->SetGround(false);

	m_iPrevDir = 1;
	m_iCurDir = 1;
	m_fSpeed = MOVEOBJ_SPEED;

	m_ObjectState = OBJECT_STATE::IDLE; // �̰� �Ⱦ���
	m_ObjectType = OBJECT_TYPE::M_PLAYER;

	m_eCurState = OBJECT_STATE::IDLE; // �̰� �ΰ� ����
	m_ePrevState = OBJECT_STATE::IDLE;

	m_curWeapon = ATTACKOBJ_WEAPON_TYPE::BASICGUN;
	m_iLife = 3;

	m_iBulletCount = 1000;
	m_iGrenadeCount = 10;


	// temp (�ؽ�ó �ε�)
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Marco.bmp");
}

void CPlayer::LateInit()
{
}

void CPlayer::Update()
{

	Move();

	Update_state();
	Update_animation();

	

	//// � �������� ���� Ÿ�� �� �޾Ƽ� �׿� �´� ���� ���� ex Į, ��, ����ź
	//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::Z) == KEY_STATE::KEY_HOLD)
	//	Attack();
}

void CPlayer::LateUpdate()
{
	if (m_pCollider->IsCollision())
	{
		// �浹�� ��� ������Ʈ�� ������Ʈ Ÿ���� �����´�
		switch (m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetObjectType()) 
		{

		// LineCollider
		case OBJECT_TYPE::C_CAMERACOLLIDER:
		{
			m_pRigidbody->SetGround(true);

			Vector2 vVel = m_pRigidbody->GetVelocity();
			m_pRigidbody->InitForce();

			Vector2 vObjPos = m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetPos();
			Vector2 vObjSize = m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetSize();

			Vector2 vPos = m_pTransform->GetPos();
			Vector2 vSize = m_pTransform->GetSize();

			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjSize.y * 0.5f + vSize.y * 0.5f) - fLen;

			Vector2 vOffset = m_pCollider->GetOffset();

			m_pTransform->SetPos(Vector2(vPos.x, vPos.y - fValue - 1.f));
			m_pCollider->SetOffset(Vector2(vOffset.x, vOffset.y - fValue - 1.f));


		}
			break;


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
	m_pRigidbody->InitAccelAlpha();
	m_pRigidbody->InitAccel();
	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iCurDir;
}

void CPlayer::Render(HDC hdc)
{
	// Temp
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vector2 vPos = m_pTransform->GetPos();
	//Vector2 vSize = m_pTransform->GetSize();

	
	//BitBlt(hdc,
	//	int(vPos.x - (float)(iWidth * 0.5f)),
	//	int(vPos.y - (float)(iHeight * 0.5f)),
	//	iWidth,
	//	iHeight,
	//	m_pTex->GetDC(),
	//	0, 0, SRCCOPY);

	TransparentBlt(hdc,
		int(vPos.x - (float)(iWidth * 0.5f)),
		int(vPos.y - (float)(iHeight * 0.5f)),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(255, 0, 255));

	/*Rectangle(hdc, int(vTempPos.x - int(vTempSize.x * 0.5f)),
		int(vTempPos.y - int(vTempSize.y * 0.5f)),
		int(vTempPos.x + int(vTempSize.x * 0.5f)),
		int(vTempPos.y + int(vTempSize.y * 0.5f)));*/
}

void CPlayer::Move()
{
	// Ű �Է¿� ���� ���̳� �ӵ� �ο�
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_HOLD)
	{
		m_pRigidbody->AddForce(MyVector2(-200.f, 0.f));
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_HOLD)
	{
		m_pRigidbody->AddForce(MyVector2(200.f, 0.f));
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_DOWN)
	{
		m_pRigidbody->AddVelocity(MyVector2(-200.f, 0.f));
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_DOWN)
	{
		m_pRigidbody->AddVelocity(MyVector2(200.f, 0.f));
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_UP)
	{
		//m_pRigidbody->SetVelocity(MyVector2(0.f, 0.f));
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_UP)
	{
		//m_pRigidbody->SetVelocity(MyVector2(0.f, 0.f));
	}

	// �߷� �ݿ� 
	//m_pRigidbody->ApplyGravity();

	// ���� �ӵ� ��� (������ �̵��� �־� �ٽ����� �κ�)
	m_pRigidbody->CalVelocity();



	// �̵� �ӷ�
	float fSpeed = m_pRigidbody->GetVelocity().Length();

	if (fSpeed != 0.f)
	{
		// �̵� ����
		Vector2 vDir = m_pRigidbody->GetVelocity();
		vDir.Normalize();

		// ������Ʈ ���� (���� �÷��̾� ��ġ = �̵����� * �̵��ӷ� * DT)
		Vector2 vPos = m_pTransform->GetPos();
		vPos += vDir * fSpeed * DT;

		m_pTransform->SetPos(vPos);
		m_pCollider->SetOffset(vPos);
	}
}

void CPlayer::Update_state() // for Animaion change
{
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_DOWN)
	{
		m_iCurDir = -1;
		m_eCurState = OBJECT_STATE::WALK;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_DOWN)
	{
		m_iCurDir = 1;
		m_eCurState = OBJECT_STATE::WALK;
	}
	if(m_pRigidbody->GetSpeed() == 0.f)
	{
		m_eCurState = OBJECT_STATE::IDLE;
	}
}

void CPlayer::Update_animation()
{
	// ���Ʈ�� 68ȭ
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iCurDir)
		return;

	switch (m_eCurState)
	{
	case OBJECT_STATE::IDLE:
	{
		// ���⿡ ���� �ִϸ��̼� ����
		//if(m_iDir == -1)
		//	//
		//else if (m_iDIr == 1)
		//	//
	}
		break;
	case OBJECT_STATE::WALK:

		break;
	case OBJECT_STATE::ATTACK:

		break;
	case OBJECT_STATE::DEAD:

		break;
	default:
		break;

	}

}

void CPlayer::Attack()
{
	// �Ѿ� �߻�
}
