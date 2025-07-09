#include "timer.h"
#include "game.h"
#include "fade.h"
#include "result.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;		//Direct3Dテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;	//頂点バッファへのポインタ
TIMER g_Timer;									//タイマー情報

//===================
//タイマーの初期化処理
//===================
void InitTimer(void)
{
	int nCnt;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_NUMBER,
		&g_pTextureTimer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME_NUM, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	g_Timer.nTimer = MAX_TIME;					//値を初期化する
	g_Timer.nTimerCount = 0;					//カウント初期化
	g_Timer.nTaimerState = TIMERSTATE_NOMAL;	//タイマー状況初期化

	//頂点情報へのポインタ
	VERTEX_2D* pVtx; 

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_TIME_NUM; nCnt++)
	{
		g_Timer.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - MAX_TIME_NUM_WIDTH * 0.4f * 3.0f + MAX_TIME_NUM_WIDTH * nCnt, MAX_TIME_NUM_HEIGHT , 0.0f);	//位置を初期化する
		g_Timer.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//色を初期化する

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Timer.pos.x - MAX_TIME_NUM_WIDTH / 2, g_Timer.pos.y - MAX_TIME_NUM_WIDTH / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Timer.pos.x + MAX_TIME_NUM_WIDTH / 2, g_Timer.pos.y - MAX_TIME_NUM_WIDTH / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Timer.pos.x - MAX_TIME_NUM_WIDTH / 2, g_Timer.pos.y + MAX_TIME_NUM_WIDTH / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Timer.pos.x + MAX_TIME_NUM_WIDTH / 2, g_Timer.pos.y + MAX_TIME_NUM_WIDTH / 2, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_Timer.col;
		pVtx[1].col = g_Timer.col;
		pVtx[2].col = g_Timer.col;
		pVtx[3].col = g_Timer.col;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();
	AddTimer();
}
//===================
//タイマーの終了処理
//===================
void UninitTimer(void)
{
	//テクスチャの破棄
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}
//===================
//タイマーの更新処理
//===================
void UpdateTimer(void)
{
	int nCnt;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);
	//時間切れまじか
	if (g_Timer.nTaimerState == TIMERSTATE_UP)
	{
		for (int nCnt = 0; nCnt < MAX_TIME_NUM; nCnt++)
		{
			g_Timer.pos = D3DXVECTOR3(200.0f + SCREEN_WIDTH * 0.3 * nCnt, SCREEN_HEIGHT * 0.5f, 0.0f);	//位置を初期化する
			g_Timer.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);												//色を初期化する

			//位置の更新
			pVtx[0].pos = D3DXVECTOR3(g_Timer.pos.x - SCREEN_WIDTH * 0.3 * 0.5, g_Timer.pos.y - MAX_TIMEUP_NUM_WIDTH / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Timer.pos.x + SCREEN_WIDTH * 0.3 * 0.5, g_Timer.pos.y - MAX_TIMEUP_NUM_WIDTH / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Timer.pos.x - SCREEN_WIDTH * 0.3 * 0.5, g_Timer.pos.y + MAX_TIMEUP_NUM_WIDTH / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Timer.pos.x + SCREEN_WIDTH * 0.3 * 0.5, g_Timer.pos.y + MAX_TIMEUP_NUM_WIDTH / 2, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = g_Timer.col;
			pVtx[1].col = g_Timer.col;
			pVtx[2].col = g_Timer.col;
			pVtx[3].col = g_Timer.col;

			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();
	//時間が減っていく
	if (g_Timer.nTimer > 0 && GetGameState() == GAMESTATE_NORMAL)
	{
		g_Timer.nTimerCount++;
		if (g_Timer.nTimerCount >= 60)
		{
			g_Timer.nTimerCount = 0;
			g_Timer.nTimer--;
			AddTimer();
		}
	}
	//状況を変える
	if(g_Timer.nTimer <= 10)
	{
		g_Timer.nTaimerState = TIMERSTATE_UP;
	}
	//時間切れ
	if(g_Timer.nTimer <= 0 && GetGameState() == GAMESTATE_NORMAL)
	{
		//フェードアウトする
		SetFade(MODE_RESULT);
		SetResult(RESULTTYPE_TIMEOVER);
	}
}
//===================
//タイマーの描画処理
//===================
void DrawTimer(void)
{
	int nCnt;
	//必要桁数分の描画
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCnt = 0; nCnt < MAX_TIME_NUM; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTimer);
		//背景の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCnt,								//描画する最初の頂点インデックス
			2);										//描画するプリミティブ（背景）数
	}
}
//===================
//タイマーの加算処理
//===================
void AddTimer(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx; 

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	int aPosTexU[3] = {};//格桁の数字を格納
	int nData1 = 100, nData2 = 10;
	int nCnt;

	//桁ごとに分割する
	for (nCnt = 0; nCnt < MAX_TIME_NUM; nCnt++)
	{
		if (nCnt == 0)
		{
			aPosTexU[0] = g_Timer.nTimer / nData1;
		}
		else
		{
			aPosTexU[nCnt] = (g_Timer.nTimer % nData1 / nData2);
			nData1 /= 10;
			nData2 /= 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();
}
//----------------------
//タイマー取得
//----------------------
TIMER* GetTimer(void)
{
	return &g_Timer;
}