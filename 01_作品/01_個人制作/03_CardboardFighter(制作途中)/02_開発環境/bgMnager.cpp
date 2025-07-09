//****************************************************************************
// 
// �w�i�}�l�[�W���[
// Author tetuji yamamoto
// 
//****************************************************************************
#include "bgManager.h"

//****************************************************************************
// �w�i�}�l�[�W���[
//****************************************************************************
CBGManager::CBGManager()
{
	memset(m_apBG,NULL,sizeof(m_apBG));
}

//****************************************************************************
// �w�i�}�l�[�W���[
//****************************************************************************
CBGManager::~CBGManager()
{
}

//****************************************************************************
// �w�i�}�l�[�W���[
//****************************************************************************
HRESULT CBGManager::Init(int nBGNum, float fFeedRate, float fFeedAngle)
{
	float fWidth = SCREEN_WIDTH * 0.5f;
	float fHeight = SCREEN_HEIGHT * 0.5f;
	D3DXVECTOR3 pos = { fWidth,fHeight,0.0f };
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };

	for (int nCnt = 0; nCnt < MAX_BG_NUM && nCnt < nBGNum; nCnt++)
	{
		float fFR = fFeedRate + fFeedRate * nCnt;
		m_apBG[nCnt] =  CBG::Create(fFR, fFeedAngle, (CBG::TYPE)nCnt);
	}

	return S_OK;
}

//****************************************************************************
// �w�i�}�l�[�W���[
//****************************************************************************
void CBGManager::Uninit(void)
{
	memset(m_apBG, NULL, sizeof(m_apBG));
	Release();
}

//****************************************************************************
// �w�i�}�l�[�W���[
//****************************************************************************
void CBGManager::Update(void)
{

}

//****************************************************************************
// �w�i�}�l�[�W���[
//****************************************************************************
void CBGManager::Draw(void)
{

}

//****************************************************************************
// �w�i�}�l�[�W���[
//****************************************************************************
CBGManager* CBGManager::Create(int nBGNum, float fFeedRate, float fFeedAngle)
{
	CBGManager* pManager = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�g2D�̐���
	if (pManager == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pManager = new CBGManager;

		if (pManager != NULL)
		{
			// ����������
			pManager->Init(nBGNum, fFeedRate, fFeedAngle);
		}
		else
		{
			MessageBox(NULL, " CBGManager::Create() > if ( pManager != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CBGManager::Create() > if ( pManager == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pManager;
}