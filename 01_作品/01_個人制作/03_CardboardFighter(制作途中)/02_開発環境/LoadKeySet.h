//************************************
// 
// キーセット読み取り
// Author Tetsuji Yamamoto
// 
//************************************
#ifndef _LOADKEYSET_H_
#define _LOADKEYSET_H_

#include "main.h"
#include "LoadKey.h"
#include <vector>

// キーセット読み取りクラス
class CLoadKeySet
{
public:
	CLoadKeySet();
	~CLoadKeySet();

	void Uninit(void);
	void Load(void);
	CLoadKey* CreateLoadKey(int nNumLoadKey);


	// ゲッター
	int GetFlame(void) { return m_nFlame; }
	std::vector<CLoadKey*> GetLoadKey(void) { return m_pLoadkey; }
	auto GetLoadKeyElementEnd(void) { return m_pLoadkey.end() - 1; }
	auto GetLoadKeyBegin(void) { return m_pLoadkey.begin(); }
	auto GetLoadKeyEnd(void) { return m_pLoadkey.end(); }

	// セッター
	void SetFlame(int nFlame) { m_nFlame = nFlame; }

private:
	int m_nFlame;			// フレーム数
	std::vector<CLoadKey*> m_pLoadkey;	// キーポインター
	int m_nNumKey;			// キー数
};

#endif // !_LOADKEYSET_H_