#include "stdafx.h"
#include "ObjectMgr.h"

CObjectMgr* CObjectMgr::m_pInst = nullptr;

void CObjectMgr::Init()
{
	for (map<OBJECT_TYPE, list<CObject*>>::iterator mapiter = m_mapObject.begin(); mapiter != m_mapObject.end(); ++mapiter)
	{
		for (list<CObject*>::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter)
		{
			(*iter)->Init();
		}
	}
}

void CObjectMgr::LateInit()
{
	for (map<OBJECT_TYPE, list<CObject*>>::iterator mapiter = m_mapObject.begin(); mapiter != m_mapObject.end(); ++mapiter)
	{
		for (list<CObject*>::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter)
		{
			(*iter)->LateInit();
		}
	}
}

void CObjectMgr::Update()
{
	for (map<OBJECT_TYPE, list<CObject*>>::iterator mapiter = m_mapObject.begin(); mapiter != m_mapObject.end(); ++mapiter)
	{
		for (list<CObject*>::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter)
		{
			(*iter)->Update();
		}
	}
}

void CObjectMgr::LateUpdate()
{
	for (map<OBJECT_TYPE, list<CObject*>>::iterator mapiter = m_mapObject.begin(); mapiter != m_mapObject.end(); ++mapiter)
	{
		for (list<CObject*>::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter)
		{
			(*iter)->LateUpdate();
		}
	}
}

void CObjectMgr::Render(HDC hdc)
{
	for (map<OBJECT_TYPE, list<CObject*>>::iterator mapiter = m_mapObject.begin(); mapiter != m_mapObject.end(); ++mapiter)
	{
		for (list<CObject*>::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter)
		{
			(*iter)->Render(hdc);
		}
	}
}

void CObjectMgr::Release()
{
	for (map<OBJECT_TYPE, list<CObject*>>::iterator mapiter = m_mapObject.begin(); mapiter != m_mapObject.end(); ++mapiter)
	{
		for (list<CObject*>::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter)
		{
			if((*iter) != nullptr)
				delete *iter;
		}
	}

	m_mapObject.clear();
}

bool CObjectMgr::AddObject(OBJECT_TYPE type, CObject* obj)
{
	if (obj == nullptr)
		return false;

	map<OBJECT_TYPE, list<CObject*>>::iterator iter = m_mapObject.find(type);

	if (iter == m_mapObject.end())
	{
		list<CObject*> listtemp;
		listtemp.push_back(obj);
		m_mapObject.insert({ type, listtemp }); 
		return true;
	}

	iter->second.push_back(obj);
	return true;
}

map<OBJECT_TYPE, list<CObject*>>* CObjectMgr::GetmapObject() 
{
	return &m_mapObject;
}

list<CObject*>* CObjectMgr::GetlistObj(OBJECT_TYPE type) 
{
	map<OBJECT_TYPE, list<CObject*>>::iterator iter = m_mapObject.find(type);

	if (iter == m_mapObject.end())
		return nullptr;

	return &(*iter).second;
}
