#ifndef _READTEXT_H_
#define _READTEXT_H_

#include "main.h"
#include "block.h"

typedef struct
{
	LPDIRECT3DTEXTURE9 apTextureBlock[BLOCKTYPE_MAX][6];	// テクスチャへのポンタ
	LPD3DXMESH apMeshBlock[BLOCKTYPE_MAX];					// メッシュ(頂点情報へのポインタ)
	LPD3DXBUFFER apBuffMatBlock[BLOCKTYPE_MAX];				// マテリアルへのポインタ
	DWORD adwNumMatBlock[BLOCKTYPE_MAX];					// マテリアルの数
}READBLOCK;

// プロトタイプ宣言
void ReadText();
void SetStage(FILE* pFile);
void ReadBlockDate(FILE* pFile);
READBLOCK *GetReadBlock();
#endif