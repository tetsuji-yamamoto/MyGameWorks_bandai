#include "charge.h"
#include "player.h"
#include "particle.h"
#include "effect.h"
#include "input.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureCharger[CHARGEUITYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharger = NULL;				//頂点バッファへのポインタ
CHARGERUI g_aChagerUI[MAX_CHARGERUI];							//充電器UIの構造体
CHARGE g_Charge;												//充電パラメーター構造体

//======================================
//充電器の初期化
//======================================
void InitCharge(void)
{
	int nCntCharger;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CHARGERUI, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharger,
		NULL);

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffCharger->Lock(0, 0, (void**)&pVtx, 0);

	g_Charge.fChargrAmount = 0;
	g_Charge.nCntTime = 0;

	//ブロックの情報の初期化
	for (nCntCharger = 0; nCntCharger < MAX_CHARGERUI; nCntCharger++)
	{
		g_aChagerUI[nCntCharger].pFileName = NULL;
		g_aChagerUI[nCntCharger].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aChagerUI[nCntCharger].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aChagerUI[nCntCharger].nType = CHARGEUITYPE_FLAME;
		g_aChagerUI[nCntCharger].nState = CHARGESTATE_NONE;
		g_aChagerUI[nCntCharger].nType = CHARGENUM_ZERO;
		g_aChagerUI[nCntCharger].fHeight = 0.0f;
		g_aChagerUI[nCntCharger].fWidth = 0.0f;
		g_aChagerUI[nCntCharger].bUse = false;

		//位置の初期化
		pVtx[0].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
		pVtx[0].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
		pVtx[1].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
		pVtx[2].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
		pVtx[3].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点データのポインタを四つ分進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCharger->Unlock();

	for (nCntCharger = 0; nCntCharger < MAX_CHARGERUI * 0.5f; nCntCharger++)
	{
		SetCharger(FILE_TEX_CHARGER_FLAME, D3DXVECTOR3(CHARGE_WIDTH + CHARGE_WIDTH * 2 * nCntCharger,SCREEN_HEIGHT - CHARGE_HEIGHT * 3.0f, 0.0f), CHARGEUITYPE_FLAME, nCntCharger, CHARGE_WIDTH);
		SetCharger(FILE_TEX_CHARGER_GAUGE, D3DXVECTOR3(CHARGE_WIDTH + CHARGE_WIDTH * 2 * nCntCharger, SCREEN_HEIGHT - CHARGE_HEIGHT * 3.0f, 0.0f), CHARGEUITYPE_GAUGE, nCntCharger, CHARGE_WIDTH);
	}
}

//======================================
//充電器充電器の終了
//======================================
void UninitCharge(void)
{
	for (int nCntCharger = 0; nCntCharger < CHARGEUITYPE_MAX; nCntCharger++)
	{
		//テクスチャの破棄
		if (g_aPTextureCharger[nCntCharger] != NULL)
		{

			g_aPTextureCharger[nCntCharger]->Release();
			g_aPTextureCharger[nCntCharger] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffCharger != NULL)
	{
		g_pVtxBuffCharger->Release();
		g_pVtxBuffCharger = NULL;
	}
}

//======================================
//充電器のアップデート
//======================================
void UpdateCharge(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffCharger->Lock(0, 0, (void**)&pVtx, 0);

	g_Charge.nCntTime++;

	//放電
	if (g_Charge.nCntTime >= 600)
	{//一定時間たっら
		g_Charge.nCntTime = 0.0f;
		ChargePower(-0.5f);
	}

	//雷情報を初期化
	for (int nCntCharger = 0; nCntCharger < MAX_CHARGERUI; nCntCharger++)
	{
		if (g_aChagerUI[nCntCharger].bUse == true)
		{
			//電池フレームの状態を更新
			ChargerFlameState(nCntCharger);
			//電池ゲージの状態を更新
			ChargerGaugeState(nCntCharger);

			//位置
			pVtx[0].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
			pVtx[0].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
			pVtx[1].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
			pVtx[2].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
			pVtx[3].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aChagerUI[nCntCharger].col;
			pVtx[1].col = g_aChagerUI[nCntCharger].col;
			pVtx[2].col = g_aChagerUI[nCntCharger].col;
			pVtx[3].col = g_aChagerUI[nCntCharger].col;
		}
		pVtx += 4;//頂点データのポインタを四つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffCharger->Unlock();
}

//======================================
//充電器の描画
//======================================
void DrawCharge(void)
{
	int nCntCharger;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCharger, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//充電器の描画
	for (nCntCharger = 0; nCntCharger < MAX_CHARGERUI; nCntCharger++)
	{
		if (g_aChagerUI[nCntCharger].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureCharger[g_aChagerUI[nCntCharger].nType]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntCharger,						//描画する最初の頂点インデックス
				2);
		}
	}
}

//======================================
//充電
//======================================
void ChargePower(float fEPower)
{
	//チャージ
	g_Charge.fChargrAmount += fEPower;
	
	if (g_Charge.fChargrAmount > MAX_ELECTRICPOWER)
	{//最大より大きくしないようにする
		g_Charge.fChargrAmount = MAX_ELECTRICPOWER;
	}
	else if (g_Charge.fChargrAmount < 0)
	{//ゼロより小さくならないように
		g_Charge.fChargrAmount = 0;
	}
}

//======================================
//充電器のフレームの状態
//======================================
void ChargerFlameState(int nCntCharger)
{
	if(g_aChagerUI[nCntCharger].nType  == CHARGEUITYPE_FLAME)
	{
		//赤色にする
		g_aChagerUI[nCntCharger].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//電力を基準に緑色にする
		if (g_aChagerUI[nCntCharger].nNumber < g_Charge.fChargrAmount)
		{
			g_aChagerUI[nCntCharger].col = D3DXCOLOR(0.0f,1.0f,0.0f,1.0f);
		}
	}
}

//======================================
//充電器のゲージの状態
//======================================
void ChargerGaugeState(int nCntCharger)
{
	if (g_aChagerUI[nCntCharger].nType == CHARGEUITYPE_GAUGE)
	{
		//透明にする
		g_aChagerUI[nCntCharger].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);

		//電力を基準に不透明にする
		if (g_aChagerUI[nCntCharger].nNumber < g_Charge.fChargrAmount)
		{
			g_aChagerUI[nCntCharger].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		}
	}
}

