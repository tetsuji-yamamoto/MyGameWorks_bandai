#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "block.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "guide.h"
#include "enemy.h"
#include "snowBall.h"
#include "edit.h"
#include "timer.h"
#include "HPGauge.h"
#include "wave.h"
#include "smoke.h"
#include "cylinder.h"

// グローバル変数宣言
GAMESTATE g_gameState = GAMESTATE_NONE;	// ゲーム状態
int g_nCounterGameState = 0;			// 状態管理カウンター
bool g_bPause = false; 

//**************************************************************************************
// ゲーム画面の初期化処理
//**************************************************************************************
void InitGame(void)
{
	// UIの類
	InitSB();		// 雪玉
	InitTimer();	// タイマー
	InitHPGauge();	// HPゲージ
	InitPause();	// ポーズ

	// エフェクト類
	InitShadow();	// 影
	InitEffect();	// エフェクト
	InitParticle();	// パーティクル
	InitSmoke();	// 煙

	InitCamera();	// カメラ
	InitBlock();	// ブロック
	InitLight();	// ライト
	InitPlayer();	// プレイヤー
	InitEnemy();	// エネミー
	InitBullet();		// 弾
	InitExplosion();	// 爆発
#ifdef _DEBUG

	InitGuide();		// ガイド
#endif // _DEBUG

	//Initcylinder();		// 山


	g_gameState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;		//カウンターをゼロ
	g_bPause = false;				//ポーズ解除
}

//**************************************************************************************
// ゲーム画面の終了処理
//**************************************************************************************
void UninitGame(void)
{
	UninitShadow();		// 影
	UninitEffect();		// エフェクト
	UninitBlock();		// ブロック
	UninitPlayer();		// プレイヤー
	UninitEnemy();		// エネミー
	UninitBullet();		// 弾
	UninitExplosion();	// 爆発
#ifdef _DEBUG

	UninitGuide();		// ガイド
#endif
	//Uninitcylinder();	// 山

	// UIの類
	UninitSB();			// 雪玉
	UninitTimer();		// タイマー
	UninitHPGauge();	// HPゲージ

	UninitPause();	// ポーズ

}

//**************************************************************************************
// ゲーム画面の更新処理
//**************************************************************************************
void UpdateGame(void)
{


	if (g_bPause == true)
	{//ポーズ中
		//ポーズ中の更新処理
		UpdatePause();
	}
	else
	{//ポーズ中でなければ
		UpdateCamera();		//カメラ
		UpdateLight();		//ライト
		UpdatePlayer();		// プレイヤー
		UpdateEnemy();		// エネミー
		UpdateShadow();		// 影
		UpdateBlock();		// ブロック
		UpdateBullet();		// 弾
		UpdateExplosion();	// 爆発
		UpdateEffect();		// エフェクト
		UpdateParticle();	// パーティクル
#ifdef _DEBUG

		UpdateGuide();		// ガイド
#endif
		UpdateSmoke();		// 煙
	//	Updatecylinder();	// 山

		// UIの類
		UpdateSB();			// 雪玉
		UpdateHPGauge();	// HPゲージ

		if (GetEditMode() == EDITMODE_NONE)
		{
			UpdateTimer();		// タイマー	
		}
	}
	
	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//ポーズキー（P）が押された
		g_bPause = g_bPause ? false : true;
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:	// 通常状態

		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_nCounterGameState = 0;
			g_gameState = GAMESTATE_NONE;	// 何もしていない状態に設定
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//**************************************************************************************
// ゲーム画面の描画処理
//**************************************************************************************
void DrawGame(void)
{
	SetCamera();		// カメラ

#ifdef _DEBUG
	DrawGuide();		// ガイド
#endif

	//Drawcylinder();		// 山
	DrawBlock();		// ブロック
	DrawShadow();		// 影
	DrawTimer();		// タイマー
	DrawEnemy();		// エネミー
	DrawPlayer();		// プレイヤー
	DrawExplosion();	// 爆発
	DrawEffect();		// エフェクト
	DrawBullet();		// 弾

	// UIの類
	DrawHPGauge();		// HPゲージ
	DrawSB();			// 雪玉


	// ポーズ中
	if (g_bPause == true)
	{
		// ポーズの描画
		DrawPause();
	}
}

//**************************************************************************************
// ゲーム状態の設定
//**************************************************************************************
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}

//**************************************************************************************
// ゲーム状態の取得
//**************************************************************************************
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//**************************************************************************************
// ポーズの有効無効設定
//**************************************************************************************
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}