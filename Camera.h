#pragma once

class CObject;

class CCamera
{
	SINGLETONE(CCamera)

public:
	void Update();

	void SetLookAt(Vector2 vec) { m_vLookAt = vec; }
	void SetTargetObj(CObject* obj) { m_TargetObj = obj; }

private:
	void CalDiff();
	
private:
	Vector2 m_vLookAt; // ���� ī�޶� �ڽ��� ���� �ִ� �� = ȭ���� �߽� 

	
	CObject* m_TargetObj; // ī�޶� Ÿ������ ��� ������Ʈ

};
