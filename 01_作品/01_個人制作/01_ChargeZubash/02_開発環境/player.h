#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "block.h"

#define PLAYER_HEIGHT (50)			//����
#define PLAYER_WIDTH (25)			//��
#define PLAYER_MOVE (5.0f)			//�ړ���
#define PLAYER_GRAVITY (1.0f)		//�d��
#define PLAYER_JUMP (20.0f)			//�W�����v
#define MAX_PLAYER_HP (10.0f)		//�ő�HP
#define FILE_TEX_PLAYER_002 "data\\PLAYER\\player002.png"

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPER = 0,	//�o��
	PLAYERSTATE_NOMAL,		//�ʏ�
	PLAYERSTATE_ATTACK,		//�U��
	PLAYERSTATE_DAMAGE,		//�_���[�W
	PLAYERSTATE_DETH,		//���S
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�̍\����
typedef struct
{
	RECT rect;			//�����蔻��p
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�F
	PLAYERSTATE state;	//���
	float fLife;		//�̗�
	int nJanpCounter;	//�W�����v�̓J�E���^�[
	int nCounterState;	//�X�e�[�g�J�E���^�[
	int nPatternAnim;	//�A�j���[�V�����p�^�[��
	int nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int nCounterJump;	//�W�����v�̓J�E���^�[
	int nCntSound;		//���J�E���^�[
	float fAnimLine;	//�A�j���[�V�����s
	float fGravity;		//�d��
	bool bDisp;			//�\�����邩
	bool bJanp;			//�W�����v�����ǂ���
	bool bStand;		//�ҋ@�����ǂ���
	bool bDirection;	//����direction
	bool bCharge;		//�`���[�W��Ԃ��ǂ���
	BLOCK* pBlock;		//�Ώۃu���b�N�ւ̃|�C���^
}Player;

//�v���g�^�C�v
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(float fDamage);
void PlayerJamp(void);
#endif