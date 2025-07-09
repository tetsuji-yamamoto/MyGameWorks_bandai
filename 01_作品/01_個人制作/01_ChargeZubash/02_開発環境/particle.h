#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"

//�}�N����`
#define MAX_PARTICLE (128)//�p�[�e�B�N���̍ő吔

//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nType;				//���
	int nDeleetType;	//���
	int nNumAppear;			//�G�t�F�N�g�̏o����
	int nRange;				//�p�x
	int nSpeedRange;		//�����͈̔�
	float fPullRadius;		//���_���W�̐ݒ�
	float fPullMove;		//�ړ��ʂ̌����W��
	float fRadius;			//���_���W�̐ݒ�
	float fLife;			//����
	float fAngle;			//�_���̊p�x
	float fLowSpeed;		//�Œ�̈ړ���
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Particle;

//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXCOLOR col,int nType, int nNumAppear, int nRange, int nSpeedRange, float fPullMove, float fRadius, float fPullRadius,float fAngle, float fLife, float fLowSpeed, float fWidth, float fHeight, int nDeleetType);
#endif // !_PARTICLE_H_
