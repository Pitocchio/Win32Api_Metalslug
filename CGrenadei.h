#pragma once
#include "Moveobj.h"

class CGrenadei : public CProjectile
{
public:
	CGrenadei();
	~CGrenadei();

public: //Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public: // Methods
	virtual void Move() override;
};


