#include "tutorial.h"
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
#include "score.h"
#include "smoke.h"
#include "signboard.h"

// グローバル変数宣言
GAMESTATE g_tutorialState = GAMESTATE_NONE;	// ゲーム状態
int g_nCounterTutorialState = 0;			// 状態管理カウンター
bool g_bPauseTutorial = false;

//*************************************************
// チュートリアル初期化
//*************************************************
void InitTutorial(void)
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
	InitGuide();		// ガイド
	InitWave();			// ウェーブ

	InitSignboard();	// 案内標識

	g_tutorialState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterTutorialState = 0;		//カウンターをゼロ
	g_bPauseTutorial = false;				//ポーズ解除
}

//*************************************************
// チュートリアル終了
//*************************************************
void UninitTutorial(void)
{
	UninitCamera();		//カメラ
	UninitLight();		//ライト
	UninitShadow();		// 影
	UninitEffect();		// エフェクト
	UninitBlock();		// ブロック
	UninitPlayer();		// プレイヤー
	UninitEnemy();		// エネミー
	UninitBullet();		// 弾
	UninitExplosion();	// 爆発
	UninitGuide();		// ガイド

	// UIの類
	UninitSB();			// 雪玉
	UninitTimer();		// タイマー
	UninitHPGauge();	// HPゲージ

	UninitPause();	// ポーズ

	UninitSignboard();	// 案内標識
}

//*************************************************
// チュートリアル更新
//*************************************************
void UpdateTutorial(void)
{
	if (g_bPauseTutorial == true)
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
		UpdateGuide();		// ガイド
		UpdateSmoke();		// 煙

		// UIの類
		UpdateSB();			// 雪玉
		UpdateTimer();		// タイマー	
		UpdateHPGauge();	// HPゲージ
		UpdateSignboard();	// 案内標識

		// ウェーブ管理

	//	WaveAppEnemy();
	}

	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{//ポーズキー（P）が押された
		g_bPauseTutorial = g_bPauseTutorial ? false : true;
	}

	switch (g_tutorialState)
	{
	case GAMESTATE_NORMAL:	// 通常状態

		break;

	case GAMESTATE_END:
		g_nCounterTutorialState++;
		if (g_nCounterTutorialState >= 60)
		{
			g_nCounterTutorialState = 0;
			g_tutorialState = GAMESTATE_NONE;	// 何もしていない状態に設定
			SetFade(MODE_GAME);
		}
		break;
	}
}

//*************************************************
// チュートリアル描画
//*************************************************
void DrawTutorial(void)
{
	SetCamera();		// カメラ

#ifdef _DEBUG
	DrawGuide();		// ガイド
#endif

	DrawBlock();		// ブロック
	DrawShadow();		// 影
	DrawEnemy();		// エネミー
	DrawPlayer();		// プレイヤー
	DrawExplosion();	// 爆発
	DrawEffect();		// エフェクト
	DrawBullet();		// 弾
	DrawSignboard();	// 案内標識

	if (GetEditMode() == EDITMODE_BLOCK)
	{
	}
	else
	{
		// UIの類
		DrawTimer();		// タイマー
		DrawSB();			// 雪玉
		DrawHPGauge();		// HPゲージ
	}


	// ポーズ中
	if (g_bPauseTutorial == true)
	{
		// ポーズの描画
		DrawPause();
	}
}

//**************************************************************************************
// ポーズの有効無効設定
//**************************************************************************************
void SetEnablePauseEX(bool bPause)
{
	g_bPauseTutorial = bPause;
}