#include "signboard.h"
#include "keyboard.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSignboard = NULL;					// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturSignboard[BOARDTYPE_MAX] = {};		// テクスチャのポインタ
SIGNBOARD g_aSignboard[BOARDTYPE_MAX];								// ボード
int nSignBoardIdx = 0;
//**************************************
// ボードの初期化
//**************************************
void InitSignboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * BOARDTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSignboard, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_MOVE.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_MOVE]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_MAKESB.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_MAKE]);


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_SNOW.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_SROW_SNOW]);


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_ICE.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_SROW_ICE]);


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_GRAVEL.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_SROW_GRAVEL]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\TUTORIAL_MOKUTEKI.jpg",
		&g_pVtxTexturSignboard[BOARDTYPE_MOKUTEKI]);


	// 頂点バッファをロック
	g_pVtxBuffSignboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBoard = 0; nCntBoard < BOARDTYPE_MAX; nCntBoard++)
	{
		g_aSignboard[nCntBoard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSignboard[nCntBoard].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aSignboard[nCntBoard].fHeight = 0.0f;
		g_aSignboard[nCntBoard].fWidth = 0.0f;
		g_aSignboard[nCntBoard].type = BOARDTYPE_MAX;
		g_aSignboard[nCntBoard].bUse = false;

		g_aSignboard[nCntBoard].fWidth = 0.0f;

		// 頂点座標の設定
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 0.0f;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 0.0f;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f;

		// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffSignboard->Unlock();

	SetSignBoard(BOARDTYPE_MOVE,
		D3DXVECTOR3(100.0f,120.0f,110.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		70.0f,
		70.0f);

	SetSignBoard(BOARDTYPE_MAKE,
		D3DXVECTOR3(520.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);

	SetSignBoard(BOARDTYPE_SROW_SNOW,
		D3DXVECTOR3(920.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);

	SetSignBoard(BOARDTYPE_SROW_ICE,
		D3DXVECTOR3(1320.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);

	SetSignBoard(BOARDTYPE_SROW_GRAVEL,
		D3DXVECTOR3(1730.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);

	SetSignBoard(BOARDTYPE_MOKUTEKI,
		D3DXVECTOR3(1940.0f, 150.0f, 140.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		70.0f,
		140.0f);
}

//*****************************
// ボードの破棄
//*****************************
void UninitSignboard(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffSignboard != NULL)
	{
		g_pVtxBuffSignboard->Release();
		g_pVtxBuffSignboard = NULL;
	}

	for (int nCnt = 0; nCnt < BOARDTYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_pVtxTexturSignboard[nCnt] != NULL)
		{
			g_pVtxTexturSignboard[nCnt]->Release();
			g_pVtxTexturSignboard[nCnt] = NULL;
		}
	}
}

//*****************************
// ボードの更新
//*****************************
void UpdateSignboard(void)
{
	if (KeyboardRepeat(DIK_I))
	{
		g_aSignboard[nSignBoardIdx].pos.z += 1.0f;
	}
	else if (KeyboardRepeat(DIK_K))
	{
		g_aSignboard[nSignBoardIdx].pos.z -= 1.0f;
	}

	if (KeyboardRepeat(DIK_J))
	{
		g_aSignboard[nSignBoardIdx].pos.x -= 1.0f;
	}
	else if (KeyboardRepeat(DIK_L))
	{
		g_aSignboard[nSignBoardIdx].pos.x += 1.0f;
	}

	if (KeyboardRepeat(DIK_U))
	{
		g_aSignboard[nSignBoardIdx].pos.y += 1.0f;
	}
	else if (KeyboardRepeat(DIK_O))
	{
		g_aSignboard[nSignBoardIdx].pos.y -= 1.0f;
	}

	if (KeyboardTrigger(DIK_M))
	{
		nSignBoardIdx++;

		if (nSignBoardIdx >= BOARDTYPE_MAX)
		{
			nSignBoardIdx = 0;
		}
	}
}

//*****************************
// ボードの描画
//*****************************
void DrawSignboard(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 254);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBoard = 0; nCntBoard < BOARDTYPE_MAX; nCntBoard++)
	{
		if (g_aSignboard[nCntBoard].bUse == true)
		{// 使ってたら
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aSignboard[nCntBoard].mtxWorld);

			// ビューマトリックス取得
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// カメラの逆行列を設定
			g_aSignboard[nCntBoard].mtxWorld._11 = mtxview._11;
			g_aSignboard[nCntBoard].mtxWorld._12 = mtxview._21;
			g_aSignboard[nCntBoard].mtxWorld._13 = mtxview._31;
			g_aSignboard[nCntBoard].mtxWorld._21 = mtxview._12;
			g_aSignboard[nCntBoard].mtxWorld._22 = mtxview._22;
			g_aSignboard[nCntBoard].mtxWorld._23 = mtxview._32;
			g_aSignboard[nCntBoard].mtxWorld._31 = mtxview._13;
			g_aSignboard[nCntBoard].mtxWorld._32 = mtxview._23;
			g_aSignboard[nCntBoard].mtxWorld._33 = mtxview._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aSignboard[nCntBoard].pos.x, g_aSignboard[nCntBoard].pos.y, g_aSignboard[nCntBoard].pos.z);
			D3DXMatrixMultiply(&g_aSignboard[nCntBoard].mtxWorld, &g_aSignboard[nCntBoard].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aSignboard[nCntBoard].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffSignboard, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pVtxTexturSignboard[g_aSignboard[nCntBoard].type]);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ボードの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBoard, 2);
		}
	}

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************
// ボードの設定
//*****************************
void SetSignBoard(BOARDTYPE type,D3DXVECTOR3 pos,D3DXCOLOR col,float fWidth,float fHeight)
{

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffSignboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBoard = 0; nCntBoard < BOARDTYPE_MAX; nCntBoard++)
	{
		if (g_aSignboard[nCntBoard].bUse == false)
		{
			g_aSignboard[nCntBoard].pos = pos;
			g_aSignboard[nCntBoard].col = col;
			g_aSignboard[nCntBoard].fHeight = fHeight;
			g_aSignboard[nCntBoard].fWidth = fWidth;
			g_aSignboard[nCntBoard].type = type;
			g_aSignboard[nCntBoard].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos.x = -fWidth;
			pVtx[0].pos.y = fHeight;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = fWidth;
			pVtx[1].pos.y = fHeight;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -fWidth;
			pVtx[2].pos.y = -fHeight;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = fWidth;
			pVtx[3].pos.y = -fHeight;
			pVtx[3].pos.z = 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffSignboard->Unlock();
}

//*****************************
// ボードの設定
//*****************************
SIGNBOARD* GetSignBoard(void)
{
	return &g_aSignboard[0];
}

int GetSignBoardContllore(void)
{
	return nSignBoardIdx;
}