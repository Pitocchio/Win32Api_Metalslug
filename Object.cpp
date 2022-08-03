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
		if ((*iter).second == nullptr)
			continue;

		delete (*iter).second;
	}
}

void CObject::Init()
{
	m_pTransform = new CTransform2D();
	AddComponent(COMPONENT_TYPE::TRANSFORM2D, m_pTransform);

	
}

void CObject::Render(HDC hdc)
{
	//실제 플레이어


	Vector2 vPos = m_pTransform->GetPos();
	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	Rectangle(hdc, int(vRenderPos.x - int(vRenderPos.x * 0.5f)),
		int(vRenderPos.y - int(vRenderPos.y * 0.5f)),
		int(vRenderPos.x + int(vRenderPos.x * 0.5f)),
		int(vRenderPos.y + int(vRenderPos.y * 0.5f)));


	//// 컴포트 렌더러 (충돌체, 좌표, 텍스트 등 디버그 용)
	//ComponentRender(hdc);
}

void CObject::ComponentRender(HDC hdc)
{
	// Collider
	if (IsComponent(COMPONENT_TYPE::BOXCOLLIDER2D))
	{
		if (!m_pCollider->IsActive())
			return;

		Vector2 vTempPos = m_pCollider->GetOffset();
		Vector2 vTempSize = dynamic_cast<CBoxCollider2D*>(m_pCollider)->GetSize();

		PEN_TYPE ePen = PEN_TYPE::GREEN; 
		if (m_pCollider->IsCollision())
			ePen = PEN_TYPE::RED;

		SelectGDI pen(hdc, ePen);
		SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW); // 임시객체(지역변수)기 때문에 나갈때 자동으로 소멸자 호출, 그때 다시 셀렉

		Rectangle(hdc, int(vTempPos.x - int(vTempSize.x * 0.5f)), 
			int(vTempPos.y - int(vTempSize.y * 0.5f)),
			int(vTempPos.x + int(vTempSize.x * 0.5f)),
			int(vTempPos.y + int(vTempSize.y * 0.5f)));
	}

	if (IsComponent(COMPONENT_TYPE::LINECOLLIDER2D))
	{
		if (!m_pCollider->IsActive())
			return;

		Vector2 vStart = dynamic_cast<CLineCollider2D*>(m_pCollider)->GetStartPoint();
		Vector2 vEnd = dynamic_cast<CLineCollider2D*>(m_pCollider)->GetEndPoint();

		PEN_TYPE ePen = PEN_TYPE::BLUE;
		SelectGDI pen(hdc, ePen);


		MoveToEx(hdc, int(vStart.x), int(vStart.y), NULL);
		LineTo(hdc, int(vEnd.x), int(vEnd.y));


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

CBoxCollider2D* CObject::GetCollider()
{
	map<COMPONENT_TYPE, CComponent*>::iterator iter;
	iter = m_mapComponent.find(COMPONENT_TYPE::BOXCOLLIDER2D);

	if (iter != m_mapComponent.end())
	{
		return dynamic_cast<CBoxCollider2D*>((*iter).second);
	}
	else
	{
		return nullptr;
	}

}

void CObject::SetPos(Vector2 pos)
{
	map<COMPONENT_TYPE, CComponent*>::iterator iter;
	iter = m_mapComponent.find(COMPONENT_TYPE::TRANSFORM2D);

	if (iter == m_mapComponent.end())
		return;

	dynamic_cast<CTransform2D*>((*iter).second)->SetPos(pos);
	
}

Vector2 CObject::GetPos() 
{
	map<COMPONENT_TYPE, CComponent*>::iterator iter;
	iter = m_mapComponent.find(COMPONENT_TYPE::TRANSFORM2D);

	/*if (iter == m_mapComponent.end())
		return;*/

	return dynamic_cast<CTransform2D*>((*iter).second)->GetPos();
}

void CObject::SetSize(Vector2 pos)
{
	map<COMPONENT_TYPE, CComponent*>::iterator iter;
	iter = m_mapComponent.find(COMPONENT_TYPE::TRANSFORM2D);

	if (iter == m_mapComponent.end())
		return;

	dynamic_cast<CTransform2D*>((*iter).second)->SetSize(pos);
}

Vector2 CObject::GetSize()
{
	map<COMPONENT_TYPE, CComponent*>::iterator iter;
	iter = m_mapComponent.find(COMPONENT_TYPE::TRANSFORM2D);

	/*if (iter == m_mapComponent.end())
		return;*/

	return dynamic_cast<CTransform2D*>((*iter).second)->GetSize();
}
