#pragma once
#include "Scene.h"

class CToolScene : public CScene
{
public:
	CToolScene();
	~CToolScene();

public: // Methods
	virtual void Update() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

