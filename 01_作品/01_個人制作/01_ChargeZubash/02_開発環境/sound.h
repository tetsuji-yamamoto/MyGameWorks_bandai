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
	//��
	SOUND_LABEL_LEIN_BGM = 0,
	SOUND_LABEL_THUNDER_SE,
	//�v���C���[
	SOUND_LABEL_PLAYERMOVE_SE,
	SOUND_LABEL_PLAYERJUMP_SE,
	SOUND_LABEL_PLAYERATTACK_SE,
	SOUND_LABEL_PLAYERCHARGE_SE,
	SOUND_LABEL_PLAYERDAMAGE_SE,
	//�r�[���\�[�h
	SOUND_LABEL_BEAMSWORD_GENERATE_SE,
	//��
	SOUND_LABEL_SNAKE_MOVE_SE,
	SOUND_LABEL_SNAKE_VOIS_SE,
	//�J�[�\��cursor
	SOUND_LABEL_CURSORMOVE_SE,
	SOUND_LABEL_CURSORDICITION_SE,
	//���U���g
	SOUND_LABEL_RESULT_GAMEOVER_SE,
	SOUND_LABEL_RESULT_GAMECREAR_SE,
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
