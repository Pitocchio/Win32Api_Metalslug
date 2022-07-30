#pragma once

class CObject;

class CObjectMgr
{
	SINGLETONE(CObjectMgr)

public: // Lifecycle
	void Init();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render(HDC hdc);
	void Release();

public: // Methods
	bool AddObject(OBJECT_TYPE type, CObject* obj);
	map<OBJECT_TYPE, list<CObject*>>* GetmapObject();
	list<CObject*>* GetlistObj(OBJECT_TYPE type);

	


private: // Variables
	map<OBJECT_TYPE, list<CObject*>> m_mapObject;
};
