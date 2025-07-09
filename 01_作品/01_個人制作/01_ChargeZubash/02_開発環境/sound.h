//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	//環境
	SOUND_LABEL_LEIN_BGM = 0,
	SOUND_LABEL_THUNDER_SE,
	//プレイヤー
	SOUND_LABEL_PLAYERMOVE_SE,
	SOUND_LABEL_PLAYERJUMP_SE,
	SOUND_LABEL_PLAYERATTACK_SE,
	SOUND_LABEL_PLAYERCHARGE_SE,
	SOUND_LABEL_PLAYERDAMAGE_SE,
	//ビームソード
	SOUND_LABEL_BEAMSWORD_GENERATE_SE,
	//蛇
	SOUND_LABEL_SNAKE_MOVE_SE,
	SOUND_LABEL_SNAKE_VOIS_SE,
	//カーソルcursor
	SOUND_LABEL_CURSORMOVE_SE,
	SOUND_LABEL_CURSORDICITION_SE,
	//リザルト
	SOUND_LABEL_RESULT_GAMEOVER_SE,
	SOUND_LABEL_RESULT_GAMECREAR_SE,
	SOUND_LABEL_MAX

} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
