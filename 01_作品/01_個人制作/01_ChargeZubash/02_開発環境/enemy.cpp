#include "enemy.h"
#include "main.h"
#include "particle.h"
#include "player.h"
#include "effect.h"
#include "sound.h"
#include "sword.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "result.h"
#include "hit.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//頂点バッファへのポインタ
ENEMY g_aEnemy[MAX_ENEMY];									//敵の情報
SNAKEHP g_snakeHP;											//蛇のｈｐ
int g_nNumEnemy = 0;										//敵の総数

//-------------------
//敵の初期化処理
//-------------------
void InitEnemy(void)
{
	int nCntEnemy;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	g_nNumEnemy = 0; 

	g_snakeHP.fLife = 0;
	g_snakeHP.fMaxLife = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pFileName = NULL;							//ファイル名
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
		g_aEnemy[nCntEnemy].rect.bottom = 0;			//四頂点情報
		g_aEnemy[nCntEnemy].rect.left = 0;			//四頂点情報
		g_aEnemy[nCntEnemy].rect.right = 0;			//四頂点情報
		g_aEnemy[nCntEnemy].rect.top = 0;			//四頂点情報
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;	//状態
		g_aEnemy[nCntEnemy].nType = ENEMYTYPE_MAX;		//種類
		g_aEnemy[nCntEnemy].nCntState = 0;				//状態管理カウンター
		g_aEnemy[nCntEnemy].fLife = 0;					//体力
		g_aEnemy[nCntEnemy].fWidth = 0.0f;				//幅
		g_aEnemy[nCntEnemy].fHeight = 0.0f;				//高さ
		g_aEnemy[nCntEnemy].bUse = false;				//使っているかどうか
		
		g_aEnemy[nCntEnemy].vertex.BottomLeft = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].vertex.BottomRight = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].vertex.TopLeft = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].vertex.TopRight = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].vertex.fAngle = 0.0f;
		g_aEnemy[nCntEnemy].vertex.fLength = 0.0f;
		g_aEnemy[nCntEnemy].vertex.fLot = 0.0f;

		g_aEnemy[nCntEnemy].snake.posFrontUnion = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].snake.posAnderUnion = D3DXVECTOR2(0.0f, 0.0f);
		g_aEnemy[nCntEnemy].snake.nCntBody = -2;
		g_aEnemy[nCntEnemy].snake.snakeState = SNAKESTATE_STANDE;
		g_aEnemy[nCntEnemy].snake.nChillTime = 0;
		g_aEnemy[nCntEnemy].snake.bAttack = false;

		g_aEnemy[nCntEnemy].snakeMove.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].snakeMove.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].snakeMove.nCntMoveTime = 0;
		g_aEnemy[nCntEnemy].snakeMove.nCntMotion = 0;
		g_aEnemy[nCntEnemy].snakeMove.nLoopCnt = 0;
		g_aEnemy[nCntEnemy].snakeMove.fLength = 0.0f;
		g_aEnemy[nCntEnemy].snakeMove.fAngle = 0.0f;
		g_aEnemy[nCntEnemy].snakeMove.fLot = 0.0f;

		//頂点座標の設定												
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_aEnemy[nCntEnemy].col;
		pVtx[1].col = g_aEnemy[nCntEnemy].col;
		pVtx[2].col = g_aEnemy[nCntEnemy].col;
		pVtx[3].col = g_aEnemy[nCntEnemy].col;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを四つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
//-------------------
//敵の終了処理
//-------------------
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		//テクスチャの破棄
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}

		g_aEnemy[nCntEnemy].bUse = false;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//-------------------
//敵の更新処理
//--------------------
void UpdateEnemy(void)
{
	Player* pPlayer = GetPlayer();	//プレイヤー取得

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//一回ゼロにして
	g_snakeHP.fLife = 0.0f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	
#ifdef _DEBUG	//デバッグ時だけ使用可能

	if (KeyboardTrigger(DIK_6) == true)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
		{
			g_aEnemy[nCntEnemy].fLife -= g_aEnemy[nCntEnemy].fLife;
		}
	}

