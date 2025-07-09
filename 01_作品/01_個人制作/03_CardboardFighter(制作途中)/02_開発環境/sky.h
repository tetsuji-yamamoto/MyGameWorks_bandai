//**************************************
// 
// 空
// Author Tetsuji Yamamoto
// 
//**************************************
#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
#include "object.h"

// 空クラス
class CSky : public CObject // CObject3D継承
{
public:
	CSky();
	~CSky();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(int nDivisionX, int nDivisionY, float fRadius);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSky* Create(int nDivisionX, int nDivisionY, float fRadius);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファへのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 m_pos;					// 位置
	int m_nIdxTexture;					// テクスチャへのインデックス
	int m_nNumPolygonMeshField;			// メッシュのポリゴンの数
	int m_nNumVtx;						// 頂点数
	int m_nNumVtxFan;					// 扇状の頂点の数
	int m_nNumVtxMeshField;				//メッシュの頂点の数
	int m_nNumIdx;						// インデックス数
	int m_nNumIdxFan;					// ファンのインデック数
	int m_nNumIdxMeshField;				// メッシュフィールドのインデックス数
	int m_nDivisionX;					// 分割数X
	int m_nDivisionY;					// 分割数Y
};


#endif // !_SKY_H_
