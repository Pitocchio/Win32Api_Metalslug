#pragma once
#include "Object.h"

class CItem : public CObject
{

public:
	CItem();
	~CItem();

protected:
	int iRemainingtime;
};

