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
	// BGM
	SOUND_LABEL_BGM_PLANTS_SWAY = 0,	// 風で草木が揺れる
	//SOUND_LABEL_BGM_MAKESNOWBALL,		// 雪玉を作る
	// SE
	SOUND_LABEL_SE_WALKONTHESNOW_L,	// 雪の上を歩く左足
	SOUND_LABEL_SE_WALKONTHESNOW_R,	// 雪の上を歩く右足
	SOUND_LABEL_SE_JUMP,			// ジャンプ音
	SOUND_LABEL_SE_THROWBALL,		// 投げる音
	SOUND_LABEL_SE_BREAKSNOWBALL,	// 雪玉が壊れる音
	SOUND_LABEL_SE_BREAKSNOWBALL_MIDI,	// 雪玉中が壊れる音
	SOUND_LABEL_SE_BREAKSNOWBALL_BIG,	// 雪玉大が壊れる音
	SOUND_LABEL_SE_BREAKICEBALL,		// 氷玉が壊れる音
	SOUND_LABEL_SE_BREAKGRAVELBALL,		// 砂利玉が壊れる音
	SOUND_LABEL_SE_HIT_ENEMY,			// 敵のヒット音
	SOUND_LABEL_SE_HIT_PLAYER,			// プレイヤーのヒット音
	SOUND_LABEL_SE_DESITION,			// 決定音
	SOUND_LABEL_SE_SELECT,				// カーソル音
	SOUND_LABEL_SE_GAMECLEAR,			// ゲームクリアー音
	SOUND_LABEL_SE_GAMEOVER,			// ゲームオーバー音
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
