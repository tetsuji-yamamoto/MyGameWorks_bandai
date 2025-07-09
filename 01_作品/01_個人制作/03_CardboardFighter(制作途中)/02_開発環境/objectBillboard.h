//*****************************************
// 
// ビルボード
// Author Tetsuji Yamamoto
// 
//*****************************************
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

#include "main.h"
#include "object.h"

// オブジェクトビルボードクラス
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard();
	~CObjectBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObjectBillboard* Create(void);
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	int m_nIdxTexture;					// テクスチャへのインデックス
};

#endif // !_OBJECTBILLBOARD_H_
