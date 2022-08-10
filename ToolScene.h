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
	void CreateMapObject();

private:
	void AddMapObject(Vector2 vClickPos, MAPOBJ_TYPE type);
	void PrintVector();

	void SaveMapObj(const wstring& _strRelativePath);
	void LoadMapObj(const wstring& _strRelativePath);


	void RenderText(HDC hdc);
	void RenderMapObj(HDC hdc);
	void RenderLiveMapObj(HDC hdc);

	void GetCurDrawObj();

	

	// Enter 입력시(SceneChange) 모든 벡터를 파일 입출력으로 파일에 저장


private: // Variables
	POINT m_ptMousePos;


	vector <MAPOBJ*> m_vecMapObj;


	POINT* m_ptTemp1;
	POINT* m_ptTemp2;


	MAPOBJ_TYPE m_curDrawObj;
};

