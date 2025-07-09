#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

//マクロ
#define MAX_TIME (120)				//幅
#define MAX_TIME_NUM (3)			//枚数
#define MAX_TIME_NUM_HEIGHT (50)	//たかさ
#define MAX_TIME_NUM_WIDTH (50)		//幅
#define MAX_TIMEUP_NUM_HEIGHT (500)	//たかさ
#define MAX_TIMEUP_NUM_WIDTH (500)	//幅

#define FILE_TEX_NUMBER "data\\NUMBER\\Number_002.png"

//タイマー状況列挙型
typedef enum
{
	TIMERSTATE_NOMAL = 0,	//通常状態
	TIMERSTATE_UP,			//時間がない状態
	TIMERSTATE_MAX
}TIMERSTATE;

//タイマー構造体
typedef struct
{
	D3DXVECTOR3 pos;	//タイマーの位置
	D3DXCOLOR col;		//色
	int nTaimerState;	//タイマー状況
	int nTimer;			//タイマーの値
	int nTimerCount;	//遅らせカウント
}TIMER;

void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void AddTimer(void);
TIMER* GetTimer(void);
#endif