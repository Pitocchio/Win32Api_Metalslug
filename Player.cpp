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

	// Component - Transform
	m_pTransform->SetOwnerObj(this);
	m_pTransform->SetPos(Vector2(PLAYER_POS_X, PLAYER_POS_Y));
	m_pTransform->SetSize(Vector2(PLAYER_SIZE_STAND_X, PLAYER_SIZE_STAND_Y));
	m_pTransform->SetAngle(NULL);

	// Component - Collider
	/*m_pCollider->SetOwnerObj(this);
	m_pCollider->SetIsColliderType(COLLIDER_TYPE::BOX2D);
	m_pCollider->SetOffset(Vector2(PLAYER_POS_X, PLAYER_POS_Y));
	dynamic_cast<CBoxCollider2D*>(m_pCollider)->SetSize(Vector2(PLAYER_SIZE_STAND_X - int(PLAYER_SIZE_STAND_X * 0.2f), PLAYER_SIZE_STAND_Y - int(PLAYER_SIZE_STAND_Y * 0.2f)));
	m_pCollider->SetIsActive(true);*/


	m_fSpeed = MOVEOBJ_SPEED;

	m_ObjectState = OBJECT_STATE::IDLE; // 이거 안쓴다
	m_ObjectType = OBJECT_TYPE::M_PLAYER;

	m_eCurState = OBJECT_STATE::IDLE; // 이거 두개 쓴다
	m_ePrevState = OBJECT_STATE::IDLE;

	


	// =========================================================== //




	// temp (텍스처 로딩)
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Marco.bmp"); // 플레이어 원본 



	// Animator (완료)
	m_pAnimator->SetOwnerObj(this);
	m_pAnimator->SetTexture(L"Tarma", L"texture\\Tarma.bmp");
	m_pAnimator->SetData(L"animation\\edit2\\Tarma.txt");
	m_pAnimator->CreateAnimation();
	m_pAnimator->PlayFirstAnimation();

	




	// =========================================================== //

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
	//m_bJump = false;
	m_bTest = false;

	m_vLook = { 0.f, 0.f };












	// 용하형 라인 충돌 
	m_fSpeed = 0.f;
	m_iCheckLine = 0;
	m_fSlope = 0.f;
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_fSpeed = 20.f;
	m_fFall = 0.f;
	m_fGrav = 70.f;
	m_fJumpSpeed = 10.f;
	fJumpStart = 0.f;
	m_bJump = false;
}

void CPlayer::LateInit()
{
}

void CPlayer::Update()
{
	if (m_iCheckLine)
	{
		m_fFall = 0;
		m_bJump = false;
	}
	else if (m_bJump || m_iCheckLine == 0)
	{
		m_fFall += (100.f - m_fFall) / (m_fGrav);
		m_tInfo.fY += m_fFall;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_tInfo.fX -= m_fSpeed;
		if (!m_bJump)
			m_tInfo.fY -= m_fSlope * m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_tInfo.fX += m_fSpeed;
		if (!m_bJump)
			m_tInfo.fY += m_fSlope * m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_RIGHT) == 0 && GetAsyncKeyState(VK_LEFT) == 0)
		m_fSpeed = 10.f;


	// 점프
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::SPACE) == KEY_STATE::DOWN) // 스페이스 누르면 점프 시작
	{
		m_fJumpSpeed = 20.f;
		fJumpStart = m_tInfo.fY;
		m_bJump = true;
	}

	if (m_bJump)
	{
		m_fJumpSpeed -= (m_fJumpSpeed - 0.f) / m_fGrav;
		m_tInfo.fY -= m_fJumpSpeed;
	}
	

	//for (auto& iter : CMapLineMgr::GetInst()->GetVecLine()) // 라인 벡터 순회
	for (auto& iter : CMapObjMgr::GetInst()->GetVecLine()) // 라인 벡터 순회
	{
		if (iter->IsInLine(Get_Info())) // 현재 플레이어가 라인에 위치해 있는가
		{
			Check_Line(iter->LineCheck(Get_Info()));
			Set_Dist(iter->Get_Dist()); // 라인의 기울기를 받아와 플레이어 슬로프에 저장 
			break;
		}
	}


	GetAnimator()->Update();

	
}

