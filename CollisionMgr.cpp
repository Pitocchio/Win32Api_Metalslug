#include "stdafx.h"
#include "CollisionMgr.h"

CCollisionMgr* CCollisionMgr::m_pInst = nullptr;

void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)OBJECT_TYPE::TYPEEND_OBJECT; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)OBJECT_TYPE::TYPEEND_OBJECT; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol)) // 비트가 체크되어 있다면
			{
				CollisionUpdate((OBJECT_TYPE)iRow, (OBJECT_TYPE)iCol);
			}
		}
	}

}

void CCollisionMgr::CheckObjectType(OBJECT_TYPE left, OBJECT_TYPE right)
{
	// 매개변수 중 더 작은 그룹 타입을 행으로, 큰 값을 열로 사용 (대칭 구조의 한쪽만 사용하기에)
	UINT iRow = (UINT)left;
	UINT iCol = (UINT)right;

	if (iCol < iRow)
	{
		iRow = (UINT)right;
		iCol = (UINT)left;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // 비트가 채워져있다면
	{
		m_arrCheck[iRow] &= ~(1 << iCol); // 체크 off
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol); // 체크 on
	}

}

void CCollisionMgr::CollisionUpdate(OBJECT_TYPE left, OBJECT_TYPE right)
{
	list<CObject*>* listLeft = CObjectMgr::GetInst()->GetlistObj(left); // 여기 지금 NULL로 들어오고 있음 수정 필요!!!
	list<CObject*>* listRight = CObjectMgr::GetInst()->GetlistObj(right);

	if(listLeft == nullptr || listRight == nullptr) // 게임 씬 첫 프레임 예외처리
		return; 

	map<ULONGLONG, bool>::iterator iter;

	for (list<CObject*>::iterator it1 = listLeft->begin(); it1 != listLeft->end(); ++it1)
	{
		if ((*it1)->GetCollider() == nullptr) // 콜라이더가 없는 경우 예외 처리
			continue;

		for (list<CObject*>::iterator it2 = listRight->begin(); it2 != listRight->end(); ++it2)
		{
			if ((*it2)->GetCollider() == nullptr || (*it1) == (*it2)) // 위와 같거나 자기 자신과의 충돌인 경우 예외 처리
				continue;

			CCollider2D* pLeftCol = (*it1)->GetCollider();
			CCollider2D* pRightCol = (*it2)->GetCollider();

			// 두 충돌체 조합 아이디 생성 by Union
			COLLIDER_ID ID;
			ID.left_id = pLeftCol->GetID();
			ID.right_id = pRightCol->GetID();
			iter = m_mapColInfo.find(ID.ID);
			
			if (iter == m_mapColInfo.end()) // 이전 프레임 충돌 정보가 없다면(이전에 충돌한 적이 없다면)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false)); // 새로이 등록 시킨다
				iter = m_mapColInfo.find(ID.ID);
			}


			if (pLeftCol->GetIsColliderType() == COLLIDER_TYPE::BOX2D && pRightCol -> GetIsColliderType() == COLLIDER_TYPE::BOX2D)
			{
				if (IsCollisionBoxBox(pLeftCol, pRightCol)) // 충돌 검사 진행 후 반환받은 bool 값으로 충돌한지 안한지 
				{
					// 현재 충돌 중이다

					if (iter->second)  // 이전프레임에도 충돌, 현재 프레임에도 충돌 (충돌이 진행중인 시점)
					{
						pLeftCol->OnCollision(pRightCol); // 나와 충돌한 상대방의 콜라이더를 취한다
						pRightCol->OnCollision(pLeftCol);
					}
					else // 이전에는 충돌하지 않았지만, 현재프레임에서 충돌했다 (충돌이 막 시작된 시점)
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
				else 
				{
					// 현재 충돌중이지 않다

					if (iter->second) // 이전에는 충돌했으나 현재는 충돌중이지 않다 (충돌이 막 종료된 시점)
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}

				}
			}

			if (pLeftCol->GetIsColliderType() == COLLIDER_TYPE::LINE2D || pRightCol->GetIsColliderType() == COLLIDER_TYPE::LINE2D)
			{
				if (IsCollisionBoxLine(pLeftCol, pRightCol)) // 충돌 검사 진행 후 반환받은 bool 값으로 충돌한지 안한지 
				{
					// 현재 충돌 중이다

					if (iter->second)  // 이전프레임에도 충돌, 현재 프레임에도 충돌 (충돌이 진행중인 시점)
					{
						pLeftCol->OnCollision(pRightCol); // 나와 충돌한 상대방의 콜라이더를 취한다
						pRightCol->OnCollision(pLeftCol);
					}
					else // 이전에는 충돌하지 않았지만, 현재프레임에서 충돌했다 (충돌이 막 시작된 시점)
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
				else
				{
					// 현재 충돌중이지 않다

					if (iter->second) // 이전에는 충돌했으나 현재는 충돌중이지 않다 (충돌이 막 종료된 시점)
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}

				}

			}
		}
	}
}

