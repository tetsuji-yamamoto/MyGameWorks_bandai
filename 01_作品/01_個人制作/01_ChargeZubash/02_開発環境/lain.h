#ifndef _LAIN_H_ //マクロ定義されえてなかったら
#define _LAIN_H_ //二重インクルード防止マクロ定義

#include "main.h"

//雨構造体
typedef struct
{
	const char* pFileName;	//ファイルネーム
	int nType;				//タイプ
	D3DXCOLOR col;			//色
	float fTexMoveX;		//テクスチャの動きX
	float fTexMoveY;		//テクスチャの動きY
	bool bUse;				//使用してるかどうか
}Lain;

//プロトタイプ宣言
void UninitLain(void);	//雨の終了
void UpdateLain(void);	//雨の更新
void DrawLain(void);	//雨の描画
void InitLain(void);	//雨の初期化
#endif 