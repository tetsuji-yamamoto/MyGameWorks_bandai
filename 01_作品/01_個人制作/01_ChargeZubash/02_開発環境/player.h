#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "block.h"

#define PLAYER_HEIGHT (50)			//高さ
#define PLAYER_WIDTH (25)			//幅
#define PLAYER_MOVE (5.0f)			//移動量
#define PLAYER_GRAVITY (1.0f)		//重力
#define PLAYER_JUMP (20.0f)			//ジャンプ
#define MAX_PLAYER_HP (10.0f)		//最大HP
#define FILE_TEX_PLAYER_002 "data\\PLAYER\\player002.png"

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPER = 0,	//出現
	PLAYERSTATE_NOMAL,		//通常
	PLAYERSTATE_ATTACK,		//攻撃
	PLAYERSTATE_DAMAGE,		//ダメージ
	PLAYERSTATE_DETH,		//死亡
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤーの構造体
typedef struct
{
	RECT rect;			//当たり判定用
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//前回の位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//色
	PLAYERSTATE state;	//状態
	float fLife;		//体力
	int nJanpCounter;	//ジャンプ力カウンター
	int nCounterState;	//ステートカウンター
	int nPatternAnim;	//アニメーションパターン
	int nCounterAnim;	//アニメーションカウンター
	int nCounterJump;	//ジャンプ力カウンター
	int nCntSound;		//音カウンター
	float fAnimLine;	//アニメーション行
	float fGravity;		//重力
	bool bDisp;			//表示するか
	bool bJanp;			//ジャンプ中かどうか
	bool bStand;		//待機中かどうか
	bool bDirection;	//向きdirection
	bool bCharge;		//チャージ状態かどうか
	BLOCK* pBlock;		//対象ブロックへのポインタ
}Player;

//プロトタイプ
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(float fDamage);
void PlayerJamp(void);
#endif