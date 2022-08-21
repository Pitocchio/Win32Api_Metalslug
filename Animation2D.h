#pragma once


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
	void RenderText(HDC hdc);


	void Create(wstring _strState, vector<Frm*>* _listFrm);
	bool IsFinish() { return m_bTopFinish; }
	void SetTexture(CTexture* _Tex) { m_pTex = _Tex; }


	void SetCurBody()
	{
		if (m_iCurBody == 1)
			m_iCurBody = 0;
		else
			m_iCurBody = 1;
	}
	bool IsRepeat() { return m_bRepeat; }
	void SetCurEditFrm();
	void SetFrmTime(float _fTime);
	void SetPivot(Vector2 _vec);
	void FlipX();
	void PlayAniToggle();
	void PlusMinusFrm(int _ival);


	// for Save
	vector<Frm*> GetTop() { return m_vecTopFrm; }
	vector<Frm*> GetBot() { return m_vecBotFrm; }

private: // Variables

	wstring				m_strName;
	CAnimator2D*		m_pAnimator;
	CTexture*			m_pTex;

	// Top
	vector<Frm*>		m_vecTopFrm;
	int					m_iCurTopFrm;
	float				m_fTopAccTime; // 누적시간 (프레임 갱신용)
	bool				m_bTopFinish;  // 애니메이션이 끝났는지 체크

	// Bottom
	vector<Frm*>		m_vecBotFrm;
	int					m_iCurBotFrm;
	float				m_fBotAccTime;
	bool				m_bBotFinish;

	bool				m_bRepeat; // 반복 여부 
	bool				m_bFlipX;

	// for Edit Scene
	UINT				m_iCurBody; // Top과 Bot중에 어떤 것을 컨트롤 할 건지
	Frm*				m_CurEditFrm; 
	bool				m_bStopAni;
	int					m_iSetStateValue;
	
};

