//****************************************************************************
// 
// �X�R�A
// Author tetuji yamamoto
// 
//****************************************************************************
#include "score.h"
#include "number.h"
#include "fontManager.h"
#include "manager.h"
#include <locale.h>

// �ÓI�����o�[�ϐ��錾
int CScore::m_nScore = 0;

//****************************************************************************
// �X�R�A
//****************************************************************************
CScore::CScore() : CObject(CObject::PRIORITY_4)
{
	memset(m_apNumber, NULL, sizeof(m_apNumber));
	m_pWord = NULL;
	m_nScore = 0;
	m_nDigit = 0;
	m_nLength = 0;
	m_nNumWord = 0;	// ������
}

//****************************************************************************
// �X�R�A
//****************************************************************************
CScore::~CScore()
{
}

//****************************************************************************
// �X�R�A
//****************************************************************************
HRESULT CScore::Init()
{
	return S_OK;
}

//****************************************************************************
// �X�R�A
//****************************************************************************
HRESULT CScore::Init(D3DXVECTOR3 startPos, D3DXCOLOR col,float fWidth, float fHeight, int nDigits, const char* pStr)
{
	// �}���`�o�C�g�����n�֐����g�p���邽�߂̐ݒ�
	setlocale(LC_ALL, "");

	int nLength = strlen(pStr);
	m_nNumWord = _mbstrlen(pStr);

	m_nDigit = nDigits;
	m_pWord = new CWord[m_nNumWord];
	m_nLength = nLength;

	int nData = 0;
	int nIdxWord = 0;
	char cDataA;
	char cDataB[3];

	// �����𐶐�
	for (int nCntLen = 0; nCntLen < nLength; nCntLen++)
	{
		cDataA = pStr[nCntLen];

		if (cDataA < 0 && nData <= 0)
		{
			cDataB[nData] = cDataA;
			nData++;
			continue;
		}
		else
		{
			cDataB[nData] = cDataA;
			cDataB[nData + 1] = '\0';
		}

		D3DXVECTOR3 pos = D3DXVECTOR3_NULL;
		pos.x = startPos.x + (fWidth) * nCntLen;
		pos.y = startPos.y;
		m_pWord[nIdxWord].Init(pos,col,fWidth,fHeight, cDataB);
		nData = 0;
		nIdxWord++;
		ZeroMemory(cDataB, sizeof(cDataB[nData]));
	}

	float fLenWidth = startPos.x + (fWidth) * nLength;
	
	// �����𐶐�
	for (int nCntDigit = 0; nCntDigit < nDigits; nCntDigit++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3_NULL;
		pos.x = fLenWidth + startPos.x + (fWidth * 2.0f) * nCntDigit;
		pos.y = startPos.y;
		m_apNumber[nCntDigit] = CNumber::Create(pos, col, fWidth, fHeight, 0);

		if (m_apNumber[nCntDigit] == NULL)
		{
			MessageBox(NULL, " CScore::Init() > if ( m_apNumber != NULL) �N���G�C�g�Ɏ��s���܂���", "Error", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

//****************************************************************************
// �X�R�A
//****************************************************************************
void CScore::Uninit(void)
{
	if (m_pWord != NULL)
	{
		for (int nCntLen = 0; nCntLen < m_nNumWord; nCntLen++)
		{
			m_pWord[nCntLen].Uninit();
		}

		delete[] m_pWord;
		m_pWord = NULL;
	}

	for (int nCntDigit = 0; nCntDigit < MAX_NUM_DIGIT; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{
			m_apNumber[nCntDigit]->Uninit();
			delete m_apNumber[nCntDigit];
			m_apNumber[nCntDigit] = NULL;
		}
	}

	Release();
}

//****************************************************************************
// �X�R�A
//****************************************************************************
void CScore::Update(void)
{
	int nData = (int)pow(10, (double)m_nDigit - 1);

	for (int nCntLen = 0; nCntLen < m_nLength; nCntLen++)
	{
		m_pWord[nCntLen].Update();
	}

	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		int nNum = m_nScore / nData;
		m_apNumber[nCntDigit]->SetNumber(nNum);

		nData = (int)((float)nData * 0.1f);
	}
}

//****************************************************************************
// �X�R�A
//****************************************************************************
void CScore::Draw(void)
{
	// �t�H���g�}�l�[�W���[�̃C���X�^���X�擾
	CFontManager* pFontMane = CManager::GetFOntMane();
	CFont *pFont = pFontMane->GetFont(CFontManager::TYPE_SCORE);

	for (int nCntLen = 0; nCntLen < m_nNumWord; nCntLen++)
	{
		m_pWord[nCntLen].Draw(pFont->GetFont());
	}

	for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
}

//****************************************************************************
// �X�R�A
//****************************************************************************
CScore* CScore::Create(D3DXVECTOR3 startPos, D3DXCOLOR col, float fWidth, float fHeight, int nDigits, const char* pStr)
{
	CScore* pScore = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�g2D�̐���
	if (pScore == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pScore = new CScore;

		if (pScore != NULL)
		{
			// ����������
			pScore->Init(startPos, col, fWidth, fHeight, nDigits, pStr);
		}
		else
		{
			MessageBox(NULL, " CEnemy* CEnemy::Create() > if ( pEnemy != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CEnemy* CEnemy::Create() > if ( pEnemy == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pScore;

}