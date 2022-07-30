#pragma once
#include "Weapon.h"

class CHeavymachinegun : public CWeapon
{
public:
	CHeavymachinegun();
	~CHeavymachinegun();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
};

