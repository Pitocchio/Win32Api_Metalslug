#pragma once
#include "Scene.h"

class CAniToolScene1 : public CScene
{

public:
	CAniToolScene1();
	~CAniToolScene1();

public: 
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Exit() override;


public: 
	void SetTexture(const wstring& _strKeyName, const wstring& _strFilePath);

	void ScrollMouse();
	bool CheckSceneChange();

	void Render_vecBox(HDC hdc);
	void Render_CurBox(HDC hdc);
	void RenderText(HDC hdc);


	

private: // Variables
	POINT m_ptMousePos;
	wstring m_strFilePath;

	vector <Box*> m_vecBox;

	POINT* m_ptTemp1;
	POINT* m_ptTemp2;

	CTexture* m_pTex;



	// Test

private:
	vector<Frame*> m_vecFrame; 
	BODY_TYPE m_Curbody;
	wstring m_wstrCurState;

	vector<wstring>  m_vecState;

public: 
	void AddvecFrame();
	void SaveMapFrame(const wstring& _strRelativePath);


	void SetCurbody(BODY_TYPE _bodytype) { m_Curbody = _bodytype; }
	void SetCurState(const wstring& _strCurstate) { m_wstrCurState = _strCurstate; }
	void PushbackState(const wstring& _strCurstate) { m_vecState.push_back(_strCurstate); }
	void Print_vecFrame();


	
};

