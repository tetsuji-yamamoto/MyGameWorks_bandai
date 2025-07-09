#include "effect.h"
#include "main.h"
#include "player.h"
#include "sword.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureEffect = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT];						//エフェクトの情報

//------------------
//エフェクトの初期化処理
//------------------
void InitEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\EFFECT\\effect000.jpg",
		&g_aPTextureEffect);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//エフェクトの情報の初期化
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].vertex.BottomLeft = D3DXVECTOR2(0.0f,0.0f);
		g_aEffect[nCntEffect].vertex.BottomRight = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[nCntEffect].vertex.TopLeft = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[nCntEffect].vertex.TopRight = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].fPullRadius = 0.0f;
		g_aEffect[nCntEffect].fPullmove = 0.0f;
		g_aEffect[nCntEffect].fMultiAlpha = 0.0f;
		g_aEffect[nCntEffect].fLife = 0.0f;
		g_aEffect[nCntEffect].fLength = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].bUse = false;

		pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - 100.0f;
		pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - 25.0f;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + 100.0f;
		pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - 25.0f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - 100.0f;
		pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + 25.0f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + 100.0f;
		pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + 25.0f;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f
			;
		//頂点カラーの設定
		pVtx[0].col = g_aEffect[nCntEffect].col;
		pVtx[1].col = g_aEffect[nCntEffect].col;
		pVtx[2].col = g_aEffect[nCntEffect].col;
		pVtx[3].col = g_aEffect[nCntEffect].col;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを四つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}
//-------------
//エフェクトの終了処理
//-------------
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_aPTextureEffect != NULL)
	{
		g_aPTextureEffect->Release();
		g_aPTextureEffect = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//-------------------
//エフェクトの更新処理
//--------------------
void UpdateEffect(void)
{
	int nCntEffect;

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//エフェクトが使用されている

			switch (g_aEffect[nCntEffect].nType)
			{
				//通常
			case EFFECTTYPE_NOMAL:
				//寿命減少
				g_aEffect[nCntEffect].fLife -= 1.0f;

				//アルファ値減少
				g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fMultiAlpha;

				//移動量を更新
				g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
				g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

				//ポリゴンサイズ減少
				g_aEffect[nCntEffect].fRadius += g_aEffect[nCntEffect].fRadius * -1 * g_aEffect[nCntEffect].fPullRadius;

				//移動量減少
				g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullmove;
				g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullmove;

				//頂点座標の設定
				pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
				pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
				pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
				pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
				pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
				pVtx[3].pos.z = 0.0f;

				//頂点カラーの設定
				pVtx[0].col = g_aEffect[nCntEffect].col;
				pVtx[1].col = g_aEffect[nCntEffect].col;
				pVtx[2].col = g_aEffect[nCntEffect].col;
				pVtx[3].col = g_aEffect[nCntEffect].col;
					break;

				//雷
			case EFFECTTYPE_THUNDER:
				UpdataThunderEffect(nCntEffect);
				break;

				//ビームソード
			case EFFECTTYPE_BEAMSWORD:
				UpdataBeamSwordEffect(nCntEffect);
					break;

				//ビーム
			case EFFECTTYPE_BEAM:
				UpdataBeamEffect(nCntEffect);
				break;

				//攻撃判定あり
			case EFFECTTYPE_ATTACK:
				UpDateAttackEffect(nCntEffect);
				break;

			default:
				break;
			}
			
		}
		
		if (g_aEffect[nCntEffect].fLife <= 0.0f)//寿命が尽きた
		{
			g_aEffect[nCntEffect].bUse = false;//使用していない状態にする
		}
		pVtx += 4;//頂点データのポインタを四つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}
//--------------------
//エフェクトの描画処理
//--------------------
void DrawEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//エフェクトの描画
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//エフェクトが使用されている
				//テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureEffect);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntEffect,							//描画する最初の頂点インデックス
				2);
		}
	}
	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================
