#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "shadow.h"

// 弾の種類
typedef enum
{
	BULLETTYPE_SNOW = 0,
	BULLETTYPE_SNOW_MEDIUM,
	BULLETTYPE_SNOW_BIG,
	BULLETTYPE_ICE,
	BULLETTYPE_GRAVEL,
	BULLETTYPE_GRAVEL_DIFFUSION,
	BULLETTYPE_MAX
}BULLETTYPE;

#define MAX_BULLET (256)			// ビルボードの最大数
#define BULLET_GRAVITY (0.2f)		// 弾の重力
#define BULLET_SPEED (10.0f)		// 弾の速度
#define BULLET_MAX_DISTANCE (100)	// 弾の最大飛距離
#define BULLET_MAKE_SPEED (60)		// 雪玉差s区政時間
#define BULLET_ATTACK_SNOW (4)				// 雪玉の攻撃力
#define BULLET_ATTACK_SNOW_MIDIUM (7)		// 中玉の攻撃力
#define BULLET_ATTACK_SNOW_BIG (9)			// 大玉の攻撃力
#define BULLET_ATTACK_ICE (5)				// 氷玉の攻撃力
#define BULLET_ATTACK_GRAVEL (3)			// 砂利玉の攻撃力
#define BULLET_ATTACK_GRAVEL_DIFFSION (4)	// 砂利拡散玉の攻撃力

#define FILE_TEX_BULLET_SNOW "date\\texture\\bullet\\SBS_BULLET_SNOW_001.png"
#define FILE_TEX_BULLET_ICE "date\\texture\\bullet\\SBS_BULLET_ICE_001.png"
#define FILE_TEX_BULLET_GRAVEL "date\\texture\\bullet\\SBS_BULLET_GRAVEL_001.png"

// 玉セット構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 dir;	// 行ってほしい方向
	D3DXVECTOR3 size;	// 大きさ
	D3DXVECTOR3 move;	// 移動量
	int nType;			// 種類
	float fLife;		// 寿命
}SETBULLET;

// ビルボード構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posOld;		// 古い位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 dir;		// 行ってほしい方向
	D3DXMATRIX mtxWorld;	// マトリクス
	D3DXVECTOR3 move;		// 移動量
	float fWidth;			// 大きさ
	int nType;				// 種類
	float fLife;			// 寿命
	bool bUse;				// 使用しているかどうか

	int nShadowIdx;	// 影のインデックス
}BULLET;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SnowBall(int nCntBl);
void SnowBallMidium(int nCntBl);
void SnowBallBig(int nCntBl);
void IceBall(int nCntBl);
void GravelBall(int nCntBl);
void GravelBallDiffusion(int nCntBl);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nBlType);

bool CollisionSpharBullet(int nCnt);

#endif // !_BILLBOARD_H_
