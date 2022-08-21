#include "stdafx.h"
#include "Animation2D.h"

CAnimation2D::CAnimation2D()
	: m_pAnimator(nullptr)
	, m_iCurTopFrm (0)
	, m_iCurBotFrm(0)
	, m_fTopAccTime(0)
	, m_fBotAccTime(0)
	, m_bTopFinish(false)
	, m_bBotFinish(false)
	, m_bRepeat(true)
	, m_iCurBody(0)
	, m_bStopAni(false)
	, m_bFlipX(false)
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
	SetCurEditFrm(); // for Edit 

	// 상체 기준
	if (m_bTopFinish)
		return;

	// Edit Scene에서 애니메이션을 Stop할 경우 아래 프레임 업데이트를 타지 않고 바로 리턴 하게끔 구현 
	if (m_bStopAni)
		return;

	m_fTopAccTime += fDT;

	if (m_vecTopFrm[m_iCurTopFrm]->Duration < m_fTopAccTime) // 누적시간이, 현재 프레임에서 머물러야 할 시간을 넘게 된다면, 다음 프레임으로 넘어감
	{
		++m_iCurTopFrm;
		++m_iCurBotFrm;

		if (m_vecTopFrm.size() <= m_iCurTopFrm)
		{
			// 상체
			m_iCurTopFrm = -1;
			m_bTopFinish = true;
			m_fTopAccTime = 0.f;

			// 하체
			m_iCurBotFrm = -1;
			m_bBotFinish = true;
			m_fBotAccTime = 0.f;

			return;
		}

		m_fTopAccTime = m_fTopAccTime - m_vecTopFrm[m_iCurTopFrm]->Duration;
	}
}

