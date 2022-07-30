#pragma once
#include "Attackobj.h"

class CEnemy : public CAttackobj
{
public:
	CEnemy();
	~CEnemy();

protected:
	OBJECT_TYPE m_Item;
	int iScorePoint;
};

