#pragma once

class CScene;

class CSceneMgr
{
	SINGLETONE(CSceneMgr)

public: // Lifecycle
	void Init();
	void Update();
	void LateUpdate();
	void Render(HDC hdc);
	void Release();

public: // Methods
	void ChangeScene(SCENE_TYPE scene);
	CScene* GetCurScene() { return m_pCurScene; }

	
	
private: // Variables
	CScene* m_arrScene[(UINT)SCENE_TYPE::TYPEEND_SCENE];  // ¸ðµç ¾À ¸ñ·Ï
	CScene* m_pCurScene; // ÇöÀç ¾À


};

