#pragma once
#include "Attackobj.h"

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

public: // Methods
	virtual void Move() override; // ������Ʈ ����� �ٲپ����
	void Update_state(); // �̰� ���߿� �����Լ� ���� �� �ٲ��� (for Animation)
	void Update_animation();

	virtual void Attack() override;


private: // Variables
	int m_iBulletCount;
	int m_iGrenadeCount;
};

