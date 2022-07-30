#pragma once
#include "Moveobj.h"

class CAttackobj : public CMoveobj
{
public:
	CAttackobj();
	~CAttackobj();

public: // Methods
	virtual void Attack() = 0;

protected: // Variables
	ATTACKOBJ_WEAPON_TYPE m_curWeapon;
	int m_iLife;
};

