#pragma once
#include "Component.h"

class CRigidbody2D : public CComponent
{
public:
	CRigidbody2D();
	~CRigidbody2D();

public: // Lifecycle
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;


public: // Methods
	void InitForce();
	void AddForce(Vector2 force);

	Vector2 GetVelocity();
	void SetVelocity(Vector2 velocity); // 내가 강제로 특정 속도를 지정
	void CalVelocity(); // 현재 속도를 계산 (물리적 이동에 있어 핵심적인 부분)
	void AddVelocity(Vector2 velocity);

	void SetMass(float mass);
	float GetMass() const;


	float GetSpeed();
	void SetMaxSpeed(float speed);


	void ApplyGravity();
	void SetGround(bool b);
	bool IsGround();

	void InitAccel();
	void InitVelocity() { m_vVelocity = Vector2(0.f, 0.f); }

	void InitAccelAlpha();
	void SetAccelAlpha(Vector2 accel);

private: // Variables
	bool m_bActive;

	Vector2 m_vForce;    // 크기(힘), 방향                         (순수한 힘의 크기 = 벡터2의 길이 / 순수한 방향 값 = 노말라이즈)
	Vector2 m_vAccel;    // 가속도(속도변화량 / 단위시간)            가속도의 크기 = 힘 / 질량 
	Vector2 m_vAccelA;   // 추가 가속도 (for 중력)
	Vector2 m_vVelocity; // 속도 (방향 + 크기(속력))          

	float m_fMaxSpeed;   // 최대 속력 제한

	float m_fMass;       // 질량           
	float m_fFricCoeff;  // 마찰계수

	bool m_bGround;

	// F = M * A;                // 힘 = 질량 X 가속도
	// V += A * DT; = 현재속도 (속도 = 가속도의 누적) 


	// Update에서 모든 방향에서 오는 힘을 더해서 하나의 힘 벡터를 만든 다음
	// LateUpdate에서 쓴다음에 초기화


};

