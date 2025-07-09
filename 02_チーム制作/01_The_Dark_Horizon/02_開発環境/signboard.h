#ifndef _SIGNBOARD_H_
#define _SIGNBOARD_H_

#include "main.h"

#define MAX_SIGNBOARD (10)

// ボードの種類
typedef enum
{
	BOARDTYPE_MOVE = 0,		// 移動
	BOARDTYPE_MAKE,			// 作る
	BOARDTYPE_SROW_SNOW,	// 投げる雪玉
	BOARDTYPE_SROW_ICE,		// 投げる氷
	BOARDTYPE_SROW_GRAVEL,	// 投げる砂利
	BOARDTYPE_MOKUTEKI,		// 投げる砂利
	BOARDTYPE_MAX
}BOARDTYPE;

// ボード構造体
typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// 色
	BOARDTYPE type;			// 種類
	float fWidth;			// 幅
	float fHeight;			// 高さ
	bool bUse;				// 使ってますか
}SIGNBOARD;

// ボード構造体
typedef struct
{
	int nIdx;	// どれ使ってるか
}SIGNBOARD_CONTROLLER;

//プロトタイプ宣言
void InitSignboard(void);
void UninitSignboard(void);
void UpdateSignboard(void);
void DrawSignboard(void);
void SetSignBoard(BOARDTYPE type, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
SIGNBOARD* GetSignBoard(void);
int GetSignBoardContllore(void);
#endif // !_SIGNBOARD_H_
