#include "stdafx.h"
#include "Object.h"
CObject::CObject()
	:m_pTransform(nullptr)
	,m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	for (map<COMPONENT_TYPE, CComponent*>::iterator iter = m_mapComponent.begin(); iter != m_mapComponent.end(); ++iter)
	{
		delete (*iter).second;
	}
}

void CObject::Init()
{
	m_pTransform = new CTransform2D();
	AddComponent(COMPONENT_TYPE::TRANSFORM2D, m_pTransform);

	m_pCollider = new CBoxCollider2D();
	AddComponent(COMPONENT_TYPE::BOXCOLLIDER2D, m_pCollider);
}

void CObject::Render(HDC hdc)
{
	// ���� �÷��̾�
	Vector2 vTempPos = m_pTransform->GetPos();
	Vector2 vTempSize = m_pTransform->GetSize();

	Rectangle(hdc, int(vTempPos.x - int(vTempSize.x * 0.5f)),
		int(vTempPos.y - int(vTempSize.y * 0.5f)),
		int(vTempPos.x + int(vTempSize.x * 0.5f)),
		int(vTempPos.y + int(vTempSize.y * 0.5f)));


	// ����Ʈ ������ (�浹ü, ��ǥ, �ؽ�Ʈ �� ����� ��)
	ComponentRender(hdc);
}

void CObject::ComponentRender(HDC hdc)
{
	// Collider
	if (IsComponent(COMPONENT_TYPE::BOXCOLLIDER2D))
	{
		if (!m_pCollider->IsActive())
			return;

		Vector2 vTempPos = m_pCollider->GetOffset();
		Vector2 vTempSize = m_pCollider->GetSize();

		PEN_TYPE ePen = PEN_TYPE::GREEN; 
		if (m_pCollider->IsCollision())
			ePen = PEN_TYPE::RED;

		SelectGDI pen(hdc, ePen);
		SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW); // �ӽð�ü(��������)�� ������ ������ �ڵ����� �Ҹ��� ȣ��, �׶� �ٽ� ����

		Rectangle(hdc, int(vTempPos.x - int(vTempSize.x * 0.5f)), 
			int(vTempPos.y - int(vTempSize.y * 0.5f)),
			int(vTempPos.x + int(vTempSize.x * 0.5f)),
			int(vTempPos.y + int(vTempSize.y * 0.5f)));
	}
}	


bool CObject::AddComponent(COMPONENT_TYPE componenttype, CComponent* component)
{
	if (m_mapComponent.find(componenttype) != m_mapComponent.end())
	{
		delete component;
		component = nullptr;

		return false;
	}
	else
	{
		m_mapComponent.insert({ componenttype, component });
		return true;
	}

	return false;
}

map<COMPONENT_TYPE, CComponent*>* CObject::GetmapComponent()
{
	return &m_mapComponent;
}

bool CObject::IsComponent(COMPONENT_TYPE componenttype)
{
	if (m_mapComponent.find(componenttype) != m_mapComponent.end())
		return true;
	else
		return false;
}
