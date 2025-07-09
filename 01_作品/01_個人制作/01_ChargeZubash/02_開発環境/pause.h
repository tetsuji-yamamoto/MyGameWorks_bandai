#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//ポーズメニュー
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	//ゲームに戻る
	PAUSE_MENU_RETRY,			//ゲームをやり直す
	PAUSE_MENU_QUIT,			//タイトル画面に戻る
	PAUSE_MENU_MAX,
}PAUSE_MENU;

//マクロ定義
#define MENU_HEIGHT (35)		//メニューUIの高さ
#define MENU_WIDTH (150)		//メニューUIの高さ
#define FILE_TEX_PAUSE_CONTENUE "data\\PAUSE\\Continue_001.jpg"
#define FILE_TEX_PAUSE_RETRY "data\\PAUSE\\Retry_001.jpg"
#define FILE_TEX_PAUSE_QUIT "data\\PAUSE\\Quit_001.jpg"

//ポーズメニュー構造体
typedef struct
{
	const char* pFileName;	//ファイルのパス
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nType;				//種類
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
}PAUSE;

//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetPause(const char* pFileName, D3DXVECTOR3 pos, D3DXCOLOR col, PAUSE_MENU type, float fWidth, float fHeight);
#endif
