#include "stdafx.h"
#include "ResMgr.h"

CResMgr* CResMgr::m_pInst = nullptr;


CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);

	if (pTex != nullptr)
		return pTex;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CRes*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
		return nullptr;
	
	return (CTexture*)iter->second;
}

void CResMgr::Release()
{
	/*map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}*/

	Safe_Delete_Map(m_mapTex);
}



// m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\MarcoMax.bmp");