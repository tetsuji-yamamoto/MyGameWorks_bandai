//*************************************
// 
// オブジェクトステージ
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _OBJECTSTAGE_H_
#define _OBJECTSTAGE_H_

#include "main.h"
#include "object.h"

// オブジェクトXクラス
class CObjectStage
{
public:
	CObjectStage();
	~CObjectStage();

	HRESULT Init() { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw(D3DXMATRIX* pMtxPearent);
	static CObjectStage* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName);
	bool CollisionMouse(float fRadius);

	// ゲッター
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXMATRIX SetMatrix(void) { return m_mtxWorld; }
	LPD3DXMESH GetMesh(void) { return m_pMesh; }
	int* GetIndexTexture(void) { return m_apIdxTexture; }

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }
	void SetIndexTexture(int* pIdx) { m_apIdxTexture = pIdx; }
	void SetAlphaColor(float fAlphar);

private:
	int* m_apIdxTexture;		// テクスチャへのインデックスポインター
	LPD3DXMESH m_pMesh;			// メッシュ
	LPD3DXBUFFER m_pBuffMat;	// マテリアル
	DWORD m_dwNumMat;			// マテリアルの数
	D3DXMATRIX m_mtxWorld;		// マトリックス

	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
};

#endif // !_OBJECTX_H_
