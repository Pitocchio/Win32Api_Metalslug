#pragma once
#include "Object.h"

class CTexture;

class CPlayer : public CObject
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
	void Update_state(); // 이거 나중에 가상함수 전부 다 바꾸자 (for Animation)
	void Update_animation();





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
	INFO m_tInfo;
	float m_fSpeed;
	float m_fGrav;
	float m_fFall;
	int m_iCheckLine;
	float m_fSlope;

	//Player
	float m_fJumpSpeed;
	bool m_bJump;
	float fJumpStart;

public:
	// OBJ
	INFO& Get_Info() { return m_tInfo; } // 오브젝트 재설계 필요
	void Set_Pos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void Check_Line(int bCheck) { m_iCheckLine = bCheck; }
	void Set_Dist(float fDist) { m_fSlope = fDist; }
	bool IsGround()
	{
		if (m_bJump)
			return true;
		else
			return false;
	}



	Vector2 GetPos() { return Vector2(m_tInfo.fX, m_tInfo.fY); } // 오브젝트 재설계 필요
	INFO GetInfo() { return m_tInfo; }


};

