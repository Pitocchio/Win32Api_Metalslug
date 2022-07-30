#pragma once
#include "Moveobj.h"

class CBullet : public CProjectile
{
public:
	CBullet();
	~CBullet();

public: //Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;

public: // Methods
	virtual void Move() override;
};

