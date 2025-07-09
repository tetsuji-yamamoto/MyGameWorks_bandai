#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

#define MAX_EFFECT (1024)		// �G�t�F�N�g�̍ő吔
#define MAX_EFFECT_TEXTUR (2)	// �G�t�F�N�g�̍ő�e�N�X�`����

// �G�t�F�N�g�^�C�v
typedef enum
{
	EFFECTTYPE_NOMAL = 0,	// �ʏ�
	EFFECTTYPE_TRAJECTORY,	// �O��
	EFFECTTYPE_SMOKE,		// ��
	EFFECTTYPE_MAX
}EFFECTTYPE;

// �G�t�F�N�g�^�C�v
typedef enum
{
	EFFECT_TEXTURETYPE_NOMAL = 0,	// �ʏ�
	EFFECT_TEXTURETYPE_SMOKE,		// ��
	EFFECT_TEXTURETYPE_MAX
}EFFECT_TEXTURETYPE;

// �G�t�F�N�g�\����
typedef struct
{
	D3DXMATRIX mtxWorld;	// �}�g���N�X
	EFFECTTYPE type;		// �^�C�v
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 gravity;	// �d��
	D3DXCOLOR col;			// �F
	int nLife;				// ����
	int nMaxLife;			// �����̍ő吔
	int nCntAmin;			// �A�j���[�V�����J�E���^�[
	int nCntPttern;			// �A�j���[�V�����p�^�[��
	float fSize;			// �傫��
	bool bUse;				// �g�p���Ă��邩�ǂ���
	bool bSubtractive;		// ���Z���������Z������

	bool bShadow;			// �e����܂���?
	int nShadowIdx;			// �e�̃C���f�b�N�X
}EFFECT;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(EFFECTTYPE effectType, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 gravity, D3DXCOLOR col, int nLife, float fSize, bool bShadow,bool bSubtractive);
void UpdateEffectTrajectory(int nCntEffect, VERTEX_3D* pVtx);
void UpdateEffectSmoke(int nCntEffect, VERTEX_3D* pVtx);
#endif // !_BILLBOARD_H_