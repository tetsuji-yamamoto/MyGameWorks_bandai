#include "main.h"
#include "particle.h"
#include "effect.h"
#include "sword.h"

//グローバル変数宣言
Particle g_aParticle[MAX_PARTICLE];	//パーティクル情報
int g_nParticleCounter;

//--------------------------------
//パーティクルの
//--------------------------------
void InitParticle(void)
{
	int nCntParticle;

	g_nParticleCounter = 0;
	//パーティクルの情報の初期化
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aParticle[nCntParticle].nNumAppear = 0;
		g_aParticle[nCntParticle].nRange = 0;
		g_aParticle[nCntParticle].nSpeedRange = 0.0f;
		g_aParticle[nCntParticle].fPullMove = 0.0f;
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].fPullRadius = 0.0f;
		g_aParticle[nCntParticle].fAngle = 0.0f;
		g_aParticle[nCntParticle].fLife = 0.0f;
		g_aParticle[nCntParticle].bUse = false;
	}
}
//--------------------------------
//パーティクルの
//--------------------------------
void UninitParticle(void)
{

}
//--------------------------------
//パーティクルの更新処理
//--------------------------------
void UpdateParticle(void)
{
	SWORD* pSword = GetSword();

	int nCntParticle;
	int nCntAppear;
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//色
	int nType;			//種類
	int nDeleetType;
	int nNumAppear;		//出す両
	int nSpeedRange;	//速さの範囲
	int nRange;			//出す角度
	float fPullMove;	//移動量の減少係数
	float fRadius;		//頂点座標の設定
	float fPullRadius;	//頂点座標の設定
	float fAngle;		//角度
	float fSpeed;		//速さ
	float fLife;		//寿命
	float fLowSpeed;	//最低の移動量
	float fWidth;		//幅
	float fHeight;		//高さ
	float fAngleEffect = 0.0f;	//エフェクトの角度

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			nNumAppear = g_aParticle[nCntParticle].nNumAppear;		//出す両
			nRange = g_aParticle[nCntParticle].nRange;				//出す角度
			nSpeedRange = g_aParticle[nCntParticle].nSpeedRange;	//速さの範囲
			fAngle = g_aParticle[nCntParticle].fAngle;				//狙いの角度

			pos = g_aParticle[nCntParticle].pos;					//位置
			col = g_aParticle[nCntParticle].col;					//色
			nType = g_aParticle[nCntParticle].nType;				//種類
			nDeleetType = g_aParticle[nCntParticle].nDeleetType;				//種類
			fRadius = g_aParticle[nCntParticle].fRadius;			//大きさの設定
			fPullRadius = g_aParticle[nCntParticle].fPullRadius;	//小さくする係数の設定
			fPullMove = g_aParticle[nCntParticle].fPullMove;		//移動量の減少係数
			fLife = g_aParticle[nCntParticle].fLife;				//寿命
			fLowSpeed = g_aParticle[nCntParticle].fLowSpeed;		//最低の移動量
			fWidth = g_aParticle[nCntParticle].fWidth;				//幅
			fHeight = g_aParticle[nCntParticle].fHeight;			//高さ

			//パーティクル生成(したい回数)
			for (nCntAppear = 0; nCntAppear < nNumAppear; nCntAppear++)
			{
				fAngle += (float)(rand() % ((nRange * 2) + 1) -nRange) / 100.0f;
				fSpeed = (float)(rand() % nSpeedRange) + fLowSpeed;

				fAngleEffect = pSword->fKeepLot;
				fAngleEffect += ((float)(rand() % 14) - 7) / 100.0f;

				//移動量の設定
				move.x = sinf(fAngle) * (fSpeed);
				move.y = cosf(fAngle) * (fSpeed);

				//エフェクトの設定
				SetEffect(pos,								//位置
					D3DXVECTOR3(move.x, move.y, move.z),	//移動量
					col,			//色
					nType,			//通常エフェクト
					fRadius,		//ポリゴンサイズ
					fHeight,		//高さ
					fWidth,			//幅
					fPullRadius,	//ポリゴンサイズ減少数
					fPullMove,		//移動量減少数
					fLife,			//寿命
					fAngleEffect,	//ポリゴン自体の角度
					nDeleetType
				);	
			}

			//終わり
			g_aParticle[nCntParticle].bUse = false;
		}
	}
}

//--------------------------------
//パーティクルの
//--------------------------------
void DrawParticle(void)
{
	
}

//--------------------------------
//パーティクルの
//--------------------------------
void SetParticle(D3DXVECTOR3 pos,D3DXCOLOR col,int nType,int nNumAppear,int nRange, int nSpeedRange,float fPullMove,float fRadius,  float fPullRadius, float fAngle,float fLife,float fLowSpeed,float fWidth,float fHeight,int nDeleetType)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//パーティクルが使用されていない
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].nType = nType;
			g_aParticle[nCntParticle].nDeleetType = nDeleetType;
			g_aParticle[nCntParticle].nNumAppear = nNumAppear;
			g_aParticle[nCntParticle].nRange = nRange;
			g_aParticle[nCntParticle].nSpeedRange = nSpeedRange;
			g_aParticle[nCntParticle].fPullMove = fPullMove;
			g_aParticle[nCntParticle].fRadius = fRadius;
			g_aParticle[nCntParticle].fPullRadius = fPullRadius;
			g_aParticle[nCntParticle].fAngle = fAngle;
			g_aParticle[nCntParticle].fLife = fLife;
			g_aParticle[nCntParticle].fLowSpeed = fLowSpeed;
			g_aParticle[nCntParticle].fWidth = fWidth;
			g_aParticle[nCntParticle].fHeight = fHeight;
			g_aParticle[nCntParticle].bUse = true;//使用している状態にする
			break;
		}
	}
}