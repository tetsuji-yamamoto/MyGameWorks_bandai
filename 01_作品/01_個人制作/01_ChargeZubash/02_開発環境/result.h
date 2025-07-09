#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

#define FILE_TEX_RESULT_GAMEOVER "data\\RESULT\\GameOver_001.png"
#define FILE_TEX_RESULT_GAMECREAR "data\\RESULT\\GameCrear_001.png"
#define FILE_TEX_RESULT_TIMEOVER "data\\RESULT\\TimeOver_001.png"

//リザルト列挙
typedef enum
{
	RESULTTYPE_GAMEOVER = 0,
	RESULTTYPE_GAMECREAR,
	RESULTTYPE_TIMEOVER,
	RESULTTYPE_MAX
}RESULTTYPE;

//リザルト情報
typedef struct
{
	const char* pFileTex;	//テクスチャパス
	RECT rect;				//四頂点
	RESULTTYPE resultType;	//リザルトタイプ
}RESULT;

//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(RESULTTYPE resultType);
#endif