#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

// 当たり判定の位置
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	float fRadius;		// 当たり判定の大きさ
}COLLISIONPOINT;

// プロトタイプ宣言
bool CollisionSphere(D3DXVECTOR3* pPosA, D3DXVECTOR3* pPosB, float fLadiusA, float fLadiusB, bool bPush);
void CollisionPointUpdate(D3DXVECTOR3* pCollisionPos, D3DXMATRIX parentMtx);

#endif
