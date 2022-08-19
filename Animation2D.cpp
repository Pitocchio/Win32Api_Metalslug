#include "stdafx.h"
#include "Animation2D.h"

CAnimation2D::CAnimation2D()
	: m_pAnimator(nullptr)
	, m_iCurFrame(0)
	, m_fAccTime(0)
	, m_bFinish(false)
	, m_iCurFrame_T (0)
	, m_fAccTime_T(0)
	, m_bFinish_T(false)
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
	//if (m_bFinish)
	//	return;

	//m_fAccTime += fDT;

	//if (m_vecFrame[m_iCurFrame].fDuration < m_fAccTime) // 누적시간이, 현재 프레임에서 머물러야 할 시간을 넘게 된다면, 다음 프레임으로 넘어감
	//{
	//	++m_iCurFrame;

	//	if (m_vecFrame.size() <= m_iCurFrame)
	//	{
	//		m_iCurFrame = -1;
	//		m_bFinish = true;
	//		m_fAccTime = 0.f;
	//		return;
	//	}

	//	m_fAccTime = m_fAccTime - m_vecFrame[m_iCurFrame].fDuration; 
	//}




	if (m_bFinish_T)
		return;

	m_fAccTime_T += fDT;

	if (m_vecFrmTop[m_iCurFrame_T]->Duration < m_fAccTime_T) // 누적시간이, 현재 프레임에서 머물러야 할 시간을 넘게 된다면, 다음 프레임으로 넘어감
	{
		++m_iCurFrame_T;

		if (m_vecFrmTop.size() <= m_iCurFrame_T)
		{
			m_iCurFrame_T = -1;
			m_bFinish_T = true;
			m_fAccTime_T = 0.f;
			return;
		}

		m_fAccTime_T = m_fAccTime_T - m_vecFrmTop[m_iCurFrame_T]->Duration;
	}
}

void CAnimation2D::Render(HDC hdc)
{
	/*
	if (m_bFinish)
		return;

	Vector2 vRenPos = CCamera::GetInst()->GetRenderPos(Vector2(dynamic_cast<CPlayer*>(m_pAnimator->GetOwnerObj())->GetInfo().fX,
		dynamic_cast<CPlayer*>(m_pAnimator->GetOwnerObj())->GetInfo().fY));
	

	vRenPos += m_vecFrame[m_iCurFrame].vOffset; // 오프셋 값 적용

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
	*/


	if (m_bFinish_T)
		return;

	int k = 0;

	if (m_pTex != nullptr)
	{

		/*Vector2 vRenPos = CCamera::GetInst()->GetRenderPos(Vector2(0.f, 0.f));

		vRenPos += m_vecFrmTop[m_iCurFrame_T]->Pivot;

		float fWitdh = m_vecFrmTop[m_iCurFrame_T]->point2.x - m_vecFrmTop[m_iCurFrame_T]->point1.x;
		float fHeight = m_vecFrmTop[m_iCurFrame_T]->point2.y - m_vecFrmTop[m_iCurFrame_T]->point1.y;

		TransparentBlt(hdc,
			int(vRenPos.x - fWitdh * 0.5f),
			int(vRenPos.y - fHeight * 0.5f),
			int(fWitdh), int(fHeight),
			m_pTex->GetDC(),
			int(m_vecFrmTop[m_iCurFrame_T]->point1.x),
			int(m_vecFrmTop[m_iCurFrame_T]->point1.y),
			int(m_vecFrmTop[m_iCurFrame_T]->point2.x),
			int(m_vecFrmTop[m_iCurFrame_T]->point2.y),
			RGB(86, 177, 222));*/


		Vector2 vRenPos = CCamera::GetInst()->GetRenderPos(Vector2(0.f, 0.f));

		vRenPos += m_vecFrmTop[m_iCurFrame_T]->Pivot;

		float fWitdh = m_vecFrmTop[m_iCurFrame_T]->point2.x - m_vecFrmTop[m_iCurFrame_T]->point1.x;
		float fHeight = m_vecFrmTop[m_iCurFrame_T]->point2.y - m_vecFrmTop[m_iCurFrame_T]->point1.y;

		TransparentBlt(hdc,
			int(vRenPos.x - fWitdh * 0.5f),
			int(vRenPos.y - fHeight * 0.5f),
			int(fWitdh), int(fHeight),
			m_pTex->GetDC(),
			int(m_vecFrmTop[m_iCurFrame_T]->point1.x),
			int(m_vecFrmTop[m_iCurFrame_T]->point1.y),
			fWitdh, fHeight,
			RGB(86, 177, 222));
	}



	RenderText(hdc);
}

