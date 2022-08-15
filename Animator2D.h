#pragma once
#include "Component.h"

// Animator�� ������Ʈ�μ� Animation�� �����ϰ� �����ϸ�, ������Ʈ�� ��Ȳ�� ���� �˸��� �ִϸ��̼��� ���

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
	void CreateAnimation(CTexture*, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vStep, UINT _iFrameCount);  // �ؽ���, LeftTop, SliceSize
	void FindAnimation();
	void PlayAnimation();




	// with Variables
	void SetOwnerObj(CObject* obj);


private: // Variables
	CObject*						m_pOwnerObj;
	map<wstring, CAnimation2D*>		m_mapAni;	// ��� �ִϸ��̼�
	CAnimation2D*					m_pCurAni;	// ���� ��� ���� �ִϸ��̼� 



	// 497(35.5) X 43
	// ����, ����


};

