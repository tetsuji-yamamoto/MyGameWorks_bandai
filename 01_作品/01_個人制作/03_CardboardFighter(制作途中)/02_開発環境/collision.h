//**************************************************************
// 
// 当たり判定
// Author Tetsuji Yamamoto
// 
//**************************************************************
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "main.h"
#include "sphere.h"
#include "object.h"
#include "cylinder.h"

//-----------------------------------------------------------------------
// 当たり判定クラス
class CCollision : public CObject // CObject継承
{
public:
	CCollision();
	~CCollision();

	HRESULT Init(void) { return S_OK; }
	void Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger);
	void Uninit(void);
	void Update(void) {}
	D3DXMATRIX Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent);
	D3DXMATRIX Update(D3DXMATRIX mtxParent);
	void Draw(void);

	static void IsDraw(void);
	static bool GetIsDraw(void) { return m_bDraw; }

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	static bool m_bDraw;		// 表示の有無
	bool m_bTrigger;			// 当たった瞬間かどうか
	D3DXVECTOR3 m_posOffset;	// 位置オフセット
	D3DXVECTOR3 m_pos;			// 位置
	D3DXMATRIX m_mtxWorld;		// マトリックス
};

//-----------------------------------------------------------------------
// 球の当たり判定クラス
class CCollisionSpher : public CCollision // CCollision継承
{
public:
	CCollisionSpher();
	~CCollisionSpher();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger,float fRadius, int nIdxModel);
	void Uninit(void);
	void Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent);
	void Update(D3DXMATRIX mtxParent);
	void Draw(void);
	static CCollisionSpher* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, int nIdxModel);

	// ゲッター
	float GetRadius(void) { return m_fRadius; }
	int GetIndexModel(void) { return m_nIdxModel; }

private:
	int m_nIdxModel;		// モデルのインデックス番号
	CSphere* m_pSpher;	// 表示用の球
	float m_fRadius;	// 半径
};

//-----------------------------------------------------------------------
// 円柱の当たり判定クラス
class CCollisionCylinder : public CCollision // CCollision継承
{
public:
	CCollisionCylinder();
	~CCollisionCylinder();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius,float fHeight);
	void Uninit(void);
	void Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent);
	void Draw(void);
	static CCollisionCylinder* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, float fHeight);

	// ゲッター
	float GetRadius(void) { return m_fRadius; }
	float GetHeight(void) { return m_fHeight; }


private:
	CCylinder* m_pCylinder;	// 表示用の円柱
	float m_fRadius;		// 半径
	float m_fHeight;		// 高さ
};
#endif // !_COLLISION_H_