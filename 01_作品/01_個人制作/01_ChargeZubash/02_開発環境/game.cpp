#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "background.h"
#include "pause.h"
#include "player.h"
#include "block.h"
#include "effect.h"
#include "particle.h"
#include "thunder.h"
#include "charge.h"
#include "sword.h"
#include "enemy.h"
#include "score.h"
#include "HPbar.h"
#include "timer.h"
#include "lain.h"

//グローバル変数宣言
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲーム状態
int g_nCounterGameState = 0;			//状態管理カウンター
bool g_bPause = false; 

//===========================================
//ゲーム画面の初期化処理
//===========================================
void InitGame(void)
{
	int nCnt;

	InitPlayer();	//プレイヤー
	InitBlock();	//ブロック
	InitPause();	//ポーズ
	InitEffect();	//エフェクト
	InitParticle();	//パーティクル
	InitThunder();	//雷
	InitCharge();	//充電
	InitSword();	//剣
	InitEnemy();	//敵
	InitHPbar();	//HPバー
	InitTimer();	//タイマー
	InitLain();		//雨


	//ブロック設置
	//床一段目
	for (nCnt = 0; nCnt < 22; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//床一段目
	for (nCnt = 0; nCnt < 22; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 3.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//床二段目1
	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		SetBlock(D3DXVECTOR3(BLOCK_WIDTH * 3.0f + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT*0.5f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//床二段目2
	for (nCnt = 0; nCnt < 6; nCnt++)
	{
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH + BLOCK_WIDTH - BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT * 0.5f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//蛇せってい
	for (int nCntEnemy = 0; nCntEnemy < MAX_SNAKE_BODY; nCntEnemy++)
	{
		SetEnemy(FILE_TEX_SNAKE, D3DXVECTOR3(800.0f, 300.0f, 0.0f), ENEMYTYPE_SNAKE, 4, SNAKE_WIDTH, SNAKE_HEIGHT);
	}

	//SetEnemy(FILE_TEX_SNAKE, D3DXVECTOR3(-800.0f, -300.0f, 0.0f), ENEMYTYPE_PUNCHINGBAG, 4, SNAKE_WIDTH, SNAKE_HEIGHT);


	SetBlock(D3DXVECTOR3(BLOCK_WIDTH + (BLOCK_WIDTH * 12.0f),  SCREEN_HEIGHT * 0.5f + (BLOCK_WIDTH * 4.0f),0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);

	SetBlock(D3DXVECTOR3(BLOCK_WIDTH + (BLOCK_WIDTH * 18.0f),  SCREEN_HEIGHT * 0.5f,0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	SetBlock(D3DXVECTOR3(BLOCK_WIDTH + (BLOCK_WIDTH * 20.0f),  SCREEN_HEIGHT * 0.5f,0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);

	SetBlock(D3DXVECTOR3(BLOCK_WIDTH + (BLOCK_WIDTH * 26.0f),  SCREEN_HEIGHT * 0.5f + (BLOCK_WIDTH * 4.0f),0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	
	//背景
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_1, BGTYPE_CLOUDY_0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_2, BGTYPE_CLOUDY_1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	g_gameState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;		//カウンターをゼロ
	g_bPause = false;				//ポーズ解除
}

//===========================================
//ゲーム画面の終了処理
//===========================================
void UninitGame(void)
{
	UninitPlayer();		//プレイヤー
	UninitBlock();		//ブロック
	UninitPause();		//ポーズ
	UninitEffect();		//エフェクト
	UninitParticle();	//パーティクル
	UninitThunder();	//雷
	UninitCharge();		//充電
	UninitSword();		//剣
	UninitEnemy();		//敵
	UninitHPbar();		//HPバー
	UninitTimer();		//タイマー
	UninitLain();	//雨

	//音止める
	StopSound();

	//背景の終わり
	EndBackground(BGTYPE_CLOUDY_0);
	EndBackground(BGTYPE_CLOUDY_1);
}

//===========================================
//ゲーム画面の更新処理
//===========================================
void UpdateGame(void)
{
	if (g_bPause == true)
	{//ポーズ中
		//ポーズ中の更新処理
		UpdatePause();
	}
	else
	{//ポーズ中でなければ
		UpdateBlock();		//ブロック
		UpdateThunder();	//雷
		UpdatePlayer();		//プレイヤー
		UpdateSword();		//剣
		UpdateCharge();		//充電
		UpdateEnemy();		//敵
		UpdateEffect();		//エフェクト
		UpdateParticle();	//パーティクル
		UpdateHPbar();		//HPバー
		UpdateTimer();		//タイマー
		UpdateLain();		//雨


	}
	
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{//ポーズキー（P）が押された
		g_bPause = g_bPause ? false : true;
	}

	////画面遷移
	//if (KeyboardTrigger(DIK_RETURN) == true)
	//{
	//	SetFade(MODE_RESULT);
	//}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://通常状態

		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	//何もしていない状態に設定
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//===========================================
//ゲーム画面の描画処理
//===========================================
void DrawGame(void)
{
	DrawThunder();	//雷
	DrawBlock();	//ブロック
	DrawEnemy();	//敵
	DrawSword();	//剣
	DrawPlayer();	//プレイヤー
	DrawCharge();	//充電
	DrawParticle();	//パーティクル
	DrawEffect();	//エフェクト
	DrawLain();		//雨
	DrawHPbar();	//HPバー
	DrawTimer();	//タイマー

	//ポーズ中
	if (g_bPause == true)
	{
		//ポーズの描画
		DrawPause();
	}
}

//===========================================
//ゲーム状態の設定
//===========================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}

//===========================================
//ゲーム状態の取得
//===========================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//===========================================
//ポーズの有効無効設定
//===========================================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}