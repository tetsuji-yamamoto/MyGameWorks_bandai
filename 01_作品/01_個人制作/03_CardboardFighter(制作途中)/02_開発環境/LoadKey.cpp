//***************************************
// 
// キー読込
// AuthorTetsujiYamamoto
// 
//***************************************
#include "LoadKey.h"
#include "loadMotionFile.h"
#include "manager.h"

//***************************************
// キー読込
//***************************************
CLoadKey::CLoadKey()
{
	m_pos = D3DXVECTOR3_NULL;
	m_rot = D3DXVECTOR3_NULL;
}

//***************************************
// キー読込
//***************************************
CLoadKey::~CLoadKey()
{
}

//***************************************
// キー読込
//***************************************
void CLoadKey::Uninit(void)
{
	delete this;
}

//***************************************
// キー読込
//***************************************
void CLoadKey::Load(void)
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

	if (strcmp(pStr, "POS") == 0)
	{// ループの有無
		// =読み取り
		nResult = fscanf(pFile, "%s", aData);

		// 位置の有無読み取り
		nResult = fscanf(pFile, "%f", &m_pos.x);
		nResult = fscanf(pFile, "%f", &m_pos.y);
		nResult = fscanf(pFile, "%f", &m_pos.z);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "ROT") == 0)
	{// キー数
		// =読み取り
		nResult = fscanf(pFile, "%s", aData);

		// 向きの読み取り
		nResult = fscanf(pFile, "%f", &m_rot.x);
		nResult = fscanf(pFile, "%f", &m_rot.y);
		nResult = fscanf(pFile, "%f", &m_rot.z);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "END_KEY") == 0)
	{// キーセット
		// キーのインデックス取得
		int nIdx = pLoadMotionFile->GetIdxKey();

		// インデックスカウントアップ
		nIdx++;

		// インデックス設定
		pLoadMotionFile->SetIdxKey(nIdx);

		// キーセット読込タイプに設定
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_KEYSET);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
}