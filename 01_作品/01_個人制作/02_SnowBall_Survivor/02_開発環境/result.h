#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

#define FILE_TEX_RESULT_GAMEOVER "date\\texture\\result\\SBS_RESULT_GAMEOVER_001.png"
#define FILE_TEX_RESULT_GAMECREAR "date\\texture\\result\\SBS_RESULT_GAMECREAR_001.png"
#define FILE_TEX_RESULT_TIMEOVER "date\\texture\\result\\SBS_RESULT_TIMEOVER_001.png"
#define FILE_TEX_RESULT_DEFAULT "date\\texture\\result\\SBS_RESULT_TIMEOVER_001.png"

// リザルト列挙
typedef enum
{
	RESULTTYPE_GAMEOVER = 0,
	RESULTTYPE_GAMECREAR,
	RESULTTYPE_TIMEOVER,
	RESULTTYPE_MAX
}RESULTTYPE;

// リザルト情報
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	const char* pFileTex;	// テクスチャパス
	RECT rect;				// 四頂点
	RESULTTYPE resultType;	// リザルトタイプ
}RESULT;

//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(RESULTTYPE resultType);
RESULTTYPE GetResult();
#endif