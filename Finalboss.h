#pragma once
#include "Enemy.h"

class CFinalboss : public CEnemy
{
public:
	CFinalboss();
	~CFinalboss();

public: //Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;

public: // Methods
	virtual void Move() override;
	virtual void Attack() override;
};

