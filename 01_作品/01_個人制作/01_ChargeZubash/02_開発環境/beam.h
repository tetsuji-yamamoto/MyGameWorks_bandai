#ifndef _BEAM_H_
#define _BEAM_H_

#include "main.h"

//ビームの最大数
#define MAX_BEAM (256) //ビームの最大数

//ビーム構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
}Beam;

//プロトタイプ宣言
void InitBeam(void);
void UninitBeam(void);
void UpdateBeam(void);
void DrawBeam(void);
void SetBeam(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fPullRadius, float fPullmove, float fLife);
#endif