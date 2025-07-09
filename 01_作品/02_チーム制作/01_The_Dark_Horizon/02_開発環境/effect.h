#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

#define MAX_EFFECT (1024)		// エフェクトの最大数
#define MAX_EFFECT_TEXTUR (2)	// エフェクトの最大テクスチャ数

// エフェクトタイプ
typedef enum
{
	EFFECTTYPE_NOMAL = 0,	// 通常
	EFFECTTYPE_TRAJECTORY,	// 軌跡
	EFFECTTYPE_SMOKE,		// 煙
	EFFECTTYPE_MAX
}EFFECTTYPE;

// エフェクトタイプ
typedef enum
{
	EFFECT_TEXTURETYPE_NOMAL = 0,	// 通常
	EFFECT_TEXTURETYPE_SMOKE,		// 煙
	EFFECT_TEXTURETYPE_MAX
}EFFECT_TEXTURETYPE;

// エフェクト構造体
typedef struct
{
	D3DXMATRIX mtxWorld;	// マトリクス
	EFFECTTYPE type;		// タイプ
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 gravity;	// 重力
	D3DXCOLOR col;			// 色
	int nLife;				// 寿命
	int nMaxLife;			// 寿命の最大数
	int nCntAmin;			// アニメーションカウンター
	int nCntPttern;			// アニメーションパターン
	float fSize;			// 大きさ
	bool bUse;				// 使用しているかどうか
	bool bSubtractive;		// 加算合成か減算合成か

	bool bShadow;			// 影ありますか?
	int nShadowIdx;			// 影のインデックス
}EFFECT;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(EFFECTTYPE effectType, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 gravity, D3DXCOLOR col, int nLife, float fSize, bool bShadow,bool bSubtractive);
void UpdateEffectTrajectory(int nCntEffect, VERTEX_3D* pVtx);
void UpdateEffectSmoke(int nCntEffect, VERTEX_3D* pVtx);
#endif // !_BILLBOARD_H_