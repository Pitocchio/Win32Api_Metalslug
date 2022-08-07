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
	dynamic_cast<CBoxCollider2D*>(m_pCollider)->SetSize(Vector2(PLAYER_SIZE_STAND_X - int(PLAYER_SIZE_STAND_X * 0.2f), PLAYER_SIZE_STAND_Y - int(PLAYER_SIZE_STAND_Y * 0.2f)));
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

	CCamera::GetInst()->SetTargetObj(this);


	m_bGravity = true;
	m_bPrevCollision = false;
	m_bCurCollision = false;

	m_CurPointCollider = {};
	m_PrevPointCollider = {};
	m_bPrevCollision = false;
	m_bCurCollision = false;

	m_bGround = false;
	m_fGravitytime = 0.f;
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

			m_pTransform->SetPos(Vector2(vPos.x, vPos.y - fValue));
			m_pCollider->SetOffset(Vector2(vOffset.x, vOffset.y - fValue));


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
	Vector2 Temp = CCamera::GetInst()->GetRenderPos(m_CurPointCollider);
	PEN_TYPE ePen = PEN_TYPE::RED;

	SelectGDI pen(hdc, ePen);
	SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW); // �ӽð�ü(��������)�� ������ ������ �ڵ����� �Ҹ��� ȣ��, �׶� �ٽ� ����

	Rectangle(hdc, int(Temp.x - 5),
		int(Temp.y - 5),
		int(Temp.x + 5),
		int(Temp.y + 5));










	// Text


	// Player Local Pos
	TCHAR tch3[128] = {};
	swprintf_s(tch3, L"LOCAL POS : %f, %f",
		CCamera::GetInst()->GetRenderPos(m_pTransform->GetPos()).x,
		CCamera::GetInst()->GetRenderPos(m_pTransform->GetPos()).y);
	//SetBkMode(hdc, TRANSPARENT);
	Vector2 tPos3 = CCamera::GetInst()->GetInst()->GetRenderPos(GetPos());
	Vector2 tSize3 =GetSize();
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x + iWidth), int(tPos3.y + iHeight), tch3, _tcslen(tch3));

	// Player World Pos
	TCHAR tch4[128] = {};
	swprintf_s(tch4, L"WORLD POS : %f, %f",
		m_pTransform->GetPos().x,
		m_pTransform->GetPos().y);
	//SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x + iWidth), int(tPos3.y + iHeight +15), tch4, _tcslen(tch4));


	// FPS
	TCHAR tch1[128] = {};
	swprintf_s(tch1, L"FPS : %.2f ",
		float(FPS));
	//SetBkMode(hdc, TRANSPARENT);
	Vector2 tPos1 = CCamera::GetInst()->GetRenderPos(Vector2(0, 0));
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x - WINDOW_WIDTH * 0.5f), int(tPos3.y - WINDOW_HEIGHT * 0.5f), tch1, _tcslen(tch1));

	// DT
	TCHAR tch2[128] = {};
	swprintf_s(tch2, L"DT : %f ",
		DT);
	//SetBkMode(hdc, TRANSPARENT);
	Vector2 tPos2 = CCamera::GetInst()->GetRenderPos(Vector2(0, 15));
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x - WINDOW_WIDTH * 0.5f), int(tPos3.y - WINDOW_HEIGHT * 0.5f + 15.f), tch2, _tcslen(tch2));


	// CAMERA
	TCHAR tch5[128] = {};
	swprintf_s(tch5, L"CAMERA LOOK AT : %f, %f ",
		CCamera::GetInst()->GetLookAt().x, CCamera::GetInst()->GetLookAt().y);
	//SetBkMode(hdc, TRANSPARENT);
	Vector2 tPos5 = CCamera::GetInst()->GetRenderPos(Vector2(0, 30));
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x - WINDOW_WIDTH * 0.5f), int(tPos3.y - WINDOW_HEIGHT * 0.5f + 30.f), tch5, _tcslen(tch5));


	
	





}

