#include "stdafx.h"
#include "Camera.h"

CCamera* CCamera::m_pInst = nullptr;

void CCamera::Init()
{
	m_pTargetObj = nullptr;

	m_fTime = 2.f;

	m_vLookAt = Vector2(PLAYER_POS_X, PLAYER_POS_Y);
	m_vPreLookAt = m_vLookAt;
	m_vCurLookAt = m_vLookAt;
	m_fSpeed = 0;

}

void CCamera::Update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->GetObjCurState() == OBJECT_STATE::DEAD)
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}


	// Camera Move by Key
	
	/*if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::UP) == KEY_STATE::KEY_HOLD)
		m_vLookAt.y -= 500.f * DT;
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::DOWN) == KEY_STATE::KEY_HOLD)
		m_vLookAt.y += 500.f * DT;
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::KEY_HOLD)
		m_vLookAt.x -= 500.f * DT;
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::KEY_HOLD)
		m_vLookAt.x += 500.f * DT;*/
	

	CalDiff();
}

void CCamera::Release()
{
	/*if (m_pTargetObj != nullptr)
	{
		delete m_pTargetObj;

		m_pTargetObj = nullptr;
	}*/
}

void CCamera::SetLookAt(Vector2 vec)
{
	m_vLookAt = vec;
	float fMoveDis = (m_vLookAt - m_vPreLookAt).Length(); // 이동 거리 구함
	m_fSpeed = fMoveDis / m_fTime; // 초당 이동 스피드 구함
	m_fAccTime = 0.f;
}

void CCamera::CalDiff()
{
	// 이전 Look과 현재 Look의 차이값을 보정해서 현재의 Look을 구한다

	// m_fTime의 시간 동안 m_vLook을 향해 감
	m_fAccTime += DT;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vector2 vLookDir = m_vLookAt - m_vPreLookAt; // Set할 Look으로의 방향을 구한다
		vLookDir.Normalize();

		m_vCurLookAt = m_vPreLookAt + vLookDir * m_fSpeed * DT; // 이전 프레임 위치에서 방향만큼 500DT의 속도로 이동
	}

	Vector2 vCenter = Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);

	m_vDiff = m_vCurLookAt - vCenter;

	m_vPreLookAt = m_vCurLookAt;
}
