#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//マクロ定義
#define MAX_RANK (5)					//表示順位数
#define MAX_RANKSCORE_NUM (3)			//表示スコア桁数0
#define MAX_RANKSCORE_HEIGHT (100)		//ランキングポリゴンの高さ
#define MAX_RANKSCORE_WIDTH (50)		//ランキングポリゴンの幅
#define MAX_RANK_WIDTH (50)				//ランクポリゴンの幅
#define MAX_RANK_SCORE_ANIM_TIME (30)	//点滅アニメーションの時間
#define MAX_BONUS_WIDTH (150)			//ボーナスの幅
#define MAX_BONUS_HEIGHT (30)			//ボーナスの高さ
//マクロ定義
#define FILE_TXT_SCORE "data\\RANKING\\ranking.txt"	//スコアのテキストデータファイル

//ランキングボーナス列挙型
typedef enum
{
	BONUS_DYING = 0,	//死にかけボーナス
	BONUS_JUNPMAN,		//ジャンプマンボーナス
	BONUS_SHOOTING,		//射撃回数ボーナス
	BONUS_MAX
}BONUS;
//ランキング演出
typedef enum
{
	DIRECT_BONUS = 0,	//ボーナスを表示
	DIRECT_RANK,		//ランキングを表示v
	DIRECT_BRINK,		//点滅
	DIRECT_MAX
}RANKDIRECT;

//ランキングスコアの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nRank;			//順位
	int nScore;			//スコア
}RankScore;
typedef struct
{
	int nSkorDirect;		//演出用
	int nSkorDirectCounter;	//演出用カウンター
}RankDirect;

//プロトタイプ宣言
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(const char* DateScore);
void SetRanking(int nScore);
#endif // !_RANKING_H_
