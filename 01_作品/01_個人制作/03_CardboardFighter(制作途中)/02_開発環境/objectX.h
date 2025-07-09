//*************************************
// 
// オブジェクトX
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

// オブジェクトXクラス
class CObjectX : public CObject // CObject継承
{
public:
	CObjectX();
	~CObjectX();

	HRESULT Init() { return S_OK; }
	HRESULT Init(const char* pXFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw(D3DXMATRIX *pMtxPearent);
	static CObjectX* Create(const char* pXFileName);

private:
	int *m_apIdxTexture;		// テクスチャへのインデックスポインター
	LPD3DXMESH m_pMesh;			// メッシュ
	LPD3DXBUFFER m_pBuffMat;	// マテリアル
	DWORD m_dwNumMat;			// マテリアルの数
	D3DXMATRIX m_mtxWorld;		// マトリックス
};

#endif // !_OBJECTX_H_
