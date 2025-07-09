#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//タイトルポリゴンタイプ
typedef enum
{
	TITLETYPE_BG = 0,	//タイトルのBG
	TITLETYPE_LOGO,		//タイトルのロゴ
	TITLETYPE_START,	//タイトルのスタートボタン
	TITLETYPE_MAX
}TITLETYPE;

//タイトル演出列挙
typedef enum
{
	TITLEDIRECT_LOGODOWN = 0,			//ロゴが下がってくる
	TITLEDIRECT_STARTAPPEAR,			//スタート出現
	TITLEDIRECT_STARTBRINK,				//スタート点滅
	TITLEDIRECT_STARTBRINK_QUICKLY,		//スタート素早く点滅quickly
}TITLEDIRECT;

//タイトル構造体
typedef struct
{
	const char* pFileName;	//ファイルネーム
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nType;				//タイプ
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使用しているかどうか
}TITLE;

//タイトルの演出構造体
typedef struct
{
	TITLEDIRECT titleDirect;	//タイトル演出順
	int nTimer;					//タイマー
	bool bBrink;				//点滅どっち？
}TITLEDIRECTOR;

//マクロ定義
#define START_WIDTH (100)	//スタートの幅
#define START_HEIGHT (35)	//スタートの高さ
#define LOGO_WIDTH (500)	//スタートの幅
#define LOGO_HEIGHT (100)	//スタートの高さ
#define FILE_TEX_TITLE_LOGO "data\\TITLE\\TITLE_CHARGE_002.png"	//タイトルのロゴ
#define FILE_TEX_TITLE_START "data\\TITLE\\Start_002.png"		//タイトルのスタートボタン

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(const char* pFileName, D3DXVECTOR3 pos, TITLETYPE type, D3DXCOLOR col, float fWidth, float fHeight);
void UpDateLogo(int nCntTitle);
void UpDateStart(int nCntTitle);
#endif