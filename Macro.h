
#pragma once

#define DEGREETORADIAN(t) ((t) * (float)M_PI / (float)180.0f)
#define RADIANTODEGREE(t) (((float)180.0f / (float)M_PI) * (t))


//#define DISTANCE(x1, x2, y1, y2) (sqrt(pow((x2) - (x1), 2) + pow((y2) - (y1), 2)))


#define DT CTimeMgr::GetInst()->GetDT()
#define fDT CTimeMgr::GetInst()->GetfDT()
#define FPS CTimeMgr::GetInst()->GetFPS()

// 복사생성자 방지
#define NO_COPY(className)	private :\
							className(const className& obj);\
							className* operator = (className* obj)\
							{return nullptr;}

// SingleTone
#define SINGLETONE(ClassName)	\
private:	\
NO_COPY(ClassName);\
ClassName(){}\
~ClassName(){}\
public:\
static ClassName* GetInst()\
{\
	if(m_pInst == NULL)\
		m_pInst = new ClassName;\
	return m_pInst;	\
}\
void DestroyInst()\
{\
	delete m_pInst;\
	m_pInst = nullptr;\
}\
private:\
static ClassName* m_pInst;
