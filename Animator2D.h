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
	//void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2 _vLT, 
	//					Vector2 _vSliceSize, Vector2 _vStep, float fDuration, UINT _iFrameCount);  // �ؽ���, LeftTop, SliceSize, ����, �ִϸ��̼� ��
	CAnimation2D* FindAnimation(const wstring& _strName);
	void PlayAnimation(const wstring& _strName, bool _bRepeat); // �̸�, �ݺ���� ����

	// with Variables
	void SetOwnerObj(CObject* obj);
	CObject* GetOwnerObj() { return m_pOwnerObj; }









public:	
	void SetData(const wstring& _strRelativePath);
	void SetTexture(const wstring& _strKeyName, const wstring& _strFilePath);
	void CreateAnimation();
	CAnimation2D* GetCurAni() { return m_pCurAni; }



private: // Variables
	CObject*						m_pOwnerObj;
	map<wstring, CAnimation2D*>		m_mapAni;	// ��� �ִϸ��̼�
	CAnimation2D*					m_pCurAni;	// ���� ��� ���� �ִϸ��̼� 
	//bool							m_bRepeat;	// �ݺ���� ����

	vector<Frm*>									m_vecFrm;
	vector<wstring>								m_vecStateName;
	map<wstring, CAnimation2D*>					m_mapAnim;


	CTexture*									m_pTex;
};

