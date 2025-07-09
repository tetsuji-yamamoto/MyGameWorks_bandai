#ifndef _HPBAR_H_
#define _HPBAR_H_

#include "main.h"

#define MAX_HPBAR_PORI (6);//ポリゴン数

#define FILE_TEX_HPBAR_PLAYER_GAUGE "data\\HPBAR\\HPbar_Gauge_001.png"
#define FILE_TEX_HPBAR_PLAYER_FRAME "data\\HPBAR\\HPbar_Frame_001.png"
#define FILE_TEX_HPBAR_ENEMY_FRAME "data\\HPBAR\\HPbar_Snake_Fraame_001.png"

#define HPBARFRAME_PRAYER_WIDTH (long)(300)
#define HPBARFRAME_PRAYER_HEIGHT (long)(20)

#define HPBARGAUGE_PRAYER_WIDTH (long)(300)
#define HPBARGAUGE_PRAYER_HEIGHT (long)(10)

#define HPBARFRAME_ENEMY_WIDTH (long)(700)
#define HPBARFRAME_ENEMY_HEIGHT (long)(35)

#define HPBARGAUGE_ENEMY_WIDTH (long)(700)
#define HPBARGAUGE_ENEMY_HEIGHT (long)(10)

//HPBARタイプ列挙
typedef enum
{
	HPBARTYPE_PLAYERGAUGE = 0,	//プレイヤーゲージ
	HPBARTYPE_PLAYERGAUGE_BACK,	//プレイヤーゲージの後ろ
	HPBARTYPE_PLAYERFRAME,		//プレイヤーフレーム
	HPBARTYPE_ENEMYGAUGE_BACK,	//敵ゲージの後ろ
	HPBARTYPE_ENEMYGAUGE,		//敵ゲージ
	HPBARTYPE_ENEMYFRAME,		//敵フレーム
	HPBARTYPE_MAX,
}HPBARTYPE;

//HPBAR構造体
typedef struct
{
	const char* pFile;		//ファイル名
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	RECT rect;				//大きさ
	HPBARTYPE type;			//種類
	float fVari;				//変化量
	bool bUse;				//使用しているかどうか
}HPBAR;

//プロトタイプ
void InitHPbar(void);
void UninitHPbar(void);
void UpdateHPbar(void);
void DrawHPbar(void);
void SetHPbar(const char *pFile, D3DXVECTOR3 pos,long lWidth,long lHeight, HPBARTYPE type);
void VariHPbar(int nCntHPbar);
void EndHPbar(int nCntHPbar);
#endif