#include "stdafx.h"
#include "EventMgr.h"



CEventMgr* CEventMgr::m_pInst = nullptr;

void CEventMgr::Update()
{
	// 이전 SCENE에서 Dead 된 오브젝트들 실제 삭제 수행 
	map<OBJECT_TYPE, list<CObject*>>* tempMapObj = CObjectMgr::GetInst()->GetmapObject();
	for (map<OBJECT_TYPE, list<CObject*>>::iterator iter = tempMapObj->begin(); iter != tempMapObj->end(); ++iter)
	{
		for (list<CObject*>::iterator it = iter->second.begin(); it != iter->second.end(); it != iter->second.end())
		{
			if ((*it)->GetObjectState() == OBJECT_STATE::DEAD)
				it = iter->second.erase(it);
			else
				it++;
		}
	}

	// 이벤트 처리
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}


void CEventMgr::Execute(const Event& event)
{
	switch (event.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{	// lParam : CObject*
		// wParam : OBJECT_TYPE

		CObject* pNewObj = (CObject*)event.lParam;
		OBJECT_TYPE eType = (OBJECT_TYPE)event.wParam;

		if (CObjectMgr::GetInst()->AddObject(eType, pNewObj))
		{
			pNewObj->Init();
		}
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{	
		CObject* pDeadObj = (CObject*)event.lParam;

		// 삭제 예정 오브젝트를 DEAD 상태로 변경
		pDeadObj->SetObjectState(OBJECT_STATE::DEAD);

	}
		break;
	case EVENT_TYPE::CHANGE_SCENE:
	{
		// lParam : Next Scene type
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)event.lParam);  // 진짜 구현(찐 이벤트 처리) 얘

	}
		break;
	}
}

void CEventMgr::AddEvent(const Event& event)
{
	m_vecEvent.push_back(event);
}

void CEventMgr::CreateObject(CObject* obj, OBJECT_TYPE type)
{
	Event evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)obj;
	evn.wParam = (DWORD_PTR)type;

	AddEvent(evn);
}

void CEventMgr::DeleteObject(CObject* obj)
{
	Event evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)obj;

	AddEvent(evn);
}

void CEventMgr::ChangeScene(SCENE_TYPE scene)
{
	Event evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_SCENE;
	evn.lParam = (DWORD_PTR)scene;

	AddEvent(evn);
}

