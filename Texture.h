#pragma once
#include "Res.h"

class CTexture : public CRes
{

public:
	CTexture();
	virtual ~CTexture();

public:
	void Load(const wstring& _strFilePath);
	UINT Width() { return m_bitInfo.bmWidth; }
	UINT Height() { return m_bitInfo.bmHeight; }
	HDC GetDC() { return m_dc; }

	BITMAP GetInfo() { return m_bitInfo; }
private:
	HDC m_dc;
	HBITMAP m_hBit;

	BITMAP m_bitInfo;

};


// »ç¿ë¹ý 
//
//CTexture* pTex = new CTexture;
//wstring strFilepath = CPathMgr::GetInst()->GetContentPath();
//strFilepath += L"texture\\Marco.bmp";
//pTex->Load(strFilepath);
//
//pTex;
//
//delete pTex;