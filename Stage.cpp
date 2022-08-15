#include "stdafx.h"
#include "Stage.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	
	//delete m_pTex;
	
}

CStage::CStage(OBJECT_TYPE objtype)
{
	m_ObjectType = objtype;
}

void CStage::Init()
{
	CObject::Init();

	m_pTex = CResMgr::GetInst()->LoadTexture(L"MapTex", L"texture\\Map.bmp");

	// Component - Transform
	m_pTransform->SetOwnerObj(this);
	m_pTransform->SetPos(Vector2(int(m_pTex->Width() * 0.5f), int(m_pTex->Height() * 0.5f)));
	m_pTransform->SetSize(Vector2(0.f, 0.f));
	m_pTransform->SetAngle(NULL);

	// Component - Collider
	//m_pCollider->SetOwnerObj(this);
	


}

void CStage::LateInit()
{
}

void CStage::Update()
{
}

void CStage::LateUpdate()
{
}

void CStage::Render(HDC hdc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_pTransform->GetPos());

	TransparentBlt(hdc,
		int(vRenderPos.x - (float)(iWidth * 0.5f)),
		int(vRenderPos.y - (float)(iHeight * 0.5f)),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(255, 255, 0));

	StretchBlt(hdc,
		0, 0,
		int(iWidth * 3), int(iHeight * 3),
		hdc,
		0, 0,
		iWidth, iHeight,
		SRCCOPY);
}


