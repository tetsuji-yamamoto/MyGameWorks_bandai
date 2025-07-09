//************************************************************************************************
// 
// モーションセット読み取り
// Author Tetsuji Yamamoto
// 
//************************************************************************************************
#include "LoadMotionSet.h"
#include "loadMotionFile.h"
#include "manager.h"

//************************************************************************************************
// モーションセット読み取り
//************************************************************************************************
CLoadMotionSet::CLoadMotionSet()
{
	m_bLoop = false;		// ループの有無
	m_nNumKey = 0;			// キー数
	m_nNumKeySet = 0;		// キーセット数
}

//************************************************************************************************
// モーションセット読み取り
//************************************************************************************************
CLoadMotionSet::~CLoadMotionSet()
{

}

//************************************************************************************************
// モーションセット読み取り
//************************************************************************************************
void CLoadMotionSet::Uninit(void)
{
	// キーセットがあるならば破棄する
	for (auto& iter : m_pLoadKeySet)
	{
		iter->Uninit();
	}
	m_pLoadKeySet.clear();
	
	delete this;
}

//************************************************************************************************
// モーションセット読み取りキーセット生成
//************************************************************************************************
CLoadKeySet* CLoadMotionSet::CreateLoadkeySet(int nNumLoadKeySet)
{
	//// キーセットの数保存
	//m_nNumKeySet = nNumLoadKeySet;

	//// ヌルであれば確保したい数分メモリを確保する
	//if (m_pLoadKeySet == NULL)
	//{
	//	m_pLoadKeySet = new CLoadKeySet[nNumLoadKeySet];
	//}

	//return m_pLoadKeySet;
	return NULL;
}

//************************************************************************************************
// モーションセット読み取り
//************************************************************************************************
void CLoadMotionSet::Load(void)
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

	if (strcmp(pStr, "LOOP") == 0)
	{// ループの有無
		// =読み取り
		nResult = fscanf(pFile, "%s", aData);

		// ループの有無読み取り
		int nData = 0;
		nResult = fscanf(pFile, "%d", &nData);
		m_bLoop = (bool)nData;

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "NUM_KEY") == 0)
	{// キー数
		// =読み取り
		nResult = fscanf(pFile, "%s", aData);

		// キー数読み取り
		nResult = fscanf(pFile, "%d", &m_nNumKey);

		// キー数分メモリを確保する
		this->CreateLoadkeySet(m_nNumKey);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "KEYSET") == 0)
	{// キーセット
		// モデル数取得
		int NumModel = pLoadMotionFile->GetModelNum();

		// キーセットのインデックス取得
		int nIdxKeySet = pLoadMotionFile->GetIdxKeySet();

		// モデルの数分キーを生成する
		CLoadKeySet* pLoadKeySet = new CLoadKeySet;

		// 要素を追加する
		m_pLoadKeySet.push_back(pLoadKeySet);

		// キーセット読込タイプに設定
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_KEYSET);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "END_MOTIONSET") == 0)
	{// 終了
		// モーションセットインデックスを取得
		int nIdx = pLoadMotionFile->GetIdxMotionset();

		// インデックスカウントアップ
		nIdx++;

		// インデックスをセット
		pLoadMotionFile->SetIdxMotionset(nIdx);

		// キーセットとキーのインデックスをリセット
		pLoadMotionFile->SetIdxKey(0);
		pLoadMotionFile->SetIdxKeySet(0);

		// スクリプト読込タイプに戻す
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_SCRIPT);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
}

//************************************************************************************************
// モーションセットキーセット読み取り
//************************************************************************************************
void CLoadMotionSet::LoadLoadKeyset(void)
{
	auto iter = m_pLoadKeySet.end() - 1;
	(*iter)->Load();
}