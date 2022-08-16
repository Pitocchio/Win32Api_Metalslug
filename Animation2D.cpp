#include "stdafx.h"
#include "Animation2D.h"

CAnimation2D::CAnimation2D()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrame(0)
	, m_fAccTime(0)
	, m_bFinish(false)
{
}

CAnimation2D::~CAnimation2D()
{
}

void CAnimation2D::Init()
{
}

void CAnimation2D::Update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_vecFrame[m_iCurFrame].fDuration < m_fAccTime) // �����ð���, ���� �����ӿ��� �ӹ����� �� �ð��� �Ѱ� �ȴٸ�, ���� ���������� �Ѿ
	{
		++m_iCurFrame;

		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrame[m_iCurFrame].fDuration; 
	}
}

void CAnimation2D::Render(HDC hdc)
{
	if (m_bFinish)
		return;

	Vector2 vRenPos = CCamera::GetInst()->GetRenderPos(Vector2(dynamic_cast<CPlayer*>(m_pAnimator->GetOwnerObj())->GetInfo().fX,
																dynamic_cast<CPlayer*>(m_pAnimator->GetOwnerObj())->GetInfo().fY));
	
	vRenPos += m_vecFrame[m_iCurFrame].vOffset; // ������ �� ����

	TransparentBlt(hdc,
		int(vRenPos.x - m_vecFrame[m_iCurFrame].vSlice.x * 0.5f),
		int(vRenPos.y - m_vecFrame[m_iCurFrame].vSlice.y * 0.5f),
		int(m_vecFrame[m_iCurFrame].vSlice.x),
		int(m_vecFrame[m_iCurFrame].vSlice.y),
		m_pTex->GetDC(),
		int(m_vecFrame[m_iCurFrame].vLT.x),
		int(m_vecFrame[m_iCurFrame].vLT.y),
		int(m_vecFrame[m_iCurFrame].vSlice.x),
		int(m_vecFrame[m_iCurFrame].vSlice.y),
		RGB(255, 255, 255));
}

void CAnimation2D::Release()
{
}

void CAnimation2D::SetFrame(int _iFrameIdx)
{
	m_bFinish = false;
	m_iCurFrame = _iFrameIdx;
	m_fAccTime = 0.f;
}

void CAnimation2D::Create(CTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vStep, float fDuration, UINT _iFrameCount)
{
	// ���⼭�� �ϳ��� �ִϸ��̼��� ������
	// �� ���� �̵� �ִϸ��̼��̶�� n���� bmp�̹����� ������, �ϳ��� ���� �̵��̶�� �ִϸ��̼��� ����� ��!

	m_pTex = _pTex;

	AniFrame frame = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frame.fDuration = fDuration;
		frame.vSlice = _vSliceSize;
		frame.vLT = _vLT + _vStep * i;

		m_vecFrame.push_back(frame);
	}
}
