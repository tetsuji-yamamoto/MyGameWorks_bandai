#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

#define MAX_BLOCK (1024)	// 最大ブロック数
#define FILE_XFILE_BLOCK_SNOW "date\\xfile\\block\\Block_Snow_001.x"
#define FILE_XFILE_BLOCK_ICE "date\\xfile\\block\\Block_Ice_001.x"
#define FILE_XFILE_BLOCK_GRAVEL "date\\xfile\\block\\Block_Gravel_001.x"
#define FILE_XFILE_BLOCK_WALL "date\\xfile\\block\\Block_Wall_001.x"
#define FILE_XFILE_BLOCK_WALL_ADULT "date\\xfile\\block\\Block_Wall_Adult_001.x"
#define FILE_XFILE_TERRITORYPOINT "date\\xfile\\block\\Block_Territorypoint_001.x"
#define FILE_XFILE_UDD_SNOW "date\\xfile\\block\\Block_Udd_Snow_001.x"

// ブロックタイプ列挙型
typedef enum
{
	BLOCKTYPE_SNOW = 0,		// 雪
	BLOCKTYPE_ICE,			// 氷
	BLOCKTYPE_GRAVEL,		// 砂利
	BLOCKTYPE_WALL,			// 壁
	BLOCKTYPE_WALL_ADULT,	// 大人の壁
	BLOCKTYPE_TERRITRY_POINT,	// 行動範囲
	BLOCKTYPE_UDD_SNOW,		// 雪の木
	BLOCKTYPE_MAX
}BLOCKTYPE;

// 判定面列挙型
typedef enum
{
	BLOCKFACETYPE_SIDE = 0,	// 横
	BLOCKFACETYPE_TOP,		// 上
	BLOCKFACETYPE_BOTTOM,	// した
	BLOCKFACETYPE_MAX
}BLOCKFACETYPE;

// ブロック構造体
typedef struct
{
	LPDIRECT3DTEXTURE9 apTextureBlock[6];	// テクスチャへのポンタ
	LPD3DXMESH pMeshBlock;					// メッシュ(頂点情報へのポインタ)
	LPD3DXBUFFER pBuffMatBlock;				// マテリアルへのポインタ
	DWORD dwNumMatBlock;					// マテリアルの数
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 vtxMinBlock, vtxMaxBlock;	// モデルの最小値最大値
	const char* pFilename;	// ファイル名
	char astr[256];			// 文字格納
	int nType;				// タイプ
	int nLife;				// 寿命
	bool bUse;				// 使っているるかどうか
}BLOCK;

// セットブロック構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	const char* pFilename;	// ファイル名
	char astr[256];			// 文字列格納用
	int nType;				// タイプ
}SETBLOCK;

// ブロックコントローラー
typedef struct
{
	int nCntNowBlock;	// 今選んでいるブロック
	int nNextBlType;	// 次に配置するブロックのタイプ
}BLOCKCONTROLLER;

// ブロックの管理
typedef struct
{
	char astr[BLOCKTYPE_MAX][256];	// 文字列格納用
	int nBlockNum;
}BLOCKMANAGER;

// ブロック判定構造体
typedef struct
{
	int nType;		// どのタイプに当たってんの？
	int nCnt;		// 何番目に当たってんの？
	int nHitfase;	// どの面に当たってるの
	bool bHit;		//　当たってます 
}BLOCKCOLLISION;

// プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(SETBLOCK setBlock, bool bFilenameAstr);
BLOCK* GetBlock(void);
BLOCKCONTROLLER* GetBlockController(void);
BLOCKMANAGER* GetBlockManager(void);

BLOCKCOLLISION CollisionBlockCharacter(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, int* pBlockType, float fWidth, float fHeight);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove);
BLOCKCOLLISION CollisionBlockBullet(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fSize);
BLOCKCOLLISION CollisionBlockSpher(D3DXVECTOR3 posA, float fSizeA, int nBreakType, bool bBreak);

BLOCK BlockSearch(BLOCKTYPE type, int nNumber);
void BlockDestroy(int nCnt);

void BlockOllDeliete(void);
void BlockControllre(void);

//BLOCK* GetBlockEX();
#endif // !_MODEL_H_
