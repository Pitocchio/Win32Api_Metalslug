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

	// Animation
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2 _vLT, 
						Vector2 _vSliceSize, Vector2 _vStep, float fDuration, UINT _iFrameCount);  // 텍스쳐, LeftTop, SliceSize, 간격, 애니메이션 수
	CAnimation2D* FindAnimation(const wstring& _strName);
	void PlayAnimation(const wstring& _strName, bool _bRepeat); // 이름, 반복재생 여부

	// with Variables
	void SetOwnerObj(CObject* obj);
	CObject* GetOwnerObj() { return m_pOwnerObj; }










private: // Variables
	CObject*						m_pOwnerObj;
	map<wstring, CAnimation2D*>		m_mapAni;	// 모든 애니메이션
	CAnimation2D*					m_pCurAni;	// 현재 재생 중인 애니메이션 
	bool							m_bRepeat;	// 반복재생 여부

	// 497(35.5) X 43
	// 가로, 세로



	// ====================== Test ====================== // 

protected:
	CTexture*									m_pTex;
	vector<Frm*>									m_vecFrm;
	map<wstring, CAnimation2D*>					m_mapAnim;
	vector<wstring>								m_vecStateName;

public:	
	void SetData(const wstring& _strRelativePath);
	void SetTexture(const wstring& _strKeyName, const wstring& _strFilePath);
	void CreateAnimation_Test();

};

