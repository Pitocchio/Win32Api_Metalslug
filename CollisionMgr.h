#pragma once

class CCollider2D;
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
	void CheckObjectType(OBJECT_TYPE left, OBJECT_TYPE right); // �浹 ����
	void ResetObjectType();
	Vector2 IntersectionPoint(const Vector2* p1, const Vector2* p2, const Vector2* p3, const Vector2* p4);


private: // ������Ʈ ���ο��� �����Ŷ� private
	void CollisionUpdate(OBJECT_TYPE left, OBJECT_TYPE right); // �浹 �˻� �ݺ���
	bool IsCollisionBoxBox(CCollider2D* pLeftCollider, CCollider2D* pRihtCollider);
	bool IsCollisionBoxLine(CCollider2D* pLeftCollider, CCollider2D* pRihtCollider);

private: // Variables
	UINT m_arrCheck[(UINT)OBJECT_TYPE::TYPEEND_OBJECT]; // ��Ʈ�����ڸ� �̿��� �浹 üũ �迭 
	map<ULONGLONG, bool> m_mapColInfo;// �浹ü ���� ���� ������ �浹 ����
	
};