//======================================
//充電を設定
//======================================
void SetCharger(const char *pFileName,D3DXVECTOR3 pos,CHARGERUITYPE type, int num, float fWidth)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffCharger->Lock(0, 0, (void**)&pVtx, 0);

	//雷情報を初期化
	for (int nCntCharger = 0; nCntCharger < MAX_CHARGERUI; nCntCharger++)
	{
		if (g_aChagerUI[nCntCharger].bUse == false)
		{
			g_aChagerUI[nCntCharger].pFileName = pFileName;
			g_aChagerUI[nCntCharger].pos = pos;
			g_aChagerUI[nCntCharger].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_aChagerUI[nCntCharger].nType = type;
			g_aChagerUI[nCntCharger].nNumber = num;
			g_aChagerUI[nCntCharger].nState = CHARGESTATE_NONE;
			g_aChagerUI[nCntCharger].fWidth = fWidth;
			g_aChagerUI[nCntCharger].fHeight = CHARGE_HEIGHT;
			g_aChagerUI[nCntCharger].bUse = true;

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pFileName,
				&g_aPTextureCharger[g_aChagerUI[nCntCharger].nType]);

			//位置
			pVtx[0].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
			pVtx[0].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
			pVtx[1].pos.y = g_aChagerUI[nCntCharger].pos.y - g_aChagerUI[nCntCharger].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aChagerUI[nCntCharger].pos.x - g_aChagerUI[nCntCharger].fWidth;
			pVtx[2].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aChagerUI[nCntCharger].pos.x + g_aChagerUI[nCntCharger].fWidth;
			pVtx[3].pos.y = g_aChagerUI[nCntCharger].pos.y + g_aChagerUI[nCntCharger].fHeight;
			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aChagerUI[nCntCharger].col;
			pVtx[1].col = g_aChagerUI[nCntCharger].col;
			pVtx[2].col = g_aChagerUI[nCntCharger].col;
			pVtx[3].col = g_aChagerUI[nCntCharger].col;

			break;
		}
		pVtx += 4;// 頂点データのポインタを四つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffCharger->Unlock();
}

//======================================
// 放出
//======================================
void DisCharge(D3DXVECTOR3 pos)
{
	SetParticle(pos,								// 位置
		D3DXCOLOR(1.0f, 0.8f, 0.8f, 1.0f),			// 色
		EFFECTTYPE_NOMAL,	//種類
		30,											// 出す量
		0,											// 出す角度
		40.0f,										// 速さ
		0.01f,										// 移動量減少数
		20.0f,										// ポリゴンサイズ
		0.01f,										// ポリゴンサイズ減少数
		D3DX_PI * 0.75f,							// 狙いの値
		15.0f,										// 寿命
		0.0f,										//最低の移動量
		0.0f,										//幅
		0.0f,				//高さ
		-1);
}

//======================================
// 充電情報を取得
//======================================
CHARGE* GetCharge(void)
{
	return &g_Charge;
}