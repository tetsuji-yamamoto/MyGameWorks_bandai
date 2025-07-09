#ifndef _EDIT_H_
#define _EDIT_H_

#include "main.h"

//�G�f�B�b�g�i���[�h�j�̎��
typedef enum
{
	EDITMODE_NONE = 0,		// �Ȃ�
	EDITMODE_BLOCK,			// �u���b�N
	EDITMODE_MAX
}EDITMODE;

// �G�f�B�^�[�Ǘ��\����
typedef struct
{
	EDITMODE mode;	// ���[�h
	int nCntTimer;	// �^�C�}�[
}EDITMANAGER;

// �v���g�^�C�v�錾
void InitEdit();
void SetEditMode(EDITMODE mode);
EDITMODE GetEditMode(void);

#endif // !_EDIT_H_