#pragma once
#include "Item.h"

class CWeapon : public CItem
{
public: 
	CWeapon();
	~CWeapon();

protected:
	int m_iBulletCount;
};

