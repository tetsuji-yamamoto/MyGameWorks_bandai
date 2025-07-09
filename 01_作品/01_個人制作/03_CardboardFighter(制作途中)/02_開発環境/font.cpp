//****************************************
// 
// �t�H���g
// Author Tetsuji Yamamoto
// 
//****************************************
#include "font.h"
#include "renderer.h"
#include "object.h"

//****************************************
// �t�H���g
//****************************************
CFont::CFont()
{
	m_pFont = NULL;
	m_nFontSize = 0;
}

//****************************************
// �t�H���g
//****************************************
CFont::~CFont()
{
}

//****************************************
// �t�H���g
//****************************************
void CFont::Init(LPSTR pFileName,int nFontSize)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	m_nFontSize = nFontSize;

	// �f�o�b�O�p�\���t�H���g�̐���
	D3DXCreateFont(pDevice, 
		nFontSize,
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		pFileName, &m_pFont);
}

//****************************************
// �t�H���g
//****************************************
void CFont::Uninit(void)
{
	//�f�o�b�O�\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//****************************************
// �t�H���g
//****************************************
CFont* CFont::Create(LPSTR pFileName, int nFontSize)
{
	CFont* pFont = NULL;
	int nNumAll = CObject::GetObujectNumAll();

	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// �������m��
	pFont = new CFont;

	if (pFont != NULL)
	{
		// ����������
		pFont->Init(pFileName, nFontSize);	// ����������
	}
	else
	{
		MessageBox(NULL, " CFont* Create() > if ( pFont != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pFont;
}
