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
	dynamic_cast<CBoxCollider2D*>(m_pCollider)->SetSize(Vector2(PLAYER_SIZE_STAND_X-int(PLAYER_SIZE_STAND_X * 0.2f), PLAYER_SIZE_STAND_Y- int(PLAYER_SIZE_STAND_Y * 0.2f)));
	m_pCollider->SetIsActive(true);

	// Component - Rigidbody
	m_pRigidbody->SetMass(1.f);
	m_pRigidbody->SetGround(false);

	m_iPrevDir = 1;
	m_iCurDir = 1;
	m_fSpeed = MOVEOBJ_SPEED;

	m_ObjectState = OBJECT_STATE::IDLE; // 이거 안쓴다
	m_ObjectType = OBJECT_TYPE::M_PLAYER;

	m_eCurState = OBJECT_STATE::IDLE; // 이거 두개 쓴다
	m_ePrevState = OBJECT_STATE::IDLE;

	m_curWeapon = ATTACKOBJ_WEAPON_TYPE::BASICGUN;
	m_iLife = 3;

	m_iBulletCount = 1000;
	m_iGrenadeCount = 10;


	// temp (텍스처 로딩)
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Marco.bmp");

	CCamera::GetInst()->SetTargetObj(this);


	m_bGravity = true;
}

void CPlayer::LateInit()
{
}

void CPlayer::Update()
{
	
	

	Move();

	Update_state();
	Update_animation();

	

	//// 어떤 어택인지 어택 타입 값 받아서 그에 맞는 어택 구현 ex 칼, 총, 수류탄
	//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::Z) == KEY_STATE::KEY_HOLD)
	//	Attack();
}

void CPlayer::LateUpdate()
{
	if (m_pCollider->IsCollision())
	{
		// 충돌한 상대 오브젝트의 오브젝트 타입을 가져온다
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
	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(hdc,
		int(vRenderPos.x - (float)(iWidth * 0.5f)),
		int(vRenderPos.y - (float)(iHeight * 0.5f)),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(255, 255, 255));

	//Vector2 vSize = m_pTransform->GetSize();	
	//BitBlt(hdc,
	//	int(vPos.x - (float)(iWidth * 0.5f)),
	//	int(vPos.y - (float)(iHeight * 0.5f)),
	//	iWidth,
	//	iHeight,
	//	m_pTex->GetDC(),
	//	0, 0, SRCCOPY);




	// Point Collider
	Vector2 Temp = CCamera::GetInst()->GetRenderPos(m_PointCollider);
	PEN_TYPE ePen = PEN_TYPE::RED;

	SelectGDI pen(hdc, ePen);
	SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW); // 임시객체(지역변수)기 때문에 나갈때 자동으로 소멸자 호출, 그때 다시 셀렉

	Rectangle(hdc, int(Temp.x - 5),
		int(Temp.y - 5),
		int(Temp.x + 5),
		int(Temp.y + 5));










	// Text


	// FPS
	TCHAR tch1[128] = {};
	swprintf_s(tch1, L"FPS : %.2f ",
		float(FPS));
	//SetBkMode(hdc, TRANSPARENT);
	Vector2 tPos1 = CCamera::GetInst()->GetRenderPos(Vector2(0, 0));
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos1.x), int(tPos1.y), tch1, _tcslen(tch1));

	// DT
	TCHAR tch2[128] = {};
	swprintf_s(tch2, L"DT : %f ",
		DT);
	//SetBkMode(hdc, TRANSPARENT);
	Vector2 tPos2 = CCamera::GetInst()->GetRenderPos(Vector2(0, 15));
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos2.x), int(tPos2.y), tch2, _tcslen(tch2));


	// Player Local Pos
	TCHAR tch3[128] = {};
	swprintf_s(tch3, L"LOCAL POS : %.2f, %.2f",
		CCamera::GetInst()->GetRenderPos(m_pTransform->GetPos()).x,
		CCamera::GetInst()->GetRenderPos(m_pTransform->GetPos()).y);
	//SetBkMode(hdc, TRANSPARENT);
	Vector2 tPos3 = CCamera::GetInst()->GetInst()->GetRenderPos(GetPos());
	Vector2 tSize3 =GetSize();
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x + iWidth), int(tPos3.y + iHeight), tch3, _tcslen(tch3));

	// Player World Pos
	TCHAR tch4[128] = {};
	swprintf_s(tch4, L"WORLD POS : %.2f, %.2f",
		m_pTransform->GetPos().x,
		m_pTransform->GetPos().y);
	//SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x + iWidth), int(tPos3.y + iHeight +15), tch4, _tcslen(tch4));



	
}