//エフェクトの設定処理
//============================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,int nType, float fRadius, float fHeight, float fWidth, float fPullRadius, float fPullmove, float fLife,float fLot, int nDeleetType)
{
	int nCntEffect;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//エフェクトが使用されていない
			g_aEffect[nCntEffect].vertex.BottomLeft = D3DXVECTOR2(fWidth, fHeight);
			g_aEffect[nCntEffect].vertex.BottomRight = D3DXVECTOR2(fWidth, fHeight);
			g_aEffect[nCntEffect].vertex.TopLeft = D3DXVECTOR2(fWidth, fHeight);
			g_aEffect[nCntEffect].vertex.TopRight = D3DXVECTOR2(fWidth, fHeight);
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].nType = nType;
			g_aEffect[nCntEffect].nDeleetType = nDeleetType;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].fHeight = fHeight;
			g_aEffect[nCntEffect].fWidth = fWidth;
			g_aEffect[nCntEffect].fPullRadius = fPullRadius;
			g_aEffect[nCntEffect].fPullmove = fPullmove;
			g_aEffect[nCntEffect].fLife = fLife;
			g_aEffect[nCntEffect].fLot = fLot;
			g_aEffect[nCntEffect].bUse = true;//使用している状態にする

			g_aEffect[nCntEffect].fMultiAlpha = g_aEffect[nCntEffect].col.a * (1 / g_aEffect[nCntEffect].fLife);

			g_aEffect[nCntEffect].fAngle = atan2f(g_aEffect[nCntEffect].fHeight, g_aEffect[nCntEffect].fWidth);
			g_aEffect[nCntEffect].fLength = sqrtf((g_aEffect[nCntEffect].fWidth * g_aEffect[nCntEffect].fWidth) + (g_aEffect[nCntEffect].fHeight * g_aEffect[nCntEffect].fHeight));

			//頂点座用の設定
			pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius ;
			pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius ;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius ;
			pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius ;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius ;
			pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius ;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius ;
			pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius ;
			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;
			break;
		}
		pVtx += 4;//頂点データのポインタを四つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//============================================
