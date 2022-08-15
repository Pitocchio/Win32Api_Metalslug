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
	//bool m_bJump;
	float m_fGravitytime;

	bool m_bTest;

	Vector2 m_vLook;






private:
	// OBJ
	bool m_bInit;
	INFO m_tInfo;
	RECT m_tRect;
	float m_fSpeed;
	bool m_bIsDead;
	float m_fAngle;
	float m_fGrav;
	float m_fFall;
	float CheckSpeed;
	int m_iCheckLine;
	float m_fSlope;

	//Player
	float m_fJumpSpeed;
	bool m_bJump;
	float fJumpStart;

public:
	// OBJ
	INFO& Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }
	void Set_Dead() { m_bIsDead = true; }
	void Set_Pos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void Check_Line(int bCheck) { m_iCheckLine = bCheck; }
	void Set_Dist(float fDist) { m_fSlope = fDist; }
	void UpdateRect()
	{
		// 왼쪽 : 중점 - (가로 크기 / 2);
		m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX / 2));
		m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX / 2));
		m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY / 2));
		m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY / 2));
	}


	Vector2 GetPOS_Test() { return Vector2(m_tInfo.fX, m_tInfo.fY); }



	INFO GetInfo() { return m_tInfo; }


};

