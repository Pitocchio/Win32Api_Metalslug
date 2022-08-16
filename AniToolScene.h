#pragma once
#include "Scene.h"

class CAniToolScene : public CScene
{

public: 
	CAniToolScene();
	~CAniToolScene();

public: // Lifecycle
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Exit() override;


private: // Methods
	bool CheckSceneChange();
	void RenderText(HDC hdc);

private: // Variables
	POINT m_ptMousePos;
	wstring m_strFilePath;



	// Test
	CAnimator2D* m_pAnimator;
	CTexture* m_pTex;


};

