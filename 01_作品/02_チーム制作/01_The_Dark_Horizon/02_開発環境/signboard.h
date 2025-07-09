#ifndef _SIGNBOARD_H_
#define _SIGNBOARD_H_

#include "main.h"

#define MAX_SIGNBOARD (10)

// �{�[�h�̎��
typedef enum
{
	BOARDTYPE_MOVE = 0,		// �ړ�
	BOARDTYPE_MAKE,			// ���
	BOARDTYPE_SROW_SNOW,	// ��������
	BOARDTYPE_SROW_ICE,		// ������X
	BOARDTYPE_SROW_GRAVEL,	// �����鍻��
	BOARDTYPE_MOKUTEKI,		// �����鍻��
	BOARDTYPE_MAX
}BOARDTYPE;

// �{�[�h�\����
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	BOARDTYPE type;			// ���
	float fWidth;			// ��
	float fHeight;			// ����
	bool bUse;				// �g���Ă܂���
}SIGNBOARD;

// �{�[�h�\����
typedef struct
{
	int nIdx;	// �ǂ�g���Ă邩
}SIGNBOARD_CONTROLLER;

//�v���g�^�C�v�錾
void InitSignboard(void);
void UninitSignboard(void);
void UpdateSignboard(void);
void DrawSignboard(void);
void SetSignBoard(BOARDTYPE type, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
SIGNBOARD* GetSignBoard(void);
int GetSignBoardContllore(void);
#endif // !_SIGNBOARD_H_
