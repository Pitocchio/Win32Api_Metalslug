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
	// Map data File load
	void LoadMapObj(const wstring& _strRelativePath);

private:
	vector <MAPOBJ*> m_vecMapObj;

	wstring m_strFilePath;

};

