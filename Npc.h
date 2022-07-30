#pragma once
#include "Moveobj.h"

class CNpc : public CMoveobj
{
public:
	CNpc();
	~CNpc();

protected:
	OBJECT_TYPE m_Item;
};

