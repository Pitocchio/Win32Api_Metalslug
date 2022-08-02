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
	Vector2 m_vLookAt; // 실제 카메라 자신이 보고 있는 곳 = 화면의 중심 

	
	CObject* m_TargetObj; // 카메라가 타겟으로 삼는 오브젝트

};
