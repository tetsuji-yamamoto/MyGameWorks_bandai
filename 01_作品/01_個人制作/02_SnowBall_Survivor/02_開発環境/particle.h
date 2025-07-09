#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "effect.h"

#define MAX_PARTICLE (256)	// 最大パーティクル数

// パーティクルタイプ
typedef enum
{
	PATITYPE_NOMAL = 0,// 通常
	PATITYPE_MAX
}PATITIPE;

// パーティクル構造体
typedef struct
{
	int nAmount;	// 出す量
	bool bUse;
}PARTICLE;

// プロトタイプ宣言
void InitParticle(void);
void UpdateParticle(void);
void SetParticle(EFFECTTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 gravity, D3DXCOLOR col, int nAmount, int nLife, float fSize, float fSpeed, bool bShadow, bool bSubtractive);

#endif // !_PARTICLE_H_
