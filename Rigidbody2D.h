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
	void SetVelocity(Vector2 velocity); // ���� ������ Ư�� �ӵ��� ����
	void CalVelocity(); // ���� �ӵ��� ��� (������ �̵��� �־� �ٽ����� �κ�)
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

	Vector2 m_vForce;    // ũ��(��), ����                         (������ ���� ũ�� = ����2�� ���� / ������ ���� �� = �븻������)
	Vector2 m_vAccel;    // ���ӵ�(�ӵ���ȭ�� / �����ð�)            ���ӵ��� ũ�� = �� / ���� 
	Vector2 m_vAccelA;   // �߰� ���ӵ� (for �߷�)
	Vector2 m_vVelocity; // �ӵ� (���� + ũ��(�ӷ�))          

	float m_fMaxSpeed;   // �ִ� �ӷ� ����

	float m_fMass;       // ����           
	float m_fFricCoeff;  // �������

	bool m_bGround;

	// F = M * A;                // �� = ���� X ���ӵ�
	// V += A * DT; = ����ӵ� (�ӵ� = ���ӵ��� ����) 


	// Update���� ��� ���⿡�� ���� ���� ���ؼ� �ϳ��� �� ���͸� ���� ����
	// LateUpdate���� �������� �ʱ�ȭ


};

