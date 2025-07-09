#include "explosion.h"
#include "camera.h"
#include "particle.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pVtxTexturExplosion = NULL;		// テクスチャのポインタ
EXPLOSION g_aExplosion[MAX_EXPOLOSION];					// 爆発

//**************************************
// 爆発の初期化
//**************************************
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPOLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\billboard\\explosion000.png",
		&g_pVtxTexturExplosion);

	// 頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EXPOLOSION; nCntEX++)
	{
		g_aExplosion[nCntEX].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_aExplosion[nCntEX].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntEX].bUse = false;

		// 頂点座標の設定
		pVtx[0].pos.x = -20.0f;
		pVtx[0].pos.y = 20.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = 20.0f;
		pVtx[1].pos.y = 20.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -20.0f;
		pVtx[2].pos.y = -20.0f;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = 20.0f;
		pVtx[3].pos.y = -20.0f;
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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

//*****************************
// 爆発の破棄
//*****************************
void UninitExplosion(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	// テクスチャの破棄
	if (g_pVtxTexturExplosion != NULL)
	{
		g_pVtxTexturExplosion->Release();
		g_pVtxTexturExplosion = NULL;
	}
}

//*****************************
// 爆発の更新
//*****************************
void UpdateExplosion(void)
{

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EXPOLOSION; nCntEX++)
	{
		if (g_aExplosion[nCntEX].bUse == true)
		{
			g_aExplosion[nCntEX].nCntTime++;

			if (g_aExplosion[nCntEX].nCntTime >= 5)
			{// タイマー
				g_aExplosion[nCntEX].nCntTime = 0;
				g_aExplosion[nCntEX].nCntPtn++;

				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f * g_aExplosion[nCntEX].nCntPtn, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntEX].nCntPtn, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + 0.125f * g_aExplosion[nCntEX].nCntPtn, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f * g_aExplosion[nCntEX].nCntPtn, 1.0f);

				if (g_aExplosion[nCntEX].nCntPtn >= 8)
				{// 枚数超えたら
					// テクスチャ座標の設定
					g_aExplosion[nCntEX].bUse = false;
				}
			}
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

//*****************************
// 爆発の描画
//*****************************
void DrawExplosion(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	for (int nCntEX = 0; nCntEX < MAX_EXPOLOSION; nCntEX++)
	{
		if (g_aExplosion[nCntEX].bUse == true)
		{// 使ってたら
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCntEX].mtxWorld);

			// ビューマトリックス取得
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// カメラの逆行列を設定
			g_aExplosion[nCntEX].mtxWorld._11 = mtxview._11;
			g_aExplosion[nCntEX].mtxWorld._12 = mtxview._21;
			g_aExplosion[nCntEX].mtxWorld._13 = mtxview._31;
			g_aExplosion[nCntEX].mtxWorld._21 = mtxview._12;
			g_aExplosion[nCntEX].mtxWorld._22 = mtxview._22;
			g_aExplosion[nCntEX].mtxWorld._23 = mtxview._32;
			g_aExplosion[nCntEX].mtxWorld._31 = mtxview._13;
			g_aExplosion[nCntEX].mtxWorld._32 = mtxview._23;
			g_aExplosion[nCntEX].mtxWorld._33 = mtxview._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntEX].pos.x, g_aExplosion[nCntEX].pos.y, g_aExplosion[nCntEX].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntEX].mtxWorld, &g_aExplosion[nCntEX].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntEX].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pVtxTexturExplosion);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// 爆発の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEX, 2);
		}
	}

	// アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//*****************************
// 爆発の設定
//*****************************
void SetExplosion(SETEXPLO setExplo)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEX = 0; nCntEX < MAX_EXPOLOSION; nCntEX++)
	{
		if (g_aExplosion[nCntEX].bUse == false)
		{
			g_aExplosion[nCntEX].pos = setExplo.pos;
			g_aExplosion[nCntEX].nCntPtn = 0;
			g_aExplosion[nCntEX].nCntTime = 0;
			g_aExplosion[nCntEX].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos.x = -setExplo.size.x;
			pVtx[0].pos.y = setExplo.size.y;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = setExplo.size.x;
			pVtx[1].pos.y = setExplo.size.y;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -setExplo.size.x;
			pVtx[2].pos.y = -setExplo.size.y;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = setExplo.size.x;
			pVtx[3].pos.y = -setExplo.size.y;
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

			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}