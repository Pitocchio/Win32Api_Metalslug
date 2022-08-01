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

	void CalVelocity(); // ���� �ۿ뿡 ���� �ӵ��� �����

	void SetMass(float mass);
	float GetMass() const;

	float GetSpeed();

	void SetVelocity(Vector2 velocity); // ���� ������ Ư�� �ӵ��� ����
	void AddVelocity(Vector2 velocity);
	Vector2 GetVelocity();
	void SetMaxSpeed(float speed);



private: // Variables
	bool m_bActive;

	Vector2 m_vForce;    // ũ��(��), ����                         (������ ���� ũ�� = ����2�� ���� / ������ ���� �� = �븻������)
	Vector2 m_vAccel;    // ���ӵ�(�ӵ���ȭ�� / �����ð�)            ���ӵ��� ũ�� = �� / ���� 
	Vector2 m_vVelocity; // �ӵ� (���� + ũ��(�ӷ�))          

	float m_fMaxSpeed;   // �ִ� �ӷ� ����

	float m_fMass;       // ����           
	float m_fFricCoeff;  // �������



	// F = M * A;                // �� = ���� X ���ӵ�
	// V += A * DT; = ����ӵ� (�ӵ� = ���ӵ��� ����) 


	// Update���� ��� ���⿡�� ���� ���� ���ؼ� �ϳ��� �� ���͸� ���� ����
	// LateUpdate���� �������� �ʱ�ȭ


};

