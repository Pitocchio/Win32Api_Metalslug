#pragma once

class CCollider;
class CBoxCollider2D;

union COLLIDER_ID
{
	struct {
		UINT left_id;
		UINT right_id;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLETONE(CCollisionMgr)

public: // Lifecycle
	void Update();

public: // Methods
	void CheckObjectType(OBJECT_TYPE left, OBJECT_TYPE right); // 충돌 지정
	void ResetObjectType();

private: // 업데이트 내부에서 돌릴거라 private
	void CollisionUpdate(OBJECT_TYPE left, OBJECT_TYPE right); // 충돌 검사 반복문
	bool IsCollision(CBoxCollider2D* pLeftCollider, CBoxCollider2D* pRihtCollider);

private: // Variables
	UINT m_arrCheck[(UINT)OBJECT_TYPE::TYPEEND_OBJECT]; // 비트연산자를 이용한 충돌 체크 배열 
	map<ULONGLONG, bool> m_mapColInfo;// 충돌체 간의 이전 프레임 충돌 정보
	
};

