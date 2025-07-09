#include "effect.h"
#include "camera.h"
#include "shadow.h"

// グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;						// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_MAX] = {};	// テクスチャのポインタ
EFFECT g_aEffect[MAX_EFFECT];											// エフェクト

//**************************************
// エフェクトの初期化
//**************************************
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect, NULL);

	VERTEX_3D* pVtx = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\shadow\\shadow000.jpg",
		&g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_NOMAL]);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"date\\texture\\effect\\smoke000.png",
		&g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_SMOKE]);

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].type = EFFECTTYPE_NOMAL;					// タイプ
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量
		g_aEffect[nCntEffect].gravity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 重力
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);		// 色
		g_aEffect[nCntEffect].nLife = 0;								// 寿命
		g_aEffect[nCntEffect].nMaxLife = 0;								// 寿命の最大数
		g_aEffect[nCntEffect].nCntAmin = 0;								// アニメーションカウンター
		g_aEffect[nCntEffect].nCntPttern = 0;							// アニメーションパターン
		g_aEffect[nCntEffect].fSize = 0;								// 大きさ
		g_aEffect[nCntEffect].bUse = false;								// 使ってますか？
		g_aEffect[nCntEffect].bShadow = false;							// 影ありますか？
		g_aEffect[nCntEffect].bSubtractive = true;						// 加算合成

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
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// エフェクトの破棄
//*****************************
void UninitEffect(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	for (int nCnt = 0; nCnt < EFFECT_TEXTURETYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_aPVtxTexturEffect[nCnt] != NULL)
		{
			g_aPVtxTexturEffect[nCnt]->Release();
			g_aPVtxTexturEffect[nCnt] = NULL;
		}
	}
}