#endif
	//更新する
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//敵の違いによる更新
			switch (g_aEnemy[nCntEnemy].nType)
			{

			case ENEMYTYPE_PUNCHINGBAG://サンドバッグ
				//頂点座標の設定
				pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].rect.left;
				pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].rect.top;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].rect.right;
				pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].rect.top;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].rect.left;
				pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].rect.bottom;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].rect.right;
				pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].rect.bottom;
				pVtx[3].pos.z = 0.0f;
				break;

			case ENEMYTYPE_SNAKE://蛇
				UpDateSnake(nCntEnemy);
 				break;
			}

			//状態による処理
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				//通常状態
				if (g_aEnemy[nCntEnemy].fLife <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_DEATH;	//デス
					g_aEnemy[nCntEnemy].bUse = false;
					g_nNumEnemy--;
				}
				break;
					
			case ENEMYSTATE_DAMAGE:
				//ダメージ状態
				
				//カウンターを減らす
				g_aEnemy[nCntEnemy].nCntState--;

				if (g_aEnemy[nCntEnemy].nCntState <= 0)
				{//カウンターがゼロになったら
					g_aEnemy[nCntEnemy].nCntState = 0;								//カウンターをゼロ
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;					//通常状態に
					g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//通常の色に
				}
				else
				{
					g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f,0.0f,0.0f,1.0f);	//赤色にする
				}

				break;

			case ENEMYSTATE_DEATH:
				//死亡状態
				
				break;
			}

			if (pPlayer->state == PLAYERSTATE_NOMAL)
			{
				//プレイヤーと敵の当たり判定
				if (HitBox(g_aEnemy[nCntEnemy].rect, pPlayer->rect, g_aEnemy[nCntEnemy].pos, pPlayer->pos, ANCHORPOINT_CENTER, ANCHORPOINT_BOTTOMCENTER) == true)
				{
					float fDistance = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;
					if (fDistance < 0)
					{//マイナスだったら
						pPlayer->move.x -= 100.0f;
					}
					else if (fDistance > 0)
					{//プラスだったら
						pPlayer->move.x += 100.0f;
					}
					HitPlayer(1.0f);
				}
			}

			g_snakeHP.fLife += g_aEnemy[nCntEnemy].fLife;

			//頂点カラーの設定
			pVtx[0].col = g_aEnemy[nCntEnemy].col;
			pVtx[1].col = g_aEnemy[nCntEnemy].col;
			pVtx[2].col = g_aEnemy[nCntEnemy].col;
			pVtx[3].col = g_aEnemy[nCntEnemy].col;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	if (g_nNumEnemy <= 0 && GetGameState() == GAMESTATE_NORMAL)
	{
		SetGameState(GAMESTATE_END);		//ゲーム終わり
		SetResult(RESULTTYPE_GAMECREAR);	//ゲームクリア
	}
}
//-------------------
//敵の描画処理
//--------------------
void DrawEnemy(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//敵の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntEnemy,							//描画する最初の頂点インデックス
				2);										//描画するプリミティブ（敵）数
		}
	}
}

