#include "cylinder.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffcylinder = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturcylinder = NULL;		// テクスチャのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffcylinder = NULL;	// インデックスへのポインタ
D3DXVECTOR3 g_poscylinder;							// 位置
D3DXVECTOR3 g_rotcylinder;							// 向き
D3DXMATRIX g_mtxWorldcylinder;						// ワールドマトリックス

D3DXVECTOR3 g_aPos[MESH_PLYGON_AII][3];	// 一ポリゴンごとの３頂点保存変数

//**************************************
// メッシュフィールドの初期化
//**************************************
void Initcylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffcylinder, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\billboard\\mountain002.png",
		&g_pVtxTexturcylinder);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffcylinder,
		NULL);

	// 頂点バッファをロック
	g_pVtxBuffcylinder->Lock(0, 0, (void**)&pVtx, 0);

	float fX = (float)FIELD_X / (float)MESH_X;
	float fZ = (float)FIELD_Z / (float)MESH_Z;

	float fRadius = 5000.0f;	// 半径

	float fAngle = (D3DX_PI * 2.0f) / (float)MESH_X;

	float fposX = 0.0f;
	float fposZ = 0.0f;

	float fTexX = 1.0f / (float)MESH_X;
	float fTexY = 1.0f / (float)MESH_Z;

	int nCntVtx = 0;

	// 位置と向きの初期化
	g_poscylinder = D3DXVECTOR3(0.0f,-500.0f,0.0f);
	g_rotcylinder = D3DXVECTOR3(0.0f,0.0f,0.0f);

	D3DXVECTOR3 VtxEX[MESH_VERTEX] = {};
	D3DXVECTOR2 bbb[MESH_VERTEX] = {};
	D3DXVECTOR3 test;

	for (int nCntV = 0; nCntV <= MESH_Z; nCntV++)
	{
		for (int nCntH = 0; nCntH <= MESH_X; nCntH++)
		{

			// 頂点情報の初期化
			pVtx[nCntVtx].pos.x = g_poscylinder.x + sinf(-fAngle * nCntH) * fRadius;
			pVtx[nCntVtx].pos.y = g_poscylinder.y + 5000.0f * nCntV;
			pVtx[nCntVtx].pos.z = g_poscylinder.z + cosf(-fAngle * nCntH) * fRadius;

			test = pVtx[nCntVtx].pos;

			// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
			D3DXVec3Normalize( &pVtx[nCntVtx].nor, &test);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtx].tex.x = -fTexX * nCntH;
			pVtx[nCntVtx].tex.y = -fTexY * nCntV;

			nCntVtx++;
		}
	}

	nCntVtx = 0;

	// 頂点バッファをアンロック
	g_pVtxBuffcylinder->Unlock();

	// インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffcylinder->Lock(0, 0, (void**)&pIdx, 0);

	int naIdxEX[MESH_INDEX];// インデックス格納用

	int nVtx = 0;
	int nIdxA = MESH_X + 1;	// 左側インデックス
	int nIdxB = 0;		// 右側インデックス

	for (int nCntA = 0; nCntA < MESH_Z; nCntA++)
	{
		for (int nCntB = 0; nCntB <= MESH_X; nCntB++)
		{
			pIdx[nVtx] = nIdxA;
			naIdxEX[nVtx] = nIdxA;
			nVtx++;
			pIdx[nVtx] = nIdxB;
			naIdxEX[nVtx] = nIdxB;
			nVtx++;
			nIdxA++;
			nIdxB++;
		}

		if (nCntA < MESH_Z - 1)
		{// 安全装置
			pIdx[nVtx] = nIdxB - 1;
			naIdxEX[nVtx] = nIdxB - 1;
			nVtx++;
			pIdx[nVtx] = nIdxA;
			naIdxEX[nVtx] = nIdxA;
			nVtx++;
		}
	}

	// インデックスバッファのアンロック
	g_pIdxBuffcylinder->Unlock();

	//nVtx = 0;
	//int nCntPoli = 0;
	//int nCntNor = 0;

	//for (nCntPoli = 0; nCntPoli < MESH_PLYGON_AII; nCntPoli++)
	//{// ポリゴン分回す
	//	// 各頂点の座標を代入していく
	//	g_aPos[nCntPoli][0] = VtxEX[naIdxEX[nVtx]];
	//	g_aPos[nCntPoli][1] = VtxEX[naIdxEX[nVtx + 1]];
	//	g_aPos[nCntPoli][2] = VtxEX[naIdxEX[nVtx + 2]];
	//	nVtx++;
	//}

	//nCntPoli = 0;
	//nVtx = 0;
}

