#include "block.h"
#include "player.h"
#include "main.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//頂点バッファへのポインタ
BLOCK g_aBlock[MAX_BLOCK];//ブロックの情報

//------------------
//ブロックの初期化処理
//------------------
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEX_BLOCK,
		&g_pTextureBlock);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].posGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nCntTime = 0;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_NOMAL;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fTexX = 1.0f;
		g_aBlock[nCntBlock].fTexY = 1.0f;
		g_aBlock[nCntBlock].bUse = false;
		//位置の初期化
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
	g_pVtxBuffBlock->Unlock();
}
//-------------
//ブロックの終了処理
//-------------
void UninitBlock(void)
{

	//テクスチャの破棄
	if (g_pTextureBlock != NULL)
	{

		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//--------------------
//ブロックの更新処理
//--------------------
void UpdateBlock(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの情報の初期化
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			switch (g_aBlock[nCntBlock].nType)
			{
			case BLOCKTYPE_MOVEX:
				//カウントして
				g_aBlock[nCntBlock].nCntTime++;

				if (g_aBlock[nCntBlock].nCntTime >= 180)
				{//一定数超えたら
					g_aBlock[nCntBlock].nCntTime *= -1;
				}

				if (g_aBlock[nCntBlock].nCntTime >= 0)
				{//プラスだったら

					g_aBlock[nCntBlock].move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
				}
				else if (g_aBlock[nCntBlock].nCntTime < 0)
				{//マイナスだったら
					g_aBlock[nCntBlock].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
				}
				break;

			case BLOCKTYPE_MOVEY:
				//カウントして
				g_aBlock[nCntBlock].nCntTime++;

				if (g_aBlock[nCntBlock].nCntTime >= 180)
				{//一定数超えたら
					g_aBlock[nCntBlock].nCntTime *= -1;
				}

				if (g_aBlock[nCntBlock].nCntTime >= 0)
				{//プラスだったら

					g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				}
				else if (g_aBlock[nCntBlock].nCntTime < 0)
				{//マイナスだったら
					g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				}
				break;
			}
		}
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;

			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[3].pos.z = 0.0f;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, g_aBlock[nCntBlock].fHeight / BLOCK_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH, g_aBlock[nCntBlock].fHeight / BLOCK_HEIGHT);

		//頂点データのポインタを四つ分進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//--------------------
//ブロックの描画処理
//--------------------
void DrawBlock(void)
{
	int nCntBlock;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ブロックの描画
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックが使用されている

				//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntBlock,							//描画する最初の頂点インデックス
				2);
		}
	}
}

//----------------
//たまの設定処理
//----------------
void SetBlock(D3DXVECTOR3 pos, int nType, float width, float height)
{
	int nCntBlock;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//ブロックが使用されていない

			g_aBlock[nCntBlock].pos = pos;			//位置
			g_aBlock[nCntBlock].nType = nType;		//種類
			g_aBlock[nCntBlock].fWidth = width;		//幅
			g_aBlock[nCntBlock].fHeight = height;	//高さ
			g_aBlock[nCntBlock].bUse = true;		//使用している状態にする

			//頂点座用の設定
			pVtx[0].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[0].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[1].pos.y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth;
			pVtx[2].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth;
			pVtx[3].pos.y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight;
			pVtx[3].pos.z = 0.0f;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, g_aBlock[nCntBlock].fHeight / BLOCK_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2(g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH, g_aBlock[nCntBlock].fHeight / BLOCK_HEIGHT);
			break;
		}

		//頂点データのポインタを四つ分進める
		pVtx += 4;

	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//====================================
//ブロックの当たり判定
//====================================
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth)
{
	bool bLanding = false;	//着地しているかどうか

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->y - PLAYER_HEIGHT < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
				pPos->y  > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
			{//プレイヤーの上側がブロックの上下両面の中,プレイヤーの下側がブロックの上下両面の中

				if (pPosOld->x - PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
					pPos->x - PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
				{//右から左への当たり判定,オルドポスがブロック右面以上右、ポスがブロック右面以下左

					//右側面当たり判定
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + PLAYER_WIDTH;
					pPMove->x = 0.0f;
				}
				else if (pPosOld->x + PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
					pPos->x + PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)
				{//左から右への当たり判定,オルドポスがブロック左面以下、ポスがブロック左面以上

					//左側面当たり判定
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - PLAYER_WIDTH;
					pPMove->x = 0.0f;
				}
			}

			if (pPos->x + PLAYER_WIDTH > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
				pPos->x - PLAYER_WIDTH < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//プレイヤーの右側がブロックの左右両面の中,プレイヤーの左側がブロックの左右両面の中

				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight &&
					pPos->y >= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
				{//上から下への当たり判定,オルドポスがブロック上面以上、ポスがブロック上面以下

					//上面当たり判定
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
					pPMove->y = 0.0f;
				}
				else if (pPosOld->y - PLAYER_HEIGHT >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//下から上への当たり判定,オルドポスがブロック上面以上、ポスがブロック上面以下

					//下面当たり判定
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT;
					pPMove->y = 0.0f;
				}
			}
		}
	}

	return bLanding;
}

//====================================
//ブロックの当たり判定X
//====================================
void CollisionBlockX(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth, BLOCK** pBlock)
{
	bool bLanding = false;	//着地しているかどうか

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->y - PLAYER_HEIGHT < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
				pPos->y  > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
			{//プレイヤーの上側がブロックの上下両面の中,プレイヤーの下側がブロックの上下両面の中

				if (pPosOld->x - PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
					pPos->x - PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
				{//右から左への当たり判定,オルドポスがブロック右面以上右、ポスがブロック右面以下左

					//右側面当たり判定
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + PLAYER_WIDTH;
					pPMove->x = 0.0f;
				}
				else if (pPosOld->x + PLAYER_WIDTH <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
					pPos->x + PLAYER_WIDTH >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth)
				{//左から右への当たり判定,オルドポスがブロック左面以下、ポスがブロック左面以上

					//左側面当たり判定
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - PLAYER_WIDTH;
					pPMove->x = 0.0f;
				}
			}
		}
	}
}

//====================================
//ブロックの当たり判定Y
//====================================
bool CollisionBlockY(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth, BLOCK** pBlock)
{
	bool bLanding = false;	//着地しているかどうか

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			if (pPos->x + PLAYER_WIDTH > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth &&
				pPos->x - PLAYER_WIDTH < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//プレイヤーの右側がブロックの左右両面の中,プレイヤーの左側がブロックの左右両面の中

				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight &&
					pPos->y >= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight)
				{//上から下への当たり判定,オルドポスがブロック上面以上、ポスがブロック上面以下

					//上面当たり判定
					bLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight;
					pPMove->y = 0.0f;

					if (pBlock != NULL)
					{//ブロックのアドレスを入れる場所がある
						*pBlock = &g_aBlock[nCntBlock];//ブロックのアドレスを代入
					}
				}
				else if (pPosOld->y - PLAYER_HEIGHT >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPos->y - PLAYER_HEIGHT <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//下から上への当たり判定,オルドポスがブロック上面以上、ポスがブロック上面以下

					//下面当たり判定
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT;
					pPMove->y = 0.0f;
				}
			}
		}
	}

	return bLanding;
}

//============================
//ブロック取得
//============================
BLOCK* GetBlock(void)
{
	return &g_aBlock[0];
}
