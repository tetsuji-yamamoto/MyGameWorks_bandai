#include "smoke.h"
#include "effect.h"

// グローバル変数宣言
SMOKE g_aSmoke[MAX_SMOKE];	// 煙情報

//************************************************
// 煙の初期化
//************************************************
void InitSmoke(void)
{
	for (int nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		g_aSmoke[nCntSmoke].nOccurrenceTimer = 0;				// 発生タイマー
		g_aSmoke[nCntSmoke].nOccurrenceInterval = 0;			// 発生間隔
		g_aSmoke[nCntSmoke].fSize = 0.0f;						// 大きさ
		g_aSmoke[nCntSmoke].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);	// 位置
		g_aSmoke[nCntSmoke].bUse = false;						// 使ってない
		g_aSmoke[nCntSmoke].bAttach = false;					// 取り付けない
	}
}

//************************************************
// 煙の設定
//************************************************
int SetSmoke(SMOKETYPE type, D3DXVECTOR3 pos,int nOccurrenceInterval,float fSize,bool bAttach)
{
	int nCntSmoke = 0;
	for (nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		if (g_aSmoke[nCntSmoke].bUse == false)
		{
			g_aSmoke[nCntSmoke].type = type;								// 種類
			g_aSmoke[nCntSmoke].nOccurrenceTimer = 0;						// 発生タイマー
			g_aSmoke[nCntSmoke].nOccurrenceInterval = nOccurrenceInterval;	// 発生間隔
			g_aSmoke[nCntSmoke].fSize = fSize;								// 発生間隔
			g_aSmoke[nCntSmoke].pos = pos;									// 位置
			g_aSmoke[nCntSmoke].bUse = true;								// 使ってる
			g_aSmoke[nCntSmoke].bAttach = bAttach;							// 取り付ける？
			break;
		}
	}

	// 結果を返す
	return nCntSmoke;
}

//************************************************
// 煙の更新
//************************************************
void UpdateSmoke(void)
{
	for (int nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		if (g_aSmoke[nCntSmoke].bUse)
		{
			switch (g_aSmoke[nCntSmoke].type)
			{
			case SMOKETYPE_NOMAL:
				g_aSmoke[nCntSmoke].nOccurrenceTimer++;	// 発生カウンター加算

				if (g_aSmoke[nCntSmoke].nOccurrenceTimer >= g_aSmoke[nCntSmoke].nOccurrenceInterval)
				{// 発生間隔より上になったら,煙を発生させる
					g_aSmoke[nCntSmoke].nOccurrenceTimer = 0;	// カウンターリセット

					SetEffect(EFFECTTYPE_SMOKE,				// タイプ
						g_aSmoke[nCntSmoke].pos,			// 位置
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 移動量
						D3DXVECTOR3(0.0f, 0.01f, 0.0f),		// 重力
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// 色
						120,								// 寿命
						g_aSmoke[nCntSmoke].fSize,			// 大きさ
						false,								// 影の仕様有無
						true								// 減算合成
					);
				}
				break;
			}
			
		}
	}
}

//************************************************
// 煙の更新
//************************************************
bool UpdateAttachSmoke(int nIdx, D3DXVECTOR3 pos)
{
	bool bResult = false;
	g_aSmoke[nIdx].nOccurrenceTimer++;	// 発生カウンター加算

	if (g_aSmoke[nIdx].nOccurrenceTimer >= g_aSmoke[nIdx].nOccurrenceInterval)
	{// 発生間隔より上になったら,煙を発生させる
		g_aSmoke[nIdx].nOccurrenceTimer = 0;	// カウンターリセット

		bResult = true;

		SetEffect(EFFECTTYPE_SMOKE,				// タイプ
			pos,								// 位置
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// 移動量
			D3DXVECTOR3(0.0f, 0.01f, 0.0f),		// 重力
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// 色
			60,									// 寿命
			g_aSmoke[nIdx].fSize,				// 大きさ
			false,								// 影の仕様有無
			true								// 減算合成
		);
	}

	//結果を返す
	return bResult;
}