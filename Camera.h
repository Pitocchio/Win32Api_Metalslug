#pragma once

class CObject;

class CCamera
{
	SINGLETONE(CCamera)

public: // Lifecycle
	void Init();
	void Update();
	void Release();

public: // Methods
	void SetLookAt(Vector2 vec); // 카메라 이동을 원할 시 호출
	void SetTargetObj(CObject* obj) { m_pTargetObj = obj; }

	Vector2 GetLookAt() { return m_vCurLookAt; }
	Vector2 GetRenderPos(Vector2 objpos) { return objpos - m_vDiff; }
	POINT GetRenderPos(POINT pos) { return POINT({ LONG(pos.x - m_vDiff.x), LONG(pos.y - m_vDiff.y) }); }
	Vector2 GetRealPos(Vector2 RenderPos) { return RenderPos + m_vDiff; }
	Vector2 GetDiff() { return m_vDiff; }

private: // Methods 
	void CalDiff(); // 해상도 중심 위치와 카메라 LookAt 좌표간의 차이 값 계산
	
private:
	Vector2 m_vLookAt; // 실제 카메라 자신이 보고 있는 곳 = 화면의 중심 
	Vector2 m_vCurLookAt; // 이전 위치와 현재 위치의 보정위치
	Vector2 m_vPreLookAt; // 카메라가 보는 이전 프레임 위치
	CObject* m_pTargetObj; // 카메라가 타겟으로 삼는 오브젝트
	Vector2 m_vDiff; // 해상도 중심 위치와 카메라 LookAt간의 차이 값

	float m_fTime; // 타겟을 따라가는 데 걸리는 시간
	float m_fSpeed; // 타겟을 따라가는 속도
	float m_fAccTime; // 누적 시간
};





/*
카메라 LookAt 변경법 (어소트락 카메라 2강)

Set할 Pos를 GetRealPos를 통해 실제 좌표로 바꾼 뒤 그걸 넘겨준다

Vector2 Pos = CCamera::GetInst()->GetRealPos(내가 지정할 좌표)
CCamera::GetInst()->SetLookAt(Pos)
*/