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

	//AniFrame& GetFrame(int _iFrameIdx) { return m_vecFrame[_iFrameIdx]; }

	//void Create(CTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, Vector2 _vStep, float fDuration, UINT _iFrameCount);
	/*bool IsFinish() { return m_bFinish; }*/

	//int GetMaxFrame() { return (int)m_vecFrame.size(); }




private: // Variables
	wstring				m_strName;
	CAnimator2D*		m_pAnimator;
	int					m_iCurFrame; // ���� ������ �� ���� ���° �������� ���;��ϳ�
	float				m_fAccTime;  // �����ð� (������ ���ſ�)
	bool				m_bFinish;   // �ִϸ��̼��� �������� üũ




	// Test
	vector<Frm*>		m_vecFrmTop;
	int					m_iCurFrame_T;

	float				m_fAccTime_T;
	bool				m_bFinish_T;

	vector<Frm*>		m_vecFrmBot;
	int					m_iCurFrame_B;
	float				m_fAccTime_B;
	bool				m_bFinish_B;

	CTexture*			m_pTex;
	

public:
	void Create(wstring _strState, vector<Frm*>* _listFrm);
	bool IsFinish() { return m_bFinish_T; }
	void SetTexture(CTexture* _Tex) { m_pTex = _Tex; }

};

