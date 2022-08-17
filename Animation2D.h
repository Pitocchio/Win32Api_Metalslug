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
	int					m_iCurFrame; // ���� ������ �� ���� ���° �������� ���;��ϳ�
	float				m_fAccTime;  // �����ð� (������ ���ſ�)
	bool				m_bFinish;   // �ִϸ��̼��� �������� üũ


	// ========== Test ======== // (DOWN�� ��� ����ü �и��� �ȵǾ� �����Ƿ� ��ü�� ����Ѵ�)
	// ��ü
	CTexture*			m_pTexTop;		// ��ü �ؽ�ó
	vector<AniFrame>	m_vecFrameTop;  // ��ü ������
	int					m_iIdxTop;		// ��ü �ε���

	// ��ü
	vector<AniFrame>	m_vecFrameBot;  // ��ü ������
	CTexture*			m_pTexBot;		// ��ü �ؽ�ó
	int					m_iIdxBot;		// ��ü �ε���

};

