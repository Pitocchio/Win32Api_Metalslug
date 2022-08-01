#pragma once
#include "Object.h"

class CRigidbody2D;

class CMoveobj : public CObject
{
public:
	CMoveobj();
	~CMoveobj();


public: // Lifecycle
	virtual void Init() override;

public: // Methods
	virtual void Move() = 0;



protected: // Variables
	Vector2 m_vLook;
	float m_fSpeed;

	CRigidbody2D* m_pRigidbody;



};

