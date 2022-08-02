#pragma once
#include "Mapcollider.h"

class CGroundCollider :  public CMapcollider
{
public:
	CGroundCollider();
	~CGroundCollider();

public: // Lifecycle
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public: // Methods
	Vector2 GetStartPoint() const { return m_vStartPoint; } 
	Vector2 GetEndPoint() const { return m_vEndPoint; }

private: // Variables
	
	Vector2 m_vStartPoint; // == transform Position
	Vector2 m_vEndPoint;
};

