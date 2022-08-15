#include "stdafx.h"
#include "Animator2D.h"

CAnimator2D::CAnimator2D()
	: m_pOwnerObj(nullptr)
	, m_pCurAni(nullptr)
{
}

CAnimator2D::~CAnimator2D()
{
	Safe_Delete_Map(m_mapAni);
}

void CAnimator2D::Init()
{
}

void CAnimator2D::Update() // ���� �ִϸ��̼��� ������Ʈ
{
	if (m_pCurAni != nullptr)
	{
		m_pCurAni->Update();
	}
}

void CAnimator2D::LateUpdate()
{
}

void CAnimator2D::Render(HDC hdc) // ���� �ִϸ��̼��� ����
{
	if (m_pCurAni != nullptr)
	{
		m_pCurAni->Render(hdc);
	}
}

void CAnimator2D::CreateAnimation(CTexture*, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vNext, UINT _iFrameCount)
{
}

void CAnimator2D::FindAnimation()
{
}

void CAnimator2D::PlayAnimation()
{
}

void CAnimator2D::SetOwnerObj(CObject* obj)
{
	m_pOwnerObj = obj;
}
