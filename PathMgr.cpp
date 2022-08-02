#include "stdafx.h"
#include "PathMgr.h"

CPathMgr* CPathMgr::m_pInst = nullptr;


void CPathMgr::Init()
{
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = wcslen(m_szContentPath);

	for (int i = iLen - 1; 0 <= i; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
}
