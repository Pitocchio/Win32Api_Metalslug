#pragma once
#include "Scene.h"

class CAniToolScene2 : public CScene
{

public: 
	CAniToolScene2();
	~CAniToolScene2();

public: // Lifecycle
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Exit() override;



private: // Methods
	void ScrollMouse();
	bool CheckSceneChange();

	void RenderText(HDC hdc);

private: // Variables
	POINT m_ptMousePos;
	wstring m_strFilePath;



	// Test
	CAnimator2D* m_pAnimator;
	CTexture* m_pTex;


};

