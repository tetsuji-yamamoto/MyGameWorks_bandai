//****************************************************************************
// 
// �^�C�}�[
// Author tetuji yamamoto
// 
//****************************************************************************
#include "timer.h"
#include "number.h"

// �ÓI�����o�[�ϐ��錾
int CTimer::m_nTime = 0;
int CTimer::m_nCntTime = 0;

//****************************************************************************
// �^�C�}�[
//****************************************************************************
CTimer::CTimer()
{
	memset(m_apNumber, NULL, sizeof(m_apNumber));
	m_nDigit = 0;
}

//****************************************************************************
// �^�C�}�[
//****************************************************************************
CTimer::~CTimer()
{
}

//****************************************************************************
// �^�C�}�[
//****************************************************************************
HRESULT CTimer::Init()
{
	return S_OK;
}

//****************************************************************************
// �^�C�}�[
//****************************************************************************
HRESULT CTimer::Init(D3DXVECTOR3 startPos, D3DXCOLOR col, float fWidth, float fHeight, int nDigits, int nTime)
{
	m_nCntTime = 0;
	m_nDigit = nDigits;
	m_nTime = nTime;

	float fDigitWidth = fWidth / nDigits;
	float fDigitWidthHerf = fDigitWidth * 0.5f;

	for (int nCntDigit = 0; nCntDigit < nDigits; nCntDigit++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3_NULL;
		pos.x = startPos.x + fDigitWidthHerf + fDigitWidth * nCntDigit;
		pos.y = startPos.y + fHeight * 0.5f;

		m_apNumber[nCntDigit] = CNumber::Create(pos, col, fDigitWidthHerf, fHeight * 0.5f, 0);

		if (m_apNumber[nCntDigit] == NULL)
		{
			MessageBox(NULL, " CTimer::Init() > if ( m_apNumber[nCntDigit] != NULL) �N���G�C�g�Ɏ��s���܂���", "Error", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

//****************************************************************************
// �^�C�}�[
//****************************************************************************
void CTimer::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Uninit();
		m_apNumber[nCntDigit] = NULL;
	}

	Release();
}

//****************************************************************************
// �^�C�}�[
//****************************************************************************
void CTimer::Update(void)
{
	if (CTimer::SecondsCnt() == true)
	{
		m_nTime--;

		if (m_nTime <= 0)
		{
			m_nTime = 0;
		}

		int nData = (int)pow(10, (double)m_nDigit - 1);

		for (int nCntDigit = 0; nCntDigit < m_nDigit; nCntDigit++)
		{
			int nNum = m_nTime / nData;
			m_apNumber[nCntDigit]->SetNumber(nNum);

			nData = (int)((float)nData * 0.1f);
		}
	}
}

//****************************************************************************
// �^�C�}�[
//****************************************************************************
void CTimer::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < MAX_TIME_DIGIT; nCntDigit++)
	{
		m_apNumber[nCntDigit]->Draw();
	}
}

//****************************************************************************
// �^�C�}�[
//****************************************************************************
CTimer* CTimer::Create(D3DXVECTOR3 startPos, D3DXCOLOR col, float fWidth, float fHeight, int nDigits, int nTime)
{
	CTimer* pTimer = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�g2D�̐���
	if (pTimer == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pTimer = new CTimer;

		if (pTimer != NULL)
		{
			// ����������
			pTimer->Init(startPos, col, fWidth, fHeight, nDigits);
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

	return pTimer;

}

//****************************************************************************
// �^�C�}�[
//****************************************************************************
bool CTimer::SecondsCnt(void)
{
	m_nCntTime++;

	if (m_nCntTime >= 60)
	{
		m_nCntTime = 0;
		return true;
	}

	return false;
}