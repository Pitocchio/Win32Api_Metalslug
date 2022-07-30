#pragma once
#include "Enemy.h"

class CZombie : public CEnemy
{
public:
	CZombie();
	~CZombie();

public: //Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public: // Methods
	virtual void Move() override;
	virtual void Attack() override;

};

