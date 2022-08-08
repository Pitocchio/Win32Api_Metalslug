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
	void SetLookAt(Vector2 vec); // ī�޶� �̵��� ���� �� ȣ��
	void SetTargetObj(CObject* obj) { m_pTargetObj = obj; }

	Vector2 GetLookAt() { return m_vCurLookAt; }
	Vector2 GetRenderPos(Vector2 objpos) { return objpos - m_vDiff; }
	POINT GetRenderPos(POINT pos) { return POINT({ LONG(pos.x - m_vDiff.x), LONG(pos.y - m_vDiff.y) }); }
	Vector2 GetRealPos(Vector2 RenderPos) { return RenderPos + m_vDiff; }
	Vector2 GetDiff() { return m_vDiff; }

private: // Methods 
	void CalDiff(); // �ػ� �߽� ��ġ�� ī�޶� LookAt ��ǥ���� ���� �� ���
	
private:
	Vector2 m_vLookAt; // ���� ī�޶� �ڽ��� ���� �ִ� �� = ȭ���� �߽� 
	Vector2 m_vCurLookAt; // ���� ��ġ�� ���� ��ġ�� ������ġ
	Vector2 m_vPreLookAt; // ī�޶� ���� ���� ������ ��ġ
	CObject* m_pTargetObj; // ī�޶� Ÿ������ ��� ������Ʈ
	Vector2 m_vDiff; // �ػ� �߽� ��ġ�� ī�޶� LookAt���� ���� ��

	float m_fTime; // Ÿ���� ���󰡴� �� �ɸ��� �ð�
	float m_fSpeed; // Ÿ���� ���󰡴� �ӵ�
	float m_fAccTime; // ���� �ð�
};





/*
ī�޶� LookAt ����� (���Ʈ�� ī�޶� 2��)

Set�� Pos�� GetRealPos�� ���� ���� ��ǥ�� �ٲ� �� �װ� �Ѱ��ش�

Vector2 Pos = CCamera::GetInst()->GetRealPos(���� ������ ��ǥ)
CCamera::GetInst()->SetLookAt(Pos)
*/