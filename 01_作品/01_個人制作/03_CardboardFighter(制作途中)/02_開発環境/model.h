//*************************************
// 
// モデル
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "object.h"

// モデルクラス
class CModel
{
public:
	CModel();
	~CModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName);
	void Uninit(void);
	void Draw(void);
	void DrawParentChild(D3DXCOLOR* pCol = NULL);
	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName);
	bool CollisionMouse(float fRadius);

	// ゲッター
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	LPD3DXMESH GetMesh(void) { return m_pMesh; }
	CModel* GetIndexParent(void) { return m_pParent; }
	int* GetIndexTexture(void) { return m_apIdxTexture; }

	// セッター
	void SetParent(CModel* pModel) { m_pParent = pModel; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }
	void SetIndexParent(CModel* pParent) { m_pParent = pParent; }
	void SetIndexTexture(int* pIdx) { m_apIdxTexture = pIdx; }
	void SetAlphaColor(float fAlphar);

private:
	int* m_apIdxTexture;		// テクスチャへのインデックスポインター
	LPD3DXMESH m_pMesh;			// メッシュ
	LPD3DXBUFFER m_pBuffMat;	// マテリアル
	DWORD m_dwNumMat;			// マテリアルの数

	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	CModel* m_pParent;		// 親モデルへのポインタ
};

#endif // !_OBJECTX_H_
