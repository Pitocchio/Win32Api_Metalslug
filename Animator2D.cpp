#include "stdafx.h"
#include "Animator2D.h"

CAnimator2D::CAnimator2D()
	: m_pOwnerObj(nullptr)
	, m_pCurAni(nullptr)
	, m_bRepeat(false)
{
}

CAnimator2D::~CAnimator2D()
{
	Safe_Delete_Map(m_mapAni);
}

void CAnimator2D::Init()
{
}

void CAnimator2D::Update() // ���� �ִϸ��̼��� ������Ʈ
{
	if (m_pCurAni != nullptr)
	{
		m_pCurAni->Update();

		if (m_bRepeat && m_pCurAni->IsFinish())
		{
			m_pCurAni->SetFrame(0);
		}
	}
}

void CAnimator2D::LateUpdate()
{
}

void CAnimator2D::Render(HDC hdc) // ���� �ִϸ��̼��� ����
{
	if (m_pCurAni != nullptr)
	{
		m_pCurAni->Render(hdc);
	}
}

void CAnimator2D::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, 
									Vector2 _vStep, float fDuration, UINT _iFrameCount)
{
	CAnimation2D* pAni = FindAnimation(_strName);
	assert(pAni == nullptr);

	pAni = new CAnimation2D;

	pAni->SetName(_strName);
	pAni->SetOwnerObj(this);  // ������� �ִϸ��̼ǵ鵵 �ִϸ����͸� �˾ƾ� ��
	pAni->Create(_pTex, _vLT, _vSliceSize, _vStep, fDuration, _iFrameCount);

	m_mapAni.insert(make_pair(_strName, pAni));
}

//
//void CAnimator2D::CreateAnimation_Test()
//{
//	m_vecFrm
//}




CAnimation2D* CAnimator2D::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;
	
	return iter->second;
}

void CAnimator2D::PlayAnimation(const wstring& _strName, bool _bRepeat)
{
	m_pCurAni = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

void CAnimator2D::SetOwnerObj(CObject* obj)
{
	m_pOwnerObj = obj;
}


void CAnimator2D::SetData(const wstring& _strRelativePath)
{
	// ����θ� �� �Լ��� ���ڷ� �޾� ������ ����
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// ���� ������ ���� 
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	if (pFile == nullptr)
		return;

	POINT pt1 = {};
	POINT pt2 = {};
	wstring state;
	UINT body;
	Vector2 pivot;
	float duration;


	// ������Ʈ ����, �̸��� ���� ���� 
	int StateSize;

	fread(&StateSize, sizeof(StateSize), 1, pFile);

	for (int i = 0; i < StateSize; ++i)
	{
		wstring temp;
		fread(&temp, sizeof(temp), 1, pFile);
		m_vecStateName.push_back(temp);
	}
	


	while (feof(pFile) == 0)
	{

		fread(&state, sizeof(state), 1, pFile);
		fread(&body, sizeof(UINT), 1, pFile);

		fread(&pt1.x, sizeof(LONG), 1, pFile);
		fread(&pt1.y, sizeof(LONG), 1, pFile);
		fread(&pt2.x, sizeof(LONG), 1, pFile);
		fread(&pt2.y, sizeof(LONG), 1, pFile);
		fread(&pivot.x, sizeof(pivot.x), 1, pFile);
		fread(&pivot.y, sizeof(pivot.y), 1, pFile);
		fread(&duration, sizeof(duration), 1, pFile);


		if (feof(pFile) != 0)
		{
			fclose(pFile);
			break;
		}
	


		Frm* temp = new Frm{ state, body, pt1, pt2, pivot, duration };
		m_vecFrm.push_back(temp);
	}

	//fclose(pFile);
}

void CAnimator2D::SetTexture(const wstring& _strKeyName, const wstring& _strFilePath)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(_strKeyName, _strFilePath);

}

void CAnimator2D::CreateAnimation_Test()
{
	// Animation�� ����� ���� ���ڷ� �����ϰ� �����ϱ� ���� map ����
	map<wstring, vector<Frm*>> mapTemp;
	map<wstring, vector<Frm*>>::iterator iterT;

	for (vector<Frm*>::iterator iterF = m_vecFrm.begin(); iterF != m_vecFrm.end(); ++iterF) // Frm ����ü (����) - ��� ������Ʈ�� �������� 
	{
		iterT = mapTemp.find((*iterF)->State);

		if (iterT == mapTemp.end())
		{
			vector<Frm*> listtemp;
			listtemp.push_back(*iterF);
			mapTemp.insert({ (*iterF)->State, listtemp });
		}
		else
		{
			(*iterT).second.push_back((*iterF));
		}
	}



	for (iterT = mapTemp.begin(); iterT != mapTemp.end(); ++iterT)
	{
		CAnimation2D* pAni = new CAnimation2D();

		pAni->Create_Test((*iterT).first, &(*iterT).second); // �ִϸ��̼��� �����ض�!

		m_mapAnim.insert(make_pair((*iterT).first, pAni)); // ���� �ִϸ��̼� �� (�갡 ��� �ִϸ��̼��� ��� ����)
	}
}
