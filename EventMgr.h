#pragma once

class CEventMgr
{
	SINGLETONE(CEventMgr)

public:
	void Update();

public:
	void AddEvent(const Event& event);
	void Execute(const Event& event);

	void CreateObject(CObject* obj, OBJECT_TYPE type);
	void DeleteObject(CObject* obj);
	void ChangeScene(SCENE_TYPE scene);

private:
	vector<Event> m_vecEvent; // 이벤트 목록 저장



};

 