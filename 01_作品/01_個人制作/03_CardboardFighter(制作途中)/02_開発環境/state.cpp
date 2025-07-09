//****************************************************************************
// 
// ���
// Author tetuji yamamoto
// 
//****************************************************************************
#include "state.h"
#include "object.h"

//****************************************************************************
// ���
//****************************************************************************
CState::CState()
{
	m_state = CState::STATE_NONE;
	m_nStateCnt = 0;
}

//****************************************************************************
// ���
//****************************************************************************
CState::~CState()
{

}

//****************************************************************************
// ���
//****************************************************************************
void CState::Init(STATE state, int nAppStateCnt)
{
	m_state = state;
	m_nStateCnt = nAppStateCnt;
}

//****************************************************************************
// ���
//****************************************************************************
void CState::Uninit()
{
	delete this;
}

//****************************************************************************
// ���
//****************************************************************************
void CState::StateCountDown(void)
{
	switch (m_state)
	{
	case STATE_NONE:
		break;

	case STATE_APPEAR:
		m_nStateCnt--;
		if (m_nStateCnt <= 0)
		{// �J�E���g���[���ɂȂ�����
			m_state = STATE_NONE;
		}
		break;

	case STATE_DAMAGE:
		m_nStateCnt--;
		if (m_nStateCnt <= 0)
		{
			m_state = STATE_NONE;	// �ʏ��Ԃɐݒ�
		}
		break;

	case STATE_DEATH:
		break;
	}
}

//****************************************************************************
// ���
//****************************************************************************
CState* CState::Create(STATE state, int nAppStateCnt)
{
	CState* pState = NULL;
	int nNumAll = CObject::GetObujectNumAll();

	// �I�u�W�F�N�g2D�̐���
	if (pState == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pState = new CState;

		if (pState != NULL)
		{
			// ����������
			pState->Init(state, nAppStateCnt);
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

	return pState;
}