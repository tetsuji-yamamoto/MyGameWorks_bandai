#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//�^�C�g���|���S���^�C�v
typedef enum
{
	TITLETYPE_BG = 0,	//�^�C�g����BG
	TITLETYPE_LOGO,		//�^�C�g���̃��S
	TITLETYPE_START,	//�^�C�g���̃X�^�[�g�{�^��
	TITLETYPE_MAX
}TITLETYPE;

//�^�C�g�����o��
typedef enum
{
	TITLEDIRECT_LOGODOWN = 0,			//���S���������Ă���
	TITLEDIRECT_STARTAPPEAR,			//�X�^�[�g�o��
	TITLEDIRECT_STARTBRINK,				//�X�^�[�g�_��
	TITLEDIRECT_STARTBRINK_QUICKLY,		//�X�^�[�g�f�����_��quickly
}TITLEDIRECT;

//�^�C�g���\����
typedef struct
{
	const char* pFileName;	//�t�@�C���l�[��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nType;				//�^�C�v
	float fWidth;			//��
	float fHeight;			//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}TITLE;

//�^�C�g���̉��o�\����
typedef struct
{
	TITLEDIRECT titleDirect;	//�^�C�g�����o��
	int nTimer;					//�^�C�}�[
	bool bBrink;				//�_�łǂ����H
}TITLEDIRECTOR;

//�}�N����`
#define START_WIDTH (100)	//�X�^�[�g�̕�
#define START_HEIGHT (35)	//�X�^�[�g�̍���
#define LOGO_WIDTH (500)	//�X�^�[�g�̕�
#define LOGO_HEIGHT (100)	//�X�^�[�g�̍���
#define FILE_TEX_TITLE_LOGO "data\\TITLE\\TITLE_CHARGE_002.png"	//�^�C�g���̃��S
#define FILE_TEX_TITLE_START "data\\TITLE\\Start_002.png"		//�^�C�g���̃X�^�[�g�{�^��

//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(const char* pFileName, D3DXVECTOR3 pos, TITLETYPE type, D3DXCOLOR col, float fWidth, float fHeight);
void UpDateLogo(int nCntTitle);
void UpDateStart(int nCntTitle);
#endif