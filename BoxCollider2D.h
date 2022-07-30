#pragma once
#include "Collider2D.h"

class CBoxCollider2D : public CCollider2D
{
public:
	CBoxCollider2D();
	~CBoxCollider2D();

public: // Lifecycle
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;

public: // Methods
	void SetColliderRect();
	RECT GetColliderRect() const;

	void SetSize(Vector2 vec);
	Vector2 GetSize() const;

private:
	RECT m_rcCollider;
	Vector2 m_vSize;
};
