#pragma once
#include "Component.h"

class CTransform2D : public CComponent
{

public:
	CTransform2D();
	~CTransform2D();
	

public: // Lifecycle
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;

public: // Methods
	void SetOwnerObj(CObject* obj);

	void SetPos(Vector2 vec);
	Vector2 GetPos() const;

	void SetSize(Vector2 vec);
	Vector2 GetSize() const;

	void SetAngle(float vec);
	float GetAngle() const;

	void SetIsActive(bool b);
	bool GetIsActive();

private: // Variables
	CObject* m_pOwnerObj;
	Vector2 m_vPos;
	Vector2 m_vSize;
	float m_fAngle;
	bool m_bActive;

};

