#pragma once
#include "Enum.h"


typedef struct MyVector2
{
	float x = 0.0f;
	float y = 0.0f;
	MyVector2() { x = 0.0f; y = 0.0f; }
	MyVector2(float fx, float fy) : x(fx), y(fy) {}

	MyVector2 operator - (MyVector2 rbs) const { return MyVector2({ x - rbs.x, y - rbs.y }); };
	MyVector2 operator + (MyVector2 rbs) const { return MyVector2({ x + rbs.x, y + rbs.y }); };
	MyVector2 operator * (float mul) const { return MyVector2({ x * mul, y * mul }); };
	MyVector2 operator / (float div) const { return MyVector2({ x / div, y / div }); };

	void operator += (MyVector2 rbs) { x += rbs.x; y += rbs.y; };
	void operator -= (MyVector2 rbs) { x -= rbs.x; y -= rbs.y; };
	void operator += (float rbs) { x += rbs; y += rbs; };
	void operator -= (float rbs) { x -= rbs; y -= rbs; };
	void operator *= (float mul) { x *= mul; y *= mul; };
	void operator /= (float div) { x /= div; y /= div; };

		


	MyVector2 operator - () { return MyVector2(-x, -y); };

	float Length() // ���� ����
	{
		if (x == 0.f && y == 0.f)
			return 0.f;
		

		return float(sqrt(pow(x, 2) + pow(y, 2))); 
	}

	void Normalize() 
	{
		if (x == 0.f && y == 0.f)
		{
			x = 0.f;
			y = 0.f;
			return;
		}

		x /= Length(); y /= Length();
	}
	float DotProduct(MyVector2 rbs) { return (x * rbs.x) + (y * rbs.y); };

	/*
	- Distance()
		������ ������ 0���� ���, ��Ÿ��� ������ ����Ͽ� dis(����)�� ���� ���Ѵ�.

	- Normalize()
		������ ����ȭ�� ���͸� ũ��(����)�� ������ ũ�Ⱑ 1�� ���͸� ����� = ���⸸ ���� �ǹǷ� ���⺤��, �������Ͷ�� �Ѵ�.
	*/

}Vector2;

typedef struct MyKey
{
	KEY_STATE state; // ���� ������ Ű�� ����
	bool bPrev; // ���� �����ӿ��� ���ȴ���

	// ���� ���� �ε��� ���� �� Ű ��
}Key;

typedef struct MyEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
}Event;
