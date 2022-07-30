#pragma once
#include "Item.h"

class CFood : public CItem
{

public:
	CFood();
	~CFood();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
};