void CAnimation2D::Render(HDC hdc)
{
	if (m_bTopFinish)
		return;

	if (m_pTex != nullptr)
	{
		// Set RenderPosition
		Vector2 vRenPos;

		if (m_pAnimator->GetOwnerObj() == nullptr)
			vRenPos = CCamera::GetInst()->GetRenderPos(Vector2(0.f, 0.f));
		else
			vRenPos = CCamera::GetInst()->GetRenderPos(dynamic_cast<CPlayer*>(m_pAnimator->GetOwnerObj())->GetPos()); // 오브젝트 재설계 필요

		// Set for Stretch
		HDC StretchDC = CreateCompatibleDC(m_pTex->GetDC());
		HBITMAP StretchBit = CreateCompatibleBitmap(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
		DeleteObject(SelectObject(StretchDC, StretchBit));
		float iExtend = 1.5; // Stretch Size


		if (m_bFlipX) // On Flip X
		{
			// Render the Bottom
			Vector2 vBotRenPos = vRenPos + m_vecBotFrm[m_iCurBotFrm]->Pivot;
			float fBotWitdh = m_vecBotFrm[m_iCurBotFrm]->point2.x - m_vecBotFrm[m_iCurBotFrm]->point1.x;
			float fBotHeight = m_vecBotFrm[m_iCurBotFrm]->point2.y - m_vecBotFrm[m_iCurBotFrm]->point1.y;
			StretchBlt(StretchDC,
				int(vBotRenPos.x - (fBotWitdh * iExtend) * -0.5f) -1,
				int(vBotRenPos.y - (fBotHeight * iExtend) * 0.5f),
				-int(fBotWitdh * iExtend), int(fBotHeight * iExtend),
				m_pTex->GetDC(),
				int(m_vecBotFrm[m_iCurBotFrm]->point1.x),
				int(m_vecBotFrm[m_iCurBotFrm]->point1.y),
				fBotWitdh, fBotHeight,
				SRCCOPY);

			TransparentBlt(hdc,
				int(vBotRenPos.x - (fBotWitdh * iExtend) * 0.5f),
				int(vBotRenPos.y - (fBotHeight * iExtend) * 0.5f),
				int(fBotWitdh * iExtend), int(fBotHeight * iExtend),
				StretchDC,
				int(vBotRenPos.x - (fBotWitdh * iExtend) * 0.5f),
				int(vBotRenPos.y - (fBotHeight * iExtend) * 0.5f),
				int(fBotWitdh * iExtend), int(fBotHeight * iExtend),
				RGB(86, 177, 222));

			// Render the Top
			Vector2 vTopRenPos = vRenPos + m_vecTopFrm[m_iCurTopFrm]->Pivot;
			float fTopWitdh = m_vecTopFrm[m_iCurTopFrm]->point2.x - m_vecTopFrm[m_iCurTopFrm]->point1.x;
			float fTopHeight = m_vecTopFrm[m_iCurTopFrm]->point2.y - m_vecTopFrm[m_iCurTopFrm]->point1.y;
			StretchBlt(StretchDC,
				int(vTopRenPos.x - (fTopWitdh * iExtend) * -0.5f) -1,
				int(vTopRenPos.y - (fTopHeight * iExtend) * 0.5f),
				-int(fTopWitdh * iExtend), int(fTopWitdh * iExtend),
				m_pTex->GetDC(),
				int(m_vecTopFrm[m_iCurTopFrm]->point1.x),
				int(m_vecTopFrm[m_iCurTopFrm]->point1.y),
				fTopWitdh, fTopHeight,
				SRCCOPY);
			TransparentBlt(hdc,
				int(vTopRenPos.x - (fTopWitdh * iExtend) * 0.5f),
				int(vTopRenPos.y - (fTopHeight * iExtend) * 0.5f),
				int(fTopWitdh * iExtend), int(fTopHeight * iExtend),
				StretchDC,
				int(vTopRenPos.x - (fTopWitdh * iExtend) * 0.5f),
				int(vTopRenPos.y - (fTopHeight * iExtend) * 0.5f),
				int(fTopWitdh * iExtend), int(fTopHeight * iExtend),
				RGB(86, 177, 222));
		}
		else // None Flip X
		{
			// Render the Bottom
			Vector2 vBotRenPos = vRenPos + m_vecBotFrm[m_iCurBotFrm]->Pivot;
			float fBotWitdh = m_vecBotFrm[m_iCurBotFrm]->point2.x - m_vecBotFrm[m_iCurBotFrm]->point1.x;
			float fBotHeight = m_vecBotFrm[m_iCurBotFrm]->point2.y - m_vecBotFrm[m_iCurBotFrm]->point1.y;
			StretchBlt(StretchDC,
				int(vBotRenPos.x - (fBotWitdh * iExtend) * 0.5f),
				int(vBotRenPos.y - (fBotHeight * iExtend) * 0.5f),
				int(fBotWitdh * iExtend), int(fBotHeight * iExtend),
				m_pTex->GetDC(),
				int(m_vecBotFrm[m_iCurBotFrm]->point1.x),
				int(m_vecBotFrm[m_iCurBotFrm]->point1.y),
				fBotWitdh, fBotHeight,
				SRCCOPY);
			TransparentBlt(hdc,
				int(vBotRenPos.x - (fBotWitdh * iExtend) * 0.5f),
				int(vBotRenPos.y - (fBotHeight * iExtend) * 0.5f),
				int(fBotWitdh * iExtend), int(fBotHeight * iExtend),
				StretchDC,
				int(vBotRenPos.x - (fBotWitdh * iExtend) * 0.5f),
				int(vBotRenPos.y - (fBotHeight * iExtend) * 0.5f),
				int(fBotWitdh * iExtend), int(fBotHeight * iExtend),
				RGB(86, 177, 222));

			// Render the Top
			Vector2 vTopRenPos = vRenPos + m_vecTopFrm[m_iCurTopFrm]->Pivot;
			float fTopWitdh = m_vecTopFrm[m_iCurTopFrm]->point2.x - m_vecTopFrm[m_iCurTopFrm]->point1.x;
			float fTopHeight = m_vecTopFrm[m_iCurTopFrm]->point2.y - m_vecTopFrm[m_iCurTopFrm]->point1.y;
			StretchBlt(StretchDC,
				int(vTopRenPos.x - (fTopWitdh * iExtend) * 0.5f),
				int(vTopRenPos.y - (fTopHeight * iExtend) * 0.5f),
				int(fTopWitdh * iExtend), int(fTopWitdh * iExtend),
				m_pTex->GetDC(),
				int(m_vecTopFrm[m_iCurTopFrm]->point1.x),
				int(m_vecTopFrm[m_iCurTopFrm]->point1.y),
				fTopWitdh, fTopHeight,
				SRCCOPY);
			TransparentBlt(hdc,
				int(vTopRenPos.x - (fTopWitdh * iExtend) * 0.5f),
				int(vTopRenPos.y - (fTopHeight * iExtend) * 0.5f),
				int(fTopWitdh * iExtend), int(fTopHeight * iExtend),
				StretchDC,
				int(vTopRenPos.x - (fTopWitdh * iExtend) * 0.5f),
				int(vTopRenPos.y - (fTopHeight * iExtend) * 0.5f),
				int(fTopWitdh * iExtend), int(fTopHeight * iExtend),
				RGB(86, 177, 222));
		}

		DeleteObject(StretchDC);
		DeleteObject(StretchBit);
	}

	if(CSceneMgr::GetInst()->GetCurScene()->GetSceneType() == SCENE_TYPE::ANITOOL2)
		RenderText(hdc);
}

void CAnimation2D::Release()
{
}

void CAnimation2D::SetFrame(int _iFrameIdx)
{


	m_bTopFinish = false;
	m_iCurTopFrm = _iFrameIdx;
	m_fTopAccTime = 0.f;

	m_bBotFinish = false;
	m_iCurBotFrm = _iFrameIdx;
	m_fBotAccTime = 0.f;
}

void CAnimation2D::RenderText(HDC hdc)
{
	SetTextAlign(hdc, TA_LEFT);
	TCHAR tch[128] = {};

	// Animation Left
	// Name
	TCHAR* tchName = (wchar_t*)m_strName.c_str();
	swprintf_s(tch, L"Ani Name(State) : %s", tchName);
	TextOut(hdc, 1, 160, tch, (int)_tcslen(tch));

	// 상체 or 하체
	if (m_iCurBody == 0)
		swprintf_s(tch, L"Control Ani : Top");
	else
		swprintf_s(tch, L"Control Ani : Bot");
	TextOut(hdc, 1, 180, tch, (int)_tcslen(tch));

	// 상체 인덱스
	swprintf_s(tch, L"Top Idx : %d", m_iCurTopFrm);
	TextOut(hdc, 1, 200, tch, (int)_tcslen(tch));

	// 상체 피벗
	swprintf_s(tch, L"Top Pivot : %f, %f", m_vecTopFrm[m_iCurTopFrm]->Pivot.x, m_vecTopFrm[m_iCurTopFrm]->Pivot.y);
	TextOut(hdc, 1, 220, tch, (int)_tcslen(tch));

	// 하체 인덱스
	swprintf_s(tch, L"Bot Idx : %d", m_iCurBotFrm);
	TextOut(hdc, 1, 240, tch, (int)_tcslen(tch));

	// 하체 피벗
	swprintf_s(tch, L"Bot Pivot : %f, %f", m_vecBotFrm[m_iCurBotFrm]->Pivot.x, m_vecBotFrm[m_iCurBotFrm]->Pivot.y);
	TextOut(hdc, 1, 260, tch, (int)_tcslen(tch));

	// 프레임 시간
	swprintf_s(tch, L"Frame Time : %f", m_vecTopFrm[m_iCurTopFrm]->Duration);
	TextOut(hdc, 1, 280, tch, (int)_tcslen(tch));

	// 반복 여부
	if (m_bRepeat)
		swprintf_s(tch, L"Repeat : True");
	else
		swprintf_s(tch, L"Repeat : False");
	TextOut(hdc, 1, 300, tch, (int)_tcslen(tch));

	// 플레이 or 스탑
	if(m_bStopAni)
		swprintf_s(tch, L"Animation : Stop");
	else
		swprintf_s(tch, L"Animation : Play");
	TextOut(hdc, 1, 320, tch, (int)_tcslen(tch));

	// 플립 여부
	if (m_bFlipX)
		swprintf_s(tch, L"Flip : true");
	else
		swprintf_s(tch, L"Flip : false");
	TextOut(hdc, 1, 340, tch, (int)_tcslen(tch));
}


void CAnimation2D::Create(wstring _strState, vector<Frm*>* _listFrm)
{
	m_strName = _strState;

	for (vector<Frm*>::iterator iter = _listFrm->begin(); iter != _listFrm->end(); ++iter)
	{
		if ((*iter)->Body == UINT(BODY_TYPE::TOP))
		{
			(*iter)->Pivot = Vector2(0, -60);
			m_vecTopFrm.push_back(*iter);
		}
		else
		{
			(*iter)->Pivot = Vector2(0, -15);
			m_vecBotFrm.push_back(*iter);
		}
	}
}

void CAnimation2D::SetCurEditFrm()
{
	if (m_iCurBody == 0)
		m_CurEditFrm = m_vecTopFrm[m_iCurTopFrm];
	else
		m_CurEditFrm = m_vecBotFrm[m_iCurBotFrm];
}

void CAnimation2D::SetFrmTime(float _fTime)
{
	//m_CurEditFrm->Duration += _fTime;

	m_vecTopFrm[m_iCurTopFrm]->Duration += _fTime;

	m_vecBotFrm[m_iCurBotFrm]->Duration += _fTime;
}

void CAnimation2D::SetPivot(Vector2 _vec)
{
	m_CurEditFrm->Pivot += _vec;
}

void CAnimation2D::FlipX()
{
	if (m_bFlipX)
		m_bFlipX = false;
	else
		m_bFlipX = true;
}

void CAnimation2D::PlayAniToggle()
{
	if (m_bStopAni)
		m_bStopAni = false;
	else
		m_bStopAni = true;

}

void CAnimation2D::PlusMinusFrm(int _ival)
{
	m_iCurTopFrm += _ival;
	m_iCurBotFrm += _ival;

	if (m_iCurTopFrm < 0)
	{
		// 상체
		m_iCurTopFrm = m_vecTopFrm.size()-1;
		m_bTopFinish = false;
		m_fTopAccTime = 0.f;

		// 하체
		m_iCurBotFrm = m_vecBotFrm.size()-1;
		m_bBotFinish = false;
		m_fBotAccTime = 0.f;

		return;
	}
	else if (m_vecTopFrm.size() <= m_iCurTopFrm)
	{
		// 상체
		m_iCurTopFrm = 0;
		m_bTopFinish = true;
		m_fTopAccTime = 0.f;

		// 하체
		m_iCurBotFrm = 0;
		m_bBotFinish = true;
		m_fBotAccTime = 0.f;

		return;
	}
}
