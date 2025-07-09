#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "shadow.h"

// �e�̎��
typedef enum
{
	BULLETTYPE_SNOW = 0,
	BULLETTYPE_SNOW_MEDIUM,
	BULLETTYPE_SNOW_BIG,
	BULLETTYPE_ICE,
	BULLETTYPE_GRAVEL,
	BULLETTYPE_GRAVEL_DIFFUSION,
	BULLETTYPE_MAX
}BULLETTYPE;

#define MAX_BULLET (256)			// �r���{�[�h�̍ő吔
#define BULLET_GRAVITY (0.2f)		// �e�̏d��
#define BULLET_SPEED (10.0f)		// �e�̑��x
#define BULLET_MAX_DISTANCE (100)	// �e�̍ő�򋗗�
#define BULLET_MAKE_SPEED (60)		// ��ʍ�s�搭����
#define BULLET_ATTACK_SNOW (4)				// ��ʂ̍U����
#define BULLET_ATTACK_SNOW_MIDIUM (7)		// ���ʂ̍U����
#define BULLET_ATTACK_SNOW_BIG (9)			// ��ʂ̍U����
#define BULLET_ATTACK_ICE (5)				// �X�ʂ̍U����
#define BULLET_ATTACK_GRAVEL (3)			// �����ʂ̍U����
#define BULLET_ATTACK_GRAVEL_DIFFSION (4)	// �����g�U�ʂ̍U����

#define FILE_TEX_BULLET_SNOW "date\\texture\\bullet\\SBS_BULLET_SNOW_001.png"
#define FILE_TEX_BULLET_ICE "date\\texture\\bullet\\SBS_BULLET_ICE_001.png"
#define FILE_TEX_BULLET_GRAVEL "date\\texture\\bullet\\SBS_BULLET_GRAVEL_001.png"

// �ʃZ�b�g�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 dir;	// �s���Ăق�������
	D3DXVECTOR3 size;	// �傫��
	D3DXVECTOR3 move;	// �ړ���
	int nType;			// ���
	float fLife;		// ����
}SETBULLET;

// �r���{�[�h�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posOld;		// �Â��ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 dir;		// �s���Ăق�������
	D3DXMATRIX mtxWorld;	// �}�g���N�X
	D3DXVECTOR3 move;		// �ړ���
	float fWidth;			// �傫��
	int nType;				// ���
	float fLife;			// ����
	bool bUse;				// �g�p���Ă��邩�ǂ���

	int nShadowIdx;	// �e�̃C���f�b�N�X
}BULLET;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SnowBall(int nCntBl);
void SnowBallMidium(int nCntBl);
void SnowBallBig(int nCntBl);
void IceBall(int nCntBl);
void GravelBall(int nCntBl);
void GravelBallDiffusion(int nCntBl);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nBlType);

bool CollisionSpharBullet(int nCnt);

#endif // !_BILLBOARD_H_