//*****************************
// エフェクトの更新
//*****************************
void UpdateEffect(void)
{

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{

			switch (g_aEffect[nCntEffect].type)
			{
			case EFFECTTYPE_NOMAL:		// 通常
				break;

			case EFFECTTYPE_TRAJECTORY:	// 軌跡
				UpdateEffectTrajectory(nCntEffect, pVtx);
				break;

			case EFFECTTYPE_SMOKE:		// 煙
				UpdateEffectSmoke(nCntEffect, pVtx);
				break;

			default:
				break;
			}

			if (g_aEffect[nCntEffect].bShadow)
			{// 影ありましたら,影の位置更新
				SetPositionShadow(g_aEffect[nCntEffect].nShadowIdx, g_aEffect[nCntEffect].pos);
			}
			
			if (g_aEffect[nCntEffect].nLife <= 0)
			{// 寿命がなくなったら,使用状態を解く
				g_aEffect[nCntEffect].bUse = false;

				if (g_aEffect[nCntEffect].bShadow)
				{// 影があるならば,影を消す
					EndShadow(g_aEffect[nCntEffect].nShadowIdx);
				}
			}
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// エフェクトの描画
//*****************************
void DrawEffect(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Zの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	for (int nCntEX = 0; nCntEX < MAX_EFFECT; nCntEX++)
	{
		if (g_aEffect[nCntEX].bUse == true)
		{// 使ってたら

			

			if (g_aEffect[nCntEX].bSubtractive == false)
			{// 減算合成だったら
				// 減算合成の設定
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			switch (g_aEffect[nCntEX].type)
			{// タイプによって張るテクスチャを変える

			case EFFECTTYPE_SMOKE:		// 煙
				//αブレンディングを元に戻す
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
				break;
			}

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEX].mtxWorld);

			// ビューマトリックス取得
			D3DXMATRIX mtxview;
			pDevice->GetTransform(D3DTS_VIEW, &mtxview);

			// カメラの逆行列を設定
			g_aEffect[nCntEX].mtxWorld._11 = mtxview._11;
			g_aEffect[nCntEX].mtxWorld._12 = mtxview._21;
			g_aEffect[nCntEX].mtxWorld._13 = mtxview._31;
			g_aEffect[nCntEX].mtxWorld._21 = mtxview._12;
			g_aEffect[nCntEX].mtxWorld._22 = mtxview._22;
			g_aEffect[nCntEX].mtxWorld._23 = mtxview._32;
			g_aEffect[nCntEX].mtxWorld._31 = mtxview._13;
			g_aEffect[nCntEX].mtxWorld._32 = mtxview._23;
			g_aEffect[nCntEX].mtxWorld._33 = mtxview._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEX].pos.x, g_aEffect[nCntEX].pos.y, g_aEffect[nCntEX].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEX].mtxWorld, &g_aEffect[nCntEX].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEX].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			switch (g_aEffect[nCntEX].type)
			{// タイプによって張るテクスチャを変える
			case EFFECTTYPE_NOMAL:		// 通常
				pDevice->SetTexture(0, g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_NOMAL]);
				break;

			case EFFECTTYPE_TRAJECTORY:	// 軌跡
				pDevice->SetTexture(0, g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_NOMAL]);
				break;

			case EFFECTTYPE_SMOKE:		// 煙
				pDevice->SetTexture(0, g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_SMOKE]);
				break;

			default:
				pDevice->SetTexture(0, g_aPVtxTexturEffect[EFFECT_TEXTURETYPE_NOMAL]);
				break;
			}

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// エフェクトの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEX, 2);

			switch (g_aEffect[nCntEX].type)
			{// タイプによって張るテクスチャを変える

			case EFFECTTYPE_SMOKE:		// 煙
				// 加算合成に戻す
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
				break;
			}

			if (g_aEffect[nCntEX].bSubtractive == false)
			{// 減算合成だったら
				// 加算合成に設定
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}
		}
	}

	// Zの比較方法
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*****************************
// エフェクトの設定
//*****************************
void SetEffect(EFFECTTYPE effectType,D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 gravity, D3DXCOLOR col,int nLife, float fSize,bool bShadow,bool bSubtractive)
{
	VERTEX_3D* pVtx = NULL;
	int nCntEffect = 0;

	// 頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse)
		{
			pVtx += 4;
			continue;
		}

		g_aEffect[nCntEffect].type = effectType;	// タイプ
		g_aEffect[nCntEffect].pos = pos;			// 位置
		g_aEffect[nCntEffect].move = move;			// 移動量
		g_aEffect[nCntEffect].gravity = gravity;	// 重力
		g_aEffect[nCntEffect].col = col;			// 色
		g_aEffect[nCntEffect].nLife = nLife;		// 寿命
		g_aEffect[nCntEffect].nMaxLife = nLife;		// 寿命の最大数
		g_aEffect[nCntEffect].nCntAmin = 0;			// アニメーションカウンター
		g_aEffect[nCntEffect].nCntPttern = 0;		// アニメーションパターン
		g_aEffect[nCntEffect].fSize = fSize;		// 大きさ
		g_aEffect[nCntEffect].bUse = true;			// 使ってますか？
		g_aEffect[nCntEffect].bShadow = bShadow;	// 影ありますか？
		g_aEffect[nCntEffect].bSubtractive = bSubtractive;	// 影ありますか？

		// 頂点座標の設定
		pVtx[0].pos.x = -fSize;
		pVtx[0].pos.y = fSize;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = fSize;
		pVtx[1].pos.y = fSize;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -fSize;
		pVtx[2].pos.y = -fSize;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = fSize;
		pVtx[3].pos.y = -fSize;
		pVtx[3].pos.z = 0.0f;

		// 頂点カラーの設定
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		// テクスチャ座標の設定
		switch (effectType)
		{// タイプによって分ける
		case EFFECTTYPE_NOMAL:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;

		case EFFECTTYPE_TRAJECTORY:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;

		case EFFECTTYPE_SMOKE:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);
			break;

		default:
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}

		if (bShadow)
		{// 影を設定するならば
			g_aEffect[nCntEffect].nShadowIdx = SetShadw(pos,D3DXVECTOR3(0.0f,0.0f,0.0f),fSize);
		}

		break;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//*****************************
