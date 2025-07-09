#ifndef _CHARGE_H_
#define _CHARGE_H_

#include "main.h"

#define MAX_ELECTRICPOWER (5) //最大電力electric power
#define MAX_CHARGERUI (10)		//UIの枚数
#define CHARGE_HEIGHT (20)		//高さ
#define CHARGE_WIDTH (30)		//幅
#define FILE_TEX_CHARGER_FLAME "data\\CHARGER\\Charger_Flame_001.png"
#define FILE_TEX_CHARGER_GAUGE "data\\CHARGER\\Charger_Gauge_001.png"

//充電器UIタイプ列挙型
typedef enum
{
	CHARGEUITYPE_FLAME = 0,	//フレーム
	CHARGEUITYPE_GAUGE,		//ゲージ
	CHARGEUITYPE_MAX
}CHARGERUITYPE;

//充電器の状態列挙型
typedef enum
{
	CHARGESTATE_NONE = 0,	//ない
	CHARGESTATE_FULL,		//フル
	CHARGESTATE_MAX
}CHARGESTATE;

//充電器の種類
typedef enum
{
	CHARGENUM_ZERO = 0,	//一個目
	CHARGENUM_ONE,		//二個目
	CHARGENUM_TWO,		//三個目
	CHARGENUM_THREE,	//四個目
	CHARGENUM_FOUR,		//五個目
	CHARGENUM_MAX
}CHARGENUM;

//充電器UIの構造体
typedef struct
{
	const char* pFileName;	//ファイルのパス
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nType;				//種類
	int nState;				//状態
	int nNumber;			//個数
	float fHeight;			//高さ
	float fWidth;			//幅
	bool bUse;				//使用しているかどうか
}CHARGERUI;

//充電エネルギーの構造体
typedef struct
{
	float fChargrAmount;//充電量Charge amount
	int nCntTime;			//放電カウント
}CHARGE;

//プロトタイプ
void InitCharge(void);
void UninitCharge(void);
void UpdateCharge(void);
void DrawCharge(void);
void SetCharger(const char* pFileName, D3DXVECTOR3 pos, CHARGERUITYPE type, int num,float fWidth);
void ChargePower(float fEPower);
void ChargerFlameState(int nCntCharger);
void ChargerGaugeState(int nCntCharger);
void DisCharge(D3DXVECTOR3 pos);
CHARGE* GetCharge(void);
#endif