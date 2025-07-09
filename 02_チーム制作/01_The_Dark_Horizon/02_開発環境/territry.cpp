#include "territry.h"

// プロトタイプ宣言

//*******************************************
// テリトリーのセット
//*******************************************
void SetTerritry(TERRITRY * pTerritry,D3DXVECTOR3 territryPos,float fRadius)
{
	pTerritry->pos = territryPos;	// 位置設定
	pTerritry->fRadius = fRadius;	// 半径設定
}

//*******************************************
// テリトリーの確認
//*******************************************
bool TerritryConfirmation(TERRITRY territry, D3DXVECTOR3 nowPos)
{
	bool bOutSide = false;	// 外側に出てますか？

	// テリトリーの中心から今の位置のベクトル
	D3DXVECTOR3 vecA = nowPos - territry.pos;	

	// 距離を図る
	float fLength = sqrtf((vecA.x * vecA.x) + (vecA.y * vecA.y) + (vecA.z * vecA.z));

	if (fLength >= territry.fRadius)
	{// 半径よりデカかったら
		bOutSide = true;	// 出てるよ
	}

	// 結果を返す
	return bOutSide;
}