void CPlayer::LateUpdate()
{
	//if (m_pCollider->IsCollision())
	//{
	//	// 충돌한 상대 오브젝트의 오브젝트 타입을 가져온다
	//	switch (m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetObjectType())
	//	{

	//		// LineCollider
	//	case OBJECT_TYPE::C_CAMERACOLLIDER:
	//	{
	//		//m_pRigidbody->SetGround(true);

	//		Vector2 vVel = m_pRigidbody->GetVelocity();
	//		m_pRigidbody->InitForce();

	//		Vector2 vObjPos = m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetPos();
	//		Vector2 vObjSize = m_pCollider->GetOtherObjCol()->GetOwnerObj()->GetSize();

	//		Vector2 vPos = m_pTransform->GetPos();
	//		Vector2 vSize = m_pTransform->GetSize();

	//		float fLen = abs(vObjPos.y - vPos.y);
	//		float fValue = (vObjSize.y * 0.5f + vSize.y * 0.5f) - fLen;

	//		Vector2 vOffset = m_pCollider->GetOffset();

	//		m_pTransform->SetPos(Vector2(vPos.x, vPos.y - fValue));
	//		m_pCollider->SetOffset(Vector2(vOffset.x, vOffset.y - fValue));


	//	}
	//	break;


	//	// MoveObj
	//	case OBJECT_TYPE::M_ZOMBIE_LIQUID:
	//		CEventMgr::GetInst()->DeleteObject(this);
	//		break;
	//	case OBJECT_TYPE::M_REBEL_GRENADE:
	//		CEventMgr::GetInst()->DeleteObject(this);
	//		break;


	//	}
	//}

	////m_pRigidbody->InitForce();
	//m_pRigidbody->InitAccelAlpha();
	//m_pRigidbody->InitAccel();
	//m_ePrevState = m_eCurState;
	////m_iPrevDir = m_iCurDir;
}

void CPlayer::Render(HDC hdc)
{
	






	// Apply Animation
	m_pAnimator->Render(hdc);





	int iWidth = (int)m_pTex->Width() - 500;
	int iHeight = (int)m_pTex->Height();

	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vector2(m_tInfo.fX, m_tInfo.fY));





	// Text


	// Player Local Pos
	TCHAR tch3[128] = {};
	swprintf_s(tch3, L"Local Pos : %f, %f",
		CCamera::GetInst()->GetRenderPos(GetPos()).x,
		CCamera::GetInst()->GetRenderPos(GetPos()).y);
	//SetBkMode(hdc, TRANSPARENT);
	Vector2 tPos3 = CCamera::GetInst()->GetInst()->GetRenderPos(GetPos());
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x + iWidth), int(tPos3.y + iHeight), tch3, _tcslen(tch3));

	// Player World Pos
	TCHAR tch4[128] = {};
	swprintf_s(tch4, L"World Pos : %f, %f",
		GetPos().x,
		GetPos().y);
	//SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x + iWidth), int(tPos3.y + iHeight + 15), tch4, _tcslen(tch4));





	// m_bJump
	TCHAR tch12[128] = {};
	if (m_bJump)
		swprintf_s(tch12, L"IsJump : TRUE");
	else
		swprintf_s(tch12, L"IsJump : FALSE");
	//SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_LEFT);
	TextOut(hdc, int(tPos3.x + iWidth), int(tPos3.y + iHeight + 30), tch12, _tcslen(tch12));



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


void CPlayer::Update_state() // for Animaion change
{
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::DOWN)
	{
		//m_iCurDir = -1;
		m_eCurState = OBJECT_STATE::WALK;
	}
	if (CInputMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::DOWN)
	{
		//m_iCurDir = 1;
		m_eCurState = OBJECT_STATE::WALK;
	}
	//if (//m_pRigidbody->GetSpeed() == 0.f)
	//{
	//	m_eCurState = OBJECT_STATE::IDLE;
	//}
}
