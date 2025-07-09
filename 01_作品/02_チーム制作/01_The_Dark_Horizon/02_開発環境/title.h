#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

// マクロ定義
#define FILE_TEX_TITLE_SBS "date\\texture\\title\\SBS_TITLE_001.png"
#define FILE_TEX_STRTBUTTON "date\\texture\\UI\\TITLE_UI_BUTTON_GAMESTART.png"
#define FILE_TEX_STRTBUTTON_SHINE "date\\texture\\UI\\TITLE_UI_BUTTON_GAMESTART_SHAINE.png"
#define FILE_TEX_TUTORIALBUTTON "date\\texture\\UI\\TITLE_UI_BUTTON_TUTORIAL.png"
#define FILE_TEX_TUTORIALBUTTON_SHINE "date\\texture\\UI\\TITLE_UI_BUTTON_TUTORIAL_SHAINE.png"

// タイトルポリゴンタイプ
typedef enum
{
	TITLETYPE_TEST = 0,	// タイトルのテスト
	TITLETYPE_BG,		// タイトルのBG
	TITLETYPE_LOGO,		// タイトルのロゴ
	TITLETYPE_START,			// タイトルのスタートボタン
	TITLETYPE_START_SHINE,		// タイトルのスタートボタン光
	TITLETYPE_TUTORIAL,			// タイトルのチュートリアルボタン
	TITLETYPE_TUTORIAL_SHINE,	// タイトルのチュートリアルボタン光
	TITLETYPE_MAX
}TITLETYPE;

// ボタンタイプ
typedef enum
{
	BUTTONTYPE_START,	// タイトルのスタートボタン
	BUTTONTYPE_TUTORIAL,	// タイトルのチュートリアルボタン
	BUTTONTYPE_MAX
}BUTTONTYPE;

// タイトル演出列挙
typedef enum
{
	TITLEDIRECT_LOGODOWN = 0,			// ロゴが下がってくる
	TITLEDIRECT_BUTTONAPPEAR,			// ボタン出現
	TITLEDIRECT_STARTBUTTONBRINK,		// スタートボタン点滅
	TITLEDIRECT_TUTORIALBUTTONBRINK,	// チュートリアルボタン点滅
	TITLEDIRECT_BUTTONBRINK_QUICKLY,	// ボタン素早く点滅quickly
}TITLEDIRECT;

// タイトル構造体
typedef struct
{
	const char* pFileName;	// ファイルネーム
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// 色
	TITLETYPE type;			// タイプ
	int nButtonIdx;			// ボタンインデックス
	float fWidth;			// 幅
	float fHeight;			// 高さ
	bool bUse;				// 使用しているかどうか
}TITLE;

// タイトルの演出構造体
typedef struct
{
	TITLEDIRECT titleDirect;	// タイトル演出順
	int nTimer;					// タイマー
	bool bBrink;				// 点滅どっち？
}TITLEDIRECTOR;

// プロトタイプ宣言
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