#include "shadow.h"
#include "block.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturShadow = NULL;		// テクスチャのポインタ
Shadow g_aShadow[MAX_SHADOW];						// 影の情報

//**************************************
// 影の初期化
//**************************************
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\shadow\\shadow000.jpg",
		&g_pVtxTexturShadow);

	// 頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aShadow[nCntShadow].col = D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f);
		g_aShadow[nCntShadow].branding = false;
		g_aShadow[nCntShadow].bUse = false;

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
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = g_aShadow[nCntShadow].col;
		pVtx[1].col = g_aShadow[nCntShadow].col;
		pVtx[2].col = g_aShadow[nCntShadow].col;
		pVtx[3].col = g_aShadow[nCntShadow].col;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}

//**************************************************************************************
// 影の破棄
//**************************************************************************************
void UninitShadow(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturShadow != NULL)
	{
		g_pVtxTexturShadow->Release();
		g_pVtxTexturShadow = NULL;
	}
}

//**************************************************************************************
// 影の更新
//**************************************************************************************
void UpdateShadow(void)
{

}

//**************************************************************************************
// 影の描画
//**************************************************************************************
void DrawShadow(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// 減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true && g_aShadow[nCntShadow].branding == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pVtxTexturShadow);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 影の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntShadow,
				2);
		}
	}

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// 設定をを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//**************************************************************************************
// 影の設定
//**************************************************************************************
int SetShadw(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fWidth)
{
	int nCntShadow = 0;

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;
			g_aShadow[nCntShadow].fWidth = fWidth;

			// 頂点座標の設定
			pVtx[0].pos.x = -fWidth;
			pVtx[0].pos.y = pos.y;
			pVtx[0].pos.z = fWidth;

			pVtx[1].pos.x = fWidth;
			pVtx[1].pos.y = pos.y;
			pVtx[1].pos.z = fWidth;

			pVtx[2].pos.x = -fWidth;
			pVtx[2].pos.y = pos.y;
			pVtx[2].pos.z = -fWidth;

			pVtx[3].pos.x = fWidth;
			pVtx[3].pos.y = pos.y;
			pVtx[3].pos.z = -fWidth;

			break;
		}

		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();

	return nCntShadow;
}

//**************************************************************************************
// 影の位置の更新処理
//**************************************************************************************
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	VERTEX_3D* pVtx = NULL;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXCOLOR col = g_aShadow[nIdxShadow].col;
	float fMaguA;
	float fMaguB;

	// 頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nIdxShadow;

	g_aShadow[nIdxShadow].pos.x = pos.x;
	g_aShadow[nIdxShadow].pos.y -= 30.0f;
	g_aShadow[nIdxShadow].pos.z = pos.z;

	g_aShadow[nIdxShadow].branding = false;	// 乗ってない

	if (CollisionBlock(&g_aShadow[nIdxShadow].pos, &pos, &move))
	{
		g_aShadow[nIdxShadow].branding = true;	// 乗ってる
		fMaguA = pos.y / g_aShadow[nIdxShadow].pos.y * 0.9f;
		fMaguB = g_aShadow[nIdxShadow].pos.y / pos.y;

		// 頂点座標の設定
		pVtx[0].pos.x = -g_aShadow[nIdxShadow].fWidth * fMaguA;
		pVtx[0].pos.y = 0.1f;
		pVtx[0].pos.z = g_aShadow[nIdxShadow].fWidth * fMaguA;

		pVtx[1].pos.x = g_aShadow[nIdxShadow].fWidth * fMaguA;
		pVtx[1].pos.y = 0.1f;
		pVtx[1].pos.z = g_aShadow[nIdxShadow].fWidth * fMaguA;

		pVtx[2].pos.x = -g_aShadow[nIdxShadow].fWidth * fMaguA;
		pVtx[2].pos.y = 0.1f;
		pVtx[2].pos.z = -g_aShadow[nIdxShadow].fWidth * fMaguA;

		pVtx[3].pos.x = g_aShadow[nIdxShadow].fWidth * fMaguA;
		pVtx[3].pos.y = 0.1f;
		pVtx[3].pos.z = -g_aShadow[nIdxShadow].fWidth * fMaguA;

		col.r = g_aShadow[nIdxShadow].col.r * fMaguB;
		col.g = g_aShadow[nIdxShadow].col.g * fMaguB;
		col.b = g_aShadow[nIdxShadow].col.b * fMaguB;
		col.a = g_aShadow[nIdxShadow].col.a * fMaguB;

		if (col.a <= 0.1f)
		{
			col.a = 0.0f;
		}

		// 頂点カラーの設定
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}

//**************************************************************************************
// 影の位置の更新処理
//**************************************************************************************
void EndShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}