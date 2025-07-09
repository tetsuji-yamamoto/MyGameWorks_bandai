#include "guide.h"
#include "camera.h"
#include "keyboard.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuide = NULL;	// 頂点バッファへのポインタ
D3DXMATRIX g_mtxWorldGuide;						// ワールドマトリックス
GUIDE g_aGude[OLL_VERTEX];					// ガイド線情報
GUDEMANAGER g_GuideMane;					// ガイド管理

//**************************************
// ガイドの初期化
//**************************************
void InitGuide(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * OLL_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGuide, NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffGuide->Lock(0, 0, (void**)&pVtx, 0);

	g_GuideMane.bDisplay = true;

	// 頂点座標の設定
	for (int nCnt = 0; nCnt < OLL_VERTEX; nCnt++)
	{
		g_aGude[nCnt].posguide = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGude[nCnt].rotguide = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGude[nCnt].type = GUDETYPE_MAX;
		g_aGude[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGude[nCnt].bUse = false;

		// 頂点座標
		pVtx[nCnt].pos = g_aGude[nCnt].posguide;

		// 法線
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[nCnt].col = g_aGude[nCnt].col;

		// 各頂点の法線の設定(＊ベクトルの大きさは1にする必要がある)
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	// XZ平面
	GUIDE gude;
	gude.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	float fA = (float)GUIDE_LINE_INTERVAL;
	float fAStart = fA * (float)(GUIDE_LINE_X / 2);
	float fB = (float)GUIDE_LINE_INTERVAL * (float)(GUIDE_LINE_X / 2);

	for (int nCnt = 0; nCnt <= GUIDE_LINE_X; nCnt++)
	{
		// 行
		SetGude(gude, D3DXVECTOR3(-fAStart + fA * nCnt, 0.0f, fB), D3DXVECTOR3(-fAStart + fA * nCnt, 0.0f, -fB));

		//列
		SetGude(gude, D3DXVECTOR3(fB, 0.0f, -fAStart + fA * nCnt), D3DXVECTOR3(-fB, 0.0f, -fAStart + fA * nCnt));
	}

	// X軸
	gude.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	SetGude(gude, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(100.0f, 0.0f, 0.0f));

	// Y軸
	gude.col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	SetGude(gude, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 100.0f, 0.0f));

	// Z軸
	gude.col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	SetGude(gude, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 100.0f));

	// 頂点バッファをアンロック
	g_pVtxBuffGuide->Unlock();
}

//*********************************************
// ガイドの破棄
//*********************************************
void UninitGuide(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffGuide != NULL)
	{
		g_pVtxBuffGuide->Release();
		g_pVtxBuffGuide = NULL;
	}
}

//*********************************************
// ガイドの破棄
//*********************************************
void UpdateGuide(void)
{
	if (KeyboardTrigger(DIK_F9))
	{
		g_GuideMane.bDisplay = !g_GuideMane.bDisplay;
	}
}

//*********************************************
// ガイドの描画
//*********************************************
void DrawGuide(void)
{
	if (g_GuideMane.bDisplay)
	{
		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// 計算用マトリックス
		D3DXMATRIX mtxRot, mtxTrans;

		for (int nCnt = 0; nCnt < OLL_VERTEX; nCnt++)
		{
			if (g_aGude[nCnt].bUse == true)
			{// 使ってタラ
				for (int nCntB = 0; nCntB < 2; nCntB++, nCnt++)
				{
					// ワールドマトリックスの初期化
					D3DXMatrixIdentity(&g_mtxWorldGuide);

					// 向きを反映
					D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGude[nCnt].rotguide.y, g_aGude[nCnt].rotguide.x, g_aGude[nCnt].rotguide.z);
					D3DXMatrixMultiply(&g_mtxWorldGuide, &g_mtxWorldGuide, &mtxRot);

					// 位置を反映
					D3DXMatrixTranslation(&mtxTrans, g_aGude[nCnt].posguide.x, g_aGude[nCnt].posguide.y, g_aGude[nCnt].posguide.z);
					D3DXMatrixMultiply(&g_mtxWorldGuide, &g_mtxWorldGuide, &mtxTrans);

					// ワールドマトリックスの設定
					pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldGuide);

					// 頂点バッファをデバイスのデータストリームに設定
					pDevice->SetStreamSource(0, g_pVtxBuffGuide, 0, sizeof(VERTEX_3D));

					// 頂点フォーマットの設定
					pDevice->SetFVF(FVF_VERTEX_3D);

					// ガイドの描画
					pDevice->DrawPrimitive(D3DPT_LINESTRIP, nCnt - nCntB, 1);
				}
				nCnt--;
			}

		}
	}
}

//*********************************************
// ガイドの設定
//*********************************************
void SetGude(GUIDE guide, D3DXVECTOR3 sp, D3DXVECTOR3 ep)
{
	int nCntVtx = 0;

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffGuide->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int nCnt = 0; nCnt < OLL_VERTEX; nCnt++)
	{
		if (g_aGude[nCnt].bUse == false)
		{
			// 始点
			g_aGude[nCnt].posguide = sp;
			g_aGude[nCnt].col = guide.col;
			g_aGude[nCnt].type = GUDETYPE_START;
			g_aGude[nCnt].bUse = true;

			pVtx[nCnt].pos = g_aGude[nCnt].posguide;
			pVtx[nCnt].col = g_aGude[nCnt].col;

			nCnt++;

			//終点
			g_aGude[nCnt].posguide = ep;
			g_aGude[nCnt].col = guide.col;
			g_aGude[nCnt].type = GUDETYPE_END;
			g_aGude[nCnt].bUse = true;

			pVtx[nCnt].pos = g_aGude[nCnt].posguide;
			pVtx[nCnt].col = g_aGude[nCnt].col;
			break;
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffGuide->Unlock();
}