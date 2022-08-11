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


private:	
	void ScrollMouse();
	bool CheckSceneChange();


	// Object Methods
	void CreateMapObject();
	void AddMapObject(Vector2 vClickPos, OBJECT_TYPE type);

	// File Methods
	void SaveMapObj(const wstring& _strRelativePath);
	void LoadMapObj(const wstring& _strRelativePath);

	// Map Tool Window Render Methods
	void RenderText(HDC hdc); // 
	void RenderMapObj(HDC hdc);
	void RenderLiveMapObj(HDC hdc);
	void GetCurDrawObj();
	
	// Console Data Print Methods
	void PrintVector();



private: // Variables
	POINT m_ptMousePos;

	vector <MAPOBJ*> m_vecMapObj;

	POINT* m_ptTemp1;
	POINT* m_ptTemp2;

	OBJECT_TYPE m_curDrawObj;

	wstring m_strFilePath;
};

