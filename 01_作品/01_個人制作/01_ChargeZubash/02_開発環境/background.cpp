#include "main.h"
#include "background.h"
#include "game.h"

//背景構造体
typedef struct
{
	const char* pFileName;	//ファイル名
	int nType;				//タイプ
	D3DXCOLOR col;			//色
	float fTexMoveX;		//テクスチャの動きX
	float fTexMoveY;		//テクスチャの動きY
	bool bUse;				//使用してるかどうか
}Background;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureBG[BGTYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//頂点バッファへのポインタ
Background g_aBG[BGTYPE_MAX];								//背景ポリゴンの情報

//==============================================
//背景画面の初期化処理
//==============================================
void InitBG(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BGTYPE_MAX, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//情報の初期化
	for (nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		g_aBG[nCntBG].nType = BGTYPE_MAX;
		g_aBG[nCntBG].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBG[nCntBG].fTexMoveX = 0.0f;
		g_aBG[nCntBG].fTexMoveY = 0.0f;
		g_aBG[nCntBG].bUse = false;

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			g_aBG[nCntBG].pFileName,
			&g_aPTextureBG[nCntBG]);

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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}
//==============================================
//背景画面の終了処理
//==============================================
void UninitBG(void)
{
	for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		//テクスチャの破棄
		if (g_aPTextureBG[nCntBG] != NULL)
		{
			g_aPTextureBG[nCntBG]->Release();
			g_aPTextureBG[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//==============================================
//背景画面の更新処理
//==============================================
void UpdateBG(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//探す
	for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		if (g_aBG[nCntBG].bUse == true)
		{
			MoveBackground(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0001f, 0.0f, nCntBG);
			MoveBackground(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0002f, 0.0f, nCntBG);
		}

		//頂点カラーの設定
		pVtx[0].col = g_aBG[nCntBG].col;
		pVtx[1].col = g_aBG[nCntBG].col;
		pVtx[2].col = g_aBG[nCntBG].col;
		pVtx[3].col = g_aBG[nCntBG].col;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_aBG[nCntBG].fTexMoveX, g_aBG[nCntBG].fTexMoveY);
		pVtx[1].tex = D3DXVECTOR2(1.0f + g_aBG[nCntBG].fTexMoveX, g_aBG[nCntBG].fTexMoveY);
		pVtx[2].tex = D3DXVECTOR2(g_aBG[nCntBG].fTexMoveX, 1.0f + g_aBG[nCntBG].fTexMoveY);
		pVtx[3].tex = D3DXVECTOR2(1.0f + g_aBG[nCntBG].fTexMoveX, 1.0f + g_aBG[nCntBG].fTexMoveY);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//==============================================
//背景画面の描画処理
//==============================================
void DrawBG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		if (g_aBG[nCntBG].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureBG[nCntBG]);

			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntBG,								//描画する最初の頂点インデックス
				2);										//描画するプリミティブ（プレイヤー）数
		}
	}
}

//===============================
//背景の設定
//===============================
void SetBackground(const char* pFileName,BGTYPE type,D3DXCOLOR col)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//探す
	for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
	{
		if (g_aBG[nCntBG].bUse == false)
		{
			g_aBG[nCntBG].pFileName = pFileName;
			g_aBG[nCntBG].col = col;
			g_aBG[nCntBG].nType = type;
			g_aBG[nCntBG].bUse = true;

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				g_aBG[nCntBG].pFileName,
				&g_aPTextureBG[nCntBG]);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

			//頂点カラーの設定
			pVtx[0].col =g_aBG[nCntBG].col;
			pVtx[1].col =g_aBG[nCntBG].col;
			pVtx[2].col =g_aBG[nCntBG].col;
			pVtx[3].col =g_aBG[nCntBG].col;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//===============================
//背景の動き
//===============================
void MoveBackground(D3DXCOLOR col, float texMoveX, float texMoveY, int nCntBG)
{

	g_aBG[nCntBG].fTexMoveX += texMoveX;
	g_aBG[nCntBG].fTexMoveY += texMoveY;

	if (g_aBG[nCntBG].fTexMoveX > 1.0f)
	{//最大より大きくなったら
		g_aBG[nCntBG].fTexMoveX = 0.0f;
	}
	else if (g_aBG[nCntBG].fTexMoveX < -1.0f)
	{//最小より小さくなったら
		g_aBG[nCntBG].fTexMoveX = 0.0f;
	}

	if (g_aBG[nCntBG].fTexMoveY > 1.0f)
	{//最大より大きくなったら
		g_aBG[nCntBG].fTexMoveY = 0.0f;
	}
	else if (g_aBG[nCntBG].fTexMoveY < -1.0f)
	{//最小より小さくなったら
		g_aBG[nCntBG].fTexMoveY = 0.0f;
	}
}

//===============================
//背景の終わり
//===============================
void EndBackground(BGTYPE type)
{
	if (type != BGTYPE_MAX)
	{
		//個別で消す
		for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
		{
			if (g_aBG[nCntBG].bUse == true && g_aBG[nCntBG].nType == type)
			{
				g_aBG[nCntBG].bUse = false;

				break;
			}
		}
	}
	else
	{
		//全部消す
		for (int nCntBG = 0; nCntBG < BGTYPE_MAX; nCntBG++)
		{
			g_aBG[nCntBG].bUse = false;
		}
	}
}