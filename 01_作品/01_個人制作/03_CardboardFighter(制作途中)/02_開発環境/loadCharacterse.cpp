//********************************************
// 
// キャラクター情報読み取り
// Author Tetsuji Yamamoto
// 
//********************************************
#include "loadCharacterse.h"
#include "manager.h"

//*************************************
// モデル読み取り
//*************************************
CCharacterSet::CCharacterSet()
{
	m_nNumParts = 0;	// パーツ数
	m_fMovement = 0.0f;	// 移動量
	m_fJump = 0.0f;		// ジャンプ力
	m_fRadius = 0.0f;	// 半径
	m_fHeight = 0.0f;	// 高さ
	m_nLife = 0;		// 体力
}

//*************************************
// モデル読み取り
//*************************************
CCharacterSet::~CCharacterSet()
{

}

//*************************************
// モデル読み取り
//*************************************
void CCharacterSet::Uninit(void)
{
	delete this;
}

//*************************************
// モデル読み取り
//*************************************
void CCharacterSet::Load()
{
	// ロードモーションファイルポインタ取得
	CLoadMotionFile* pLoadMotionFile = CManager::GetLoadMotionFile();

	// ファイル取得
	FILE* pFile = pLoadMotionFile->GetFile();

	// 読み取った文字列取得
	char* pStr = pLoadMotionFile->GetStr();

	// ＝読み取り変数
	char aData[3] = {};

	if (strcmp(pStr, "END_CHARACTERSET") == 0)
	{// キャラクター情報読み取り終了

		// スクリプト読み取りタイプに変更
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_SCRIPT);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "NUM_PARTS") == 0)
	{
		// ＝読み取り
		fscanf(pFile, "%s", aData);

		// パーツ数読み取り
		fscanf(pFile, "%d", &m_nNumParts);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "MOVE") == 0)
	{
		// ＝読み取り
		fscanf(pFile, "%s", aData);

		// 値読み取り
		fscanf(pFile, "%f", &m_fMovement);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "JUMP") == 0)
	{
		// ＝読み取り
		fscanf(pFile, "%s", aData);

		// 値読み取り
		fscanf(pFile, "%f", &m_fJump);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "RADIUS") == 0)
	{
		// ＝読み取り
		fscanf(pFile, "%s", aData);

		// 値み取り
		fscanf(pFile, "%f", &m_fRadius);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "HEIGHT") == 0)
	{
		// ＝読み取り
		fscanf(pFile, "%s", aData);

		// 値み取り
		fscanf(pFile, "%f", &m_fHeight);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "LIFE") == 0)
	{
		// ＝読み取り
		fscanf(pFile, "%s", aData);

		// 値み取り
		fscanf(pFile, "%d", &m_nLife);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "PARTSSET") == 0)
	{
		// パーツセット読み取りタイプに変更
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_PARTSSET);

		// パーツセットのインスタンス生成、確保
		CLoadPartsSet* pLoadPartsSet = new CLoadPartsSet;

		// パーツセットの情報を末尾に追加
		pLoadMotionFile->SetPushBackLoadPartsSet(&pLoadPartsSet);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
}

//--------------------------------------------------------------------------------
// パーツセット

//*************************************
// パーツ読み取りコンストラクタ
//*************************************
CLoadPartsSet::CLoadPartsSet()
{
	m_nIdxParent = -1;
	memset(m_pos, NULL, sizeof(m_pos));
	memset(m_rot, NULL, sizeof(m_rot));
}

//*************************************
// パーツ読み取りデストラクタ
//*************************************
CLoadPartsSet::~CLoadPartsSet()
{

}

//*************************************
// パーツ読み取り終了処理
//*************************************
void CLoadPartsSet::Uninit(void)
{
	delete this;
}

//*************************************
// パーツ読み取り
//*************************************
void CLoadPartsSet::Load()
{
	// ロードモーションファイルポインタ取得
	CLoadMotionFile* pLoadMotionFile = CManager::GetLoadMotionFile();
	FILE* pFile = pLoadMotionFile->GetFile();

	char* pStr = pLoadMotionFile->GetStr();
	char aData[3] = {};
	int nResult;

	if (strcmp(pStr, "INDEX") == 0)
	{// インデックス
		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "PARENT") == 0)
	{// 親
		nResult = fscanf(pFile, "%s", aData);			// =を読み込む
		nResult = fscanf(pFile, "%d", &m_nIdxParent);	// 親インデックスを読み込む

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "POS") == 0)
	{// 位置
		nResult = fscanf(pFile, "%s", aData);		// =を読み込む
		nResult = fscanf(pFile, "%f", &m_pos.x);	// x座標を読み込む
		nResult = fscanf(pFile, "%f", &m_pos.y);	// y座標を読み込む
		nResult = fscanf(pFile, "%f", &m_pos.z);	// z座標を読み込む

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "ROT") == 0)
	{// 向き
		nResult = fscanf(pFile, "%s", aData);		// =を読み込む
		nResult = fscanf(pFile, "%f", &m_rot.x);	// x軸を読み込む
		nResult = fscanf(pFile, "%f", &m_rot.y);	// y軸を読み込む
		nResult = fscanf(pFile, "%f", &m_rot.z);	// z軸を読み込む

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "END_PARTSSET") == 0)
	{// 終わり
		// パーツセットインデックスを取得
		int nIdx = pLoadMotionFile->GetIdxLoadPartsSet();

		// パーツインデックスカウントアップ
		nIdx++;

		// パーツセットインデックスを設定
		pLoadMotionFile->SetIdxLoadPartsSet(nIdx);

		//	キャラクター情報読み取りタイプに変更
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_CHARCTERSET);

		// 文字列を空にする
		pLoadMotionFile->ClearStr();

		// 文字列インデックスをリセット
		pLoadMotionFile->ResetIdxStr();
	}
}