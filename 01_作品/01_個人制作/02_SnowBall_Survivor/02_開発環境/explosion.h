#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

#define MAX_EXPOLOSION (256)	// ビルボードの最大数

// 玉セット構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 size;	// 大きさ
}SETEXPLO;

// ビルボード構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX mtxWorld;	// マトリクス
	int nCntTime;			// タイマー
	int nCntPtn;			// パターン
	bool bUse;				// 使用しているかどうか
}EXPLOSION;

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(SETEXPLO setExplo);

#endif // !_BILLBOARD_H_
