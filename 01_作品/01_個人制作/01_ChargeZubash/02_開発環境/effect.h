#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//エフェクトの最大数
#define MAX_EFFECT (4090) //エフェクトの最大数

//エフェクトの種類
typedef enum
{
	EFFECTTYPE_NOMAL = 0,	//通常
	EFFECTTYPE_THUNDER,		//雷
	EFFECTTYPE_BEAMSWORD,	//ビームソード
	EFFECTTYPE_BEAM,		//ビームエフェクト
	EFFECTTYPE_ATTACK,		//攻撃判定があるエフェクト
	EFFECTTYPE_MAX
}EFFECTTYPE;

//エフェクト構造体の定義
typedef struct
{
	VERTEX vertex;			//四頂点
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//色
	int nType;				//タイプ
	int nDeleetType;		//消すやつ
	float fRadius;			//大きさの設定
	float fHeight;			//高さ
	float fWidth;			//幅
	float fPullRadius;		//頂点座標の設定
	float fPullmove;		//移動量
	float fMultiAlpha;		//アルファ値の減衰数multiplier
	float fLife;			//寿命
	float fLength;			//対角線
	float fAngle;			//向き
	float fLot;				//角度
	bool bUse;				//使用しているかどうか
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nType, float fRadius,float fHeight, float fWidth, float fPullRadius, float fPullmove, float fLife, float fAngle,int nDeleetType);
void UpdataBeamSwordEffect(int nCntEffect);
void UpdataBeamEffect(int nCntEffect);
void UpDateAttackEffect(int nCntEffect);
void EndEffect(int nType,int nDeleetType);
void UpdataThunderEffect(int nCntEffect);
#endif