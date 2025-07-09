#ifndef _FADE_H_                                                                                                                                                                                                                                                                                                                                                                                                                                 //山本哲司
#define _FADE_H_

#include "main.h"

//フェードの状態
typedef enum
{
	FADE_NONE = 0,	//何もしていない状態
	FADE_IN,		//フェードイン状態
	FADE_OUT,		//フェードアウト状態
	FADE_MAX
}FADE;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          //山本哲司
//プロトタイプ宣言
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);
#endif