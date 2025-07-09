//************************************************
// 
// 攻撃
// Author Tsuji Yamamoto
// 
//************************************************
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "main.h"

// 攻撃クラス
class CAttack
{
public:
	CAttack();
	~CAttack();

	void Set(int nBeginningTime,int nAttackTime,int nEndingTime, int nAttackPower);
	void Uninit(void) { delete this; }
	bool Update(void);
	static CAttack* Create(void);

	// ゲッター
	int GetAttackPower(void) { return m_nAttackPower; }
	bool GetIsAttack(void) { return m_bAttack; }
	bool GetIsAttackTime(void) { return m_bAttackTime; }
	bool GetIsAttackEnd(void) { return m_bAttackEnd; }

	// セッター
	void SetIsAttack(bool bAttack) { m_bAttack = bAttack; }
	void SetIsAttackEnd(bool bAttackEnd) { m_bAttackEnd = bAttackEnd; }

private:
	bool m_bAttack;			// 攻撃の有無
	bool m_bAttackEnd;		// 攻撃終わりの有無
	bool m_bAttackTime;		// 攻撃時間の有無
	int m_nAttackPower;		// 攻撃力
	int m_nCntTime;			// 時間計測カウンター
	int m_nBeginningTime;	// 始まり時間
	int m_nAttackTime;		// 攻撃時間
	int m_nEndingTime;		// 終わり時間
};

#endif // !_ATTACK_H_