//ビームソードエフェクトの更新
//============================================
void UpdataBeamSwordEffect(int nCntEffect)
{
	//プレイヤー取得
	Player* pPlayer = GetPlayer();
	//剣取得
	SWORD* pSword = GetSword();

	float fAngle = 0.0f;
	float fLength = 0.0f;
	float fLot = 0.0f;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEffect;

	g_aEffect[nCntEffect].pos = pSword->pos;

	fAngle = atan2f(g_aEffect[nCntEffect].fHeight, g_aEffect[nCntEffect].fWidth);
	fLength = sqrtf((g_aEffect[nCntEffect].fWidth * g_aEffect[nCntEffect].fWidth) + (g_aEffect[nCntEffect].fHeight * g_aEffect[nCntEffect].fHeight));

	if (pPlayer->bDirection == false)
	{//左向き
		pSword->pos.x = pPlayer->pos.x - pSword->fPositionX;	//位置X
		fLot = pSword->fLot * -1.0f;							//向き
	}
	else if (pPlayer->bDirection == true)
	{//右向き
		pSword->pos.x = pPlayer->pos.x + pSword->fPositionX;	//位置X
		fLot = pSword->fLot;									//向き
	}

	g_aEffect[nCntEffect].vertex.TopLeft.x = sinf(-D3DX_PI * 0.5f + fAngle - fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopLeft.y = cosf(D3DX_PI * 0.5f + fAngle - fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopRight.x = sinf(D3DX_PI * 0.5f + fAngle + fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopRight.y = cosf(D3DX_PI * 0.5f + fAngle + fLot) * fLength;
	g_aEffect[nCntEffect].vertex.BottomLeft.x = sinf(-D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomLeft.y = cosf(-D3DX_PI * 0.5 + fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomRight.x = sinf(D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomRight.y = cosf(-D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;

	//頂点座標の設定
	pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.TopLeft.x;;
	pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.TopLeft.y;;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.TopRight.x;
	pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.TopRight.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.BottomLeft.x;
	pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.BottomLeft.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.BottomRight.x;
	pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.BottomRight.y;
	pVtx[3].pos.z = 0.0f;

	//頂点カラーの設定
	pVtx[0].col = g_aEffect[nCntEffect].col;
	pVtx[1].col = g_aEffect[nCntEffect].col;
	pVtx[2].col = g_aEffect[nCntEffect].col;
	pVtx[3].col = g_aEffect[nCntEffect].col;

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//============================================
//攻撃エフェクトの更新
//============================================
void UpDateAttackEffect(int nCntEffect)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEffect;

	//寿命減少
	g_aEffect[nCntEffect].fLife -= 1.0f;

	//アルファ値減少
	g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fMultiAlpha;

	//移動量を更新
	g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
	g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

	//ポリゴンサイズ減少
	g_aEffect[nCntEffect].fRadius += g_aEffect[nCntEffect].fRadius * -1 * g_aEffect[nCntEffect].fPullRadius;

	//移動量減少
	g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullmove;
	g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullmove;

	//頂点座標の設定
	pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
	pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
	pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
	pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
	pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
	pVtx[3].pos.z = 0.0f;

	//頂点カラーの設定
	pVtx[0].col = g_aEffect[nCntEffect].col;
	pVtx[1].col = g_aEffect[nCntEffect].col;
	pVtx[2].col = g_aEffect[nCntEffect].col;
	pVtx[3].col = g_aEffect[nCntEffect].col;

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//============================================
//エフェクトを消す
//============================================
void EndEffect(int nType, int nDeleetType)
{
	int nCntEffect;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true && g_aEffect[nCntEffect].nType == nType && g_aEffect[nCntEffect].nDeleetType == nDeleetType)
		{//エフェクトが使用されていない
			g_aEffect[nCntEffect].bUse = false;
		}
		pVtx += 4;//頂点データのポインタを四つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//============================================
//ビームエフェクトの更新
//============================================
void UpdataBeamEffect(int nCntEffect)
{
	//プレイヤー取得
	Player* pPlayer = GetPlayer();
	//剣取得
	SWORD* pSword = GetSword();

	float fAngle = 0.0f;
	float fLength = 0.0f;
	float fLot = 0.0f;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEffect;

	//寿命減少
	g_aEffect[nCntEffect].fLife -= 1.0f;

	//アルファ値減少
	g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fMultiAlpha;

	//移動量を更新
	g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
	g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

	//移動量減少
	g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullmove;
	g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullmove;

	fAngle = g_aEffect[nCntEffect].fAngle;
	fLength = g_aEffect[nCntEffect].fLength;
	fLot = g_aEffect[nCntEffect].fLot;

	g_aEffect[nCntEffect].vertex.TopLeft.x = sinf(-D3DX_PI * 0.5f + fAngle - fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopLeft.y = cosf(D3DX_PI * 0.5f + fAngle - fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopRight.x = sinf(D3DX_PI * 0.5f + fAngle + fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopRight.y = cosf(D3DX_PI * 0.5f + fAngle + fLot) * fLength;
	g_aEffect[nCntEffect].vertex.BottomLeft.x = sinf(-D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomLeft.y = cosf(-D3DX_PI * 0.5 + fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomRight.x = sinf(D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomRight.y = cosf(-D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;

	//頂点座標の設定
	pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.TopLeft.x;
	pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.TopLeft.y;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.TopRight.x;
	pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.TopRight.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.BottomLeft.x;
	pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.BottomLeft.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.BottomRight.x;
	pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.BottomRight.y;
	pVtx[3].pos.z = 0.0f;

	//頂点カラーの設定
	pVtx[0].col = g_aEffect[nCntEffect].col;
	pVtx[1].col = g_aEffect[nCntEffect].col;
	pVtx[2].col = g_aEffect[nCntEffect].col;
	pVtx[3].col = g_aEffect[nCntEffect].col;

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//============================================
//雷の更新
//============================================
void UpdataThunderEffect(int nCntEffect)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEffect;

	//寿命減少
	g_aEffect[nCntEffect].fLife -= 1.0f;

	//アルファ値減少
	g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fMultiAlpha;

	//移動量を更新
	g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
	g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

	//ポリゴンサイズ減少
	g_aEffect[nCntEffect].fRadius += g_aEffect[nCntEffect].fRadius * -1 * g_aEffect[nCntEffect].fPullRadius;

	//移動量減少
	g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullmove;
	g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullmove;

	//頂点座標の設定
	pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
	pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
	pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
	pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
	pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
	pVtx[3].pos.z = 0.0f;

	//頂点カラーの設定
	pVtx[0].col = g_aEffect[nCntEffect].col;
	pVtx[1].col = g_aEffect[nCntEffect].col;
	pVtx[2].col = g_aEffect[nCntEffect].col;
	pVtx[3].col = g_aEffect[nCntEffect].col;

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}