#pragma once
#include "Attackobj.h"

class CPlayer : public CAttackobj
{
public:
	CPlayer();
	~CPlayer();


public: // Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public: // Methods
	virtual void Move() override;
	virtual void Attack() override;


private: // Variables
	int m_iBulletCount;
	int m_iGrenadeCount;
};

