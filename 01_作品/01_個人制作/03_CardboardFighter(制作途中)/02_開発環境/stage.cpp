//******************************************
// 
// ステージ
// Author Tetsuji Yamamoto
// 
//******************************************
#include "stage.h"
#include "manager.h"
#include "input.h"

//******************************************
// ステージコンストラクタ
//******************************************
CStage::CStage()
{
	m_pSky = NULL;			// 空のポインター
	m_pCylinderBG = NULL;	// シリンダーポインター
	m_pMeshField = NULL;	// メッシュフィールドのポインター
}

//******************************************
// ステージデストラクタ
//******************************************
CStage::~CStage()
{
}

//******************************************
// ステージ初期化
//******************************************
HRESULT CStage::Init(const char* pFIleName)
{
	// 空
	m_pSky = CSky::Create(10, 10, 5000.0f);

	// シリンダー背景
	m_pCylinderBG = CCylinderBG::Create(D3DXVECTOR3_NULL, 100, 1, 3000.0f, 1000.0f);

	// ステージを読み込む
	Load(pFIleName);
	
	// 壁生成
	CWall* pWallA = new CWall;
	CWall* pWallB = new CWall;
	CWall* pWallC = new CWall;
	CWall* pWallD = new CWall;
	pWallA = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -64.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), D3DXCOLOR_NULL, 2500.0f, 500.0f, 0.0f, NULL);
	pWallB = CWall::Create(D3DXVECTOR3(1130.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR_NULL, 500.0f, 500.0f, 0.0f, NULL);
	pWallC = CWall::Create(D3DXVECTOR3(-1100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR_NULL, 500.0f, 500.0f, 0.0f, NULL);
	pWallD = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -279.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f), D3DXCOLOR_NULL, 2500.0f, 500.0f, 0.0f, NULL);
	m_pWall.push_back(pWallA);
	m_pWall.push_back(pWallB);
	m_pWall.push_back(pWallC);
	m_pWall.push_back(pWallD);

	return S_OK;
}

//******************************************
// ステージ終了
//******************************************
void CStage::Uninit(void)
{
	// 空の破棄
	if (m_pSky != NULL)
	{
		m_pSky = NULL;
	}

	// メッシュフィールドの破棄
	if (m_pMeshField != NULL)
	{
		m_pMeshField = NULL;
	}

	// シリンダーの破棄
	if (m_pCylinderBG != NULL)
	{
		m_pCylinderBG = NULL;
	}

	// 壁の破棄
	if (m_pWall.capacity() > 0)
	{
		m_pWall.clear();
	}

	// ステージオブジェクトの破棄
	if (m_pObjStage.capacity() > 0)
	{
		for (auto& iter : m_pObjStage)
		{
			iter->Uninit();
		}
		m_pObjStage.clear();
	}

	// 自身の破棄
	Release();
}

//******************************************
// ステージ更新
//******************************************
void CStage::Update(void)
{

}

//******************************************
// ステージ描画
//******************************************
void CStage::Draw(void)
{
	// ステージオブジェクトの描画
	for (auto& iter : m_pObjStage)
	{
		iter->Draw();
	}
}

//******************************************
// ステージ読込
//******************************************
void CStage::Load(const char* pFileName)
{
	// 読み取り用としてファイルを開く
	FILE* pFile = fopen(pFileName, "r");

	// ファイルが開けなかった
	if (pFile == NULL)
	{
		MessageBox(NULL, "CStage::Load() > ファイルが開けませんでした", "Error", MB_OK);
		return;
	}

	// ファイルが開けたら
	char aStr[1024] = {};	// 文字列
	bool bComment = false;	// コメントの有無
	int nIdxStr = 0;		// 文字列インデックス
	int nIdxFileName = 0;	// ファイル名インデックス
	char aData[4] = {};		// =読み取り用
	int nType = TYPE_MAX;	// 読み取りタイプ

	// 読み取り用変数
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 向き
	char aFileName[128] = {};	// ファイル名

	while (1)
	{// ループ

		// 一文字読み取る
		char cData = fgetc(pFile);

		if (cData == '#')
		{// コメント文字を読んだらそのあとの文字は読み飛ばす
			bComment = true;				// コメント有の状態にする
			memset(aStr, 0, sizeof(aStr));	// 文字列を空にする
			nIdxStr = 0;					// 文字列インデックスリセット
			continue;						// whileから
		}
		else if (cData == '\n')
		{// 改行よんだら
			bComment = false;				// コメント無の状態にする
			memset(aStr, 0, sizeof(aStr));	// 文字列を空にする
			nIdxStr = 0;					// 文字列インデックスリセット
			continue;						// whileから
		}
		else if (cData == '\t')
		{// タブ文字よんだら
			continue;	// whileから
		}
		else if (cData == EOF)
		{// タブ文字よんだら
			break;	// whileから抜け出す
		}

		if (bComment == true)
		{// コメント機能がオン
			continue;	// whileから
		}

		aStr[nIdxStr] = cData;	// 一文字代入
		nIdxStr++;				// インデックスカウントアップ

		// モデル読込
		if (strcmp(aStr, "MODEL_SET") == 0)
		{
			// 読み取りタイプをモデルに変更
			nType = TYPE_MODEL;
		}
		// メッシュフィールド読込
		else if (strcmp(aStr, "MESHFIELD_SET") == 0)
		{
			// 読み取りタイプをモデルに変更
			nType = TYPE_MESHFIELD;
		}

		// タイプ別で読み取り
		switch (nType)
		{
			// モデル
		case TYPE_MODEL:
			// 位置を読み込む
			if (strcmp(aStr, "POS") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 数値を読み込む
				fscanf(pFile, "%f", &pos.x);
				fscanf(pFile, "%f", &pos.y);
				fscanf(pFile, "%f", &pos.z);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// 向きを読み込む
			else if (strcmp(aStr, "ROT") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 数値を読み込む
				fscanf(pFile, "%f", &rot.x);
				fscanf(pFile, "%f", &rot.y);
				fscanf(pFile, "%f", &rot.z);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// ファイル名を読み込む
			else if (strcmp(aStr, "FILE_NAME") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// ファイル名を読み込む
				fscanf(pFile, "%s", aFileName);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// モデルを生成
			else if (strcmp(aStr, "MODEL_SET_END") == 0)
			{
				// モデルのインスタンス生成、初期化
				CObjectStage* pStage = new CObjectStage;
				pStage->Init(pos,rot, aFileName);

				// 要素を追加する
				m_pObjStage.push_back(pStage);

				// タイプを戻す
				nType = TYPE_MAX;

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			break;

			// メッシュフィールド
		case TYPE_MESHFIELD:
			// ファイル名を読み込む
			if (strcmp(aStr, "FILE_NAME") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// 値を読み込む
				fscanf(pFile, "%s", aFileName);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			// メッシュフィールドの生成
			if (strcmp(aStr, "MESHFIELD_SET_END") == 0)
			{
				// =を読み込む
				fscanf(pFile, "%s", &aData[0]);

				// メッシュフィールドのメモリ確保
				m_pMeshField = new CMeshField;

				// メッシュフィールドの読込処理をする
				m_pMeshField->Load(aFileName);

				// 文字列を空にする
				memset(aStr, 0, sizeof(aStr));

				// 文字列インデックスリセット
				nIdxStr = 0;
			}
			break;
		}
	}

	// ファイルを閉じる
	fclose(pFile);
}
