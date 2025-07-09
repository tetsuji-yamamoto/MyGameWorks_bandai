#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//�}�N����`
#define MAX_BLOCK (125)		//�u���b�N�̍ő吔
#define BLOCK_HEIGHT (32)	//�u���b�N�̍���
#define BLOCK_WIDTH (32)	//�u���b�N�̕�

#define FILE_TEX_BLOCK "data\\BLOCK\\Block_004.jpg"

//�u���b�N�̎��
typedef enum
{
	BLOCKTYPE_NOMAL = 0,//�����Ȃ����
	BLOCKTYPE_MOVEX,		//X�ɓ������
	BLOCKTYPE_MOVEY,		//Y�ɓ������
	BLOCKTYPE_MAX
}BLOCKTYPE;

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 posGoal;//�ڕW�̈ʒugoal
	int nCntTime;		//�J�E���g�^�C�}�[
	int nType;			//���
	float fWidth;		//��
	float fHeight;		//����
	float fTexX;		//�e�N�X�`������
	float fTexY;		//�e�N�X�`����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}BLOCK;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,int nType,float width,float height);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth);
void CollisionBlockX(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth,BLOCK ** pBlock);
bool CollisionBlockY(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth, BLOCK** pBlock);
BLOCK* GetBlock(void);
#endif