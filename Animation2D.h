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
	CTexture*			m_pTex; // ���� �̰� �ִϸ��̼��� ��� �־�� �ϳ�? 
	//vector<AniFrame>	m_vecFrame;
	int					m_iCurFrame; // ���� ������ �� ���� ���° �������� ���;��ϳ�
	float				m_fAccTime;  // �����ð� (������ ���ſ�)
	bool				m_bFinish;   // �ִϸ��̼��� �������� üũ







	// ========== Test ======== // (DOWN�� ��� ����ü �и��� �ȵǾ� �����Ƿ� ��ü�� ����Ѵ�)
	
private:
	// �ؽ��Ĵ� Animator�� �ִ� �� ��ӹ޾Ƽ� ����Ѵ�
	 
	// ��ü
	vector<Frm*>		m_vecFrame_T;  // ���� ��ü �ؽ�ó���� �߶󳻾� �� ��ġ ���� �÷��� Ÿ���� ���� ����
	int					m_iCurFrame_T;
	float				m_fAccTime_T;
	bool				m_bFinish_T;

	// ��ü
	vector<Frm*>		m_vecFrame_B;
	int					m_iCurFrame_B;
	float				m_fAccTime_B;
	bool				m_bFinish_B;



public: 
	void Create_Test(wstring _strState, vector<Frm*>* _listFrm);

};

