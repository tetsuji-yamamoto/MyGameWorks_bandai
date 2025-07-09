#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "model.h"
#include "motion.h"
#include "collision.h"
#include "HPGauge.h"
#include "territry.h"
#include "block.h"
#include "shadow.h"

// エネミーの種類
typedef enum
{
	ENEMYTYPE_NOMAL = 0,	// 通常 
	ENEMYTYPE_REMOATE,		// 遠隔
	ENEMYTYPE_MAX
}ENEMYTYPE;

// モーションの種類
typedef enum
{
	MOTIONTYPE_ENEMY_NEUTRAL = 0,	// 待機
	MOTIONTYPE_ENEMY_MOVE,			// 移動
	MOTIONTYPE_ENEMY_ATTACK,		// 攻撃
	MOTIONTYPE_ENEMY_JUMP,			// ジャンプ
	MOTIONTYPE_ENEMY_RANDING,		// 着地
	MOTIONTYPE_ENEMY_DAMAGE,		// ダメージ
	MOTIONTYPE_ENEMY_DAETH,			// 死
	MOTIONTYPE_ENEMY_MAX
}MOTIONTYPE_ENEMY;

// エネミーのパーツの配置列挙
typedef enum
{
	MODELPOSITION_ENEMY_BODY = 0,	// 体
	MODELPOSITION_ENEMY_HEAD,		// 頭
	MODELPOSITION_ENEMY_ARM_R,		// 右腕
	MODELPOSITION_ENEMY_HAND_R,		// 右手
	MODELPOSITION_ENEMY_ARM_L,		// 左腕
	MODELPOSITION_ENEMY_HAND_L,		// 左手
	MODELPOSITION_ENEMY_LEG_R,		// 右腿
	MODELPOSITION_ENEMY_FOOT_R,		// 右足
	MODELPOSITION_ENEMY_LEG_L,		// 左腿
	MODELPOSITION_ENEMY_FOOT_L,		// 左足
	MODELPOSITION_ENEMY_MAX
}MODELPOSITION_ENEMY;

// マクロ定義
#define MAX_ENEMY (32)			// 敵の最大数
#define ENEMY_MOVE_SPEED (1.0f)	// 移動量
#define ENEMY_MOVE_SPEED_CHASE (1.5f)	// 追いかける移動量

// エネミーの構造体
typedef struct
{
	LPDIRECT3DTEXTURE9 apTextureEnemy[6];	// テクスチャへのポンタ
	LPD3DXMESH pMeshEnemy;					// メッシュ(頂点情報へのポインタ)
	LPD3DXBUFFER pBuffMatEnemy;				// マテリアルへのポインタ
	DWORD dwNumMatEnemy;					// マテリアルの数
	D3DXMATRIX mtxWorldEnemy;				// ワールドマトリックス

	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 posOld;	// 古い位置
	D3DXVECTOR3 move;	// 移動量
	D3DXVECTOR3 rot;	// 向き
	ENEMYTYPE type;		// 種類
	bool bUse;			// 使っているかどうか

	// モーションの類
	MOTIONTYPE_ENEMY motiontype;	// モーションの種類
	Model aModel[10];				// モデル(パーツ)
	CHARPARAM charParam;			// パラメータ
	MOTION motion;					// モーション

	COLLISIONPOINT aColiPoint[MODELPOSITION_ENEMY_MAX];	// 当たり判定の位置
	BLOCKCOLLISION blockCollision;

	HPGAUGE_HAVE HPGaugeHave[3];	// HPゲージ

	TERRITRY myTerrtry;				// テリトリー
	TERRITRY myDistance;			// 

	int nShadowIdx;		// 影のインデックス
	int naSmokeIdx[2];	// 煙のインデックス

}ENEMY;

// エネミーの管理構造体
typedef struct
{
	int nNumEnemy;	// エネミーの総数自身の間合い
}ENEMY_MANAGER;

// プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type);

void CollisionEnemy(int nCntEnemy);
void HitEnemy(int nCntEnemy, int nDamage);
void EnemyStateManegement(int nCnt);

void NeutralEnemy(int nCntEnemy);
void EnemyStateChangeMove(int nCntEnemy);
void ChaseEnemy(int nCntEnemy);
void AttackEnemy(int nCntEnemy);
void GoHomeEnemy(int nCntEnemy);
void PatrolEnemy(int nCntEnemy);

ENEMY *GetEnemy(void);
ENEMY_MANAGER GetEnemyManager(void);
#endif // !_ENEMY_H_
