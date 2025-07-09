//*************************************
// 
// �t�H���g�}�l�[�W���[
// Author Tetsuji Yamamoto
// 
//*************************************
#include "fontManager.h"

//*************************************
// �t�H���g�}�l�[�W���[
//*************************************
CFontManager::CFontManager()
{
	ZeroMemory(m_apFont, sizeof(m_apFont));
}

//*************************************
// �t�H���g�}�l�[�W���[
//*************************************
CFontManager::~CFontManager()
{
}

//*************************************
// �t�H���g�}�l�[�W���[
//*************************************
void CFontManager::Init(void)
{
	for (int nCntFont = 0; nCntFont < TYPE_MAX; nCntFont++)
	{
		m_apFont[nCntFont] = CFont::Create((LPSTR)m_apFileName[nCntFont],m_aFontSize[nCntFont]);
	}
}

//*************************************
// �t�H���g�}�l�[�W���[
//*************************************
void CFontManager::Uninit(void)
{
	for (int nCntFont = 0; nCntFont < TYPE_MAX; nCntFont++)
	{
		if (m_apFont[nCntFont] != NULL)
		{
			m_apFont[nCntFont]->Uninit();
			delete m_apFont[nCntFont];
			m_apFont[nCntFont] = NULL;
		}
	}
}

//*************************************
// �t�H���g�}�l�[�W���[
//*************************************
CFontManager* CFontManager::Create(void)
{
	CFontManager* pFontMane = NULL;

	// �������m��
	pFontMane = new CFontManager;

	if (pFontMane != NULL)
	{
		// ����������
		pFontMane->Init();	// ����������
	}
	else
	{
		MessageBox(NULL, " CFontManager* Create() > if ( pFont != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pFontMane;
}