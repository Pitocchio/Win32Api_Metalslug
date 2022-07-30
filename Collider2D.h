#pragma once
#include "Component.h"

class CCollider2D : public CComponent
{

public:
	CCollider2D();
	CCollider2D(const CCollider2D& origin);
	~CCollider2D();

//public: // Lifecycle
//	virtual void Init() override;
//	virtual void Update() override;
//	virtual void LateUpdate() override;
//	virtual void Render(HDC hdc) override;

public: // Methods
	void SetOwnerObj(CObject* obj);
	CObject* GetOwnerObj();

	CBoxCollider2D* GetOtherObjCol();

	void SetOffset(Vector2 vec);
	Vector2 GetOffset() const;

	bool IsCollision() const;

	void SetIsColliderType(COLLIDER_TYPE type);
	COLLIDER_TYPE GetIsColliderType() const;

	void SetIsActive(bool b);
	bool IsActive();

	UINT GetID() { return m_iID; }

	CCollider2D& operator = (CCollider2D& origin) = delete; 

	//충돌 시점 함수
	void OnCollision(CBoxCollider2D* pOther); // 충돌이 진행중인 시점
	void OnCollisionEnter(CBoxCollider2D* pOther); // 충돌이 처음 막 시작된 시점
	void OnCollisionExit(CBoxCollider2D* pOther); // 충돌이 처음 막 종료된 시점


protected: // Variables
	CObject* m_pOwnerObj;

	CBoxCollider2D* m_pOtherObjCol;

	COLLIDER_TYPE m_ColliderType;
	UINT m_iCollision;
	Vector2 m_vOffset;
	bool m_bActive;

	UINT m_iID; // 충돌체 고유 ID 값
	static UINT g_iNextID;
};