void CPlayer::Move()
{
	// 키 입력에 따른 힘이나 속도 부여
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



	//// Temp Up Down
	//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::UP) == KEY_STATE::KEY_HOLD)
	//{
	//	m_pRigidbody->AddForce(MyVector2(0.f, -200.f));
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::DOWN) == KEY_STATE::KEY_HOLD)
	//{
	//	m_pRigidbody->AddForce(MyVector2(0.f, 200.f));
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::UP) == KEY_STATE::KEY_DOWN)
	//{
	//	m_pRigidbody->AddVelocity(MyVector2(0.f, -200.f));
	//}
	//if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::DOWN) == KEY_STATE::KEY_DOWN)
	//{
	//	m_pRigidbody->AddVelocity(MyVector2(0.f, 200.f));
	//}


	// 중력 반영 
	if (m_bGravity)
	{
		m_pRigidbody->ApplyGravity();
	}

	// 현재 속도 계산 (물리적 이동에 있어 핵심적인 부분)
	m_pRigidbody->CalVelocity();



	// 이동 속력
	float fSpeed = m_pRigidbody->GetVelocity().Length();

	if (fSpeed != 0.f)
	{
		// 이동 방향
		Vector2 vDir = m_pRigidbody->GetVelocity();
		vDir.Normalize();

		// 컴포넌트 적용 (현재 플레이어 위치 = 이동방향 * 이동속력 * DT)
		Vector2 vPos = m_pTransform->GetPos();
		vPos += vDir * fSpeed * DT;

		m_pTransform->SetPos(vPos);
		m_pCollider->SetOffset(vPos);
	}



	// Pixel Collision Test
	m_PointCollider = Vector2(GetPos().x, GetPos().y + (GetSize().y *0.5f));

	Vector2 TempColliderPos = CCamera::GetInst()->GetRenderPos(m_PointCollider);
	COLORREF PixRGB = GetPixel(CCore::GetInst()->GetMainDC(), int(TempColliderPos.x), int(TempColliderPos.y));
	
	BYTE r = GetRValue(PixRGB);
	BYTE g = GetGValue(PixRGB);
	BYTE b = GetBValue(PixRGB);

	if (GetRValue(PixRGB) == 0 && GetGValue(PixRGB) == 255 && GetBValue(PixRGB) == 0)
	{
		cout << "========================================\n";

		cout << "PointCollider Pos : " << m_PointCollider.x << ", " << m_PointCollider.y << endl;
		cout << "Obj Pos           : " << GetPos().x << ", " << GetPos().y << endl;

		float Ygap = abs(m_PrevColliderPos.y - m_PointCollider.y);
		cout << "Gap : " << Ygap << endl;
		SetPos(Vector2(GetPos().x, GetPos().y - Ygap));
		cout << "Obj Pos           : " << GetPos().x << " " << GetPos().y << "\n\n";


		m_bGravity = false;
		m_pRigidbody->InitForce();
		m_pRigidbody->InitVelocity();
		m_pRigidbody->InitAccel();
		m_pRigidbody->InitAccelAlpha();
	}
	m_PrevColliderPos = m_PointCollider;
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
	// 어소트락 68화
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iCurDir)
		return;

	switch (m_eCurState)
	{
	case OBJECT_STATE::IDLE:
	{
		// 방향에 따라 애니메이션 실행
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
	// 총알 발사
}
