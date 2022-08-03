#pragma once

class CComponent;
class CTransform2D;
class CBoxCollider2D;
class CCollider2D;

class CObject
{
public:
	CObject();
	virtual ~CObject();

public: // Lifecycle
	virtual void Init();
	virtual void LateInit() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hdc);
	void ComponentRender(HDC hdc); // Render에서 호출

public: // Methods

	bool AddComponent(COMPONENT_TYPE componenttype, CComponent* component);
	map <COMPONENT_TYPE, CComponent*>* GetmapComponent();
	bool IsComponent(COMPONENT_TYPE componenttype);


	void SetObjectType(OBJECT_TYPE type) { m_ObjectType = type; }
	OBJECT_TYPE GetObjectType() const { return m_ObjectType; }

	void SetObjectState(OBJECT_STATE type) { m_ObjectState = type; }
	OBJECT_STATE GetObjectState() const { return m_ObjectState; }

	CBoxCollider2D* GetCollider();

	void SetPos(Vector2 pos);
	Vector2 GetPos();
	void SetSize(Vector2 pos);
	Vector2 GetSize();


	OBJECT_STATE GetObjCurState() { return m_eCurState; }

protected: // Variables
	map<COMPONENT_TYPE, CComponent*> m_mapComponent;
	OBJECT_TYPE m_ObjectType;

	// 이거 안쓰고
	OBJECT_STATE m_ObjectState;

	// 이거 쓴다
	OBJECT_STATE m_eCurState;
	OBJECT_STATE m_ePrevState;

	CTransform2D* m_pTransform;
	CCollider2D* m_pCollider;
	
	

};

