#ifndef _WAVE_H_
#define _WAVE_H_

#include "main.h"
#include "enemy.h"

typedef enum
{
	WAVETYPE_0 = 0,
	WAVETYPE_1,
	WAVETYPE_2,
	WAVETYPE_3,
	WAVETYPE_4,
	WAVETYPE_MAX
}WAVETYPE;

// ウェーブ保存構造体
typedef struct
{
	int nEnemy[ENEMYTYPE_MAX];	// 敵情報
}WAVE;

// ウェーブ保存構造体
typedef struct
{
	WAVE wave[WAVETYPE_MAX];
	int nNowWave;	// 現在のウェーブ
}WAVEINFO;

// プロトタイプ宣言
void InitWave(void);
void ReadWave(void);
void WaveAppEnemy(void);

#endif