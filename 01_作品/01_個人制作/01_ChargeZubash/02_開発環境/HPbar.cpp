#include "HPbar.h"
#include "effect.h"
#include "enemy.h"
#include "player.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureHPbar[HPBARTYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHPbar = NULL;				//頂点バッファへのポインタ
HPBAR g_aHPbar[HPBARTYPE_MAX];								//ｈｐバー情報

//======================================
//HPbar器の初期化
//======================================
void InitHPbar(void)
{
	int nCntHPbar;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HPBARTYPE_MAX, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHPbar,
		NULL);

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffHPbar->Lock(0, 0, (void**)&pVtx, 0);


	//ブロックの情報の初期化
	for (nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		g_aHPbar[nCntHPbar].pFile = NULL;
		g_aHPbar[nCntHPbar].pos = D3DXVECTOR3(0.0f,0.0f,0.0);
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aHPbar[nCntHPbar].rect.bottom = 0;
		g_aHPbar[nCntHPbar].rect.left = 0;
		g_aHPbar[nCntHPbar].rect.right = 0;
		g_aHPbar[nCntHPbar].rect.top = 0;
		g_aHPbar[nCntHPbar].type = HPBARTYPE_MAX;
		g_aHPbar[nCntHPbar].fVari = 1.0f;

		//位置の初期化
		pVtx[0].pos.x = g_aHPbar[nCntHPbar].pos.x - g_aHPbar[nCntHPbar].rect.left;;
		pVtx[0].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
		pVtx[1].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aHPbar[nCntHPbar].pos.x - g_aHPbar[nCntHPbar].rect.left;
		pVtx[2].pos.y = g_aHPbar[nCntHPbar].pos.y + g_aHPbar[nCntHPbar].rect.bottom;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
		pVtx[3].pos.y = g_aHPbar[nCntHPbar].pos.y + g_aHPbar[nCntHPbar].rect.bottom;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_aHPbar[nCntHPbar].col;
		pVtx[1].col = g_aHPbar[nCntHPbar].col;
		pVtx[2].col = g_aHPbar[nCntHPbar].col;
		pVtx[3].col = g_aHPbar[nCntHPbar].col;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点データのポインタを四つ分進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffHPbar->Unlock();

	//プレイヤー
	SetHPbar(FILE_TEX_HPBAR_PLAYER_GAUGE,D3DXVECTOR3(0.0f, SCREEN_HEIGHT - HPBARFRAME_PRAYER_HEIGHT,0.0f), HPBARGAUGE_PRAYER_WIDTH, HPBARGAUGE_PRAYER_HEIGHT,HPBARTYPE_PLAYERGAUGE_BACK);
	SetHPbar(FILE_TEX_HPBAR_PLAYER_GAUGE,D3DXVECTOR3(0.0f, SCREEN_HEIGHT - HPBARFRAME_PRAYER_HEIGHT,0.0f), HPBARGAUGE_PRAYER_WIDTH, HPBARGAUGE_PRAYER_HEIGHT,HPBARTYPE_PLAYERGAUGE);
	SetHPbar(FILE_TEX_HPBAR_PLAYER_FRAME,D3DXVECTOR3(0.0f, SCREEN_HEIGHT - HPBARFRAME_PRAYER_HEIGHT,0.0f), HPBARFRAME_PRAYER_WIDTH, HPBARFRAME_PRAYER_HEIGHT,HPBARTYPE_PLAYERFRAME);
	//敵
	SetHPbar(FILE_TEX_HPBAR_PLAYER_GAUGE,D3DXVECTOR3(SCREEN_WIDTH*0.5f- HPBARFRAME_PRAYER_WIDTH*0.5f, SCREEN_HEIGHT - HPBARFRAME_ENEMY_HEIGHT,0.0f), HPBARGAUGE_ENEMY_WIDTH, HPBARGAUGE_ENEMY_HEIGHT,HPBARTYPE_ENEMYGAUGE_BACK);
	SetHPbar(FILE_TEX_HPBAR_PLAYER_GAUGE,D3DXVECTOR3(SCREEN_WIDTH*0.5f- HPBARFRAME_PRAYER_WIDTH*0.5f, SCREEN_HEIGHT - HPBARFRAME_ENEMY_HEIGHT,0.0f), HPBARGAUGE_ENEMY_WIDTH, HPBARGAUGE_ENEMY_HEIGHT,HPBARTYPE_ENEMYGAUGE);
	SetHPbar(FILE_TEX_HPBAR_ENEMY_FRAME,D3DXVECTOR3(SCREEN_WIDTH*0.5f- HPBARFRAME_PRAYER_WIDTH * 0.5f, SCREEN_HEIGHT - HPBARFRAME_ENEMY_HEIGHT,0.0f), HPBARFRAME_ENEMY_WIDTH, HPBARFRAME_ENEMY_HEIGHT,HPBARTYPE_ENEMYFRAME);
}

