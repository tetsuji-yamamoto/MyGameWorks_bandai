//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	// BGM
	SOUND_LABEL_BGM_PLANTS_SWAY = 0,	// ���ő��؂��h���
	//SOUND_LABEL_BGM_MAKESNOWBALL,		// ��ʂ����
	// SE
	SOUND_LABEL_SE_WALKONTHESNOW_L,	// ��̏���������
	SOUND_LABEL_SE_WALKONTHESNOW_R,	// ��̏������E��
	SOUND_LABEL_SE_JUMP,			// �W�����v��
	SOUND_LABEL_SE_THROWBALL,		// �����鉹
	SOUND_LABEL_SE_BREAKSNOWBALL,	// ��ʂ����鉹
	SOUND_LABEL_SE_BREAKSNOWBALL_MIDI,	// ��ʒ������鉹
	SOUND_LABEL_SE_BREAKSNOWBALL_BIG,	// ��ʑ傪���鉹
	SOUND_LABEL_SE_BREAKICEBALL,		// �X�ʂ����鉹
	SOUND_LABEL_SE_BREAKGRAVELBALL,		// �����ʂ����鉹
	SOUND_LABEL_SE_HIT_ENEMY,			// �G�̃q�b�g��
	SOUND_LABEL_SE_HIT_PLAYER,			// �v���C���[�̃q�b�g��
	SOUND_LABEL_SE_DESITION,			// ���艹
	SOUND_LABEL_SE_SELECT,				// �J�[�\����
	SOUND_LABEL_SE_GAMECLEAR,			// �Q�[���N���A�[��
	SOUND_LABEL_SE_GAMEOVER,			// �Q�[���I�[�o�[��
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
