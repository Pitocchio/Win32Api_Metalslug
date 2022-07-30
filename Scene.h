#pragma once

class CObject;

class CScene
{
public:
	CScene();
	virtual ~CScene();

public: // Methods
	virtual void Enter() = 0; // 진입시 (Init)
	virtual void Exit() = 0; // 나갈시 (Release)

	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC hdc);


	void SetSceneType(const SCENE_TYPE type) { m_SceneType = type; }
	const SCENE_TYPE GetSceneType() { return m_SceneType; }

protected: // Variables

	SCENE_TYPE m_SceneType;

};
