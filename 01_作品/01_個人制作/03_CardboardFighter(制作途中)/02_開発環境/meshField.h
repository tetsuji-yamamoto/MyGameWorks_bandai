//*********************************************
// 
// メッシュフィールド
// Author Tetsuji Yamamoto
// 
//*********************************************
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "object.h"

// メッシュフィールドクラス
class CMeshField : public CObject	// CObject継承
{
public:
	CMeshField();
	~CMeshField();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fWidth, float fheight, const char* pTexturePass = NULL);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ResetNormal(void);
	static CMeshField* Create(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fWidth, float fheight, const char* pTexturePass = NULL);
	bool Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pNor = NULL);
	void EditHeight(D3DXVECTOR3 pos, float fHeight, float fRadius);
	void Save(const char* pFilePass);
	void Load(const char* pFilePass);

	// セッター
	void SetColor(D3DXCOLOR col);
	void SetPosition(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファへのポインタ
	D3DXVECTOR3 m_startPos;				// 始まりの位置
	int m_nIdxTexture;					// テクスチャへのインデックス
	int m_nNumPolygon;					// ポリゴン数
	int m_nNumVtx;						// 頂点数
	int m_nNumIdx;						// インデックス数
	int m_nDivisionX;					// Xの分割数
	int m_nDivisionY;					// Yの分割数
	float m_fWidth;						// 幅
	float m_fHeight;					// 高さ
};

#endif // !_MESHFIELD_H_
