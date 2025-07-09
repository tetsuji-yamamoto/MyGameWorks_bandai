#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

// �}�N����`
#define FILE_TEX_TITLE_SBS "date\\texture\\title\\SBS_TITLE_001.png"
#define FILE_TEX_STRTBUTTON "date\\texture\\UI\\TITLE_UI_BUTTON_GAMESTART.png"
#define FILE_TEX_STRTBUTTON_SHINE "date\\texture\\UI\\TITLE_UI_BUTTON_GAMESTART_SHAINE.png"
#define FILE_TEX_TUTORIALBUTTON "date\\texture\\UI\\TITLE_UI_BUTTON_TUTORIAL.png"
#define FILE_TEX_TUTORIALBUTTON_SHINE "date\\texture\\UI\\TITLE_UI_BUTTON_TUTORIAL_SHAINE.png"

// �^�C�g���|���S���^�C�v
typedef enum
{
	TITLETYPE_TEST = 0,	// �^�C�g���̃e�X�g
	TITLETYPE_BG,		// �^�C�g����BG
	TITLETYPE_LOGO,		// �^�C�g���̃��S
	TITLETYPE_START,			// �^�C�g���̃X�^�[�g�{�^��
	TITLETYPE_START_SHINE,		// �^�C�g���̃X�^�[�g�{�^����
	TITLETYPE_TUTORIAL,			// �^�C�g���̃`���[�g���A���{�^��
	TITLETYPE_TUTORIAL_SHINE,	// �^�C�g���̃`���[�g���A���{�^����
	TITLETYPE_MAX
}TITLETYPE;

// �{�^���^�C�v
typedef enum
{
	BUTTONTYPE_START,	// �^�C�g���̃X�^�[�g�{�^��
	BUTTONTYPE_TUTORIAL,	// �^�C�g���̃`���[�g���A���{�^��
	BUTTONTYPE_MAX
}BUTTONTYPE;

// �^�C�g�����o��
typedef enum
{
	TITLEDIRECT_LOGODOWN = 0,			// ���S���������Ă���
	TITLEDIRECT_BUTTONAPPEAR,			// �{�^���o��
	TITLEDIRECT_STARTBUTTONBRINK,		// �X�^�[�g�{�^���_��
	TITLEDIRECT_TUTORIALBUTTONBRINK,	// �`���[�g���A���{�^���_��
	TITLEDIRECT_BUTTONBRINK_QUICKLY,	// �{�^���f�����_��quickly
}TITLEDIRECT;

// �^�C�g���\����
typedef struct
{
	const char* pFileName;	// �t�@�C���l�[��
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	TITLETYPE type;			// �^�C�v
	int nButtonIdx;			// �{�^���C���f�b�N�X
	float fWidth;			// ��
	float fHeight;			// ����
	bool bUse;				// �g�p���Ă��邩�ǂ���
}TITLE;

// �^�C�g���̉��o�\����
typedef struct
{
	TITLEDIRECT titleDirect;	// �^�C�g�����o��
	int nTimer;					// �^�C�}�[
	bool bBrink;				// �_�łǂ����H
}TITLEDIRECTOR;

// �v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(D3DXVECTOR3 pos, D3DXCOLOR col, TITLETYPE type, BUTTONTYPE buttonType, const char* pFileName, float fWidth, float fHeight);
int TitleManager(void);
int TitleLogoAnimation(D3DXVECTOR3 posDest, D3DXVECTOR3 move);
int TitleStartButtonAnimation(void);
int TitleTutorialButtonAnimation(void);
int TitleStartButtonShine(void);
int TitleTutorialButtonShine(void);
#endif