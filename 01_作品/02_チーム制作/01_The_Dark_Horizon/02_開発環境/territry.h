#ifndef _TERRITRY_H_
#define _TERRITRY_H_

#include "main.h"

// テリトリー構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	float fRadius;		// 半径(範囲)
	float fAngle;		// 行く向き
	int nTimer;			// 時間計測用
	int nBreakTimer;	// 休憩時間計測用
	int nPatrolTimer;	// パトロールタイマー
	int nAngerTimer;	// 怒りタイマー
	int nPatrolRimit;	// 巡回限界時間
}TERRITRY;

void SetTerritry(TERRITRY* pTerritry, D3DXVECTOR3 territryPos, float fRadius);
bool TerritryConfirmation(TERRITRY territry, D3DXVECTOR3 nowPos);

#endif // !_TERRITRY_H_
