#pragma once
#include "Moveobj.h"

class CLiquid :public CProjectile
{
public:
	CLiquid();
	~CLiquid();

public: //Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public: // Methods
	virtual void Move() override;

};

