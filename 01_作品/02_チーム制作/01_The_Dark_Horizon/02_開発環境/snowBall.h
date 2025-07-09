#ifndef _SNOWBALL_H_
#define _SNOWBALL_H_

#include "main.h"

// ��ʂ̎��
typedef enum
{
	SNOWBALLTYPE_SNOW = 0,		// ��
	SNOWBALLTYPE_SNOW_MIDIUM,	// �ᒆ���炢
	SNOWBALLTYPE_SNOW_BIG,		// �Ⴈ������
	SNOWBALLTYPE_ICE,			// �X
	SNOWBALLTYPE_GRAVEL,		// ����
	SNOWBALLTYPE_MAX
}SNOWBALLTYPE;

// �}�N����`
#define SB_WEIGHT_SNOW (2)			// ��ʂ̏d��
#define SB_WEIGHT_SNOW_MIDIUM (3)	// ��ʂ̏d��
#define SB_WEIGHT_SNOW_BIG (4)		// ��ʂ̏d��
#define SB_WEIGHT_SNOW (2)		// ��ʂ̏d��
#define SB_WEIGHT_ICE (3)		// �X�ʂ̏d��
#define SB_WEIGHT_GRAVEL (1)	// �����ʂ̏d��
#define SB_WEIGHT_MAX (10)		// �S�̂̏d��
#define MAX_SB_POLIGON (32)		// �|���S���̍ő吔
#define SB_MAKETIMER_SNOW (10)		// ��ʍ�鎞��
#define SB_MAKETIMER_SNOW_MIDI (60)	// ��ʒ���鎞��
#define SB_MAKETIMER_SNOW_BIG (90)	// ��ʑ��鎞��
#define SB_MAKETIMER_ICE (30)		// ��ʑ��鎞��
#define SB_MAKETIMER_GRAVEL (20)	// ��ʑ��鎞��

// ��ʍ\����
typedef struct
{
	int nSnowBallWeight;	// �����ʂ̏d��
	int nSnowOrder[12];		// ��ʂ̏���
	int nIceOrder[12];		// �X�̏���
	int nGravelOrder[12];	// �����̏���
	int nBallType;			// �{�[���̎��
	int nMakeType;			// ��ʍ����
	int nMakeTimerSnow;		// ��ʍ�鎞��
	int nMakeTimerSnowMidi;	// ��ʒ���鎞��B
	int nMakeTimerSnowBig;	// ��ʑ��鎞��C
	int nMakeTimerIce;		// �X�ʍ�鎞��C
	int nMakeTimerIGravel;	// �����e��鎞��C
	bool bSrow;	// ������
}SNOWBALL;

// ��ʊǗ��\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXCOLOR col;		// �F
	RECT rect;			// �傫��
	int nType;			// ���
	bool bUse;			// �g�p���Ă��邩�ǂ���
}SNOWBALL_UI_MANAGER;

// �v���g�^�C�v�錾
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
