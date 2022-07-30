#pragma once

class CComponent
{
public: 
	CComponent();
	~CComponent();

	// ����׽� Ȯ�ο� ex �ݶ��̴� ����, ���� ����, ���� ��ǥ ��� �� 
public:
	virtual void Init() = 0; 
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hdc) = 0;
};

