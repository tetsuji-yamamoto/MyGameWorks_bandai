#ifndef _BEAM_H_
#define _BEAM_H_

#include "main.h"

//�r�[���̍ő吔
#define MAX_BEAM (256) //�r�[���̍ő吔

//�r�[���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Beam;

//�v���g�^�C�v�錾
void InitBeam(void);
void UninitBeam(void);
void UpdateBeam(void);
void DrawBeam(void);
void SetBeam(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fPullRadius, float fPullmove, float fLife);
#endif