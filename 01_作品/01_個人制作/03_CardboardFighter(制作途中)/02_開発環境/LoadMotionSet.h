//**********************************
// 
// モーションセット読み取り
// Author Tetsuji Yamamoto
// 
//**********************************
#ifndef _MOTIONSET_H_
#define _MOTIONSET_H_

#include "main.h"
#include "motion.h"
#include "LoadKeySet.h"
#include <vector>

// モーションセット読込クラス
class CLoadMotionSet
{
public:
#define MAX_LOAD_MOTION (32)	// モーションの最大数

	CLoadMotionSet();
	~CLoadMotionSet();

	void Uninit(void);
	void Load(void);
	CLoadKeySet* CreateLoadkeySet(int nNumLoadKeySet);
	void LoadLoadKeyset(void);

	// ゲッター
	bool GetLoop(void) { return m_bLoop; }
	int GetNumKey(void) { return m_nNumKey; }
	std::vector<CLoadKeySet*> GetkeySet(void) { return m_pLoadKeySet; }
	auto GetLoadKeySetBegin(void) { return m_pLoadKeySet.begin(); }
	auto GetLoadKeySetEnd(void) { return m_pLoadKeySet.end(); }
	auto GetLoadKeySetElementEnd(void) { return m_pLoadKeySet.end() - 1; }

	// セッター
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void SetNumKey(int nNumKey) { m_nNumKey = nNumKey; }

private:
	bool m_bLoop;	// ループの有無
	int m_nNumKey;	// キー数

	std::vector<CLoadKeySet*> m_pLoadKeySet;	// キーセットポインタ
	int m_nNumKeySet;							// キーセットの数
};

#endif // !_MOTIONSET_H_