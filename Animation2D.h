#pragma once

class CAnimator2D;

class CAnimation2D
{
public:
	CAnimation2D();
	~CAnimation2D();

public: // Lifecycle
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

public: // Methods
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	void SetOwnerObj(CAnimator2D* _pAni){ m_pAnimator = _pAni; }
	void SetFrame(int _iFrameIdx);
	//AniFrame& GetFrame(int _iFrameIdx) { return m_vecFrame[_iFrameIdx]; }

	void Create(CTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vStep, float fDuration, UINT _iFrameCount);
	bool IsFinish() { return m_bFinish; }

	//int GetMaxFrame() { return (int)m_vecFrame.size(); }






private: // Variables
	wstring				m_strName;
	CAnimator2D*		m_pAnimator;
	CTexture*			m_pTex; // 굳이 이걸 애니메이션이 들고 있어야 하나? 
	//vector<AniFrame>	m_vecFrame;
	int					m_iCurFrame; // 여러 프레임 중 지금 몇번째 프레임이 나와야하냐
	float				m_fAccTime;  // 누적시간 (프레임 갱신용)
	bool				m_bFinish;   // 애니메이션이 끝났는지 체크







	// ========== Test ======== // (DOWN의 경우 상하체 분리가 안되어 있으므로 상체만 사용한다)
	
private:
	// 텍스쳐는 Animator에 있는 거 상속받아서 사용한다
	 
	// 상체
	vector<Frm*>		m_vecFrame_T;  // 원본 전체 텍스처에서 잘라내야 할 위치 값과 플레이 타임을 갖고 있음
	int					m_iCurFrame_T;
	float				m_fAccTime_T;
	bool				m_bFinish_T;

	// 하체
	vector<Frm*>		m_vecFrame_B;
	int					m_iCurFrame_B;
	float				m_fAccTime_B;
	bool				m_bFinish_B;



public: 
	void Create_Test(wstring _strState, vector<Frm*>* _listFrm);

};

