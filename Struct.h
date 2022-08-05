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

	float Length() // 벡터 길이
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
		벡터의 시점을 0으로 잡고, 피타고라스 정리를 사용하여 dis(빗변)의 값을 구한다.

	- Normalize()
		벡터의 정규화는 벡터를 크기(길이)로 나누어 크기가 1인 벡터를 만든다 = 방향만 갖게 되므로 방향벡터, 단위벡터라고도 한다.
	*/

}Vector2;

typedef struct MyKey
{
	KEY_STATE state; // 현재 프레임 키의 상태
	bool bPrev; // 이전 프레임에서 눌렸는지

	// 벡터 내의 인덱스 값이 곧 키 값
}Key;

typedef struct MyEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
}Event;
