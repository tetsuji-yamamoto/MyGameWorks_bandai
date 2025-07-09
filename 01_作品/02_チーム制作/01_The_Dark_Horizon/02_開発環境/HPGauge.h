#ifndef _HPGAUGE_H_
#define _HPGAUGE_H_

#include "main.h"

#define MAX_HPGAUGE_POLIGON (256)

// HP�Q�[�W��UI�̎��
typedef enum
{
	HPGAUGETYPE_BG = 0,			// �t���[��
	HPGAUGETYPE_GAUGE,			// �ʏ�Q�[�W
	HPGAUGETYPE_GAUGE_REDZONE,	// �ԃQ�[�W
	HPGAUGETYPE_MAX
}HPGAUGETYPE;

// HP�Q�[�W�\����
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	HPGAUGETYPE type;		// ���
	int nIdxUI;				// �C���f�b�N�X
	float fMaxWidth;		// �ő�̂��������@
	float fWidth;			// ��
	float fHeight;			// ����
	bool bUse;				// �g���Ă܂���
}HPGAUGE;

// �L���������Q�[�W�\����
typedef struct
{
	HPGAUGETYPE type;		// ���
	int nMaxHP;				// �ő�̗̑�
	int nIdxUI;				// �C���f�b�N�X
}HPGAUGE_HAVE;

//�v���g�^�C�v�錾
void InitHPGauge(void);
void UninitHPGauge(void);
void UpdateHPGauge(void);
void DrawHPGauge(void);

void SetHPGauge(HPGAUGE_HAVE* pHPGaugeHave, HPGAUGETYPE type, D3DXCOLOR col, float fHeight, float fWidth,int nMaxHP);
void UpdateHPGaugePos(HPGAUGE_HAVE* pHPGaugeHave, D3DXVECTOR3 pos, float fHeigt, float fSlide);
void UpdateHPGaugeWidth(HPGAUGE_HAVE* pHPGaugeHave, int nowHP);
void UpdateHPGaugeRedZoneWidth(HPGAUGE_HAVE* pHPGaugeHave, int nowHP);
void EndHPGauge(HPGAUGE_HAVE* pHPGaugeHave);
void UpdateGaugeWidth(HPGAUGE_HAVE* pHPGaugeHave, int nNowNum, bool bOrver);

#endif // !_HPGAUGE_H_
