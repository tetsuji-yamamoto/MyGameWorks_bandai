#ifndef _SMOKE_H_
#define _SMOKE_H_

#include "main.h"

// 煙のタイプ
typedef enum
{
	SMOKETYPE_NOMAL = 0,	// 通常
	SMOKETYPE_ATTACH,		// 取り付け
	SMOKETYPE_FUTSTEP,		// 砂埃
	SMOKETYPE_MAX
}SMOKETYPE;

// マクロ定義
#define MAX_SMOKE (256)	// 煙の最大数

// 煙構造体
typedef struct
{
	SMOKETYPE type;				// 種類
	D3DXVECTOR3 pos;			// 位置
	int nOccurrenceTimer;		// 発生タイマー
	int nOccurrenceInterval;	// 発生間隔
	float fSize;				// 大きさ
	bool bUse;					// 使ってますか？
	bool bAttach;				// 何かに取り付けますか？
}SMOKE;

// プロトタイプ宣言
void InitSmoke(void);
int SetSmoke(SMOKETYPE type,D3DXVECTOR3 pos, int nOccurrenceInterval, float fSize, bool bAttach);
void UpdateSmoke(void);
bool UpdateAttachSmoke(int nIdx, D3DXVECTOR3 pos);

#endif // !_SMOKE_H_
