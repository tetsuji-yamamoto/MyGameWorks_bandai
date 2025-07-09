//**********************************************
// 
// ��ԏ���
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _STATE_H_
#define _STATE_H_

#include "main.h"
#include "object.h"

#define STATE_COUNT_NOMAL (60)

// �I�u�W�F�N�g2D�N���X
class CState
{
public:

	// ���
	typedef enum
	{
		STATE_NONE = 0,
		STATE_APPEAR,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	CState();
	~CState();

	void Init(STATE state = STATE_APPEAR, int nAppStateCnt = STATE_COUNT_NOMAL);
	void Uninit();
	void StateCountDown(void);

	// �Z�b�^�[
	void SetState(STATE state) { m_state = state; }
	void SetStateCnt(int nLimit) { m_nStateCnt = nLimit; }

	// �Q�b�^�[
	int GetStateCnt(void) { return m_nStateCnt; }
	int GetState(void) { return (int)m_state; }

	static CState* Create(STATE state = STATE_APPEAR, int nAppStateCnt = STATE_COUNT_NOMAL);

private:
	int m_nStateCnt;					// �X�e�[�g�J�E���^�[
	STATE m_state;						// ���
};

#endif
