#pragma once
class CAnimation2D
{
public:
	CAnimation2D();
	~CAnimation2D();

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

private:

};

