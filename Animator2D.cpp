#include "stdafx.h"
#include "Animator2D.h"

CAnimator2D::CAnimator2D()
	: m_pOwnerObj(nullptr)
	, m_pCurAni(nullptr)	
	, m_pTex(nullptr)
{
}

CAnimator2D::~CAnimator2D()
{
	Safe_Delete_Map(m_mapAnim);
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



CAnimation2D* CAnimator2D::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;
	
	return iter->second;
}

void CAnimator2D::SetCurAnimation(const wstring& _strName)
{
	m_pCurAni = FindAnimation(_strName);
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

			wifs.getline(str, 64); // �ٹٲ޿� ����ó��


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
	/*
	// =================== PARSING =====================//
		
	m_vecFrm���� ��� State�� ���׹������� ���� �ִ� ����
	*/

	map<wstring, vector<Frm*>> mapTemp;
	map<wstring, vector<Frm*>>::iterator iterT;

	for (vector<Frm*>::iterator iterF = m_vecFrm.begin(); iterF != m_vecFrm.end(); ++iterF) 
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

	/*
	
	// =================== PARSING�� �����͸� �������� �ִϸ��̼� ����  =====================//

	*/
	for (iterT = mapTemp.begin(); iterT != mapTemp.end(); ++iterT)
	{
		CAnimation2D* pAni = new CAnimation2D;
		pAni->SetOwnerObj(this);
		pAni->SetTexture(m_pTex);
		pAni->Create((iterT->first), &(iterT->second)); // State ���� �ִϸ��̼� ����

		m_mapAnim.insert(make_pair((*iterT).first, pAni)); // State�� Key�� �׿� �ش��ϴ� �ִϸ��̼��� Value�� ���� ���� �ִϸ��̼� �ʿ� pushback
	}
}

void CAnimator2D::Save(const wstring& _strRelativePath)
{
	/*
	
	m_mapAnim�� ��� ������(�ǹ�, ������ Ÿ�� �� ��� ������ �Ϸ�� ���� �ִϸ��̼�)�� ���Ϸ� �����Ѵ�.

	�� ������ GameScene���� Load�� �����̴�.
	
	*/

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	wofstream ofs(strFilePath, ios::out | ios::trunc);

	for (map<wstring, CAnimation2D*>::iterator iter = m_mapAnim.begin(); iter != m_mapAnim.end(); ++iter) // Key���� ������Ʈ ���� map�� ��ȸ�Ѵ�
	{
		vector<Frm*> vecTop = (*iter).second->GetTop();
		vector<Frm*> vecBot = (*iter).second->GetBot();

		for (vector <Frm*>::iterator Topiter = vecTop.begin(); Topiter != vecTop.end(); ++Topiter)
		{
			ofs << (*Topiter)->State << endl
				<< (*Topiter)->Body << endl
				<< (*Topiter)->point1.x << endl
				<< (*Topiter)->point1.y << endl
				<< (*Topiter)->point2.x << endl
				<< (*Topiter)->point2.y << endl
				<< (*Topiter)->Pivot.x << endl
				<< (*Topiter)->Pivot.y << endl
				<< (*Topiter)->Duration << endl << endl;
		}

		for (vector <Frm*>::iterator Botiter = vecBot.begin(); Botiter != vecBot.end(); ++Botiter)
		{
			ofs << (*Botiter)->State << endl
				<< (*Botiter)->Body << endl
				<< (*Botiter)->point1.x << endl
				<< (*Botiter)->point1.y << endl
				<< (*Botiter)->point2.x << endl
				<< (*Botiter)->point2.y << endl
				<< (*Botiter)->Pivot.x << endl
				<< (*Botiter)->Pivot.y << endl
				<< (*Botiter)->Duration << endl << endl;
		}


	}


	ofs.close();
}
