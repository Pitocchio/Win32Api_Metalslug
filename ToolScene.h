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

	

	// Enter �Է½�(SceneChange) ��� ���͸� ���� ��������� ���Ͽ� ����


private: // Variables
	POINT m_ptMousePos;


	vector <MAPOBJ*> m_vecMapObj;


	POINT* m_ptTemp1;
	POINT* m_ptTemp2;


	MAPOBJ_TYPE m_curDrawObj;
};

