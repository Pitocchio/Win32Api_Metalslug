#pragma once

class CTexture;

class CResMgr
{
	SINGLETONE(CResMgr)

public:
	CTexture* LoadTexture(const wstring& _strKry, const wstring& _strRelativePath);

	CTexture* FindTexture(const wstring& _strKry);

	void Release();
private:
	map<wstring, CTexture*> m_mapTex;
};

