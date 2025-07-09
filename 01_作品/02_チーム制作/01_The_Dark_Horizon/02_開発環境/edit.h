#ifndef _EDIT_H_
#define _EDIT_H_

#include "main.h"

//エディット（モード）の種類
typedef enum
{
	EDITMODE_NONE = 0,		// なし
	EDITMODE_BLOCK,			// ブロック
	EDITMODE_MAX
}EDITMODE;

// エディター管理構造体
typedef struct
{
	EDITMODE mode;	// モード
	int nCntTimer;	// タイマー
}EDITMANAGER;

// プロトタイプ宣言
void InitEdit();
void SetEditMode(EDITMODE mode);
EDITMODE GetEditMode(void);

#endif // !_EDIT_H_