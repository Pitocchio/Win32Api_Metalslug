#include "stdafx.h"
#include "CollisionMgr.h"

CCollisionMgr* CCollisionMgr::m_pInst = nullptr;

void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)OBJECT_TYPE::TYPEEND_OBJECT; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)OBJECT_TYPE::TYPEEND_OBJECT; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol)) // ��Ʈ�� üũ�Ǿ� �ִٸ�
			{
				CollisionUpdate((OBJECT_TYPE)iRow, (OBJECT_TYPE)iCol);
			}
		}
	}

}

void CCollisionMgr::CheckObjectType(OBJECT_TYPE left, OBJECT_TYPE right)
{
	// �Ű����� �� �� ���� �׷� Ÿ���� ������, ū ���� ���� ��� (��Ī ������ ���ʸ� ����ϱ⿡)
	UINT iRow = (UINT)left;
	UINT iCol = (UINT)right;

	if (iCol < iRow)
	{
		iRow = (UINT)right;
		iCol = (UINT)left;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // ��Ʈ�� ä�����ִٸ�
	{
		m_arrCheck[iRow] &= ~(1 << iCol); // üũ off
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); // üũ on
	}

}

void CCollisionMgr::CollisionUpdate(OBJECT_TYPE left, OBJECT_TYPE right)
{
	list<CObject*>* listLeft = CObjectMgr::GetInst()->GetlistObj(left); // ���� ���� NULL�� ������ ���� ���� �ʿ�!!!
	list<CObject*>* listRight = CObjectMgr::GetInst()->GetlistObj(right);

	if(listLeft == nullptr || listRight == nullptr) // ���� �� ù ������ ����ó��
		return; 

	map<ULONGLONG, bool>::iterator iter;

	for (list<CObject*>::iterator it1 = listLeft->begin(); it1 != listLeft->end(); ++it1)
	{
		if ((*it1)->GetCollider() == nullptr) // �ݶ��̴��� ���� ��� ���� ó��
			continue;

		for (list<CObject*>::iterator it2 = listRight->begin(); it2 != listRight->end(); ++it2)
		{
			if ((*it2)->GetCollider() == nullptr || (*it1) == (*it2)) // ���� ���ų� �ڱ� �ڽŰ��� �浹�� ��� ���� ó��
				continue;

			CBoxCollider2D* pLeftCol = (*it1)->GetCollider();
			CBoxCollider2D* pRightCol = (*it2)->GetCollider();

			// �� �浹ü ���� ���̵� ���� by Union
			COLLIDER_ID ID;
			ID.left_id = pLeftCol->GetID();
			ID.right_id = pRightCol->GetID();
			iter = m_mapColInfo.find(ID.ID);
			
			if (iter == m_mapColInfo.end()) // ���� ������ �浹 ������ ���ٸ�(������ �浹�� ���� ���ٸ�)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false)); // ������ ��� ��Ų��
				iter = m_mapColInfo.find(ID.ID);
			}


			if (IsCollision(pLeftCol, pRightCol)) // �浹 �˻� ���� �� ��ȯ���� bool ������ �浹���� ������ 
			{
				// ���� �浹 ���̴�

				if (iter->second)  // ���������ӿ��� �浹, ���� �����ӿ��� �浹 (�浹�� �������� ����)
				{
					pLeftCol->OnCollision(pRightCol); // ���� �浹�� ������ �ݶ��̴��� ���Ѵ�
					pRightCol->OnCollision(pLeftCol);
				}
				else // �������� �浹���� �ʾ�����, ���������ӿ��� �浹�ߴ� (�浹�� �� ���۵� ����)
				{
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else 
			{
				// ���� �浹������ �ʴ�

				if (iter->second) // �������� �浹������ ����� �浹������ �ʴ� (�浹�� �� ����� ����)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}

			}
		}
	}
}

bool CCollisionMgr::IsCollision(CBoxCollider2D* pLeftCollider, CBoxCollider2D* pRihtCollider)
{
	Vector2 vLeftPos = pLeftCollider->GetOffset();
	Vector2 vLeftSize = pLeftCollider->GetSize();

	Vector2 vRightPos = pRihtCollider->GetOffset();
	Vector2 vRightSize = pRihtCollider->GetSize();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftSize.x + vRightSize.x) * 0.5f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftSize.y + vRightSize.y) * 0.5f)
	{
		return true;
	}

	return false;
}



void CCollisionMgr::ResetObjectType()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJECT_TYPE::TYPEEND_OBJECT);
}
