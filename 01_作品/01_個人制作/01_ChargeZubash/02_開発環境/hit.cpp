#include "hit.h"
#include "effect.h"
//矩形と矩形の当たり判定
bool HitBox(RECT rectA, RECT rectB,D3DXVECTOR3 posA,D3DXVECTOR3 posB, ANCHORPOINT anchorpointA, ANCHORPOINT anchorpointB)
{
	bool bHit = false;
	HITBOX hitbox[2];

	//ブチコム
	hitbox[0].rect = rectA;
	hitbox[1].rect = rectB;
	hitbox[0].pos = posA;
	hitbox[1].pos = posB;
	hitbox[0].anchrpoint = anchorpointA;
	hitbox[1].anchrpoint = anchorpointB;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{//二つ分計算
		//四頂点に情報ぶち込む
		switch (hitbox[nCnt].anchrpoint)
		{
		case ANCHORPOINT_CENTER://中央
			hitbox[nCnt].vertex.BottomLeft.x = hitbox[nCnt].pos.x - hitbox[nCnt].rect.left;
			hitbox[nCnt].vertex.BottomLeft.y = hitbox[nCnt].pos.y + hitbox[nCnt].rect.bottom;
			hitbox[nCnt].vertex.BottomRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.BottomRight.y = hitbox[nCnt].pos.y + hitbox[nCnt].rect.bottom;
			hitbox[nCnt].vertex.TopLeft.x = hitbox[nCnt].pos.x - hitbox[nCnt].rect.left;
			hitbox[nCnt].vertex.TopLeft.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top;
			hitbox[nCnt].vertex.TopRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.TopRight.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top;
			break;

		case ANCHORPOINT_BOTTOMLEFT://左下
			hitbox[nCnt].vertex.BottomLeft.x = hitbox[nCnt].pos.x;
			hitbox[nCnt].vertex.BottomLeft.y = hitbox[nCnt].pos.y;
			hitbox[nCnt].vertex.BottomRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.BottomRight.y = hitbox[nCnt].pos.y;
			hitbox[nCnt].vertex.TopLeft.x = hitbox[nCnt].pos.x;
			hitbox[nCnt].vertex.TopLeft.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top * 2.0f;
			hitbox[nCnt].vertex.TopRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.TopRight.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top * 2.0f;
			break;

		case ANCHORPOINT_BOTTOMCENTER://下中央
			hitbox[nCnt].vertex.BottomLeft.x = hitbox[nCnt].pos.x - hitbox[nCnt].rect.left;
			hitbox[nCnt].vertex.BottomLeft.y = hitbox[nCnt].pos.y;
			hitbox[nCnt].vertex.BottomRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.BottomRight.y = hitbox[nCnt].pos.y;
			hitbox[nCnt].vertex.TopLeft.x = hitbox[nCnt].pos.x - hitbox[nCnt].rect.left;
			hitbox[nCnt].vertex.TopLeft.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top * 2.0f;
			hitbox[nCnt].vertex.TopRight.x = hitbox[nCnt].pos.x + hitbox[nCnt].rect.right;
			hitbox[nCnt].vertex.TopRight.y = hitbox[nCnt].pos.y - hitbox[nCnt].rect.top * 2.0f;
			break;
		}
	}

	if (hitbox[0].vertex.TopLeft.x <= hitbox[1].vertex.BottomRight.x &&
		hitbox[1].vertex.TopLeft.x <= hitbox[0].vertex.BottomRight.x &&
		hitbox[0].vertex.TopLeft.y <= hitbox[1].vertex.BottomRight.y &&
		 hitbox[1].vertex.TopLeft.y <= hitbox[0].vertex.BottomRight.y)
	{
		bHit = true;
	}

	//SetEffect(D3DXVECTOR3(hitbox[0].vertex.BottomLeft.x, hitbox[0].vertex.BottomLeft.y, 0.0f),	//位置
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
	//	D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f),		//色
	//	EFFECTTYPE_NOMAL,						//通常エフェクト
	//	10.0f,									//ポリゴンサイズ
	//	0.0f,									//高さ
	//	0.0f,									//幅
	//	0.0f,									//ポリゴンサイズ減少数
	//	0.0f,									//移動量減少数
	//	2.0f,									//寿命
	//	0.0f,									//角度
	//	-1										//消すやつ
	//);

	//SetEffect(D3DXVECTOR3(hitbox[0].vertex.BottomRight.x, hitbox[0].vertex.BottomRight.y, 0.0f),	//位置
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
	//	D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f),		//色
	//	EFFECTTYPE_NOMAL,						//通常エフェクト
	//	10.0f,									//ポリゴンサイズ
	//	0.0f,									//高さ
	//	0.0f,									//幅
	//	0.0f,									//ポリゴンサイズ減少数
	//	0.0f,									//移動量減少数
	//	2.0f,									//寿命
	//	0.0f,									//角度
	//	-1										//消すやつ
	//);

	//SetEffect(D3DXVECTOR3(hitbox[0].vertex.TopLeft.x, hitbox[0].vertex.TopLeft.y, 0.0f),	//位置
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
	//	D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f),		//色
	//	EFFECTTYPE_NOMAL,						//通常エフェクト
	//	10.0f,									//ポリゴンサイズ
	//	0.0f,									//高さ
	//	0.0f,									//幅
	//	0.0f,									//ポリゴンサイズ減少数
	//	0.0f,									//移動量減少数
	//	2.0f,									//寿命
	//	0.0f,									//角度
	//	-1										//消すやつ
	//);

	//SetEffect(D3DXVECTOR3(hitbox[0].vertex.TopRight.x, hitbox[0].vertex.TopRight.y, 0.0f),	//位置
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),			//移動量
	//	D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f),		//色
	//	EFFECTTYPE_NOMAL,						//通常エフェクト
	//	10.0f,									//ポリゴンサイズ
	//	0.0f,									//高さ
	//	0.0f,									//幅
	//	0.0f,									//ポリゴンサイズ減少数
	//	0.0f,									//移動量減少数
	//	2.0f,									//寿命
	//	0.0f,									//角度
	//	-1										//消すやつ
	//);

	return bHit;
}