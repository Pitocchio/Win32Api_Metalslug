#pragma once
#include "Scene.h"

class CAniToolScene1 : public CScene
{

public:
	CAniToolScene1();
	~CAniToolScene1();

public: // Lifecycle
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Exit() override;


public: // from Main;
	void SetTexture(const wstring& _strFilePath);



	void ScrollMouse();
	bool CheckSceneChange();
	void AddvecBox();
	void Print_vecBox();

	void Render_vecBox(HDC hdc);
	void Render_CurBox(HDC hdc);
	void RenderText(HDC hdc);


	void SaveMapBox(const wstring& _strRelativePath);
	

private: // Variables
	POINT m_ptMousePos;
	wstring m_strFilePath;

	vector <Box*> m_vecBox;

	POINT* m_ptTemp1;
	POINT* m_ptTemp2;

	CTexture* m_pTex;

	
};

