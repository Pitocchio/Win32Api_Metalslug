#include "stdafx.h"
#include "Camera.h"

CCamera* CCamera::m_pInst = nullptr;

void CCamera::Init()
{
	m_pTargetObj = nullptr;

	m_fTime = 2.f;

	m_vLookAt = Vector2(0.f, 0.f);
	m_vPreLookAt = m_vLookAt;
	m_vCurLookAt = m_vLookAt;
	m_fSpeed = 0;
	bBlock = false;
}

void CCamera::Update()
{
	if (!bBlock)
	{

		if (m_pTargetObj)
		{
			if (m_pTargetObj->GetObjCurState() == OBJECT_STATE::DEAD)
			{
				m_pTargetObj = nullptr;
			}
			else
			{
				// m_vLookAt = m_pTargetObj->GetPos();
				m_vLookAt = dynamic_cast<CPlayer*>(m_pTargetObj)->GetPOS_Test();
			}
		}

		CalDiff();
	}
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
	float fMoveDis = (m_vLookAt - m_vPreLookAt).Length(); // �̵� �Ÿ� ����
	m_fSpeed = fMoveDis / m_fTime; // �ʴ� �̵� ���ǵ� ����
	m_fAccTime = 0.f;

	//m_vLookAt = vec;
}

void CCamera::CalDiff()
{
	// ���� Look�� ���� Look�� ���̰��� �����ؼ� ������ Look�� ���Ѵ�
	// m_fTime�� �ð� ���� m_vLook�� ���� ��

	m_fAccTime += fDT;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vector2 vLookDir = m_vLookAt - m_vPreLookAt; // Set�� Look������ ������ ���Ѵ�
		vLookDir.Normalize();

		m_vCurLookAt = m_vPreLookAt + vLookDir * m_fSpeed * fDT; // ���� ������ ��ġ���� ���⸸ŭ 500DT�� �ӵ��� �̵�
	}

	Vector2 vCenter = Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);

	m_vDiff = m_vCurLookAt - vCenter;

	m_vPreLookAt = m_vCurLookAt;


	//
	//Vector2 vLookDir = m_vLookAt - m_vPreLookAt; // Set�� Look������ ������ ���Ѵ�
	//vLookDir.Normalize();

	//m_vCurLookAt = m_vPreLookAt + vLookDir * 500.f * fDT; // ���� ������ ��ġ���� ���⸸ŭ 500DT�� �ӵ��� �̵�

	//Vector2 vCenter = Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f);

	//m_vDiff = m_vCurLookAt - vCenter;

	//m_vPreLookAt = m_vCurLookAt;

}
