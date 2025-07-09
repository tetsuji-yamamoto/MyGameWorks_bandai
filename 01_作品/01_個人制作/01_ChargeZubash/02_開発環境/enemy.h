#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//�}�N��
#define MAX_ENEMY (125)		//�G�̍ő吔
#define MAX_SNAKE_BODY (20)	//�G�̍ő吔
#define PB_WIDTH (50)		//��
#define PB_HEIGHT (100)		//����
#define SNAKE_WIDTH (20)	//��
#define SNAKE_HEIGHT (50)	//����
#define SNAKE_MOVESPEED (10)	//�ւ̑���
#define FILE_TEX_PB "data\\ENEMY\\Panchingbag_001.jpg"
#define FILE_TEX_SNAKE "data\\ENEMY\\Snake_001.png"

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_DEATH,		//���S���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�̎��
typedef enum 
{
	ENEMYTYPE_PUNCHINGBAG = 0,//�T���h�o�b�Opunching bag
	ENEMYTYPE_SNAKE,//��
	ENEMYTYPE_MAX
}ENEMYTYPE;

//�֍s����
typedef enum
{
	SNAKESTATE_APPEAR = 0,	//�o��
	SNAKESTATE_STANDE,		//�ҋ@
	SNAKESTATE_HEADBUTT,	//�U��Headbutt
	SNAKESTATE_TOUR,		//�U��tourbutt
	SNAKESTATE_MAX,
}SNAKESTATE;

//�֍\����
typedef struct
{
	D3DXVECTOR2 posFrontUnion;	//�O���̈ʒu
	D3DXVECTOR2 posAnderUnion;	//��덇�̈ʒu
	SNAKESTATE snakeState;		//�ւ̏��
	int nCntBody;				//���Ԗڂ̑̂�
	int nChillTime;				//�ҋ@���Ă��鎞��
	bool bAttack;				//�U�����邩�ǂ���
}SNAKE;

//�̗͍\����
typedef struct
{
	float fMaxLife;
	float fLife;
}SNAKEHP;

//�ւ̓����\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ړI�̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nCntMoveTime;	//�J�E���^�[
	int nCntMotion;		//�����J�E���^�[
	int nLoopCnt;		//���[�v�J�E���^�[
	float fLength;		//�_�Ɠ_�̋���
	float fAngle;		//����
	float fLot;			//�p�x
}SNAKEMOVE;

//�G�\����
typedef struct
{
	const char* pFileName;	//�t�@�C����
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F
	RECT rect;				//�l���_���
	VERTEX vertex;			//�l���_
	ENEMYSTATE state;		//���
	SNAKE snake;			//�֏��
	SNAKEMOVE snakeMove;	//�ւ̓���
	int nType;				//���
	float fLife;			//�̗�
	int nCntState;			//��ԊǗ��J�E���^�[
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g���Ă��邩�ǂ���
}ENEMY;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(const char * pFileName ,D3DXVECTOR3 pos, int nType, float fLife, float fWidth, float fHeight);
void HitEnemy(int nCntEnemy,float fDamage);
void UpDateSnake(int nCntEnemy);
void SnakeHeadbutt(int nSnakeHead);
void SnakeTour(int nSnakeHead);
void SnakeStand(int nSnakeHead);
ENEMY* GetEnemy(void);
SNAKEHP* GetSnakeHP(void);
int GetNumEnemy(void);
#endif
