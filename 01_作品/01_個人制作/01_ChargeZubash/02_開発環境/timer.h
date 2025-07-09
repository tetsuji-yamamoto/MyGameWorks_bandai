#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

//�}�N��
#define MAX_TIME (120)				//��
#define MAX_TIME_NUM (3)			//����
#define MAX_TIME_NUM_HEIGHT (50)	//������
#define MAX_TIME_NUM_WIDTH (50)		//��
#define MAX_TIMEUP_NUM_HEIGHT (500)	//������
#define MAX_TIMEUP_NUM_WIDTH (500)	//��

#define FILE_TEX_NUMBER "data\\NUMBER\\Number_002.png"

//�^�C�}�[�󋵗񋓌^
typedef enum
{
	TIMERSTATE_NOMAL = 0,	//�ʏ���
	TIMERSTATE_UP,			//���Ԃ��Ȃ����
	TIMERSTATE_MAX
}TIMERSTATE;

//�^�C�}�[�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�^�C�}�[�̈ʒu
	D3DXCOLOR col;		//�F
	int nTaimerState;	//�^�C�}�[��
	int nTimer;			//�^�C�}�[�̒l
	int nTimerCount;	//�x�点�J�E���g
}TIMER;

void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
void AddTimer(void);
TIMER* GetTimer(void);
#endif