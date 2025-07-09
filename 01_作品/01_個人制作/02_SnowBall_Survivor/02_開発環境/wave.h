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

// �E�F�[�u�ۑ��\����
typedef struct
{
	int nEnemy[ENEMYTYPE_MAX];	// �G���
}WAVE;

// �E�F�[�u�ۑ��\����
typedef struct
{
	WAVE wave[WAVETYPE_MAX];
	int nNowWave;	// ���݂̃E�F�[�u
}WAVEINFO;

// �v���g�^�C�v�錾
void InitWave(void);
void ReadWave(void);
void WaveAppEnemy(void);

#endif