//************************************
// 
// キーセット読み取り
// Author Tetsuji Yamamoto
// 
//************************************

#include "LoadKeySet.h"
#include "loadMotionFile.h"
#include "manager.h"

//************************************
// キーセット読み取り
//************************************
CLoadKeySet::CLoadKeySet() 
{
	m_nFlame = 0;		// フレーム数
	m_nNumKey = 0;		// キー数
}

//************************************
// キーセット読み取り
//************************************
CLoadKeySet::~CLoadKeySet()
{
}

//************************************
// キーセット読み取り
//************************************
void CLoadKeySet::Uninit(void)
{
	// キーがあるのならば破棄する
	for (auto& iter : m_pLoadkey)
	{
		iter->Uninit();
	}
	m_pLoadkey.clear();

	delete this;
}

//************************************
// キーセット読み取り生成
//************************************
CLoadKey* CLoadKeySet::CreateLoadKey(int nNumLoadKey)
{
	//// キー数保存
	//m_nNumKey = nNumLoadKey;
	//
	//// ヌルであれば確保したい数分メモリを確保する
	//if (m_pLoadkey == NULL)
	//{
	//	m_pLoadkey = new CLoadKey[nNumLoadKey];
	//}
	//
	//return m_pLoadkey;

	return NULL;
}

//************************************
// キーセット読み取り初期化
//************************************
void CLoadKeySet::Load(void)
{
	// ロードモーションファイルポインタ取得
	CLoadMotionFile* pLoadMotionFile = CManager::GetLoadMotionFile();

	// ファイル取得
	FILE* pFile = pLoadMotionFile->GetFile();

	// 読み取った文字列取得
	char* pStr = pLoadMotionFile->GetStr();

	// ＝読み取り用変数
	char aData[3] = {};

	// 読込結果用変数
	int nResult;

	if (strcmp(pStr, "FRAME") == 0)
	{// ループの有無
		// =読み取り
		nResult = fscanf(pFile, "%s", aData);

		// フレーム数読み取り
		nResult = fscanf(pFile, "%d", &m_nFlame);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "KEY") == 0)
	{// ループの有無
		// キーセット読込タイプに設定
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_KEY);

		// キーのメモリ確保
		CLoadKey* pLoadKey = new CLoadKey;

		// 要素追加
		m_pLoadkey.push_back(pLoadKey);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "END_KEYSET") == 0)
	{// キーセット

		// キーセットのインデックス取得
		int nIdxKeySet = pLoadMotionFile->GetIdxKeySet();

		// インデックスカウントアップ
		nIdxKeySet++;

		// インデックス設定
		pLoadMotionFile->SetIdxKeySet(nIdxKeySet);

		// キーインデックス初期化
		pLoadMotionFile->SetIdxKey(0);

		// キーセット読込タイプに設定
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_MOTIONSET);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
}
