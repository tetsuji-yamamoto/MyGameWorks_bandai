#ifndef _THUNDER_H_
#define _THUNDER_H_

#include "main.h"

typedef enum
{
	THUNDERTYPE_NOMAL = 0,
	THUNDERTYPE_MAX
}THUNDERTYPE;

typedef enum
{
	THUNDERDIRECT_XSELECT = 0,	//落ちる場所を選ぶ
	THUNDERDIRECT_YSELECT,		//落ちる場所を選ぶ
	THUNDERDIRECT_PREMONISION,	//落ちる場所を予感させる
	THUNDERDIRECT_FALLING,		//落雷
	THUNDERDIRECT_END,			//終わり
	THUNDERDIRECT_MAX,

}THUNDERDIRECT;
//マクロ定義
#define FILE_TEX_THUNDER "data\\THNDER\\Thunder_001.png"
#define MAX_THUNDER (50)//雷の最大数
#define THUNDER_WIDTH (25)//雷の幅
#define THUNDER_DAMAGE (1)//雷のダメージ

//雷構造体
typedef struct
{
	const char* pFileName;	//ファイルネーム
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;		//前の位置
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//色
	int nType;				//タイプ
	int nThunderx;			//落ちる場所
	int nDirection;			//演出
	int nCntTiming;			//落ちるタイミング
	int nCntStrikeTime;		//落ちるまでのタイミング
	int nEPower;			//電力
	float fThunderWidth;	//幅
	float fThunderHeight;	//高さ
	bool bUse;				//使用してるかどうか
	bool bHit;				//当たっているかどうか
	bool bFell;				//落ちたかどうか
}THUNDER;

//プロトタイプ宣言
void InitThunder(void);
void UninitThunder(void);
void UpdateThunder(void);
void DrawThunder(void);
void SetThunder(const char* pFileName, THUNDERTYPE type);
void LightningStrike(int nCntThunder);
void SelectStrike(int nCntThunder);
void ThunderFalling(int nCntThunder);
bool HitThunder(D3DXVECTOR3 pos, float fHeight);
#endif // !1
