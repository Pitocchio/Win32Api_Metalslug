#pragma once
#include "Scene.h"

class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene();

public: // Methods

	virtual void Update() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Render(HDC hdc) override;


private:
	vector <MAPOBJ*> m_vecMapObj;
};

