#ifndef _BACKGROUND_H_ //マクロ定義されえてなかったら
#define _BACKGROUND_H_ //二重インクルード防止マクロ定義

#include "main.h"

#define FALE_TEX_BG_TITLE_CLOUDY_1 "data\\BG\\Thunderstorm_001.png"
#define FALE_TEX_BG_TITLE_CLOUDY_2 "data\\BG\\Thunderstorm_002.png"

//背景の種類列挙型
typedef enum
{
	BGTYPE_TITLE = 0,		//タイトルの背景
	BGTYPE_TUTORIAL,		//チュートリアルの背景
	BGTYPE_GAME,			//ゲームの背景
	BGTYPE_RESULT_GAMEOVER,	//ゲームオーバーの背景
	BGTYPE_RESULT_GAMECLER,	//ゲームクリアの背景
	BGTYPE_RANKING,			//ランキングの背景
	BGTYPE_CLOUDY_0,		//曇りの背景
	BGTYPE_CLOUDY_1,		//黒い曇りの背景
	BGTYPE_MAX
}BGTYPE;

//プロトタイプ宣言
void UninitBG(void);	//背景の終了
void UpdateBG(void);	//背景の更新
void DrawBG(void);		//背景の描画
void InitBG(void);		//背景の初期化
void SetBackground(const char* pFileName, BGTYPE type, D3DXCOLOR col);				//背景
void MoveBackground(D3DXCOLOR col, float texMoveX, float texMoveY, int nCntBG);	//背景
void EndBackground(BGTYPE type);	//背景終わり

#endif 