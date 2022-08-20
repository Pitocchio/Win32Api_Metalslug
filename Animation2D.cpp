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
	// 상체 기준

	if (m_bTopFinish)
		return;

	int k = 0;

	if (m_pTex != nullptr)
	{
		Vector2 vRenPos = CCamera::GetInst()->GetRenderPos(Vector2(0.f, 0.f));

		// Bottom
		Vector2 vBotRenPos = vRenPos + m_vecBotFrm[m_iCurBotFrm]->Pivot;

		float fBotWitdh = m_vecBotFrm[m_iCurBotFrm]->point2.x - m_vecBotFrm[m_iCurBotFrm]->point1.x;
		float fBotHeight = m_vecBotFrm[m_iCurBotFrm]->point2.y - m_vecBotFrm[m_iCurBotFrm]->point1.y;

		TransparentBlt(hdc,
			int(vBotRenPos.x - fBotWitdh * 0.5f),
			int(vBotRenPos.y - fBotHeight * 0.5f),
			int(fBotWitdh), int(fBotHeight),
			m_pTex->GetDC(),
			int(m_vecBotFrm[m_iCurBotFrm]->point1.x),
			int(m_vecBotFrm[m_iCurBotFrm]->point1.y),
			fBotWitdh, fBotHeight,
			RGB(86, 177, 222));

		// Top
		Vector2 vTopRenPos = vRenPos + m_vecTopFrm[m_iCurTopFrm]->Pivot;

		float fTopWitdh = m_vecTopFrm[m_iCurTopFrm]->point2.x - m_vecTopFrm[m_iCurTopFrm]->point1.x;
		float fTopHeight = m_vecTopFrm[m_iCurTopFrm]->point2.y - m_vecTopFrm[m_iCurTopFrm]->point1.y;

		TransparentBlt(hdc,
			int(vTopRenPos.x - fTopWitdh * 0.5f),
			int(vTopRenPos.y - fTopHeight * 0.5f),
			int(fTopWitdh), int(fTopHeight),
			m_pTex->GetDC(),
			int(m_vecTopFrm[m_iCurTopFrm]->point1.x),
			int(m_vecTopFrm[m_iCurTopFrm]->point1.y),
			fTopWitdh, fTopHeight,
			RGB(86, 177, 222));
	}

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




	swprintf_s(tch, L"Num 2, 4, 6, 8 : Animation Move (5px)");
	TextOut(hdc, 1, 400, tch, (int)_tcslen(tch));

	/*swprintf_s(tch, L"Num 2, 4, 6, 8 + Ctrl: Animation Move (1px)");
	TextOut(hdc, 1, 420, tch, (int)_tcslen(tch));*/

	swprintf_s(tch, L"Ctrl : Choice Top or Bottom");
	TextOut(hdc, 1, 440, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Shift : LR Flip");
	TextOut(hdc, 1, 460, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Enter : Play Toggle(On/Off)");
	TextOut(hdc, 1, 480, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"LEFT_KEY : Prev Frame");
	TextOut(hdc, 1, 500, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"RIGHT_KEY : Next Frame");
	TextOut(hdc, 1, 520, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"UP_KEY : Frame Time 0.01second + ");
	TextOut(hdc, 1, 540, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"DOWN_KEY : Frame Time 0.01second - ");
	TextOut(hdc, 1, 560, tch, (int)_tcslen(tch));

}


void CAnimation2D::Create(wstring _strState, vector<Frm*>* _listFrm)
{
	m_strName = _strState;

	for (vector<Frm*>::iterator iter = _listFrm->begin(); iter != _listFrm->end(); ++iter)
	{
		if ((*iter)->Body == UINT(BODY_TYPE::TOP))
			m_vecTopFrm.push_back(*iter);
		else
			m_vecBotFrm.push_back(*iter);
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
		m_bTopFinish = true;
		m_fTopAccTime = 0.f;

		// 하체
		m_iCurBotFrm = m_vecBotFrm.size()-1;
		m_bBotFinish = true;
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
