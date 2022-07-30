#pragma once

class CComponent;
class CTransform2D;
class CBoxCollider2D;

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



	void SetObjectType(OBJECT_TYPE type) { m_ObjectType = type; }
	OBJECT_TYPE GetObjectType() const { return m_ObjectType; }

	void SetObjectState(OBJECT_STATE type) { m_ObjectState = type; }
	OBJECT_STATE GetObjectState() const { return m_ObjectState; }



	// Transform
	void SetTransformOwnerObj(CObject* obj);

	CTransform2D* GetTransform() { return m_pTransform; }
	
	void SetTransformPos(Vector2 vec);
	Vector2 GetTransformPos() const;

	void SetTransformSize(Vector2 vec);
	Vector2 GetTransformSize() const;

	void SetTransformAngle(float angle);
	float GetTransformAngle() const;

	// Collider - Parents

	void SetColliderOwnerObj(CObject* obj);

	CBoxCollider2D* GetCollider() { return m_pCollider; }

	void SetColliderOffset(Vector2 vec);
	Vector2 GetColliderOffset() const;

	bool GetColliderIscollision() const;

	// Collider - Children
	void SetColliderRect();
	RECT GetColliderRect() const;

	void SetColliderSize(Vector2 vec);
	Vector2 GetColliderSize() const;



	// Collision



protected: // Variables
	map<COMPONENT_TYPE, CComponent*> m_mapComponent;
	OBJECT_TYPE m_ObjectType;
	OBJECT_STATE m_ObjectState;

	CTransform2D* m_pTransform;
	CBoxCollider2D* m_pCollider;
	
	

};