//*******************************************
// メッシュフィールドの破棄
//*******************************************
void Uninitcylinder(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffcylinder != NULL)
	{
		g_pVtxBuffcylinder->Release();
		g_pVtxBuffcylinder = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturcylinder != NULL)
	{
		g_pVtxTexturcylinder->Release();
		g_pVtxTexturcylinder = NULL;
	}

	// インデックスバッファの解放
	if (g_pIdxBuffcylinder != NULL)
	{
		g_pIdxBuffcylinder->Release();
		g_pIdxBuffcylinder = NULL;
	}
}

//*******************************************
// メッシュフィールドの破棄
//*******************************************
void Updatecylinder(void)
{

}

//*******************************************
// メッシュフィールドの描画
//*******************************************
void Drawcylinder(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldcylinder);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotcylinder.y, g_rotcylinder.x, g_rotcylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldcylinder, &g_mtxWorldcylinder, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_poscylinder.x, g_poscylinder.y, g_poscylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldcylinder, &g_mtxWorldcylinder, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldcylinder);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffcylinder, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffcylinder);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pVtxTexturcylinder);
	
	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,MESH_VERTEX,0,MESH_PLYGON_AII);
}

//*******************************************
// メッシュフィールドの当たり判定
//*******************************************
bool CollisionMesh(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove)
{
	D3DXVECTOR3 vecLineA[3];
	D3DXVECTOR3 vecLineB[3];
	float fCloss[3];
	bool bRanding = false;

	for (int nCntPoli = 0; nCntPoli < MESH_PLYGON_AII; nCntPoli++)
	{// ポリゴン分回す
		for (int nCntPoliApp = 0; nCntPoliApp < MESH_X * 2; nCntPoliApp++)
		{// 見えるポリゴン
			// 左周りにベクトルを求める
			vecLineA[0] = g_aPos[nCntPoli][0] - g_aPos[nCntPoli][1];
			vecLineA[1] = g_aPos[nCntPoli][2] - g_aPos[nCntPoli][0];
			vecLineA[2] = g_aPos[nCntPoli][1] - g_aPos[nCntPoli][2];

			// 各頂点とのベクトル
			vecLineB[0] = *pPos - g_aPos[nCntPoli][1];
			vecLineB[1] = *pPos - g_aPos[nCntPoli][0];
			vecLineB[2] = *pPos - g_aPos[nCntPoli][2];

			// Yの外積を求める
			fCloss[0] = (vecLineA[0].z * vecLineB[0].x) - (vecLineA[0].x * vecLineB[0].z);
			fCloss[1] = (vecLineA[1].z * vecLineB[1].x) - (vecLineA[1].x * vecLineB[1].z);
			fCloss[2] = (vecLineA[2].z * vecLineB[2].x) - (vecLineA[2].x * vecLineB[2].z);

			if (fCloss[0] < 0 && fCloss[1] < 0 && fCloss[2] < 0 || 
				fCloss[0] > 0 && fCloss[1] > 0 && fCloss[2] > 0)
			{// すべてマイナスまたはすべてプラスなら
				D3DXVECTOR3 vecNor;	// 法線ベクトル
				D3DXVECTOR3 vecC = g_aPos[nCntPoli][0] - g_aPos[nCntPoli][1];	// ポリゴンの一辺ベクトル
				D3DXVECTOR3 vecD = g_aPos[nCntPoli][2] - g_aPos[nCntPoli][1];	// ポリゴンの一辺ベクトル
				D3DXVECTOR3 vecE = *pPos - g_aPos[nCntPoli][0];					// どっかの頂点からポスのベクトル
				float fDotY;	// 答え
				float faxbx;	// 途中式
				float fazbz;	// 途中式

				// 法線ベクトルを求める
				vecNor.x = (vecC.y * vecD.z) - (vecC.z * vecD.y);
				vecNor.y = (vecC.z * vecD.x) - (vecC.x * vecD.z);
				vecNor.z = (vecC.x * vecD.y) - (vecC.y * vecD.x);

				// 正規化
				D3DXVec3Normalize(&vecNor, &vecNor);

				// 一番大きいのを頼む
				if (vecE.y <= vecLineB[0].y)
				{
					vecE = vecLineB[0];
				}

				if (vecE.y <= vecLineB[1].y)
				{
					vecE = vecLineB[1];
				}

				if (vecE.y <= vecLineB[2].y)
				{
					vecE = vecLineB[2];
				}

				// 内積がゼロになるときのY座標
				faxbx = -(vecNor.x * vecE.x);
				fazbz = -(vecNor.z * vecE.z);

 				fDotY = (faxbx + fazbz) * (1.0f / vecNor.y);

				if (pPos->y <= fDotY)
				{// 求めた値より小さかったら
					// 求めた位置にする
					pPos->y = fDotY;
					pMove->y = 0.0f;
					bRanding = true;	// 乗ってますよ
				}
			}
			nCntPoli++;	// 一つポリゴン進める
		}
			nCntPoli += 3;	// 縮退ポリゴン分進める
	}

	// 結果を返す
	return bRanding;
}