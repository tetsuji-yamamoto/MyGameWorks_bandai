#include "collision.h"
#include "effect.h"

//******************************************************
// 球の当たり判定
//******************************************************
bool CollisionSphere(D3DXVECTOR3 *pPosA, D3DXVECTOR3 *pPosB,float fLadiusA, float fLadiusB,bool bPush)
{
	bool bCollision = false;
	float fRange = fLadiusA + fLadiusB;		// 半径と半径を足した値
	D3DXVECTOR3 vecA = *pPosA - *pPosB;		// ベクトルA
	D3DXVECTOR3 vecB;						// fRangeのときのベクトルの値
	D3DXVECTOR3 vecC;						// fRangeのときのベクトルの値

	// 距離を求める
	float fLength = sqrtf((vecA.x * vecA.x) + (vecA.y * vecA.y) + (vecA.z * vecA.z));

	if (fLength <= 0)
	{
		fLength = 1;
	}

	if (fLength <= fRange)
	{// 短かったら
		bCollision = true;
		vecB = (fRange * vecA) / fLength;
		vecC = vecB - vecA;

		if (bPush)
		{// 押し返してもいいよ
			*pPosA += vecC;
		}

	}

	// 結果を返す
	return bCollision;
}

//******************************************************
// 当たり判定の位置更新
//******************************************************
void CollisionPointUpdate(D3DXVECTOR3* pCollisionPos, D3DXMATRIX parentMtx)
{
	pCollisionPos->x = parentMtx._41;
	pCollisionPos->y = parentMtx._42;
	pCollisionPos->z = parentMtx._43;
}