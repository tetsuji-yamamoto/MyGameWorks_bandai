#include "effect.h"
#include "particle.h"

// グローバル変数宣言
PARTICLE g_aParticle[MAX_PARTICLE];						// パーティクル

//**************************************
// パーティクルの初期化
//**************************************
void InitParticle(void)
{
	for (int nCntPati = 0; nCntPati < MAX_PARTICLE; nCntPati++)
	{
	
	}
}

//**************************************
// パーティクルの更新
//**************************************
void UpdateParticle(void)
{

}

//**************************************
// パーティクルの設定
//**************************************
void SetParticle(EFFECTTYPE type,D3DXVECTOR3 pos, D3DXVECTOR3 gravity, D3DXCOLOR col, int nAmount,int nLife,float fSize,float fSpeed,bool bShadow,bool bSubtractive)
{
	D3DXVECTOR3 move;	// 移動量算出用
	float fLotA;		// 角度
	float fLotB;		// 角度

	for (int nCntPati = 0; nCntPati < nAmount; nCntPati++)
	{
		fLotA = (float)(rand() % 628 - 314) * 0.01f;	// ランダムで角度算出
		fLotB = (float)(rand() % 628 - 314) * 0.01f;	// ランダムで角度算出
		move.x = sinf(fLotA) * sinf(fLotB) * fSpeed;
		move.y = cosf(fLotA) * fSpeed;
		move.z = sinf(fLotA) * cosf(fLotB) * fSpeed;

		SetEffect(type,		// タイプ
			pos,			// 位置
			move,			// 移動量
			gravity,		// 重力
			col,			// 色
			nLife,			// 寿命
			fSize,			// 大きさ
			bShadow,		// 影の仕様有無
			bSubtractive	// 加算合成
		);
	}
}