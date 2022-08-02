#pragma once
#include "Mapcollider.h"

class CEnemycollider : public CMapcollider
{

public:
	CEnemycollider();
	~CEnemycollider();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

