#include "stdafx.h"
#include "Animator2D.h"

CAnimator2D::CAnimator2D()
	: m_pOwnerObj(nullptr)
	, m_pCurAni(nullptr)
	, m_bRepeat(false)
{
}

CAnimator2D::~CAnimator2D()
{
	Safe_Delete_Map(m_mapAni);
}

void CAnimator2D::Init()
{
}

void CAnimator2D::Update() // 현재 애니메이션을 업데이트
{
	if (m_pCurAni != nullptr)
	{
		m_pCurAni->Update();

		if (m_bRepeat && m_pCurAni->IsFinish())
		{
			m_pCurAni->SetFrame(0);
		}
	}
}

void CAnimator2D::LateUpdate()
{
}

void CAnimator2D::Render(HDC hdc) // 현재 애니메이션을 렌더
{
	if (m_pCurAni != nullptr)
	{
		m_pCurAni->Render(hdc);
	}
}

void CAnimator2D::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, 
									Vector2 _vStep, float fDuration, UINT _iFrameCount)
{
	CAnimation2D* pAni = FindAnimation(_strName);
	assert(pAni == nullptr);

	pAni = new CAnimation2D;

	pAni->SetName(_strName);
	pAni->SetOwnerObj(this);  // 만들어진 애니메이션들도 애니메이터를 알아야 함
	pAni->Create(_pTex, _vLT, _vSliceSize, _vStep, fDuration, _iFrameCount);

	m_mapAni.insert(make_pair(_strName, pAni));
}

CAnimation2D* CAnimator2D::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation2D*>::iterator iter = m_mapAni.find(_strName);

	if (iter == m_mapAni.end())
		return nullptr;
	
	return iter->second;
}

void CAnimator2D::PlayAnimation(const wstring& _strName, bool _bRepeat)
{
	m_pCurAni = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

void CAnimator2D::SetOwnerObj(CObject* obj)
{
	m_pOwnerObj = obj;
}
