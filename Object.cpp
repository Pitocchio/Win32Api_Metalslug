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
	// 실제 플레이어
	Vector2 vTempPos = m_pTransform->GetPos();
	Vector2 vTempSize = m_pTransform->GetSize();

	Rectangle(hdc, int(vTempPos.x - int(vTempSize.x * 0.5f)),
		int(vTempPos.y - int(vTempSize.y * 0.5f)),
		int(vTempPos.x + int(vTempSize.x * 0.5f)),
		int(vTempPos.y + int(vTempSize.y * 0.5f)));


	// 컴포트 렌더러 (충돌체, 좌표, 텍스트 등 디버그 용)
	ComponentRender(hdc);
}

void CObject::ComponentRender(HDC hdc)
{
	// 콜라이더
	if (!m_pCollider->IsActive())
		return;

	Vector2 vTempPos = m_pCollider->GetOffset();
	Vector2 vTempSize = m_pCollider->GetSize();

	PEN_TYPE ePen = PEN_TYPE::GREEN; //
	if (m_pCollider->IsCollision())
		ePen = PEN_TYPE::RED;//


	SelectGDI pen(hdc, ePen);//
	SelectGDI brush(hdc, BRUSH_TYPE::HOLLOW); // 임시객체(지역변수)기 때문에 나갈때 자동으로 소멸자 호출, 그때 다시 셀렉

	Rectangle(hdc, int(vTempPos.x - int(vTempSize.x * 0.5f)),
		int(vTempPos.y - int(vTempSize.y * 0.5f)),
		int(vTempPos.x + int(vTempSize.x * 0.5f)),
		int(vTempPos.y + int(vTempSize.y * 0.5f)));

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



void CObject::SetTransformOwnerObj(CObject* obj)
{
	m_pTransform->SetOwnerObj(this);
}

void CObject::SetTransformPos(Vector2 vec)
{
	m_pTransform->SetPos(vec);
}

Vector2 CObject::GetTransformPos() const
{
	return m_pTransform->GetPos();
}

void CObject::SetTransformSize(Vector2 vec)
{
	m_pTransform->SetSize(vec);
}

Vector2 CObject::GetTransformSize() const
{
	return m_pTransform->GetSize();
}

void CObject::SetTransformAngle(float angle)
{
	m_pTransform->SetAngle(angle);
}

float CObject::GetTransformAngle() const
{
	return m_pTransform->GetAngle();
}

void CObject::SetColliderOwnerObj(CObject* obj)
{
	m_pCollider->SetOwnerObj(this);
}

void CObject::SetColliderOffset(Vector2 vec)
{
	m_pCollider->SetOffset(vec);
}

Vector2 CObject::GetColliderOffset() const
{
	return m_pCollider->GetOffset();
}


bool CObject::GetColliderIscollision() const
{
	return m_pCollider->IsCollision();
}

void CObject::SetColliderRect()
{
	dynamic_cast<CBoxCollider2D*>(m_pCollider)->SetColliderRect();
}

RECT CObject::GetColliderRect() const
{
	return dynamic_cast<CBoxCollider2D*>(m_pCollider)->GetColliderRect();
}

void CObject::SetColliderSize(Vector2 vec)
{
	dynamic_cast<CBoxCollider2D*>(m_pCollider)->SetSize(vec);
}

Vector2 CObject::GetColliderSize() const
{
	return dynamic_cast<CBoxCollider2D*>(m_pCollider)->GetSize();
}
