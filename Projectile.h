#pragma once
#include "Moveobj.h"

class CProjectile : public CMoveobj
{
public: 
	CProjectile();
	~CProjectile();



public: // Methods
	
	void SetDamage(int value);
	int GetDamage() const;

protected:
	int m_iDamage;

};

