//************************************************
// 
// 攻撃
// Author Tsuji Yamamoto
// 
//************************************************
#include "attack.h"

//************************************************
// 攻撃コンストラクタ
//************************************************
CAttack::CAttack()
{
	m_bAttack = false;		// 攻撃の有無
	m_bAttackTime = false;	// 攻撃時間の有無
	m_bAttackEnd = true;	// 攻撃終わりの有無
	m_nAttackPower = 0;		// 攻撃力
	m_nCntTime = 0;			// 時間計測カウンター
	m_nBeginningTime = 0;	// 始まり時間
	m_nAttackTime = 0;		// 攻撃時間
	m_nEndingTime = 0;		// 終わり時間
}

//************************************************
// 攻撃デストラクタ
//************************************************
CAttack::~CAttack()
{
}

//************************************************
// 攻撃設定処理
//************************************************
void CAttack::Set(int nBeginningTime, int nAttackTime, int nEndingTime, int nAttackPower)
{
	m_bAttack = true;					// 攻撃している状態にする
	m_bAttackTime = false;				// 攻撃している時間でない状態にする
	m_bAttackEnd = false;				// 攻撃終わりの有無
	m_nCntTime = 0;						// 時間計測カウンターリセット
	m_nAttackPower = nAttackPower;		// 攻撃力
	m_nBeginningTime = nBeginningTime;	// 始まり時間
	m_nAttackTime = nAttackTime;		// 攻撃時間
	m_nEndingTime = nEndingTime;		// 終わり時間
}

//************************************************
// 攻撃更新処理
//************************************************
bool CAttack::Update(void)
{
	// 攻撃していなかったら処理をしない
	if (m_bAttack == false)
	{
		return false;
	}

	// 全体の時間を求める
	int nAllTime = m_nBeginningTime + m_nAttackTime + m_nEndingTime;

	// 時間カウンターカウントアップ
	m_nCntTime++;

	// カウンターが攻撃時間に入ったら (カウンターが始まり時間以上かつ攻撃時間と始まり時間の合計以内であれば)
	if (m_nCntTime > m_nBeginningTime && m_nCntTime <= m_nAttackTime + m_nBeginningTime)
	{
		// 攻撃している時間状態にする
		m_bAttackTime = true;
	}
	else
	{
		// 攻撃しいない時間状態にする
		m_bAttackTime = false;
	}

	// カウンターが全体の時間を越したら
	if ( m_nCntTime > nAllTime)
	{
		// 攻撃していない状態にする
		m_bAttack = false;

		// 攻撃が終わった状態にする
		m_bAttackEnd = true;
	}

	// 結果を返す
	return m_bAttackTime;
}

//************************************************
// 攻撃生成処理
//************************************************
CAttack* CAttack::Create(void)
{
	// 攻撃クラスのインスタンス生成
	CAttack* pAttack = new CAttack;

	// メモリが確保できなかたっら
	if (pAttack == NULL)
	{
		// メッセージ表示
		MessageBox(NULL, " CAttack::Create() > メモリを確保できませんでした", "Error", MB_OK);
	}

	// 結果を返す
	return pAttack;
}