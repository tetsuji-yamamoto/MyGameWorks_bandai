#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//チュートリアルポリゴンタイプ
typedef enum
{
	TUTORIALTYPE_MOVE = 0,	//チュートリアル移動
	TUTORIALTYPE_JUMP,		//チュートリアルジャンプ
	TUTORIALTYPE_ATTACK,	//チュートリアル攻撃
	TUTORIALTYPE_THUNDER,	//チュートリアル雷
	TUTORIALTYPE_DISCHARGE,	//チュートリアル放出
	TUTORIALTYPE_END,		//チュートリアル終わり
	TUTORIALTYPE_MAX
}TUTRIALTYPE;

#define FILE_TEX_TUTORIAL_TEST "data\\TUTORIAL\\test.png"
#define FILE_TEX_TUTORIAL_MOVE "data\\TUTORIAL\\Tutorial_MOVE_001.png"
#define FILE_TEX_TUTORIAL_JUMP "data\\TUTORIAL\\Tutorial_JUMP_001.png"
#define FILE_TEX_TUTORIAL_ATTACK "data\\TUTORIAL\\Tutorial_ATTACK_001.png"
#define FILE_TEX_TUTORIAL_THUNDER "data\\TUTORIAL\\Tutorial_THUNDER_001.png"
#define FILE_TEX_TUTORIAL_DISCHARGE "data\\TUTORIAL\\Tutorial_DISCHARGE_001.png"
#define FILE_TEX_TUTORIAL_END "data\\TUTORIAL\\Tutorial_END_001.png"

//チュートリアル構造体
typedef struct
{
	const char* pFileName;	//ファイルネーム
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nType;				//タイプ
	int nCntTime;			//タイマー
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bDisp;				//セットしたかどうかdisplay
	bool bBrink;			//点滅用フラグ
	bool bInput;			//入力したかどうか
}TUTORIAL;

//プロトタイプ宣言
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorial(const char* pFileName, D3DXVECTOR3 pos, D3DXCOLOR col, TUTRIALTYPE type, float fWidth, float fHeight);
bool TutorialInput(void);
void SetEnablePause2(bool bPause);
#endif // !_TUTORIAL_H_