//===============================
//敵の設定処理
//===============================
void SetEnemy(const char* pFileName, D3DXVECTOR3 pos, int nType,float fLife,float fWidth,float fHeight)
{
	int nCntEnemy;

	VERTEX_2D* pVtx;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//使ってなかったら

			g_nNumEnemy++;//総数プラス
			g_aEnemy[nCntEnemy].pFileName = pFileName;
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].fLife = fLife;
			g_aEnemy[nCntEnemy].fWidth = fWidth;
			g_aEnemy[nCntEnemy].fHeight = fHeight;
			g_aEnemy[nCntEnemy].rect.bottom = fHeight;
			g_aEnemy[nCntEnemy].rect.left = fWidth;
			g_aEnemy[nCntEnemy].rect.right = fWidth;
			g_aEnemy[nCntEnemy].rect.top = fHeight;
			g_aEnemy[nCntEnemy].bUse = true;

			g_snakeHP.fMaxLife += g_aEnemy[nCntEnemy].fLife;

			//テクスチャ4枚分の読み込み
			D3DXCreateTextureFromFile(pDevice,
				g_aEnemy[nCntEnemy].pFileName,
				&g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//頂点座標の設定
			pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].rect.left;
			pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].rect.top;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].rect.right;
			pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].rect.top;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].rect.left;
			pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].rect.bottom;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].rect.right;
			pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].rect.bottom;
			pVtx[3].pos.z = 0.0f;

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

			break;
		}

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//===============================
//敵の被弾処理
//===============================
void HitEnemy(int nCntEnemy, float fDamage)
{
	if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
	{
		g_aEnemy[nCntEnemy].fLife -= fDamage;

		if (g_aEnemy[nCntEnemy].fLife > 0)
		{//生きていたら
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;	//ダメージ状態に
			g_aEnemy[nCntEnemy].nCntState = 30;				//状態管理カウンターを設定

		}
		else if (g_aEnemy[nCntEnemy].fLife <= 0)
		{//死んでいたら
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DEATH;	//デス
			g_aEnemy[nCntEnemy].bUse = false;
			g_nNumEnemy--;

			if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_PUNCHINGBAG)
			{
				//敵設置
				g_snakeHP.fMaxLife = 0.0f;	//MAX体力リセット
				SetEnemy(FILE_TEX_PB, D3DXVECTOR3(1100.0f, 490.0f, 0.0f), ENEMYTYPE_PUNCHINGBAG, 5, PB_WIDTH, PB_HEIGHT);//復活させる
			}
		}
		PlaySound(SOUND_LABEL_PLAYERATTACK_SE);	//ヒット音
	}
}

//===============================
//敵の設定処理
//===============================
ENEMY* GetEnemy(void)
{
	return &g_aEnemy[0];
}

SNAKEHP* GetSnakeHP(void)
{
	return &g_snakeHP;
}
//===============================
//敵の総数の取得
//===============================
int GetNumEnemy()
{
	return g_nNumEnemy;
}

