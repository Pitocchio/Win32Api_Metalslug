#pragma once
#include "Attackobj.h"

class CTexture;

class CPlayer : public CAttackobj
{
public:
	CPlayer();
	~CPlayer();


public: // Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	//  temp
	virtual void Render(HDC hdc) override;

public: // Methods
	virtual void Move() override; // 업데이트 무브로 바꾸어야함
	void Update_state(); // 이거 나중에 가상함수 전부 다 바꾸자 (for Animation)
	void Update_animation();

	virtual void Attack() override;


private: // Variables
	int m_iBulletCount;
	int m_iGrenadeCount;



//temp
private:
	CTexture* m_pTex;

	bool m_bGravity;


	Vector2 m_CurPointCollider;
	Vector2 m_PrevPointCollider;
	bool m_bCurCollision;
	bool m_bPrevCollision;

	bool m_bGround;
	float m_fGravitytime;

};

