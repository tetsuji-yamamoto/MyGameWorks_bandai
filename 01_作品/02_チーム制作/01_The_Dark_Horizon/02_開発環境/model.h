#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

// モデル構造体
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[6];	// テクスチャへのポンタ
	LPD3DXMESH pMesh;		// メッシュ(頂点情報へのポインタ)
	LPD3DXBUFFER pBuffMat;	// マテリアルへのポインタ
	DWORD dwNumMat;			// マテリアルの数
	int nIdxModelParent;	// 親モデルのインデックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 offSet;		// オフセット
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX mtxWorld;	// ワールドマトリックス

}Model;

// モデルの色管理
typedef struct
{
	float fR;	// 赤
	float fG;	// 緑
	float fB;	// 青
	float fA;	// アルファ値
}MODELCOLER;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

void SetModel(char astr[], Model* pModel, int nModelNum);
void PartsSet(FILE* pFile, Model* model);
void EndPartsSet(Model* pModel, Model model, int nIndex);

#endif // !_MODEL_H_
