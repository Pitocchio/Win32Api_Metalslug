#pragma once
#include "Scene.h"

class CToolScene : public CScene
{
public:
	CToolScene();
	~CToolScene();

public: // Methods
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Exit() override;


public:
	void ScrollMouse();
	bool CheckSceneChange();
	void AddMapObject();

	vector<LINE>* GetvecLine() { return &m_vecLine; }


private: // Variables
	POINT m_pointMousePos;

	vector <LINE> m_vecLine;

	
	POINT* m_ptSrc;
	POINT* m_ptDst;

	bool m_bLinePairPull;
};