//===============================
//蛇の更新
//===============================
void UpDateSnake(int nCntEnemy)
{
	int nCnt = 0;
	int nCntBody = 0;//蛇の体の順番
	int nState = 0;//状態

	g_aEnemy[nCntEnemy].rect.bottom = SNAKE_WIDTH;
	g_aEnemy[nCntEnemy].rect.left = SNAKE_WIDTH;
	g_aEnemy[nCntEnemy].rect.right = SNAKE_WIDTH;
	g_aEnemy[nCntEnemy].rect.top = SNAKE_WIDTH;

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEnemy;

	//順番を整える
	for (nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true && g_aEnemy[nCnt].nType == ENEMYTYPE_SNAKE)
		{//いたら
			g_aEnemy[nCnt].snake.nCntBody = nCntBody;//順番を入れてあげる
			nCntBody++;
		}

		if (nCntBody >= MAX_SNAKE_BODY)
		{//体の数を超えたら
			break;
		}
	}

	nCntBody = 0;//初期値に戻す

	//頭だったら
	if (g_aEnemy[nCntEnemy].snake.nCntBody == 0)
	{
		//攻撃状態じゃない
		if (g_aEnemy[nCntEnemy].snake.bAttack == false)
		{
			if (g_aEnemy[nCntEnemy].snake.nChillTime <= 0)
			{//一定時間たったら
				//ランダムで決めて
				nState = rand() % 100;
				//ランダムで出た値で状態を変える
				if (nState >= 0 && nState < 60)
				{
					g_aEnemy[nCntEnemy].snake.snakeState = SNAKESTATE_HEADBUTT;
				}
				else if (nState >= 60 && nState < 100)
				{
					g_aEnemy[nCntEnemy].snake.snakeState = SNAKESTATE_TOUR;

				}

				//アタック状態にする
				g_aEnemy[nCntEnemy].snake.bAttack = true;	//攻撃状態
				g_aEnemy[nCntEnemy].snake.nChillTime = rand()% 1000;	//タイマーゼロ
			}
			else
			{
				g_aEnemy[nCntEnemy].snake.nChillTime--;	//カウンターを加算
				SnakeStand(nCntEnemy);
			}
		}

		//攻撃状態
		if(g_aEnemy[nCntEnemy].snake.bAttack == true)
		{
			switch (g_aEnemy[nCntEnemy].snake.snakeState)
			{
				break;
			case SNAKESTATE_HEADBUTT:
				SnakeHeadbutt(nCntEnemy);
				break;

			case SNAKESTATE_TOUR:
				SnakeTour(nCntEnemy);
				break;
			}
		}
	}
	
	//順番にくっつけていく
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true && g_aEnemy[nCnt].nType == ENEMYTYPE_SNAKE)
		{
			if ((g_aEnemy[nCntBody].snake.nCntBody - g_aEnemy[nCnt].snake.nCntBody) == (-1))
			{//前のやつとの差がマイナス1だったら

				g_aEnemy[nCnt].vertex.fLot += (g_aEnemy[nCntBody].vertex.fLot - g_aEnemy[nCnt].vertex.fLot) * 0.01f;
				g_aEnemy[nCnt].pos.x = g_aEnemy[nCntBody].pos.x + sinf(D3DX_PI + g_aEnemy[nCntBody].vertex.fLot) * SNAKE_HEIGHT;
				g_aEnemy[nCnt].pos.y = g_aEnemy[nCntBody].pos.y + cosf(D3DX_PI + g_aEnemy[nCntBody].vertex.fLot) * SNAKE_HEIGHT;
			}
			nCntBody = nCnt;

			if (g_aEnemy[nCnt].vertex.fLot > D3DX_PI)
			{// 角度の正規化
				float Diff;
				Diff = (g_aEnemy[nCnt].vertex.fLot - D3DX_PI);
				g_aEnemy[nCnt].vertex.fLot = -D3DX_PI + Diff;
			}
			else if (g_aEnemy[nCnt].vertex.fLot < -D3DX_PI)
			{// 角度の正規化
				float Diff;
				Diff = (g_aEnemy[nCnt].vertex.fLot + D3DX_PI);
				g_aEnemy[nCnt].vertex.fLot = D3DX_PI - Diff;
			}
		}

		if (nCntBody >= MAX_SNAKE_BODY)
		{//体の数数を超えたら
			nCntBody = 0;	//初期値に戻す
			break;
		}
		g_aEnemy[nCntEnemy].vertex.fLength = sqrtf((SNAKE_WIDTH * SNAKE_WIDTH) + (SNAKE_HEIGHT * SNAKE_HEIGHT));
		g_aEnemy[nCntEnemy].vertex.fAngle = atan2f(SNAKE_HEIGHT, SNAKE_WIDTH);

		g_aEnemy[nCntEnemy].vertex.TopLeft.x = sinf(-D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle - g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.TopLeft.y = cosf(D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle - g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.TopRight.x = sinf(D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle + g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.TopRight.y = cosf(D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle + g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.BottomLeft.x = sinf(-D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle + g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.BottomLeft.y = cosf(-D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle + g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.BottomRight.x = sinf(D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle - g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;
		g_aEnemy[nCntEnemy].vertex.BottomRight.y = cosf(-D3DX_PI * 0.5f + g_aEnemy[nCntEnemy].vertex.fAngle - g_aEnemy[nCntEnemy].vertex.fLot) * g_aEnemy[nCntEnemy].vertex.fLength;

	}

	//頂点座標の設定
	pVtx[0].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].vertex.TopLeft.x;
	pVtx[0].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].vertex.TopLeft.y;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].vertex.TopRight.x;
	pVtx[1].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].vertex.TopRight.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].vertex.BottomLeft.x;
	pVtx[2].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].vertex.BottomLeft.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].vertex.BottomRight.x;
	pVtx[3].pos.y = g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].vertex.BottomRight.y;
	pVtx[3].pos.z = 0.0f;

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


	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	SetEffect(pVtx[0].pos,	//位置
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
		D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f),		//色
		EFFECTTYPE_NOMAL,						//通常エフェクト
		10.0f,									//ポリゴンサイズ
		0.0f,									//高さ
		0.0f,									//幅
		0.0f,									//ポリゴンサイズ減少数
		0.0f,									//移動量減少数
		5.0f,									//寿命
		0.0f,									//角度
		-1										//消すやつ
		);

	SetEffect(pVtx[1].pos,	//位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
		D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f),		//色
		EFFECTTYPE_NOMAL,						//通常エフェクト
		6.0f,									//ポリゴンサイズ
		0.0f,									//高さ
		0.0f,									//幅
		0.0f,									//ポリゴンサイズ減少数
		0.0f,									//移動量減少数
		4.0f,									//寿命
		0.0f,									//角度
		-1										//消すやつ
	);

	SetEffect(pVtx[2].pos,	//位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
		D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f),		//色
		EFFECTTYPE_NOMAL,						//通常エフェクト
		6.0f,									//ポリゴンサイズ
		0.0f,									//高さ
		0.0f,									//幅
		0.0f,									//ポリゴンサイズ減少数
		0.0f,									//移動量減少数
		4.0f,									//寿命
		0.0f,									//角度
		-1										//消すやつ
	);

	SetEffect(pVtx[3].pos,	//位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
		D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f),		//色
		EFFECTTYPE_NOMAL,						//通常エフェクト
		6.0f,									//ポリゴンサイズ
		0.0f,									//高さ
		0.0f,									//幅
		0.0f,									//ポリゴンサイズ減少数
		0.0f,									//移動量減少数
		4.0f,									//寿命
		0.0f,									//角度
		-1										//消すやつ
	);

	SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].snake.posFrontUnion.x, g_aEnemy[nCntEnemy].snake.posFrontUnion.y, 0.0f),	//位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),		//色
		EFFECTTYPE_NOMAL,						//通常エフェクト
		6.0f,									//ポリゴンサイズ
		0.0f,									//高さ
		0.0f,									//幅
		0.0f,									//ポリゴンサイズ減少数
		0.0f,									//移動量減少数
		4.0f,									//寿命
		0.0f,									//角度
		-1										//消すやつ
	);

	SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].snake.posAnderUnion.x, g_aEnemy[nCntEnemy].snake.posAnderUnion.y, 0.0f),	//位置
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
		D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),		//色
		EFFECTTYPE_NOMAL,						//通常エフェクト
		6.0f,									//ポリゴンサイズ
		0.0f,									//高さ
		0.0f,									//幅
		0.0f,									//ポリゴンサイズ減少数
		0.0f,									//移動量減少数
		4.0f,									//寿命
		0.0f,									//角度
		-1										//消すやつ
	);
}

