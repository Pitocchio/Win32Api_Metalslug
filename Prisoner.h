#pragma once
#include "Npc.h"

class CPrisoner : public CNpc
{
public:
	CPrisoner();
	~CPrisoner();

public: //Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;

public: // Methods
	virtual void Move() override;
};

