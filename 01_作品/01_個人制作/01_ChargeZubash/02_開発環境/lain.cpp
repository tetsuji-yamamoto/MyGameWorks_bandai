#include "lain.h"
#include "sound.h"
//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureLain = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLain = NULL;		//頂点バッファへのポインタ
Lain g_lain;										//雨ポリゴンの情報

//==============================================
//雨画面の初期化処理
//==============================================
void InitLain(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLain,
		NULL);

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffLain->Lock(0, 0, (void**)&pVtx, 0);

	//情報の初期化

	g_lain.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
	g_lain.fTexMoveX = 0.0f;
	g_lain.fTexMoveY = 0.0f;
	g_lain.bUse = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\LAIN\\Lein_001.png",
		&g_pTextureLain);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffLain->Unlock();

	//雨音
	PlaySound(SOUND_LABEL_LEIN_BGM);
}
//==============================================
//雨画面の終了処理
//==============================================
void UninitLain(void)
{
	//テクスチャの破棄
	if (g_pTextureLain != NULL)
	{
		g_pTextureLain->Release();
		g_pTextureLain = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLain != NULL)
	{
		g_pVtxBuffLain->Release();
		g_pVtxBuffLain = NULL;
	}

	g_lain.bUse = false;//使用しない
}

//==============================================
//雨画面の更新処理
//==============================================
void UpdateLain(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffLain->Lock(0, 0, (void**)&pVtx, 0);

	if (g_lain.bUse == true)
	{
		g_lain.fTexMoveX += 0.001f;
		g_lain.fTexMoveY -=0.05f;

		if (g_lain.fTexMoveX > 1.0f)
		{//最大より大きくなったら
			g_lain.fTexMoveX = 0.0f;
		}
		else if (g_lain.fTexMoveX < -1.0f)
		{//最小より小さくなったら
			g_lain.fTexMoveX = 0.0f;
		}

		if (g_lain.fTexMoveY > 1.0f)
		{//最大より大きくなったら
			g_lain.fTexMoveY = 0.0f;
		}
		else if (g_lain.fTexMoveY < -1.0f)
		{//最小より小さくなったら
			g_lain.fTexMoveY = 0.0f;
		}
	}

	//頂点カラーの設定
	pVtx[0].col = g_lain.col;
	pVtx[1].col = g_lain.col;
	pVtx[2].col = g_lain.col;
	pVtx[3].col = g_lain.col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_lain.fTexMoveX, g_lain.fTexMoveY);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_lain.fTexMoveX, g_lain.fTexMoveY);
	pVtx[2].tex = D3DXVECTOR2(g_lain.fTexMoveX, 1.0f + g_lain.fTexMoveY);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_lain.fTexMoveX, 1.0f + g_lain.fTexMoveY);

	//頂点バッファをアンロックする
	g_pVtxBuffLain->Unlock();
}

//==============================================
//雨画面の描画処理
//==============================================
void DrawLain(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLain, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_lain.bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureLain);

		//プレイヤーの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			0,										//描画する最初の頂点インデックス
			2);										//描画するプリミティブ（プレイヤー）数
	}

}