//===============================
//蛇の頭突き
//===============================
void SnakeHeadbutt(int nSnakeHead)
{
	int nCntEnemy = 0;
	float fLoty = 0.0f;
	float distance, distance1 = 0.0f;

	D3DXVECTOR3 fMovey = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player* pPlayer = GetPlayer();	//プレイヤー取得

	switch (g_aEnemy[nSnakeHead].snakeMove.nCntMotion)
	{
	case 0://目的地への角度を求める
	//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT - g_aEnemy[nSnakeHead].pos.y);
		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 1://狙った向きへ頭を向けて
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//一定時間たったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//次のモーションへカウント
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
		}
		else
		{//角度を足し続ける
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 2://狙った方向に進んでいく
		//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT - g_aEnemy[nSnakeHead].pos.y);
		//目的地までの角度と距離を求めて
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 10)
		{//近くなかったら
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//近くなったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;//次のモーションへカウント

		}
		break;

	case 3://プレイヤーに狙い定め
		//今の場所からプレイヤーまでの間を調べる
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);

		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 60.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;	//次のモーションへカウント
		break;

	case 4:
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;	//次のモーションへカウント

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 60)
		{//一定時間たったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//次のモーションへカウント
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//蛇の声

		}
		else
		{//角度を足し続ける
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 5://突進
		//プレイヤーとの距離を測る
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;

		if (g_aEnemy[nSnakeHead].snakeMove.fLength <= SCREEN_HEIGHT)
		{//プレイヤーとの距離が短かったら
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//遠くなったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;	//モーションリセット
			g_aEnemy[nSnakeHead].snake.snakeState = SNAKESTATE_STANDE;//状態を待機状態へ
			g_aEnemy[nSnakeHead].snake.bAttack = false;//待機状態
		}
		
		break;
	}
	
}

