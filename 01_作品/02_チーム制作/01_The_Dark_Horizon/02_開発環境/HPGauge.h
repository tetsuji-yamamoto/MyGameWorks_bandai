#ifndef _HPGAUGE_H_
#define _HPGAUGE_H_

#include "main.h"

#define MAX_HPGAUGE_POLIGON (256)

// HPゲージのUIの種類
typedef enum
{
	HPGAUGETYPE_BG = 0,			// フレーム
	HPGAUGETYPE_GAUGE,			// 通常ゲージ
	HPGAUGETYPE_GAUGE_REDZONE,	// 赤ゲージ
	HPGAUGETYPE_MAX
}HPGAUGETYPE;

// HPゲージ構造体
typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// 色
	HPGAUGETYPE type;		// 種類
	int nIdxUI;				// インデックス
	float fMaxWidth;		// 最大のおおきさ　
	float fWidth;			// 幅
	float fHeight;			// 高さ
	bool bUse;				// 使ってますか
}HPGAUGE;

// キャラが持つゲージ構造体
typedef struct
{
	HPGAUGETYPE type;		// 種類
	int nMaxHP;				// 最大の体力
	int nIdxUI;				// インデックス
}HPGAUGE_HAVE;

//プロトタイプ宣言
void InitHPGauge(void);
void UninitHPGauge(void);
void UpdateHPGauge(void);
void DrawHPGauge(void);

void SetHPGauge(HPGAUGE_HAVE* pHPGaugeHave, HPGAUGETYPE type, D3DXCOLOR col, float fHeight, float fWidth,int nMaxHP);
void UpdateHPGaugePos(HPGAUGE_HAVE* pHPGaugeHave, D3DXVECTOR3 pos, float fHeigt, float fSlide);
void UpdateHPGaugeWidth(HPGAUGE_HAVE* pHPGaugeHave, int nowHP);
void UpdateHPGaugeRedZoneWidth(HPGAUGE_HAVE* pHPGaugeHave, int nowHP);
void EndHPGauge(HPGAUGE_HAVE* pHPGaugeHave);
void UpdateGaugeWidth(HPGAUGE_HAVE* pHPGaugeHave, int nNowNum, bool bOrver);

#endif // !_HPGAUGE_H_
