//************************************************
// 
// �U��
// Author Tsuji Yamamoto
// 
//************************************************
#include "attack.h"

//************************************************
// �U���R���X�g���N�^
//************************************************
CAttack::CAttack()
{
	m_bAttack = false;		// �U���̗L��
	m_bAttackTime = false;	// �U�����Ԃ̗L��
	m_bAttackEnd = true;	// �U���I���̗L��
	m_nAttackPower = 0;		// �U����
	m_nCntTime = 0;			// ���Ԍv���J�E���^�[
	m_nBeginningTime = 0;	// �n�܂莞��
	m_nAttackTime = 0;		// �U������
	m_nEndingTime = 0;		// �I��莞��
}

//************************************************
// �U���f�X�g���N�^
//************************************************
CAttack::~CAttack()
{
}

//************************************************
// �U���ݒ菈��
//************************************************
void CAttack::Set(int nBeginningTime, int nAttackTime, int nEndingTime, int nAttackPower)
{
	m_bAttack = true;					// �U�����Ă����Ԃɂ���
	m_bAttackTime = false;				// �U�����Ă��鎞�ԂłȂ���Ԃɂ���
	m_bAttackEnd = false;				// �U���I���̗L��
	m_nCntTime = 0;						// ���Ԍv���J�E���^�[���Z�b�g
	m_nAttackPower = nAttackPower;		// �U����
	m_nBeginningTime = nBeginningTime;	// �n�܂莞��
	m_nAttackTime = nAttackTime;		// �U������
	m_nEndingTime = nEndingTime;		// �I��莞��
}

//************************************************
// �U���X�V����
//************************************************
bool CAttack::Update(void)
{
	// �U�����Ă��Ȃ������珈�������Ȃ�
	if (m_bAttack == false)
	{
		return false;
	}

	// �S�̂̎��Ԃ����߂�
	int nAllTime = m_nBeginningTime + m_nAttackTime + m_nEndingTime;

	// ���ԃJ�E���^�[�J�E���g�A�b�v
	m_nCntTime++;

	// �J�E���^�[���U�����Ԃɓ������� (�J�E���^�[���n�܂莞�Ԉȏォ�U�����ԂƎn�܂莞�Ԃ̍��v�ȓ��ł����)
	if (m_nCntTime > m_nBeginningTime && m_nCntTime <= m_nAttackTime + m_nBeginningTime)
	{
		// �U�����Ă��鎞�ԏ�Ԃɂ���
		m_bAttackTime = true;
	}
	else
	{
		// �U�������Ȃ����ԏ�Ԃɂ���
		m_bAttackTime = false;
	}

	// �J�E���^�[���S�̂̎��Ԃ��z������
	if ( m_nCntTime > nAllTime)
	{
		// �U�����Ă��Ȃ���Ԃɂ���
		m_bAttack = false;

		// �U�����I�������Ԃɂ���
		m_bAttackEnd = true;
	}

	// ���ʂ�Ԃ�
	return m_bAttackTime;
}

//************************************************
// �U����������
//************************************************
CAttack* CAttack::Create(void)
{
	// �U���N���X�̃C���X�^���X����
	CAttack* pAttack = new CAttack;

	// ���������m�ۂł��Ȃ�������
	if (pAttack == NULL)
	{
		// ���b�Z�[�W�\��
		MessageBox(NULL, " CAttack::Create() > ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// ���ʂ�Ԃ�
	return pAttack;
}