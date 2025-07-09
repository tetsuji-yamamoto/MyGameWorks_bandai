#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�G�t�F�N�g�̍ő吔
#define MAX_EFFECT (4090) //�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�̎��
typedef enum
{
	EFFECTTYPE_NOMAL = 0,	//�ʏ�
	EFFECTTYPE_THUNDER,		//��
	EFFECTTYPE_BEAMSWORD,	//�r�[���\�[�h
	EFFECTTYPE_BEAM,		//�r�[���G�t�F�N�g
	EFFECTTYPE_ATTACK,		//�U�����肪����G�t�F�N�g
	EFFECTTYPE_MAX
}EFFECTTYPE;

//�G�t�F�N�g�\���̂̒�`
typedef struct
{
	VERTEX vertex;			//�l���_
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F
	int nType;				//�^�C�v
	int nDeleetType;		//�������
	float fRadius;			//�傫���̐ݒ�
	float fHeight;			//����
	float fWidth;			//��
	float fPullRadius;		//���_���W�̐ݒ�
	float fPullmove;		//�ړ���
	float fMultiAlpha;		//�A���t�@�l�̌�����multiplier
	float fLife;			//����
	float fLength;			//�Ίp��
	float fAngle;			//����
	float fLot;				//�p�x
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nType, float fRadius,float fHeight, float fWidth, float fPullRadius, float fPullmove, float fLife, float fAngle,int nDeleetType);
void UpdataBeamSwordEffect(int nCntEffect);
void UpdataBeamEffect(int nCntEffect);
void UpDateAttackEffect(int nCntEffect);
void EndEffect(int nType,int nDeleetType);
void UpdataThunderEffect(int nCntEffect);
#endif