// 軌跡エフェクトの更新
//*****************************
void UpdateEffectTrajectory(int nCntEffect, VERTEX_3D* pVtx)
{
	g_aEffect[nCntEffect].nLife--;	// 寿命減らす
	float fMagu = (float)g_aEffect[nCntEffect].nLife / (float)g_aEffect[nCntEffect].nMaxLife;	// 寿命のの倍率を求める

	float fSizeEX = g_aEffect[nCntEffect].fSize * fMagu;	// 大きさに倍率をかける

	D3DXCOLOR colEX = g_aEffect[nCntEffect].col;	// 計算後の色 
	colEX.r *= fMagu * fMagu * fMagu;	// 色を減らす
	colEX.g *= fMagu * fMagu * fMagu;	// 色を減らす
	colEX.b *= fMagu * fMagu * fMagu;	// 色を減らす
	colEX.a *= fMagu * fMagu * fMagu;	// 色を減らす

	D3DXVECTOR3 move;
	g_aEffect[nCntEffect].move += g_aEffect[nCntEffect].gravity;
	move.x = g_aEffect[nCntEffect].move.x * fMagu;
	move.y = g_aEffect[nCntEffect].move.y * fMagu;
	move.z = g_aEffect[nCntEffect].move.z * fMagu;

	// 移動量追加
	g_aEffect[nCntEffect].pos += move;

	// 頂点座標の設定
	pVtx[0].pos.x = -fSizeEX;
	pVtx[0].pos.y = fSizeEX;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fSizeEX;
	pVtx[1].pos.y = fSizeEX;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -fSizeEX;
	pVtx[2].pos.y = -fSizeEX;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fSizeEX;
	pVtx[3].pos.y = -fSizeEX;
	pVtx[3].pos.z = 0.0f;

	// 頂点カラーの設定
	pVtx[0].col = colEX;
	pVtx[1].col = colEX;
	pVtx[2].col = colEX;
	pVtx[3].col = colEX;
}

//*****************************
// 煙エフェクトの更新
//*****************************
void UpdateEffectSmoke(int nCntEffect, VERTEX_3D* pVtx)
{
	g_aEffect[nCntEffect].nLife--;	// 寿命減らす
	float fMagu = (float)g_aEffect[nCntEffect].nLife / (float)g_aEffect[nCntEffect].nMaxLife;	// 寿命のの倍率を求める

	float fSizeEX = g_aEffect[nCntEffect].fSize * fMagu;	// 大きさに倍率をかける

	D3DXCOLOR colEX = g_aEffect[nCntEffect].col;	// 計算後の色 
	colEX.r *= fMagu * fMagu * fMagu;	// 色を減らす
	colEX.g *= fMagu * fMagu * fMagu;	// 色を減らす
	colEX.b *= fMagu * fMagu * fMagu;	// 色を減らす
	colEX.a *= fMagu * fMagu * fMagu;	// 色を減らす

	D3DXVECTOR3 move;
	g_aEffect[nCntEffect].move += g_aEffect[nCntEffect].gravity;
	move.x = g_aEffect[nCntEffect].move.x * fMagu;
	move.y = g_aEffect[nCntEffect].move.y * fMagu;
	move.z = g_aEffect[nCntEffect].move.z * fMagu;

	g_aEffect[nCntEffect].nCntAmin++;

	if (g_aEffect[nCntEffect].nCntAmin >= 10)
	{// 一定数カウントしたら
		g_aEffect[nCntEffect].nCntAmin = 0;	// カウンターリセット
		g_aEffect[nCntEffect].nCntPttern++;

		if (g_aEffect[nCntEffect].nCntPttern > 8)
		{// パターンが上限を超えたらゼロ
			g_aEffect[nCntEffect].nCntPttern = 0;
		}
	}

	// 移動量追加
	g_aEffect[nCntEffect].pos += move;

	// 頂点座標の設定
	pVtx[0].pos.x = -fSizeEX;
	pVtx[0].pos.y = fSizeEX;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fSizeEX;
	pVtx[1].pos.y = fSizeEX;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -fSizeEX;
	pVtx[2].pos.y = -fSizeEX;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fSizeEX;
	pVtx[3].pos.y = -fSizeEX;
	pVtx[3].pos.z = 0.0f;

	// 頂点カラーの設定
	pVtx[0].col = colEX;
	pVtx[1].col = colEX;
	pVtx[2].col = colEX;
	pVtx[3].col = colEX;

	// テクスチャ座標の設定
	float fTexXA = 0.125f * (float)g_aEffect[nCntEffect].nCntPttern;
	float fTexXB = 0.125f + 0.125f * (float)g_aEffect[nCntEffect].nCntPttern;
	pVtx[0].tex = D3DXVECTOR2(fTexXA, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexXB, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTexXA, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexXB, 1.0f);
}