void CPlayer::Move()
{
	// Ű �Է¿� ���� ���̳� �ӵ� �ο�
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_HOLD)
	{
		//m_pRigidbody->AddForce(MyVector2(-200.f, 0.f));

		Vector2 Look = { -1, 0 };
		Vector2 Pos = GetPos();
		Pos.x += Look.x * 200.f * fDT;

		SetPos(Pos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_HOLD)
	{
		//m_pRigidbody->AddForce(MyVector2(200.f, 0.f));
		Vector2 Look = { 1, 0 };
		Vector2 Pos = GetPos();
		Pos.x += Look.x * 200.f * fDT;

		SetPos(Pos);
	
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_DOWN)
	{
		//m_pRigidbody->AddVelocity(MyVector2(-200.f, 0.f));
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_DOWN)
	{
		//m_pRigidbody->AddVelocity(MyVector2(200.f, 0.f));
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


	// �߷� �ݿ� 
	//if (m_bGravity)
	//{
	//	m_pRigidbody->ApplyGravity();
	//}
	////m_pRigidbody->ApplyGravity();


	//// ���� �ӵ� ��� (������ �̵��� �־� �ٽ����� �κ�)
	//m_pRigidbody->CalVelocity();



	//// �̵� �ӷ�
	//float fSpeed = m_pRigidbody->GetVelocity().Length();

	//if (fSpeed != 0.f)
	//{
	//	// �̵� ����
	//	Vector2 vDir = m_pRigidbody->GetVelocity();
	//	vDir.Normalize();

	//	// ������Ʈ ���� (���� �÷��̾� ��ġ = �̵����� * �̵��ӷ� * DT)
	//	Vector2 vPos = m_pTransform->GetPos();
	//	vPos += vDir * fSpeed * DT;

	//	m_pTransform->SetPos(vPos);
	//	m_pCollider->SetOffset(vPos);
	//}






	//  Not Ground => Apply Gravity
	if (!m_bGround)
	{
		m_fGravitytime += fDT;
		float m_Temp = GRAVITY * m_fGravitytime * fDT;
		SetPos(Vector2(GetPos().x, GetPos().y + m_Temp));
	}


	// Pixel Collision
	m_CurPointCollider = Vector2(GetPos().x, GetPos().y + (GetSize().y * 0.5f));

	Vector2 TempColliderPos = CCamera::GetInst()->GetRenderPos(m_CurPointCollider);
	COLORREF PixRGB = GetPixel(CCore::GetInst()->GetMainDC(), int(TempColliderPos.x), int(TempColliderPos.y));
	
	BYTE r = GetRValue(PixRGB);
	BYTE g = GetGValue(PixRGB);
	BYTE b = GetBValue(PixRGB);

	if (GetRValue(PixRGB) == 0 && GetGValue(PixRGB) == 255 && GetBValue(PixRGB) == 0)
		m_bCurCollision = true;
	else
		m_bCurCollision = false;


	if (m_bCurCollision)
	{
		m_bGround = true;
		m_fGravitytime = 0.f;

		if (!m_bPrevCollision) // OnCollision_Enter
		{
			if (m_CurPointCollider.y != m_PrevPointCollider.y)
				printf("OnCollision_Enter\n\n");

			float fYgap = abs(m_CurPointCollider.y - m_PrevPointCollider.y) * fDT;
			SetPos(Vector2(GetPos().x, GetPos().y - fYgap+1));
		}
		else if (m_bPrevCollision) // OnCollision_Stay
		{
			if (m_CurPointCollider.y != m_PrevPointCollider.y)
				printf("OnCollision_Stay\n\n");
		}
	}
	else if (!m_bCurCollision)
	{
		m_bGround = false;

		if (!m_bPrevCollision) // No Cillision
		{
			if (m_CurPointCollider.y != m_PrevPointCollider.y)
				printf("NoCollision\n\n");
		}
		else if (m_bPrevCollision) // OnCollision_Exit
		{
			if (m_CurPointCollider.y != m_PrevPointCollider.y)
				printf("OnCollision_Exit\n\n");
		}
	}


	m_PrevPointCollider = m_CurPointCollider;
	m_bPrevCollision = m_bCurCollision;

	//if (m_PointCollider.y != m_PrevColliderPos.y)
	//{
	//	printf("===============================================\n");
	//	printf("Prev OBJ Pos           - X : %f, Y : %f\n", GetPos().x, GetPos().y);
	//}

	//if (m_bCurCollision) 
	//{
	//	if (!m_bPrevCollision) // OnCollision_Enter
	//	{
	//		if (m_PointCollider.y != m_PrevColliderPos.y)
	//		{
	//			printf("\n[OnCollision_Enter]\n");
	//		}
	//		m_fGravitytime = 0.f;

	//		//float Ygap = abs(m_PointCollider.y - m_PrevColliderPos.y);
	//		SetPos(Vector2(GetPos().x, GetPos().y  - m_Temp)); // + 3
	//	}
	//	else if (m_bPrevCollision) // OnCollision_Stay
	//	{
	//		if (m_PointCollider.y != m_PrevColliderPos.y)
	//		{
	//			printf("\n[OnCollision_Stay]\n");
	//		}
	//		m_fGravitytime = 0.f;

	//		//float Ygap = abs(m_PointCollider.y - m_PrevColliderPos.y);
	//		SetPos(Vector2(GetPos().x, GetPos().y - m_Temp)); // + 3

	//	}
	//}
	//else
	//{
	//	if (!m_bPrevCollision)
	//	{
	//		if (m_PointCollider.y != m_PrevColliderPos.y)
	//		{
	//			printf("\n[NO_COLLISION]\n");
	//		}
	//	}
	//	else if (m_bPrevCollision) // OnCollision_Exit
	//	{
	//		if (m_PointCollider.y != m_PrevColliderPos.y)
	//		{
	//			printf("\n[OnCollision_Exit]\n");
	//		}
	//	}

	//	m_fGravitytime += fDT;
	//	m_Temp = GRAVITY * m_fGravitytime * fDT;
	//	SetPos(Vector2(GetPos().x, GetPos().y + m_Temp));
	//	
	//	if (m_PointCollider.y != m_PrevColliderPos.y)
	//	{
	//		printf("\n%f\n",m_Temp);
	//	}
	//	
	//}

	//if (m_PointCollider.y != m_PrevColliderPos.y)
	//{
	//	
	//	printf("\nCur OBJ Pos           - X : %f, Y : %f\n\n", GetPos().x, GetPos().y);
	//}



	//m_bPrevCollision = m_bCurCollision;

	//m_PrevColliderPos = m_PointCollider;


	//if (GetRValue(PixRGB) == 0 && GetGValue(PixRGB) == 255 && GetBValue(PixRGB) == 0)
	//{

	//	if (m_PrevColliderPos.y < m_PointCollider.y)
	//	{
	//		cout << "========================================\n";
	//		printf("PointCollider Pos - X : %f, Y : %f\n", m_PointCollider.x, m_PointCollider.y);
	//		printf("Obj Pos           - X : %f, Y : %f\n", GetPos().x, GetPos().y);
	//		float Ygap = abs(m_PrevColliderPos.y - m_PointCollider.y);
	//		printf("Gap               - %f\n", Ygap);
	//		SetPos(Vector2(GetPos().x, GetPos().y - Ygap));
	//		printf("Obj Pos           - X : %f, Y : %f\n", GetPos().x, GetPos().y);
	//		printf("���� �浹!\n\n");

	//		m_bGravity = false;
	//		m_pRigidbody->InitForce();
	//		m_pRigidbody->InitVelocity();
	//		m_pRigidbody->InitAccel();
	//		m_pRigidbody->InitAccelAlpha();

	//	}
	//	/*else if (m_PrevColliderPos.x < m_PointCollider.x)
	//	{
	//		cout << "========================================\n";
	//		printf("PointCollider Pos - X : %f, Y : %f\n", m_PointCollider.x, m_PointCollider.y);
	//		printf("Obj Pos           - X : %f, Y : %f\n", GetPos().x, GetPos().y);
	//		float Xgap = abs(m_PrevColliderPos.x - m_PointCollider.x);
	//		printf("Gap               - %f\n", Xgap);
	//		SetPos(Vector2(GetPos().x, GetPos().y - Xgap));
	//		printf("Obj Pos           - X : %f, Y : %f\n\n", GetPos().x, GetPos().y);
	//		printf("������ �浹!\n\n");
	//		m_bGravity = false;


	//	}*/
	//	
	//}
	//else
	//{
	//	m_bGravity = true;
	//}
	//m_PrevColliderPos = m_PointCollider;


	//cout << GetPos().x << endl;
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
