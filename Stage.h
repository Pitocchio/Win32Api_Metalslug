#pragma once
#include "Object.h"

class CStage : public CObject
{
public:
	CStage();
	~CStage();
	CStage(OBJECT_TYPE objtype);

public:
	virtual void Init() override;
	virtual void LateInit() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;



private:
	CTexture* m_pTex;


};

