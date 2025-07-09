#ifndef _SNOWBALL_H_
#define _SNOWBALL_H_

#include "main.h"

// 雪玉の種類
typedef enum
{
	SNOWBALLTYPE_SNOW = 0,		// 雪
	SNOWBALLTYPE_SNOW_MIDIUM,	// 雪中くらい
	SNOWBALLTYPE_SNOW_BIG,		// 雪おっきい
	SNOWBALLTYPE_ICE,			// 氷
	SNOWBALLTYPE_GRAVEL,		// 砂利
	SNOWBALLTYPE_MAX
}SNOWBALLTYPE;

// マクロ定義
#define SB_WEIGHT_SNOW (2)			// 雪玉の重さ
#define SB_WEIGHT_SNOW_MIDIUM (3)	// 雪玉の重さ
#define SB_WEIGHT_SNOW_BIG (4)		// 雪玉の重さ
#define SB_WEIGHT_SNOW (2)		// 雪玉の重さ
#define SB_WEIGHT_ICE (3)		// 氷玉の重さ
#define SB_WEIGHT_GRAVEL (1)	// 砂利玉の重さ
#define SB_WEIGHT_MAX (10)		// 全体の重さ
#define MAX_SB_POLIGON (32)		// ポリゴンの最大数
#define SB_MAKETIMER_SNOW (10)		// 雪玉作る時間
#define SB_MAKETIMER_SNOW_MIDI (60)	// 雪玉中作る時間
#define SB_MAKETIMER_SNOW_BIG (90)	// 雪玉大作る時間
#define SB_MAKETIMER_ICE (30)		// 雪玉大作る時間
#define SB_MAKETIMER_GRAVEL (20)	// 雪玉大作る時間

// 雪玉構造体
typedef struct
{
	int nSnowBallWeight;	// 砂利玉の重さ
	int nSnowOrder[12];		// 雪玉の順番
	int nIceOrder[12];		// 氷の順番
	int nGravelOrder[12];	// 砂利の順番
	int nBallType;			// ボールの種類
	int nMakeType;			// 雪玉作る種類
	int nMakeTimerSnow;		// 雪玉作る時間
	int nMakeTimerSnowMidi;	// 雪玉中作る時間B
	int nMakeTimerSnowBig;	// 雪玉大作る時間C
	int nMakeTimerIce;		// 氷玉作る時間C
	int nMakeTimerIGravel;	// 砂利弾作る時間C
	bool bSrow;	// 投げた
}SNOWBALL;

// 雪玉管理構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXCOLOR col;		// 色
	RECT rect;			// 大きさ
	int nType;			// 種類
	bool bUse;			// 使用しているかどうか
}SNOWBALL_UI_MANAGER;

// プロトタイプ宣言
void InitSB(void);
void UninitSB(void);
void UpdateSB(void);
void DrawSB(void);
void SetSBUI(int nType, int nCntOrder);
void EndSBUI(SNOWBALL* pSnowBall, int nType);
int MakeOrderSnowBall(SNOWBALL* pSnowBall, int* nType);
int BreakOrderSnowBall(SNOWBALL* pSnowBall, int nType);
void MakeSnowBall(SNOWBALL* pSnowBall, int nMakeType);

#endif // !_SNOWBALL_H_
