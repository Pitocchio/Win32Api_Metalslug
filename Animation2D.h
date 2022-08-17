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
	AniFrame& GetFrame(int _iFrameIdx) { return m_vecFrame[_iFrameIdx]; }

	void Create(CTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vStep, float fDuration, UINT _iFrameCount);
	bool IsFinish() { return m_bFinish; }

	int GetMaxFrame() { return (int)m_vecFrame.size(); }


	// ========== Test ======== //




private: // Variables
	wstring				m_strName;
	CAnimator2D*		m_pAnimator;
	CTexture*			m_pTex;
	vector<AniFrame>	m_vecFrame;
	int					m_iCurFrame; // 여러 프레임 중 지금 몇번째 프레임이 나와야하냐
	float				m_fAccTime;  // 누적시간 (프레임 갱신용)
	bool				m_bFinish;   // 애니메이션이 끝났는지 체크


	// ========== Test ======== // (DOWN의 경우 상하체 분리가 안되어 있으므로 상체만 사용한다)
	// 상체
	CTexture*			m_pTexTop;		// 상체 텍스처
	vector<AniFrame>	m_vecFrameTop;  // 상체 프레임
	int					m_iIdxTop;		// 상체 인덱스

	// 하체
	vector<AniFrame>	m_vecFrameBot;  // 하체 프레임
	CTexture*			m_pTexBot;		// 하체 텍스처
	int					m_iIdxBot;		// 하체 인덱스

};

