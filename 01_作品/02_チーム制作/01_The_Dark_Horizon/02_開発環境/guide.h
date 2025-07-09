#ifndef _GUIDE_H_
#define _GUIDE_H_

#include "main.h"

#define LINE_X (1)
#define LINE_Y (1)
#define LINE_Z (1)
#define GUIDE_LINE_X (50)
#define GUIDE_LINE_Z (50)

#define GUIDE_LINE_INTERVAL (10)

#define OLL_VERTEX (LINE_X * 2 + LINE_Y * 2 + LINE_Z * 2 + (GUIDE_LINE_X + 1) * 2 + (GUIDE_LINE_Z + 1) * 2)


// ガイド線タイプ
typedef enum
{
	GUDETYPE_START = 0,
	GUDETYPE_END,
	GUDETYPE_MAX,
}GUDETYPE;

// ガイド線構造体
typedef struct
{
	D3DXVECTOR3 posguide;	// 位置
	D3DXVECTOR3 rotguide;	// 向き
	D3DXCOLOR col;			// 色
	GUDETYPE type;			// 種類
	bool bUse;
}GUIDE;

// ガイド管理構造体
typedef struct
{
	bool bDisplay;
}GUDEMANAGER;

//プロトタイプ宣言
void InitGuide(void);
void UninitGuide(void);
void UpdateGuide(void);
void DrawGuide(void);
void SetGude(GUIDE guide,D3DXVECTOR3 sp, D3DXVECTOR3 ep);
#endif // !_POLYGON_H_