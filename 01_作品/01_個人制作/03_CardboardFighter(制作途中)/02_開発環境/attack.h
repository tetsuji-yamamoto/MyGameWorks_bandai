//************************************************
// 
// �U��
// Author Tsuji Yamamoto
// 
//************************************************
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "main.h"

// �U���N���X
class CAttack
{
public:
	CAttack();
	~CAttack();

	void Set(int nBeginningTime,int nAttackTime,int nEndingTime, int nAttackPower);
	void Uninit(void) { delete this; }
	bool Update(void);
	static CAttack* Create(void);

	// �Q�b�^�[
	int GetAttackPower(void) { return m_nAttackPower; }
	bool GetIsAttack(void) { return m_bAttack; }
	bool GetIsAttackTime(void) { return m_bAttackTime; }
	bool GetIsAttackEnd(void) { return m_bAttackEnd; }

	// �Z�b�^�[
	void SetIsAttack(bool bAttack) { m_bAttack = bAttack; }
	void SetIsAttackEnd(bool bAttackEnd) { m_bAttackEnd = bAttackEnd; }

private:
	bool m_bAttack;			// �U���̗L��
	bool m_bAttackEnd;		// �U���I���̗L��
	bool m_bAttackTime;		// �U�����Ԃ̗L��
	int m_nAttackPower;		// �U����
	int m_nCntTime;			// ���Ԍv���J�E���^�[
	int m_nBeginningTime;	// �n�܂莞��
	int m_nAttackTime;		// �U������
	int m_nEndingTime;		// �I��莞��
};

#endif // !_ATTACK_H_
