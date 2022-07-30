#pragma once

class CComponent
{
public: 
	CComponent();
	~CComponent();

	// 디버그시 확인용 ex 콜라이더 색깔, 라인 색깔, 현재 좌표 출력 등 
public:
	virtual void Init() = 0; 
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hdc) = 0;
};

