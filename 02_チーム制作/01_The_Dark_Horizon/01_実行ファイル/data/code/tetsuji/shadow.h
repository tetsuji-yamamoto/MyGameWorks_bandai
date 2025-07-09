#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

// マクロ定義
#define MAX_SHADOW (256)	// 影の最大数

// 影構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posEX;		// 位置EX
	D3DXVECTOR3 rot;		// 向き
	D3DXCOLOR col;			// 色
	D3DXMATRIX mtxWorld;	// マトリックス
	bool bUse;				// 使用するかどうか
	bool branding;			// 乗ってるかどうか
	float fWidth;			// 幅
}Shadow;

// プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadw(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void EndShadow(int nIdxShadow);

#endif // !_SHADOW_H_
