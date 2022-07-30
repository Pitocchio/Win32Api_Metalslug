#pragma once
#include "Object.h"

class CMoveobj : public CObject
{
public:
	CMoveobj();
	~CMoveobj();



public: // Methods
	virtual void Move() = 0;


protected: // Variables
	Vector2 m_vLook;
	float m_fSpeed;


};

