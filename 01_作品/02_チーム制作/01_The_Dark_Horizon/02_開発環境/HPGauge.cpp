#include "HPGauge.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHPGauge = NULL;				// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_apVtxTexturHPGauge[HPGAUGETYPE_MAX] = {};	// テクスチャのポインタ
HPGAUGE g_aHPGauge[MAX_HPGAUGE_POLIGON];	// hpゲージ情報

//*****************************************************
// HPゲージ初期化
//*****************************************************
void InitHPGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_HPGAUGE_POLIGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHPGauge, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\HPGauge_Frame_001.png",
		&g_apVtxTexturHPGauge[HPGAUGETYPE_BG]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\HPGauge_Bar_001.png",
		&g_apVtxTexturHPGauge[HPGAUGETYPE_GAUGE]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\UI\\HPGauge_Bar_001.png",
		&g_apVtxTexturHPGauge[HPGAUGETYPE_GAUGE_REDZONE]);


	// 頂点バッファをロック
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBl = 0; nCntBl < MAX_HPGAUGE_POLIGON; nCntBl++)
	{
		g_aHPGauge[nCntBl].pos = D3DXVECTOR3(1.0f,1.0f,1.0f);		// 位置
		g_aHPGauge[nCntBl].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);	// 色
		g_aHPGauge[nCntBl].type = HPGAUGETYPE_MAX;		// 種類
		g_aHPGauge[nCntBl].nIdxUI = -1;					// インデックス
		g_aHPGauge[nCntBl].fMaxWidth = 0.0f;			// 最大のおおきさ　
		g_aHPGauge[nCntBl].fWidth = 0.0f;				// 幅
		g_aHPGauge[nCntBl].fHeight = 0.0f;				// 高さ
		g_aHPGauge[nCntBl].bUse = false;				// 使ってますか

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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// HPゲージ終了
//*****************************************************
void UninitHPGauge(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffHPGauge != NULL)
	{
		g_pVtxBuffHPGauge->Release();
		g_pVtxBuffHPGauge = NULL;
	}

	for (int nCnt = 0; nCnt < HPGAUGETYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_apVtxTexturHPGauge[nCnt] != NULL)
		{
			g_apVtxTexturHPGauge[nCnt]->Release();
			g_apVtxTexturHPGauge[nCnt] = NULL;
		}
	}
}

//*****************************************************
// HPゲージ更新
//*****************************************************
void UpdateHPGauge(void)
{

}

