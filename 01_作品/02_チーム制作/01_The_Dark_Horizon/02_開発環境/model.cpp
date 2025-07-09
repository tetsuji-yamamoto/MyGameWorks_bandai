#include "model.h"
#include "motion.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureModel[6] = {};	// テクスチャへのポンタ


//********************************************
//モデルの初期化
//********************************************
void InitModel(void)
{

}

//********************************************
// モデルの終了処理
//********************************************
void UninitModel(void)
{

}

//********************************************
// モデルの更新
//********************************************
void UpdateModel(void)
{

}

//********************************************
// モデルの描画
//********************************************
void DrawModel(void)
{
	
}

//********************************************
// モデルの設定
//********************************************
void SetModel(char astr[], Model* pModel, int nModelNum)
{
	const char* pFileName = astr;

	pModel += nModelNum;	// モデル分進める

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	HRESULT hresult;
	hresult = D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&pModel->pBuffMat,
		NULL,
		&pModel->dwNumMat,
		&pModel->pMesh);

	if (FAILED(hresult))
	{// 失敗した！
		return;
	}

	//マテリアルデータへのポインタを取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pModel->dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// テクスチャファイルが存在する

			// このファイル名を使用してテクスチャを読み込む
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&pModel->apTexture[nCntMat]);
		}
	}
}

//********************************************
// パーツの設定
//********************************************
void PartsSet(FILE *pFile,Model* model)
{
	char astrA[256] = {};	// 文字列格納用変数
	char astrB[256] = {};	// 古い格納用変数
	char* aResult = 0;
	int nResult = 0;
	int nCnt = 0;
	int nNumParts = 0;// パーツ数

	Model SetModel;
	SetModel.nIdxModelParent = -1;// 親
	int nIndex = 0;
	SetModel.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetModel.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	while (1)
	{
		// 一文字読み取る
		aResult = fgets(&astrA[0], 2, pFile);

		// 一文字ずつ代入
		astrB[nCnt] = astrA[0];

		// カウントを進める,上限超えたらゼロ
		nCnt = (nCnt + 1) % 256;

		if (strcmp(&astrA[0], "#") == 0)
		{// コメント文字を読んだらそのあとの文字は読み飛ばす
			ReadComment(pFile, aResult);	// コメントを読み飛ばす
			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
			nCnt = 0;						// 保存用文字列のカウントゼロ
		}
		else if (strcmp(&astrA[0], "\n") == 0)
		{// 改行よんだら

			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
			nCnt = 0;						// 保存用文字列のカウントゼロ
		}
		else if (strcmp(&astrA[0], "\t") == 0)
		{// 改行よんだら

			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
			nCnt = 0;						// 保存用文字列のカウントゼロ
		}
		else if (strcmp(&astrB[0], "INDEX") == 0)
		{// インデックス読み込み
			nResult = fscanf(pFile,"%s",&astrA[0]);		// =読み込み
			nResult = fscanf(pFile, "%d", &nIndex);		// 値読み込み
			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
			nCnt = 0;						// 保存用文字列のカウントゼロ
		}
		else if (strcmp(&astrB[0], "PARENT") == 0)
		{// 親読み込み
			nResult = fscanf(pFile, "%s", &astrA[0]);					// =読み込み
			nResult = fscanf(pFile, "%d", &SetModel.nIdxModelParent);	// 値読み込み
			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
			nCnt = 0;						// 保存用文字列のカウントゼロ
		}
		else if (strcmp(&astrB[0], "POS") == 0)
		{// 位置読み込み
			nResult = fscanf(pFile, "%s", &astrA[0]);		// =読み込み
			nResult = fscanf(pFile, "%f", &SetModel.pos.x);	// 値読み込みX
			nResult = fscanf(pFile, "%f", &SetModel.pos.y);	// 値読み込みY
			nResult = fscanf(pFile, "%f", &SetModel.pos.z);	// 値読み込みZ
			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
			nCnt = 0;						// 保存用文字列のカウントゼロ
		}
		else if (strcmp(&astrB[0], "ROT") == 0)
		{// 角度読み込み
			nResult = fscanf(pFile, "%s", &astrA[0]);		// =読み込み
			nResult = fscanf(pFile, "%f", &SetModel.rot.x);	// 値読み込みX
			nResult = fscanf(pFile, "%f", &SetModel.rot.y);	// 値読み込みY
			nResult = fscanf(pFile, "%f", &SetModel.rot.z);	// 値読み込みZ
			StringClear(&astrB[0], 256);	// 保存用文字列のクリア
			nCnt = 0;						// 保存用文字列のカウントゼロ
		}
		else if (strcmp(&astrB[0], "END_PARTSSET") == 0)
		{// 読み込んだものをぶち込む
			EndPartsSet(model,SetModel,nIndex);
			break;
		}

		if (aResult == NULL)
		{// テキストファイル全部読み切っちゃった
			break;
		}
		else if (nResult == EOF)
		{// テキストファイル全部読み切っちゃった
			break;
		}
	}
}

//********************************************
// パーツの設定
//********************************************
void EndPartsSet(Model* pModel, Model model, int nIndex)
{
	pModel += nIndex;	//　インデックス分進める

	pModel->nIdxModelParent = model.nIdxModelParent;	// 親代入
	pModel->pos = model.pos;	// 位置代入
	pModel->rot = model.rot;	// 角度代入

	pModel->offSet = model.pos;	// オフセット代入

}