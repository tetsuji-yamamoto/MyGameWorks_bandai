#include "snowBall.h"
#include "bullet.h"
#include "block.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureSB[SNOWBALLTYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSB = NULL;				// 頂点バッファへのポインタ
SNOWBALL_UI_MANAGER g_aSBUIMane[MAX_SB_POLIGON];			// 雪玉管理情報

//*********************************************************
// 雪玉の初期化
//*********************************************************
void InitSB(void)
{
	int nCnt;

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_SNOW_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_SNOW]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_SNOW_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_SNOW_MIDIUM]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_SNOW_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_SNOW_BIG]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_ICE_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_ICE]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\bullet\\SBS_BULLET_GRAVEL_001.png",
		&g_aPTextureSB[SNOWBALLTYPE_GRAVEL]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SB_POLIGON, // 必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSB,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffSB->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
	{
		g_aSBUIMane[nCnt].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aSBUIMane[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_MAX;
		g_aSBUIMane[nCnt].bUse = false;

		g_aSBUIMane[nCnt].rect.bottom = (long)0.0f;
		g_aSBUIMane[nCnt].rect.left = (long)0.0f;
		g_aSBUIMane[nCnt].rect.right = (long)0.0f;
		g_aSBUIMane[nCnt].rect.top = (long)0.0f;

		// 頂点座標の設定
		pVtx[0].pos = g_aSBUIMane[nCnt].pos;
		pVtx[1].pos = g_aSBUIMane[nCnt].pos;
		pVtx[2].pos = g_aSBUIMane[nCnt].pos;
		pVtx[3].pos = g_aSBUIMane[nCnt].pos;

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_aSBUIMane[nCnt].col;
		pVtx[1].col = g_aSBUIMane[nCnt].col;
		pVtx[2].col = g_aSBUIMane[nCnt].col;
		pVtx[3].col = g_aSBUIMane[nCnt].col;

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffSB->Unlock();
}

//*********************************************************
// 雪玉の終了
//*********************************************************
void UninitSB(void)
{
	int nCnt = 0;
	for (nCnt = 0; nCnt < SNOWBALLTYPE_MAX; nCnt++)
	{// テクスチャへのポインタ破棄
		if (g_aPTextureSB[nCnt] != NULL)
		{
			g_aPTextureSB[nCnt]->Release();	
			g_aPTextureSB[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffSB != NULL)
	{// 頂点バッファへのポインタ破棄
		g_pVtxBuffSB->Release();
		g_pVtxBuffSB = NULL;
	}
}

//*********************************************************
// 雪玉の更新
//*********************************************************
void UpdateSB(void)
{
	
}

//*********************************************************
// 雪玉の描画
//*********************************************************
void DrawSB(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSB, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
	{
 		if (g_aSBUIMane[nCnt].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureSB[g_aSBUIMane[nCnt].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				4 * nCnt,								// 描画する最初の頂点インデックス
				2);										// 描画するプリミティブ数
		}
	}
}

//*********************************************************
// 雪玉UIの設定
//*********************************************************
void SetSBUI(int nType, int nCntOrder)
{
	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	if (nCntOrder != -1)
	{
		// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
		g_pVtxBuffSB->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
		{
			if (g_aSBUIMane[nCnt].bUse == false)
			{
				float fRadius = 20.0f;
				g_aSBUIMane[nCnt].pos.z = 0.0f;
				g_aSBUIMane[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0);
				g_aSBUIMane[nCnt].nType = nType;
				g_aSBUIMane[nCnt].bUse = true;

				switch (nType)
				{
				case BULLETTYPE_SNOW:	// 雪玉
					g_aSBUIMane[nCnt].pos.x = 20.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_SNOW;
					break;

				case BULLETTYPE_SNOW_MEDIUM:	// 雪玉中くらい
					g_aSBUIMane[nCnt].pos.x = 20.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_SNOW_MIDIUM;
					fRadius *= 1.5f;
					break;

				case BULLETTYPE_SNOW_BIG:// 大玉
					g_aSBUIMane[nCnt].pos.x = 20.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_SNOW_BIG;
					fRadius *= 2.0f;
					break;

				case BULLETTYPE_ICE:// 氷玉
					g_aSBUIMane[nCnt].pos.x = 60.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_ICE;
					break;

				case BULLETTYPE_GRAVEL:// 砂利玉
					g_aSBUIMane[nCnt].pos.x = 100.0f;
					g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * (float)nCntOrder);
					g_aSBUIMane[nCnt].nType = SNOWBALLTYPE_GRAVEL;
					break;
				}

				g_aSBUIMane[nCnt].rect.bottom = (long)fRadius;
				g_aSBUIMane[nCnt].rect.left = (long)-fRadius;
				g_aSBUIMane[nCnt].rect.right = (long)fRadius;
				g_aSBUIMane[nCnt].rect.top = (long)-fRadius;

				// 頂点座標の設定
				pVtx[0].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.left;
				pVtx[0].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.top;
				pVtx[0].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

				pVtx[1].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.right;
				pVtx[1].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.top;
				pVtx[1].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

				pVtx[2].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.left;
				pVtx[2].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.bottom;
				pVtx[2].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

				pVtx[3].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.right;
				pVtx[3].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.bottom;
				pVtx[3].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;
				break;
			}
			pVtx += 4;
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffSB->Unlock();
}

//*********************************************************
// 雪玉の終わり
//*********************************************************
void EndSBUI(SNOWBALL* pSnowBall, int nType)
{
	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffSB->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
	{
		if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == nType)
		{
			g_aSBUIMane[nCnt].bUse = false;
			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffSB->Unlock();

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffSB->Lock(0, 0, (void**)&pVtx, 0);

	int nCntOrder = 0;

	for (int nCnt = 0; nCnt < MAX_SB_POLIGON; nCnt++)
	{
		
		switch (nType)
		{
		case BULLETTYPE_SNOW:	// 雪玉
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nSnowOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;

		case BULLETTYPE_SNOW_MEDIUM:	// 雪玉中くらい
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nSnowOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;

		case BULLETTYPE_SNOW_BIG:// 大玉
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nSnowOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;

		case BULLETTYPE_ICE:	// 氷玉
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nIceOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;

		case BULLETTYPE_GRAVEL:	// 砂利玉
			if (g_aSBUIMane[nCnt].bUse == true && g_aSBUIMane[nCnt].nType == pSnowBall->nGravelOrder[nCntOrder])
			{
				g_aSBUIMane[nCnt].pos.y = (SCREEN_HEIGHT * 0.6f) - (40.0f * nCntOrder);
				nCntOrder++;
			}
			break;
		}
		

		// 頂点座標の設定
		pVtx[0].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.left;
		pVtx[0].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.top;
		pVtx[0].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

		pVtx[1].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.right;
		pVtx[1].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.top;
		pVtx[1].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

		pVtx[2].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.left;
		pVtx[2].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.bottom;
		pVtx[2].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;

		pVtx[3].pos.x = g_aSBUIMane[nCnt].pos.x + g_aSBUIMane[nCnt].rect.right;
		pVtx[3].pos.y = g_aSBUIMane[nCnt].pos.y + g_aSBUIMane[nCnt].rect.bottom;
		pVtx[3].pos.z = g_aSBUIMane[nCnt].pos.z + 0.0f;
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffSB->Unlock();
}

//*********************************************************
// 雪玉作るよ
//*********************************************************
int MakeOrderSnowBall(SNOWBALL *pSnowBall,int *nType)
{
	bool bSet = false;
	bool bMakeBall = false;
	int nCnt = 0;
	int nSnoOll = pSnowBall->nMakeTimerSnow + pSnowBall->nMakeTimerSnowMidi + pSnowBall->nMakeTimerSnowBig;	// 雪玉の作った時間

	if (nSnoOll >= SB_MAKETIMER_SNOW)
	{// 雪玉
		*nType = BULLETTYPE_SNOW;
		bMakeBall = true;	// 作った
	}

	if (nSnoOll >= SB_MAKETIMER_SNOW_MIDI)
	{// 雪玉中
		*nType = BULLETTYPE_SNOW_MEDIUM;
		bMakeBall = true;	// 作った
	}

	if (nSnoOll >= SB_MAKETIMER_SNOW_BIG)
	{// 雪玉大
		*nType = BULLETTYPE_SNOW_BIG;
		bMakeBall = true;	// 作った
	}

	if (pSnowBall->nMakeTimerIce >= SB_MAKETIMER_ICE)
	{// 氷玉
		*nType = BULLETTYPE_ICE;
		bMakeBall = true;	// 作った
	}

	if (pSnowBall->nMakeTimerIGravel >= SB_MAKETIMER_GRAVEL)
	{// 砂利玉
		*nType = BULLETTYPE_GRAVEL;
		bMakeBall = true;	// 作った
	}

	if (bMakeBall == false)
	{// 作れてない
		*nType = -1;
	}

	for (nCnt = 0; nCnt < 10; nCnt++)
	{
		if (*nType == -1)
		{// カウント不十分、タイプがなかったら
			nCnt = -1;
			break;
		}

		switch (*nType)
		{
		case BULLETTYPE_SNOW:	// 雪玉
			if (pSnowBall->nSnowOrder[nCnt] == -1)
			{
				pSnowBall->nSnowOrder[nCnt] = BULLETTYPE_SNOW;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_SNOW;
				bSet = true;	// 見つけた
			}
			break;

		case BULLETTYPE_SNOW_MEDIUM:	// 雪玉中くらい
			if (pSnowBall->nSnowOrder[nCnt] == -1)
			{
				pSnowBall->nSnowOrder[nCnt] = BULLETTYPE_SNOW_MEDIUM;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_SNOW_MIDIUM;
				bSet = true;	// 見つけた
			}
			break;

		case BULLETTYPE_SNOW_BIG:// 大玉
			if (pSnowBall->nSnowOrder[nCnt] == -1)
			{
				pSnowBall->nSnowOrder[nCnt] = BULLETTYPE_SNOW_BIG;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_SNOW_BIG;
				bSet = true;	// 見つけた
			}
			break;

		case BULLETTYPE_ICE:	// 氷玉
			if (pSnowBall->nIceOrder[nCnt] == -1)
			{
				pSnowBall->nIceOrder[nCnt] = BULLETTYPE_ICE;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_ICE;
				bSet = true;	// 見つけた
			}
			break;

		case BULLETTYPE_GRAVEL:	// 砂利玉
			if (pSnowBall->nGravelOrder[nCnt] == -1)
			{
				pSnowBall->nGravelOrder[nCnt] = BULLETTYPE_GRAVEL;
				pSnowBall->nSnowBallWeight += SB_WEIGHT_GRAVEL;
				bSet = true;	// 見つけた
			}
			break;
		}

		if (bSet)
		{// セットし終わったよ
			break;
		}
	}

	if (bSet == false)
	{// セットし終わったよ
		nCnt = -1;
	}

	return nCnt;
}

//*********************************************************
// 雪玉作るよ
//*********************************************************
int BreakOrderSnowBall(SNOWBALL* pSnowBall, int nType)
{
	int nBallType = -1;

	// 一番古いやつを使って
	switch (nType)
	{
	case BULLETTYPE_SNOW:	// 雪玉
		if (pSnowBall->nSnowOrder[0] != -1)
		{// なんかあったら
			nBallType = pSnowBall->nSnowOrder[0];			// 保存されたタイプを代入
			pSnowBall->nSnowOrder[0] = -1;					// なくす
		}
		break;

	case BULLETTYPE_ICE:	// 氷玉
		if (pSnowBall->nIceOrder[0] != -1)
		{// なんかあったら
			nBallType = pSnowBall->nIceOrder[0];			// 保存されたタイプを代入
			pSnowBall->nIceOrder[0] = -1;					// なくす
		}
		break;

	case BULLETTYPE_GRAVEL:	// 砂利玉
		if (pSnowBall->nGravelOrder[0] != -1)
		{// なんかあったら
			nBallType = pSnowBall->nGravelOrder[0];			// 保存されたタイプを代入
			pSnowBall->nGravelOrder[0] = -1;				// なくす
		}
		break;
	}

	if (nBallType != -1)
	{
		// 重さ減らしましょ
		switch (nBallType)
		{
		case BULLETTYPE_SNOW:	// 雪玉
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_SNOW;	// 重さ減らす
			break;

		case BULLETTYPE_SNOW_MEDIUM:	// 中玉
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_SNOW_MIDIUM;	// 重さ減らす
			break;

		case BULLETTYPE_SNOW_BIG:	// 雪玉
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_SNOW_BIG;	// 重さ減らす
			break;

		case BULLETTYPE_ICE:	// 氷玉
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_ICE;	// 重さ減らす
			break;

		case BULLETTYPE_GRAVEL:	// 砂利玉
			pSnowBall->nSnowBallWeight -= SB_WEIGHT_GRAVEL;	// 重さ減らす
			break;
		}

		// 並べ直し
		for (int nCnt = 1; nCnt < 12; nCnt++)
		{
			switch (nType)
			{
			case BULLETTYPE_SNOW:	// 雪玉
				pSnowBall->nSnowOrder[nCnt - 1] = pSnowBall->nSnowOrder[nCnt];
				break;

			case BULLETTYPE_SNOW_MEDIUM:	// 中玉
				pSnowBall->nSnowOrder[nCnt - 1] = pSnowBall->nSnowOrder[nCnt];
				break;

			case BULLETTYPE_SNOW_BIG:	// 大玉
				pSnowBall->nSnowOrder[nCnt - 1] = pSnowBall->nSnowOrder[nCnt];
				break;

			case BULLETTYPE_ICE:	// 氷玉
				pSnowBall->nIceOrder[nCnt - 1] = pSnowBall->nIceOrder[nCnt];
				break;

			case BULLETTYPE_GRAVEL:	// 砂利玉
				pSnowBall->nGravelOrder[nCnt - 1] = pSnowBall->nGravelOrder[nCnt];
				break;
			}
		}
	}

	// 結果を返す
	return nBallType;
}

//*********************************************************
// 雪玉作る時間計測
//*********************************************************
void MakeSnowBall(SNOWBALL* pSnowBall,int nMakeType)
{
	//if (nMakeType != pSnowBall->nMakeType)
	//{// 作ってる種類違ったら
	//	pSnowBall->nMakeType = nMakeType;	// メイクタイプ変更
	//	pSnowBall->nMakeTimer = 0;			// カウントリセット
	//}

	//pSnowBall->nMakeTimer++;	// カウント追加
}