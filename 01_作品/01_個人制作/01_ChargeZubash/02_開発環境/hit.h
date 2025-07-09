#ifndef _HIT_H_
#define _HIT_H_

#include "main.h"

//アンカーポイントの場所anchor point
typedef enum
{
	ANCHORPOINT_CENTER = 0,//center
	ANCHORPOINT_BOTTOMLEFT,//左下
	ANCHORPOINT_BOTTOMCENTER,//下中央
}ANCHORPOINT;

//矩形の当たり判定構造体
typedef struct
{
	RECT rect;				//頂点情報
	VERTEX vertex;			//四頂点情報
	D3DXVECTOR3 pos;		//位置
	ANCHORPOINT anchrpoint;	//アンカーポイント
}HITBOX;

bool HitBox(RECT rectA, RECT rectB, D3DXVECTOR3 posA, D3DXVECTOR3 posB, ANCHORPOINT anchorpointA, ANCHORPOINT anchorpointB);	//矩形と矩形rectangleand rectangle

#endif // !_HIT_H_