bool CCollisionMgr::IsCollisionBoxBox(CCollider2D* pLeftCollider, CCollider2D* pRihtCollider)
{
	Vector2 vLeftPos = pLeftCollider->GetOffset();
	Vector2 vLeftSize = dynamic_cast<CBoxCollider2D*>(pLeftCollider)->GetSize();

	Vector2 vRightPos = pRihtCollider->GetOffset();
	Vector2 vRightSize = dynamic_cast<CBoxCollider2D*>(pLeftCollider)->GetSize();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftSize.x + vRightSize.x) * 0.5f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftSize.y + vRightSize.y) * 0.5f)
	{
		return true;
	}

	return false;
}

bool CCollisionMgr::IsCollisionBoxLine(CCollider2D* pLeftCollider, CCollider2D* pRihtCollider)
{
	//Vector2 vLineStart;
	//Vector2 vLineEnd;
	//Vector2 vBoxPos;
	//Vector2 vBoxSize;

	//if (pLeftCollider->GetIsColliderType() == COLLIDER_TYPE::LINE2D)
	//{
	//	vLineStart = dynamic_cast<CMapLineCollider2D*>(pLeftCollider)->GetStartPoint();
	//	vLineEnd = dynamic_cast<CMapLineCollider2D*>(pLeftCollider)->GetEndPoint();

	//	vBoxPos = pRihtCollider->GetOffset();
	//	vBoxSize = dynamic_cast<CBoxCollider2D*>(pRihtCollider)->GetSize();
	//}
	//else
	//{
	//	vLineStart = dynamic_cast<CMapLineCollider2D*>(pRihtCollider)->GetStartPoint();
	//	vLineEnd = dynamic_cast<CMapLineCollider2D*>(pRihtCollider)->GetEndPoint();

	//	vBoxPos = pLeftCollider->GetOffset();
	//	vBoxSize = dynamic_cast<CBoxCollider2D*>(pLeftCollider)->GetSize();
	//}

	//// 플레이어 콜라이더의 밑변 y 값
	//float fPlayerPosY = vBoxPos.y + vBoxSize.y * 0.5f;

	//// 플레이어와 그라운드의 충돌을 처리하기 위한 선분 (플레이어 윗변 Y부터 플레이어 size y*1.5까지)
	//Vector2 vVerticalLineStart = vBoxPos;
	//Vector2 vVerticalLineEnd  = Vector2(vBoxPos.x, fPlayerPosY + vBoxSize.y * 0.5f);

	//// VetricalLine과 Ground 선분의 교차점 
	//Vector2 vGroundPos = IntersectionPoint(&vVerticalLineStart, &vVerticalLineEnd, &vLineStart, &vLineEnd);


	//


	//if (fPlayerPosY > vGroundPos.y)
	//{
	//}
	//	return true;


	return false;
}



void CCollisionMgr::ResetObjectType()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)OBJECT_TYPE::TYPEEND_OBJECT);
}

Vector2 CCollisionMgr::IntersectionPoint(const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4)
{
	Vector2 ret;

	ret.x = ((p1->x * p2->y - p1->y * p2->x) * (p3->x - p4->x) - (p1->x - p2->x) * (p3->x * p4->y - p3->y * p4->x)) / ((p1->x - p2->x) * (p3->y - p4->y) - (p1->y - p2->y) * (p3->x - p4->x));

	ret.y = ((p1->x * p2->y - p1->y * p2->x) * (p3->y - p4->y) - (p1->y - p2->y) * (p3->x * p4->y - p3->y * p4->x)) / ((p1->x - p2->x) * (p3->y - p4->y) - (p1->y - p2->y) * (p3->x - p4->x));

	return ret;
}

