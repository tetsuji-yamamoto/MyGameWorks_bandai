#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//�`���[�g���A���|���S���^�C�v
typedef enum
{
	TUTORIALTYPE_MOVE = 0,	//�`���[�g���A���ړ�
	TUTORIALTYPE_JUMP,		//�`���[�g���A���W�����v
	TUTORIALTYPE_ATTACK,	//�`���[�g���A���U��
	TUTORIALTYPE_THUNDER,	//�`���[�g���A����
	TUTORIALTYPE_DISCHARGE,	//�`���[�g���A�����o
	TUTORIALTYPE_END,		//�`���[�g���A���I���
	TUTORIALTYPE_MAX
}TUTRIALTYPE;

#define FILE_TEX_TUTORIAL_TEST "data\\TUTORIAL\\test.png"
#define FILE_TEX_TUTORIAL_MOVE "data\\TUTORIAL\\Tutorial_MOVE_001.png"
#define FILE_TEX_TUTORIAL_JUMP "data\\TUTORIAL\\Tutorial_JUMP_001.png"
#define FILE_TEX_TUTORIAL_ATTACK "data\\TUTORIAL\\Tutorial_ATTACK_001.png"
#define FILE_TEX_TUTORIAL_THUNDER "data\\TUTORIAL\\Tutorial_THUNDER_001.png"
#define FILE_TEX_TUTORIAL_DISCHARGE "data\\TUTORIAL\\Tutorial_DISCHARGE_001.png"
#define FILE_TEX_TUTORIAL_END "data\\TUTORIAL\\Tutorial_END_001.png"

//�`���[�g���A���\����
typedef struct
{
	const char* pFileName;	//�t�@�C���l�[��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nType;				//�^�C�v
	int nCntTime;			//�^�C�}�[
	float fWidth;			//��
	float fHeight;			//����
	bool bDisp;				//�Z�b�g�������ǂ���display
	bool bBrink;			//�_�ŗp�t���O
	bool bInput;			//���͂������ǂ���
}TUTORIAL;

//�v���g�^�C�v�錾
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorial(const char* pFileName, D3DXVECTOR3 pos, D3DXCOLOR col, TUTRIALTYPE type, float fWidth, float fHeight);
bool TutorialInput(void);
void SetEnablePause2(bool bPause);
#endif // !_TUTORIAL_H_