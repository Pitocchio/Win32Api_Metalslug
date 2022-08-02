#include "stdafx.h"
#include "Texture.h"

CTexture::CTexture()
	: m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// ���Ϸκ��� �ε��� �����͸� ��Ʈ������ ����
	m_hBit = (HBITMAP) LoadImage(nullptr, _strFilePath.c_str(), 
								IMAGE_BITMAP, 0, 0, 
								LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (m_hBit == nullptr)
		return;
	
	// ��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);

	// ��Ʈ�� ���� �޾ƿ�
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