//======================================
//HPbar器HPbar器の終了
//======================================
void UninitHPbar(void)
{
	for (int nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		//テクスチャの破棄
		if (g_aPTextureHPbar[nCntHPbar] != NULL)
		{

			g_aPTextureHPbar[nCntHPbar]->Release();
			g_aPTextureHPbar[nCntHPbar] = NULL;
		}
		EndHPbar(nCntHPbar);
	}

	//頂点バッファの破棄
	if (g_pVtxBuffHPbar != NULL)
	{
		g_pVtxBuffHPbar->Release();
		g_pVtxBuffHPbar = NULL;
	}
}

//======================================
//HPbar器のアップデート
//======================================
void UpdateHPbar(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffHPbar->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		if (g_aHPbar[nCntHPbar].bUse == true)
		{
			VariHPbar(nCntHPbar);

			switch (g_aHPbar[nCntHPbar].type)
			{

			case HPBARTYPE_PLAYERGAUGE:
			g_aHPbar[nCntHPbar].rect.right = (HPBARFRAME_PRAYER_WIDTH) * g_aHPbar[nCntHPbar].fVari;
				break;

			case HPBARTYPE_ENEMYGAUGE:
				g_aHPbar[nCntHPbar].rect.right = (HPBARFRAME_ENEMY_WIDTH) * g_aHPbar[nCntHPbar].fVari;
				break;

			default:
				break;
			}

			//頂点座標更新
			pVtx[0].pos.x = g_aHPbar[nCntHPbar].pos.x;
			pVtx[0].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
			pVtx[1].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aHPbar[nCntHPbar].pos.x;
			pVtx[2].pos.y = g_aHPbar[nCntHPbar].pos.y + g_aHPbar[nCntHPbar].rect.bottom;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
			pVtx[3].pos.y = g_aHPbar[nCntHPbar].pos.y + g_aHPbar[nCntHPbar].rect.bottom;
			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aHPbar[nCntHPbar].col;
			pVtx[1].col = g_aHPbar[nCntHPbar].col;
			pVtx[2].col = g_aHPbar[nCntHPbar].col;
			pVtx[3].col = g_aHPbar[nCntHPbar].col;

		}

		pVtx += 4;//頂点データのポインタを四つ分進める
	}

	
	//頂点バッファをアンロックする
	g_pVtxBuffHPbar->Unlock();
}

//======================================
//HPbar器の描画
//======================================
void DrawHPbar(void)
{
	int nCntHPbar;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHPbar, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//HPbar器の描画
	for (nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		if (g_aHPbar[nCntHPbar].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureHPbar[nCntHPbar]);

			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntHPbar,							//描画する最初の頂点インデックス
				2);
		}
	}
}

