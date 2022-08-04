#include "stdafx.h"
#include "Stage.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

CStage::CStage(OBJECT_TYPE objtype)
{
	m_ObjectType = objtype;
}

void CStage::Init()
{
	CObject::Init();

	m_pTex = CResMgr::GetInst()->LoadTexture(L"MapTex", L"texture\\MapPixelTest.bmp");

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
		RGB(255, 0, 255));


	//TransparentBlt(hdc,
	//	int(vRenderPos.x * 0.8f - (float)(iWidth * 0.5f)),
	//	int(vRenderPos.y * 0.8f - (float)(iHeight * 0.5f)),
	//	iWidth, iHeight,
	//	m_pTex->GetDC(),
	//	0, 0, iWidth, iHeight,
	//	RGB(255, 0, 255));
}


