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

typedef struct MyMouse
{
	MOUSE_STATE state; // ���� ������ ���콺�� ����
	bool bPrev; // ���� �����ӿ��� ���ȴ���

	// ���� ���� �ε��� ���� �� Ű ��
}Mouse;

typedef struct MyEvent
{
	EVENT_TYPE eEven;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
}Event;



typedef struct tagInfo
{
	float fX, fY; // ����
	float fCX, fCY; // ���� ���� ũ�� (/2 X)
}INFO;


// MapTool



typedef struct MyMapObj
{
	POINT* point1; // Line�� ��� Src, Col�� ��� LeftTpo
	POINT* point2; // Line�� ��� Dst, Col�� ��� RightBottom

	UINT Coltype;

}MAPOBJ;


//
//// Animation
//typedef struct MyAniFrame
//{
//	Vector2 vLT;
//	Vector2 vSlice;
//	Vector2 vOffset = Vector2(0.f, 0.f);
//
//	float fDuration; // �ش� �����ӿ� �ӹ��� �ð� 
//
//}AniFrame;



typedef struct MyRectangle
{
	POINT* point1;
	POINT* point2;
}Box;





typedef struct MyFrame
{
	wstring  State;
	UINT Body;
	
	POINT* point1;
	POINT* point2;
	
	Vector2 Pivot;

	float Duration;

}Frame;


typedef struct MyFrm
{
	/*MyFrm(wstring state, UINT body, POINT pt1, POINT pt2, Vector2 pvt, float duration)
		:State(state),
		 Body(body),
		 point1(pt1),
		 point2(pt2),
		 Pivot(pvt),
		 Duration(duration)
	{

	}*/
	wstring  State;
	UINT Body;

	POINT point1;
	POINT point2;

	Vector2 Pivot;

	float Duration;
}Frm;