//======================================
//HPbarを設定
//======================================
void SetHPbar(const char* pFile, D3DXVECTOR3 pos, long lWidth, long lHeight, HPBARTYPE type)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffHPbar->Lock(0, 0, (void**)&pVtx, 0);

	//雷情報を初期化
	for (int nCntHPbar = 0; nCntHPbar < HPBARTYPE_MAX; nCntHPbar++)
	{
		if (g_aHPbar[nCntHPbar].bUse == false)
		{
			g_aHPbar[nCntHPbar].pFile = pFile;
			g_aHPbar[nCntHPbar].pos = pos;
			g_aHPbar[nCntHPbar].rect.bottom = lHeight;
			g_aHPbar[nCntHPbar].rect.left = lWidth;
			g_aHPbar[nCntHPbar].rect.right = lWidth;
			g_aHPbar[nCntHPbar].rect.top = lHeight;
			g_aHPbar[nCntHPbar].type = type;
			g_aHPbar[nCntHPbar].fVari = 1.0f;
			g_aHPbar[nCntHPbar].bUse = true;

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pFile,
				&g_aPTextureHPbar[nCntHPbar]);

			//位置
			pVtx[0].pos.x = g_aHPbar[nCntHPbar].pos.x;
			pVtx[0].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
			pVtx[1].pos.y = g_aHPbar[nCntHPbar].pos.y - g_aHPbar[nCntHPbar].rect.top;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aHPbar[nCntHPbar].pos.x;
			pVtx[2].pos.y = g_aHPbar[nCntHPbar].pos.y;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aHPbar[nCntHPbar].pos.x + g_aHPbar[nCntHPbar].rect.right;
			pVtx[3].pos.y = g_aHPbar[nCntHPbar].pos.y;
			pVtx[3].pos.z = 0.0f;

			break;
		}
		pVtx += 4;// 頂点データのポインタを四つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffHPbar->Unlock();
}

//======================================
//HPbarを変化
//======================================
void VariHPbar(int nCntHPbar)
{
	Player* pPlayer = GetPlayer();		//プレイヤー取得
	ENEMY* pEnemy = GetEnemy();			//エネミー取得
	SNAKEHP* pSnakeHP = GetSnakeHP();	//蛇の総HP
	switch (g_aHPbar[nCntHPbar].type)
	{
	case HPBARTYPE_PLAYERGAUGE_BACK:
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);//黒色
		break;

	case HPBARTYPE_PLAYERGAUGE:
		
		g_aHPbar[nCntHPbar].fVari = pPlayer->fLife / MAX_PLAYER_HP;

		if ((pPlayer->fLife / MAX_PLAYER_HP) * 100.0f >= 50.0f)
		{//半分以上合ったら
			g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.0f,1.0f,1.0f,1.0f);//青色
		}
		else if ((pPlayer->fLife / MAX_PLAYER_HP) * 100.0f < 50.0f &&
			(pPlayer->fLife / MAX_PLAYER_HP) * 100.0f >= 30.0f)
		{//50%を下回った
			g_aHPbar[nCntHPbar].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);//黄色
		}
		else if ((pPlayer->fLife / MAX_PLAYER_HP) * 100.0f < 30.0f &&
			(pPlayer->fLife / MAX_PLAYER_HP) * 100.0f >= 0.0f)
		{//30%を下回った
			g_aHPbar[nCntHPbar].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//赤色
		}

		break;

	case HPBARTYPE_PLAYERFRAME:
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.4f, 0.6f, 0.6f, 1.0f);//黒色
		break;

	case HPBARTYPE_ENEMYGAUGE_BACK:
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);//黒色
		break;

	case HPBARTYPE_ENEMYGAUGE:
		g_aHPbar[nCntHPbar].fVari = pSnakeHP->fLife / pSnakeHP->fMaxLife;
		g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.9f, 1.0f, 0.0f, 1.0f);//黄緑色
		break;

		case HPBARTYPE_ENEMYFRAME:
			g_aHPbar[nCntHPbar].col = D3DXCOLOR(0.9f, 1.0f, 0.0f, 1.0f);//黄緑色
			break;
	default:
		break;
	}
}

//======================================
//HPbarの終了
//======================================
void EndHPbar(int nCntHPbar)
{
	g_aHPbar[nCntHPbar].bUse = false;
}

//======================================
//敵のHPbarの更新
//======================================