void CAnimation2D::Release()
{
}

void CAnimation2D::SetFrame(int _iFrameIdx)
{
	m_bFinish_T = false;
	m_iCurFrame_T = _iFrameIdx;
	m_fAccTime_T = 0.f;
}

void CAnimation2D::RenderText(HDC hdc)
{
	SetTextAlign(hdc, TA_LEFT);
	TCHAR tch[128] = {};

	// Animation Left
	// Name
	swprintf_s(tch, L"Ani Name(State) : ");
	TextOut(hdc, 1, 160, tch, (int)_tcslen(tch));

	// 상체 or 하체
	swprintf_s(tch, L"Control Ani : ");
	TextOut(hdc, 1, 180, tch, (int)_tcslen(tch));

	// 상체 인덱스
	swprintf_s(tch, L"Top Idx : ");
	TextOut(hdc, 1, 200, tch, (int)_tcslen(tch));

	// 상체 피벗
	swprintf_s(tch, L"Top Pivot : ");
	TextOut(hdc, 1, 220, tch, (int)_tcslen(tch));

	// 하체 인덱스
	swprintf_s(tch, L"Bot Idx : ");
	TextOut(hdc, 1, 240, tch, (int)_tcslen(tch));

	// 하체 피벗
	swprintf_s(tch, L"Top Pivot : ");
	TextOut(hdc, 1, 260, tch, (int)_tcslen(tch));

	// 프레임 시간
	swprintf_s(tch, L"Frame Time : ");
	TextOut(hdc, 1, 280, tch, (int)_tcslen(tch));

	// 반복 여부
	swprintf_s(tch, L"Repeat : ");
	TextOut(hdc, 1, 300, tch, (int)_tcslen(tch));




	swprintf_s(tch, L"Num 2, 4, 6, 8 : Animation Move (5px)");
	TextOut(hdc, 1, 400, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Num 2, 4, 6, 8 + Ctrl: Animation Move (1px)");
	TextOut(hdc, 1, 420, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Ctrl : Choice Top or Bottom");
	TextOut(hdc, 1, 440, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Shift : LR Flip");
	TextOut(hdc, 1, 460, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"Enter : Play Toggle(On/Off)");
	TextOut(hdc, 1, 480, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"LEFT_KEY : Prev State");
	TextOut(hdc, 1, 500, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"RIGHT_KEY : Next State");
	TextOut(hdc, 1, 520, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"UP_KEY : Frame Time 0.01second + ");
	TextOut(hdc, 1, 540, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"DOWN_KEY : Frame Time 0.01second - ");
	TextOut(hdc, 1, 560, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"S : Save");
	TextOut(hdc, 1, 580, tch, (int)_tcslen(tch));

	swprintf_s(tch, L"L : Load");
	TextOut(hdc, 1, 600, tch, (int)_tcslen(tch));
}


void CAnimation2D::Create(wstring _strState, vector<Frm*>* _listFrm)
{
	for (vector<Frm*>::iterator iter = _listFrm->begin(); iter != _listFrm->end(); ++iter)
	{
		if ((*iter)->Body == UINT(BODY_TYPE::TOP))
			m_vecFrmTop.push_back(*iter);
		else
			m_vecFrmBot.push_back(*iter);
	}
}