//===============================
//蛇のツアー
//===============================
void SnakeTour(int nSnakeHead)
{
	int nCntEnemy = 0;
	float fLoty = 0.0f;
	float distance, distance1 = 0.0f;

	D3DXVECTOR3 fMovey = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player* pPlayer = GetPlayer();	//プレイヤー取得

	switch (g_aEnemy[nSnakeHead].snakeMove.nCntMotion)
	{
	case 0://目的地への角度を求める
		//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.5f - g_aEnemy[nSnakeHead].pos.y);
		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 1://狙った向きへ頭を向けて
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//一定時間たったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//次のモーションへカウント
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ

		}
		else
		{//角度を足し続ける
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 2://狙った方向に頭向けて
	//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.5f - g_aEnemy[nSnakeHead].pos.y);

		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 3://中心へゴー
	//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.5f - g_aEnemy[nSnakeHead].pos.y);
		//目的地までの角度と距離を求めて
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 30)
		{//近くなかったら
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		else
		{//近くなったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;//次のモーションへカウント
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//蛇の声
		}
		break;

	case 4://目的地への角度を求める
		//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (-SCREEN_HEIGHT - g_aEnemy[nSnakeHead].pos.y);
		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 5://頭向けて
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//一定時間たったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//次のモーションへカウント
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//蛇の声

		}
		else
		{//角度を足し続ける
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 6://
		//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 0.5f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (-SCREEN_HEIGHT * 2.0f- g_aEnemy[nSnakeHead].pos.y);
		//目的地までの角度と距離を求めて
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 30)
		{//近くなかったら
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//近くなったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;//次のモーションへカウント
		}
		break;

	case 7://目的地への角度を求める
		g_aEnemy[nSnakeHead].pos = D3DXVECTOR3(SCREEN_WIDTH * 2.0f,SCREEN_HEIGHT * 0.4f,0.0f);
	//今の場所から目的の値までの間を調べる
		distance = (-SCREEN_WIDTH * 2.0f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.4f - g_aEnemy[nSnakeHead].pos.y);
		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 8://頭向けて

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//一定時間たったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//次のモーションへカウント
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//蛇の声

		}
		else
		{//角度を足し続ける
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;//タイマーカウント
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 9://左側へゴー
	//今の場所から目的の値までの間を調べる
		distance = (-SCREEN_WIDTH * 2.0f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.4f - g_aEnemy[nSnakeHead].pos.y);
		//目的地までの角度と距離を求めて
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 30)
		{//近くなかったら
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 2.0f;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 2.0f;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//近くなったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;//次のモーションへカウント
		}
		break;

	case 10://目的地への角度を求める
		g_aEnemy[nSnakeHead].pos = D3DXVECTOR3(-SCREEN_WIDTH * 2.0f, SCREEN_HEIGHT * 0.7f, 0.0f);
		//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 2.0f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.8f - g_aEnemy[nSnakeHead].pos.y);
		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 30.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 11://頭向けて

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 30)
		{//一定時間たったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;		//次のモーションへカウント
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
			PlaySound(SOUND_LABEL_SNAKE_VOIS_SE);				//蛇の声

		}
		else
		{//角度を足し続ける
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;

		}

		break;

	case 12://左側へゴー
		//今の場所から目的の値までの間を調べる
		distance = (SCREEN_WIDTH * 2.0f - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (SCREEN_HEIGHT * 0.8f - g_aEnemy[nSnakeHead].pos.y);
		//目的地までの角度と距離を求めて
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 30)
		{//近くなかったら
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 2.0f;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 2.0f;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
		}
		else
		{//近くなったら
			g_aEnemy[nSnakeHead].snakeMove.nLoopCnt++;
			if (g_aEnemy[nSnakeHead].snakeMove.nLoopCnt >= 1)
			{
				//終わり
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;//次のモーションへカウント
				g_aEnemy[nSnakeHead].snake.snakeState = SNAKESTATE_STANDE;//状態を待機状態へ
				g_aEnemy[nSnakeHead].snake.bAttack = false;//待機状態
			}
			else
			{
				//繰り返す
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 7;
			}
		}
		break;
	}
}