//*****************************************************
// HPゲージ表示
//*****************************************************
void DrawHPGauge(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntBl = 0; nCntBl < MAX_HPGAUGE_POLIGON; nCntBl++)
	{
		if (g_aHPGauge[nCntBl].bUse == true)
		{// 使ってたら
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aHPGauge[nCntBl].mtxWorld);

			// ビューマトリックス取得
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// カメラの逆行列を設定
			g_aHPGauge[nCntBl].mtxWorld._11 = mtxview._11;
			g_aHPGauge[nCntBl].mtxWorld._12 = mtxview._21;
			g_aHPGauge[nCntBl].mtxWorld._13 = mtxview._31;
			g_aHPGauge[nCntBl].mtxWorld._21 = mtxview._12;
			g_aHPGauge[nCntBl].mtxWorld._22 = mtxview._22;
			g_aHPGauge[nCntBl].mtxWorld._23 = mtxview._32;
			g_aHPGauge[nCntBl].mtxWorld._31 = mtxview._13;
			g_aHPGauge[nCntBl].mtxWorld._32 = mtxview._23;
			g_aHPGauge[nCntBl].mtxWorld._33 = mtxview._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aHPGauge[nCntBl].pos.x, g_aHPGauge[nCntBl].pos.y, g_aHPGauge[nCntBl].pos.z);
			D3DXMatrixMultiply(&g_aHPGauge[nCntBl].mtxWorld, &g_aHPGauge[nCntBl].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aHPGauge[nCntBl].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffHPGauge, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_apVtxTexturHPGauge[g_aHPGauge[nCntBl].type]);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 弾の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBl, 2);
		}
	}

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************************************
// HPゲージの設定
//*****************************************************
void SetHPGauge(HPGAUGE_HAVE* pHPGaugeHave, HPGAUGETYPE type, D3DXCOLOR col,float fHeight,float fWidth,int nMaxHP)
{
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHP = 0; nCntHP < MAX_HPGAUGE_POLIGON; nCntHP++)
	{// マックス分回す
		if (g_aHPGauge[nCntHP].bUse == false)
		{// 使ってなかったら
			pHPGaugeHave->type = type;
			pHPGaugeHave->nIdxUI = nCntHP;
			pHPGaugeHave->nMaxHP = nMaxHP;

			g_aHPGauge[nCntHP].bUse = true;
			g_aHPGauge[nCntHP].nIdxUI = nCntHP;
			g_aHPGauge[nCntHP].type = type;
			g_aHPGauge[nCntHP].col = col;
			g_aHPGauge[nCntHP].fMaxWidth = fWidth;
			g_aHPGauge[nCntHP].fWidth = fWidth;
			g_aHPGauge[nCntHP].fHeight = fHeight;

			// 頂点座標の設定
			pVtx[0].pos.x = 0.0f;
			pVtx[0].pos.y = fHeight;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = fWidth;
			pVtx[1].pos.y = fHeight;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = 0.0f;
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
			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// HPゲージの位置更新
//*****************************************************
void UpdateHPGaugePos(HPGAUGE_HAVE* pHPGaugeHave,D3DXVECTOR3 pos,float fHeigt,float fSlide)
{
	if (g_aHPGauge[pHPGaugeHave->nIdxUI].bUse == false)
	{// 使ってないよ
		return;
	}

	// 位置設定
	g_aHPGauge[pHPGaugeHave->nIdxUI].pos.x = pos.x - fSlide;
	g_aHPGauge[pHPGaugeHave->nIdxUI].pos.y = pos.y + fHeigt;
	g_aHPGauge[pHPGaugeHave->nIdxUI].pos.z = pos.z;
}

//*****************************************************
// HPゲージの長さ更新
//*****************************************************
void UpdateHPGaugeWidth(HPGAUGE_HAVE* pHPGaugeHave, int nowHP)
{
	if (pHPGaugeHave->type != HPGAUGETYPE_GAUGE)
	{// ゲージじゃないよ
		return;
	}

	if (g_aHPGauge[pHPGaugeHave->nIdxUI].bUse == false)
	{// 使ってないよ
		return;
	}

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * pHPGaugeHave->nIdxUI;

	float fMagu = (float)nowHP / (float)pHPGaugeHave->nMaxHP;

	if (fMagu > 1.0f)
	{
		fMagu = 1.0f;
	}

	// 頂点座標の設定
	pVtx[0].pos.x = -0.0f;
	pVtx[0].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth * fMagu;
	pVtx[1].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth * fMagu;
	pVtx[3].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[3].pos.z = 0.0f;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// HPの赤ゲージの長さ更新
//*****************************************************
void UpdateHPGaugeRedZoneWidth(HPGAUGE_HAVE* pHPGaugeHave, int nowHP)
{
	if (pHPGaugeHave->type != HPGAUGETYPE_GAUGE_REDZONE)
	{// 赤ゲージじゃないよ
		return;
	}
	
	if (g_aHPGauge[pHPGaugeHave->nIdxUI].bUse == false)
	{// 使ってないよ
		return;
	}

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * pHPGaugeHave->nIdxUI;
	float fMagu = (float)nowHP / (float)pHPGaugeHave->nMaxHP;

	if (fMagu > 1.0f)
	{
		fMagu = 1.0f;
	}

	float fWidthEX = g_aHPGauge[pHPGaugeHave->nIdxUI].fMaxWidth * fMagu;
	float fDiffWidth = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth - fWidthEX;

	g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth -= fDiffWidth * 0.01f;

	// 頂点座標の設定
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth;
	pVtx[1].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth;
	pVtx[3].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[3].pos.z = 0.0f;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// ゲージの長さ更新
//*****************************************************
void UpdateGaugeWidth(HPGAUGE_HAVE* pHPGaugeHave, int nNowNum,bool bOrver)
{
	if (g_aHPGauge[pHPGaugeHave->nIdxUI].bUse == false)
	{// 使ってないよ
		return;
	}

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffHPGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * pHPGaugeHave->nIdxUI;

	float fMagu = (float)nNowNum / (float)pHPGaugeHave->nMaxHP;

	if (fMagu >= 1.0f && bOrver == true)
	{// オーバーしちゃダメ
		fMagu = 1.0f;
	}

	// 頂点座標の設定
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth * fMagu;
	pVtx[1].pos.y = g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aHPGauge[pHPGaugeHave->nIdxUI].fWidth * fMagu;
	pVtx[3].pos.y = -g_aHPGauge[pHPGaugeHave->nIdxUI].fHeight;
	pVtx[3].pos.z = 0.0f;

	// 頂点バッファをアンロック
	g_pVtxBuffHPGauge->Unlock();
}

//*****************************************************
// ゲージの終わり
//*****************************************************
void EndHPGauge(HPGAUGE_HAVE* pHPGaugeHave)
{
	g_aHPGauge[pHPGaugeHave->nIdxUI].bUse = false;
}
