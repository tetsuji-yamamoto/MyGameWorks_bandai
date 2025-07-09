#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "model.h"
#include "motion.h"
#include "collision.h"
#include "HPGauge.h"
#include "territry.h"
#include "block.h"
#include "shadow.h"

// �G�l�~�[�̎��
typedef enum
{
	ENEMYTYPE_NOMAL = 0,	// �ʏ� 
	ENEMYTYPE_REMOATE,		// ���u
	ENEMYTYPE_MAX
}ENEMYTYPE;

// ���[�V�����̎��
typedef enum
{
	MOTIONTYPE_ENEMY_NEUTRAL = 0,	// �ҋ@
	MOTIONTYPE_ENEMY_MOVE,			// �ړ�
	MOTIONTYPE_ENEMY_ATTACK,		// �U��
	MOTIONTYPE_ENEMY_JUMP,			// �W�����v
	MOTIONTYPE_ENEMY_RANDING,		// ���n
	MOTIONTYPE_ENEMY_DAMAGE,		// �_���[�W
	MOTIONTYPE_ENEMY_DAETH,			// ��
	MOTIONTYPE_ENEMY_MAX
}MOTIONTYPE_ENEMY;

// �G�l�~�[�̃p�[�c�̔z�u��
typedef enum
{
	MODELPOSITION_ENEMY_BODY = 0,	// ��
	MODELPOSITION_ENEMY_HEAD,		// ��
	MODELPOSITION_ENEMY_ARM_R,		// �E�r
	MODELPOSITION_ENEMY_HAND_R,		// �E��
	MODELPOSITION_ENEMY_ARM_L,		// ���r
	MODELPOSITION_ENEMY_HAND_L,		// ����
	MODELPOSITION_ENEMY_LEG_R,		// �E��
	MODELPOSITION_ENEMY_FOOT_R,		// �E��
	MODELPOSITION_ENEMY_LEG_L,		// ����
	MODELPOSITION_ENEMY_FOOT_L,		// ����
	MODELPOSITION_ENEMY_MAX
}MODELPOSITION_ENEMY;

// �}�N����`
#define MAX_ENEMY (32)			// �G�̍ő吔
#define ENEMY_MOVE_SPEED (1.0f)	// �ړ���
#define ENEMY_MOVE_SPEED_CHASE (1.5f)	// �ǂ�������ړ���

// �G�l�~�[�̍\����
typedef struct
{
	LPDIRECT3DTEXTURE9 apTextureEnemy[6];	// �e�N�X�`���ւ̃|���^
	LPD3DXMESH pMeshEnemy;					// ���b�V��(���_���ւ̃|�C���^)
	LPD3DXBUFFER pBuffMatEnemy;				// �}�e���A���ւ̃|�C���^
	DWORD dwNumMatEnemy;					// �}�e���A���̐�
	D3DXMATRIX mtxWorldEnemy;				// ���[���h�}�g���b�N�X

	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 posOld;	// �Â��ʒu
	D3DXVECTOR3 move;	// �ړ���
	D3DXVECTOR3 rot;	// ����
	ENEMYTYPE type;		// ���
	bool bUse;			// �g���Ă��邩�ǂ���

	// ���[�V�����̗�
	MOTIONTYPE_ENEMY motiontype;	// ���[�V�����̎��
	Model aModel[10];				// ���f��(�p�[�c)
	CHARPARAM charParam;			// �p�����[�^
	MOTION motion;					// ���[�V����

	COLLISIONPOINT aColiPoint[MODELPOSITION_ENEMY_MAX];	// �����蔻��̈ʒu
	BLOCKCOLLISION blockCollision;

	HPGAUGE_HAVE HPGaugeHave[3];	// HP�Q�[�W

	TERRITRY myTerrtry;				// �e���g���[
	TERRITRY myDistance;			// 

	int nShadowIdx;		// �e�̃C���f�b�N�X
	int naSmokeIdx[2];	// ���̃C���f�b�N�X

}ENEMY;

// �G�l�~�[�̊Ǘ��\����
typedef struct
{
	int nNumEnemy;	// �G�l�~�[�̑������g�̊ԍ���
}ENEMY_MANAGER;

// �v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type);

void CollisionEnemy(int nCntEnemy);
void HitEnemy(int nCntEnemy, int nDamage);
void EnemyStateManegement(int nCnt);

void NeutralEnemy(int nCntEnemy);
void EnemyStateChangeMove(int nCntEnemy);
void ChaseEnemy(int nCntEnemy);
void AttackEnemy(int nCntEnemy);
void GoHomeEnemy(int nCntEnemy);
void PatrolEnemy(int nCntEnemy);

ENEMY *GetEnemy(void);
ENEMY_MANAGER GetEnemyManager(void);
#endif // !_ENEMY_H_
