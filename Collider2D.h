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

	//�浹 ���� �Լ�
	void OnCollision(CBoxCollider2D* pOther); // �浹�� �������� ����
	void OnCollisionEnter(CBoxCollider2D* pOther); // �浹�� ó�� �� ���۵� ����
	void OnCollisionExit(CBoxCollider2D* pOther); // �浹�� ó�� �� ����� ����


protected: // Variables
	CObject* m_pOwnerObj;

	CBoxCollider2D* m_pOtherObjCol;

	COLLIDER_TYPE m_ColliderType;
	UINT m_iCollision;
	Vector2 m_vOffset;
	bool m_bActive;

	UINT m_iID; // �浹ü ���� ID ��
	static UINT g_iNextID;
};

