#pragma once
#include "Collider2D.h"

class CLineCollider2D : public CCollider2D
{

public:
	CLineCollider2D();
	~CLineCollider2D();

public: // Lifecycle
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;


public: // Methods
	void SetStartPoint(Vector2 vec) { m_vStartPoint = vec; }
	void SetEndPoint(Vector2 vec) { m_vEndPoint = vec; }
	Vector2 GetStartPoint() const { return m_vStartPoint; }
	Vector2 GetEndPoint() const { return m_vEndPoint; }
	

private:
	Vector2 m_vStartPoint;
	Vector2 m_vEndPoint;
	
};

