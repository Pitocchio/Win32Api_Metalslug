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
	virtual void Move() override; // ������Ʈ ����� �ٲپ����
	void Update_state(); // �̰� ���߿� �����Լ� ���� �� �ٲ��� (for Animation)
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

