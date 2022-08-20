#include "stdafx.h"
#include "Animator2D.h"

CAnimator2D::CAnimator2D()
	: m_pOwnerObj(nullptr)
	, m_pCurAni(nullptr)
	//, m_bRepeat(false)
	, m_pTex(nullptr)
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

		if (m_pCurAni->IsRepeat() && m_pCurAni->IsFinish())
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

//void CAnimator2D::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vector2 _vLT, Vector2 _vSliceSize, 
//									Vector2 _vStep, float fDuration, UINT _iFrameCount)
//{
//	CAnimation2D* pAni = FindAnimation(_strName);
//	assert(pAni == nullptr);
//
//	pAni = new CAnimation2D;
//
//	pAni->SetName(_strName);
//	pAni->SetOwnerObj(this);  // ������� �ִϸ��̼ǵ鵵 �ִϸ����͸� �˾ƾ� ��
//	pAni->Create(_pTex, _vLT, _vSliceSize, _vStep, fDuration, _iFrameCount);
//
//	m_mapAni.insert(make_pair(_strName, pAni));
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
	//m_bRepeat = _bRepeat;
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

	wifstream wifs;
	wifs.open(strFilePath, ios::in);

	if (wifs.is_open())
	{
		while (!wifs.eof())
		{		
			WCHAR str[256];
			wifs.getline(str, 256);
			wstring state(&str[0]);

			wifs.getline(str, 64);
			UINT body = _wtoi(str);

			wifs.getline(str, 64);
			int pt1x = _wtoi(str);
			wifs.getline(str, 64);
			int pt1y = _wtoi(str);
			wifs.getline(str, 64);
			int pt2x = _wtoi(str);
			wifs.getline(str, 64);
			int pt2y = _wtoi(str);
			POINT pt1; 
			pt1.x = pt1x;
			pt1.y = pt1y;
			POINT pt2;
			pt2.x = pt2x;
			pt2.y = pt2y;
			
		
			wifs.getline(str, 64);
			float pvx = _wtof(str);
			wifs.getline(str, 64);
			float pvy = _wtof(str);
			Vector2 pivot = { pvx, pvy };

			wifs.getline(str, 64);
			float duration = _wtof(str);

			wifs.getline(str, 64);


			if (wifs.eof())
				break;

			Frm* temp = new Frm{ state, body, pt1, pt2, pivot, duration };
			m_vecFrm.push_back(temp);
		}
		wifs.close();
	}
}

void CAnimator2D::SetTexture(const wstring& _strKeyName, const wstring& _strFilePath)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(_strKeyName, _strFilePath);
	
	int k = 0;
}

void CAnimator2D::CreateAnimation()
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
		CAnimation2D* pAni = new CAnimation2D;
		pAni->SetTexture(m_pTex);
		pAni->Create((iterT->first), &(iterT->second)); // �ִϸ��̼��� �����ض�!

		m_mapAnim.insert(make_pair((*iterT).first, pAni)); // ���� �ִϸ��̼� �� (�갡 ��� �ִϸ��̼��� ��� ����)
	}
}
