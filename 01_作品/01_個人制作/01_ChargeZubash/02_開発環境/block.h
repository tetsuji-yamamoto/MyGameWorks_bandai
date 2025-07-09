#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//マクロ定義
#define MAX_BLOCK (125)		//ブロックの最大数
#define BLOCK_HEIGHT (32)	//ブロックの高さ
#define BLOCK_WIDTH (32)	//ブロックの幅

#define FILE_TEX_BLOCK "data\\BLOCK\\Block_004.jpg"

//ブロックの種類
typedef enum
{
	BLOCKTYPE_NOMAL = 0,//動かないやつ
	BLOCKTYPE_MOVEX,		//Xに動くやつ
	BLOCKTYPE_MOVEY,		//Yに動くやつ
	BLOCKTYPE_MAX
}BLOCKTYPE;

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 posGoal;//目標の位置goal
	int nCntTime;		//カウントタイマー
	int nType;			//種類
	float fWidth;		//幅
	float fHeight;		//高さ
	float fTexX;		//テクスチャ高さ
	float fTexY;		//テクスチャ幅
	bool bUse;			//使用しているかどうか
}BLOCK;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,int nType,float width,float height);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth);
void CollisionBlockX(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth,BLOCK ** pBlock);
bool CollisionBlockY(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPMove, float fHeight, float fWidth, BLOCK** pBlock);
BLOCK* GetBlock(void);
#endif