//===============================
//蛇の待機状態
//===============================
void SnakeStand(int nSnakeHead)
{
	int nCntEnemy = 0;
	float fLoty = 0.0f;
	float distance, distance1 = 0.0f;

	D3DXVECTOR3 fMovey = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player* pPlayer = GetPlayer();	//プレイヤー取得

	switch (g_aEnemy[nSnakeHead].snakeMove.nCntMotion)
	{
	case 0://目的地への角度を求める
		//今の場所から目的の値までの間を調べる
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle - g_aEnemy[nSnakeHead].vertex.fLot) / 15.0f;
		g_aEnemy[nSnakeHead].snakeMove.nCntMotion++;
		break;

	case 1://狙った向きへ頭を向けて
		g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime++;
		//今の場所から目的の値までの間を調べる
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;

		if (g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime >= 15)
		{//一定時間たったら
			if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 200)
			{//離れていたら
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 2;		//次のモーションへカウント
				g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
			}
			else if (g_aEnemy[nSnakeHead].snakeMove.fLength < 100)
			{//近かったら
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 3;		//次のモーションへカウント
				g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
			}
			else
			{//どちらでもない
				g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;		//次のモーションへカウント
				g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
			}
		}
		else
		{//角度を足し続ける
			g_aEnemy[nSnakeHead].vertex.fLot += g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;

	case 2://近づく
		//今の場所から目的の値までの間を調べる
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle = atan2f(distance, distance1);
		//距離を調べて
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength < 200)
		{//近づいていたら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;		//次のモーションへカウント
			g_aEnemy[nSnakeHead].snakeMove.nCntMoveTime = 0;	//タイマーゼロ
		}
		else
		{
			//向いている方向に移動させる
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 0.6f;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 0.6f;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
			g_aEnemy[nSnakeHead].vertex.fLot = g_aEnemy[nSnakeHead].snakeMove.fLot;

		}
		break;

	case 3://距離を取る
		//今の場所から目的の値までの間を調べる
		distance = (pPlayer->pos.x - g_aEnemy[nSnakeHead].pos.x);
		distance1 = (pPlayer->pos.y - g_aEnemy[nSnakeHead].pos.y);
		//目的の角度を求めて
		g_aEnemy[nSnakeHead].snakeMove.fAngle =- atan2f(distance, distance1);
		//距離を調べて
		g_aEnemy[nSnakeHead].snakeMove.fLength = sqrtf((distance * distance) + (distance1 * distance1)) * 0.5f;
		//目的の角度から今の角度の間を調べる
		g_aEnemy[nSnakeHead].snakeMove.fLot = (g_aEnemy[nSnakeHead].snakeMove.fAngle);

		if (g_aEnemy[nSnakeHead].snakeMove.fLength >= 500)
		{//遠くなったら
			g_aEnemy[nSnakeHead].snakeMove.nCntMotion = 0;		//次のモーションへカウント
		}
		else
		{
			//向いている方向に移動させる
			g_aEnemy[nSnakeHead].move.x = sinf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 0.6f;
			g_aEnemy[nSnakeHead].move.y = cosf(g_aEnemy[nSnakeHead].snakeMove.fAngle) * SNAKE_MOVESPEED * 0.6f;
			g_aEnemy[nSnakeHead].pos += g_aEnemy[nSnakeHead].move;
			g_aEnemy[nSnakeHead].vertex.fLot = g_aEnemy[nSnakeHead].snakeMove.fLot;
		}
		break;
	}
}