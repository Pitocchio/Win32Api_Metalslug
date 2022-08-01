#pragma once
#include "Mapcollider.h"

class CCameracollider : public CMapcollider
{

public:
	CCameracollider();
	~CCameracollider();

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

