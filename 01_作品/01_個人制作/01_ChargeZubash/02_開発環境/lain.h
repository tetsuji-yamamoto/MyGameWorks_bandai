#ifndef _LAIN_H_ //�}�N����`���ꂦ�ĂȂ�������
#define _LAIN_H_ //��d�C���N���[�h�h�~�}�N����`

#include "main.h"

//�J�\����
typedef struct
{
	const char* pFileName;	//�t�@�C���l�[��
	int nType;				//�^�C�v
	D3DXCOLOR col;			//�F
	float fTexMoveX;		//�e�N�X�`���̓���X
	float fTexMoveY;		//�e�N�X�`���̓���Y
	bool bUse;				//�g�p���Ă邩�ǂ���
}Lain;

//�v���g�^�C�v�錾
void UninitLain(void);	//�J�̏I��
void UpdateLain(void);	//�J�̍X�V
void DrawLain(void);	//�J�̕`��
void InitLain(void);	//�J�̏�����
#endif 