#ifndef _HPBAR_H_
#define _HPBAR_H_

#include "main.h"

#define MAX_HPBAR_PORI (6);//�|���S����

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

//HPBAR�^�C�v��
typedef enum
{
	HPBARTYPE_PLAYERGAUGE = 0,	//�v���C���[�Q�[�W
	HPBARTYPE_PLAYERGAUGE_BACK,	//�v���C���[�Q�[�W�̌��
	HPBARTYPE_PLAYERFRAME,		//�v���C���[�t���[��
	HPBARTYPE_ENEMYGAUGE_BACK,	//�G�Q�[�W�̌��
	HPBARTYPE_ENEMYGAUGE,		//�G�Q�[�W
	HPBARTYPE_ENEMYFRAME,		//�G�t���[��
	HPBARTYPE_MAX,
}HPBARTYPE;

//HPBAR�\����
typedef struct
{
	const char* pFile;		//�t�@�C����
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	RECT rect;				//�傫��
	HPBARTYPE type;			//���
	float fVari;				//�ω���
	bool bUse;				//�g�p���Ă��邩�ǂ���
}HPBAR;

//�v���g�^�C�v
void InitHPbar(void);
void UninitHPbar(void);
void UpdateHPbar(void);
void DrawHPbar(void);
void SetHPbar(const char *pFile, D3DXVECTOR3 pos,long lWidth,long lHeight, HPBARTYPE type);
void VariHPbar(int nCntHPbar);
void EndHPbar(int nCntHPbar);
#endif