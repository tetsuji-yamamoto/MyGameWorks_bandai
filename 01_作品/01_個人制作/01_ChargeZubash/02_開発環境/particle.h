#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"

//マクロ定義
#define MAX_PARTICLE (128)//パーティクルの最大数

//パーティクル構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nType;				//種類
	int nDeleetType;	//種類
	int nNumAppear;			//エフェクトの出す量
	int nRange;				//角度
	int nSpeedRange;		//速さの範囲
	float fPullRadius;		//頂点座標の設定
	float fPullMove;		//移動量の減少係数
	float fRadius;			//頂点座標の設定
	float fLife;			//寿命
	float fAngle;			//狙いの角度
	float fLowSpeed;		//最低の移動量
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
}Particle;

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXCOLOR col,int nType, int nNumAppear, int nRange, int nSpeedRange, float fPullMove, float fRadius, float fPullRadius,float fAngle, float fLife, float fLowSpeed, float fWidth, float fHeight, int nDeleetType);
#endif // !_PARTICLE_H_
