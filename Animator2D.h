#pragma once
#include "Component.h"

// Animator은 컴포넌트로서 Animation을 보유하고 관리하며, 오브젝트의 상황에 따라 알맞은 애니메이션을 재생

class CAnimation2D;
class CTexture;

class CAnimator2D : public CComponent
{
public: CAnimator2D();
	  ~CAnimator2D();

public: // Lifecycle
	virtual void Init() override;
	virtual void Update() override; // Animator Update() -> Current Animation Update()
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;

public: // Methods


	CAnimation2D* FindAnimation(const wstring& _strName);

	void SetCurAnimation(const wstring& _strName);
	void PlayFirstAnimation()
	{
		m_pCurAni = m_mapAnim.begin()->second;
	}

	void SetOwnerObj(CObject* obj);

	CObject* GetOwnerObj() 
	{
		if (m_pOwnerObj != nullptr)
			return m_pOwnerObj;
		else
			return nullptr; 
	}


public:	
	void SetData(const wstring& _strRelativePath);
	void SetTexture(const wstring& _strKeyName, const wstring& _strFilePath);
	void CreateAnimation();
	CAnimation2D* GetCurAni() { return m_pCurAni; }

	void Save(const wstring& _strRelativePath); // for ANITOOL SCENE 2


private: // Variables
	CObject*						m_pOwnerObj;
	CAnimation2D*					m_pCurAni;	
	vector<Frm*>					m_vecFrm;
	vector<wstring>					m_vecStateName;
	map<wstring, CAnimation2D*>		m_mapAnim;
	CTexture*									m_pTex;
};

