#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "block.h"
#include "snowBall.h"
#include "model.h"
#include "motion.h"
#include "collision.h"
#include "HPGauge.h"
#include "shadow.h"
#include "effect.h"

// モーションの種類
typedef enum
{
	MOTIONTYPE_PLAYER_NEUTRAL = 0,	// 待機
	MOTIONTYPE_PLAYER_MOVE,			// 移動
	MOTIONTYPE_PLAYER_ATTACK,		// 攻撃
	MOTIONTYPE_PLAYER_JUMP,			// ジャンプ
	MOTIONTYPE_PLAYER_RANDING,		// 着地
	MOTIONTYPE_PLAYER_ATTACK_SUPER,	// 大技
	MOTIONTYPE_PLAYER_MAKESNOWBALL,	// こねこね
	MOTIONTYPE_PLAYER_SPEEDATTACK,	// 早投げ
	MOTIONTYPE_PLAYER_WIN,			// 勝
	MOTIONTYPE_PLAYER_LOSE,			// 負け
	MOTIONTYPE_PLAYER_DAMAGE,		// ダメージ
	MOTIONTYPE_PLAYER_DEATH,		// 死
	MOTIONTYPE_PLAYER_MAX
}MOTIONTYPE_PLAYER;

// プレイヤーのパーツの配置列挙
typedef enum
{
	MODELPOSITION_PLAYER_BODY = 0,	// 体
	MODELPOSITION_PLAYER_HEAD,		// 頭
	MODELPOSITION_PLAYER_ARM_R,		// 右腕
	MODELPOSITION_PLAYER_HAND_R,	// 右手
	MODELPOSITION_PLAYER_ARM_L,		// 左腕
	MODELPOSITION_PLAYER_HAND_L,	// 左手
	MODELPOSITION_PLAYER_LEG_R,		// 右腿
	MODELPOSITION_PLAYER_FOOT_R,	// 右足
	MODELPOSITION_PLAYER_LEG_L,		// 左腿
	MODELPOSITION_PLAYER_FOOT_L,	// 左足
	MODELPOSITION_PLAYER_MAX
}MODELPOSITION_PLAYER;

// マクロ定義
#define PLAYER_MOVE (5.0f)
#define PLAYER_JUMP (5.0f)
#define PLAYER_HP (50.0f)

// プレイヤー情報構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posOld;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 rotDest;	// 目的の向き
	D3DXVECTOR3 size;		// 大きさ
	int nMakeTimer;	// 雪玉を作る時間

	// 雪玉関係
	SNOWBALL snowBall;		// 雪玉情報
	int nBlockType;			// 踏んでるブロックのタイプ

	// モーションの類
	MOTIONTYPE_PLAYER motiontype;
	Model aModel[10];		// モデル(パーツ)
	CHARPARAM charParam;	// パラメータ
	MOTION motion;			// モーション

	// 当たり判定
	COLLISIONPOINT aPlayerColiPoint[MODELPOSITION_PLAYER_MAX];	// 当たり判定の位置

	// ゲージの類
	HPGAUGE_HAVE HPGaugeHave[3];	// HPゲージ
	HPGAUGE_HAVE SBGaugeHave[3];	// 雪玉ゲージ
	HPGAUGE_HAVE SBMidiGaugeHave;	// 雪玉中ゲージ
	HPGAUGE_HAVE SBBigGaugeHave;	// 雪玉大ゲージ
	HPGAUGE_HAVE SBIceGaugeHave;	// 氷玉ゲージ
	HPGAUGE_HAVE SBGraGaugeHave;	// 砂利玉ゲージ
	HPGAUGE_HAVE aSBWateGauge[3];	// 重さゲージ

	int nShadowIdx;	// 影のインデックス
	int naSmokeIdx[2];	// 煙のインデックス
}PLAYER;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);

void PlayerStateManegement(void);
void PlayerStateChangeMove(void);
void PlayerStateChangeJump(void);
void PlayerStateChangeAttack(void);
void HitPlayer(int nDamage);

#endif // !_PLAYER_H_
