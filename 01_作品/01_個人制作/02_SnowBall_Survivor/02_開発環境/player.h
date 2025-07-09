#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "block.h"
#include "snowBall.h"
#include "model.h"
#include "motion.h"
#include "collision.h"
#include "HPGauge.h"
#include "shadow.h"
#include "effect.h"

// ���[�V�����̎��
typedef enum
{
	MOTIONTYPE_PLAYER_NEUTRAL = 0,	// �ҋ@
	MOTIONTYPE_PLAYER_MOVE,			// �ړ�
	MOTIONTYPE_PLAYER_ATTACK,		// �U��
	MOTIONTYPE_PLAYER_JUMP,			// �W�����v
	MOTIONTYPE_PLAYER_RANDING,		// ���n
	MOTIONTYPE_PLAYER_ATTACK_SUPER,	// ��Z
	MOTIONTYPE_PLAYER_MAKESNOWBALL,	// ���˂���
	MOTIONTYPE_PLAYER_SPEEDATTACK,	// ������
	MOTIONTYPE_PLAYER_WIN,			// ��
	MOTIONTYPE_PLAYER_LOSE,			// ����
	MOTIONTYPE_PLAYER_DAMAGE,		// �_���[�W
	MOTIONTYPE_PLAYER_DEATH,		// ��
	MOTIONTYPE_PLAYER_MAX
}MOTIONTYPE_PLAYER;

// �v���C���[�̃p�[�c�̔z�u��
typedef enum
{
	MODELPOSITION_PLAYER_BODY = 0,	// ��
	MODELPOSITION_PLAYER_HEAD,		// ��
	MODELPOSITION_PLAYER_ARM_R,		// �E�r
	MODELPOSITION_PLAYER_HAND_R,	// �E��
	MODELPOSITION_PLAYER_ARM_L,		// ���r
	MODELPOSITION_PLAYER_HAND_L,	// ����
	MODELPOSITION_PLAYER_LEG_R,		// �E��
	MODELPOSITION_PLAYER_FOOT_R,	// �E��
	MODELPOSITION_PLAYER_LEG_L,		// ����
	MODELPOSITION_PLAYER_FOOT_L,	// ����
	MODELPOSITION_PLAYER_MAX
}MODELPOSITION_PLAYER;

// �}�N����`
#define PLAYER_MOVE (5.0f)
#define PLAYER_JUMP (5.0f)
#define PLAYER_HP (50.0f)

// �v���C���[���\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posOld;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 rotDest;	// �ړI�̌���
	D3DXVECTOR3 size;		// �傫��
	int nMakeTimer;	// ��ʂ���鎞��

	// ��ʊ֌W
	SNOWBALL snowBall;		// ��ʏ��
	int nBlockType;			// ����ł�u���b�N�̃^�C�v

	// ���[�V�����̗�
	MOTIONTYPE_PLAYER motiontype;
	Model aModel[10];		// ���f��(�p�[�c)
	CHARPARAM charParam;	// �p�����[�^
	MOTION motion;			// ���[�V����

	// �����蔻��
	COLLISIONPOINT aPlayerColiPoint[MODELPOSITION_PLAYER_MAX];	// �����蔻��̈ʒu

	// �Q�[�W�̗�
	HPGAUGE_HAVE HPGaugeHave[3];	// HP�Q�[�W
	HPGAUGE_HAVE SBGaugeHave[3];	// ��ʃQ�[�W
	HPGAUGE_HAVE SBMidiGaugeHave;	// ��ʒ��Q�[�W
	HPGAUGE_HAVE SBBigGaugeHave;	// ��ʑ�Q�[�W
	HPGAUGE_HAVE SBIceGaugeHave;	// �X�ʃQ�[�W
	HPGAUGE_HAVE SBGraGaugeHave;	// �����ʃQ�[�W
	HPGAUGE_HAVE aSBWateGauge[3];	// �d���Q�[�W

	int nShadowIdx;	// �e�̃C���f�b�N�X
	int naSmokeIdx[2];	// ���̃C���f�b�N�X
}PLAYER;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER* GetPlayer(void);

void PlayerStateManegement(void);
void PlayerStateChangeMove(void);
void PlayerStateChangeJump(void);
void PlayerStateChangeAttack(void);
void HitPlayer(int nDamage);

#endif // !_PLAYER_H_
