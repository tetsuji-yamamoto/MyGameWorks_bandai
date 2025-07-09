//****************************************************************************
// 
// íe
// Author tetuji yamamoto
// 
//****************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "object2D.h"

// íeÉNÉâÉX
class CBullet : public CObject2D	// CObject2Dåpè≥
{
public:
	CBullet(int nPriority = PRIORITY_NOMAL);
	~CBullet();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage,float fMovement, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ÉQÉbÉ^Å[
	D3DXVECTOR3 GetMove(void) { return m_move; }
	int GetLife() { return m_nLife; }
	int GetMaxLife() { return m_nMaxLife; }
	float GetMovement() { return m_fMovement; }

	// ÉZÉbÉ^Å[
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	D3DXVECTOR3 m_move;							// à⁄ìÆó 
	float m_fMovement;							// à⁄ìÆíl
	int m_nLife;								// éıñΩ
	int m_nMaxLife;								// ç≈ëÂéıñΩ
	int m_nDamage;								// çUåÇóÕ
};

// íeÉNÉâÉX
class CBulletPlayer : public CBullet	// CObject2Dåpè≥
{
public:
	CBulletPlayer(int nPriority = PRIORITY_NOMAL);
	~CBulletPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage, float fMovement, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage, float fMovement, float fWidth, float fHeight);
	bool CollisionEnemy(D3DXVECTOR3 pos);

private:
};

// íeÉNÉâÉX
class CBulletEnemy : public CBullet	// CObject2Dåpè≥
{
public:
	CBulletEnemy(int nPriority = PRIORITY_NOMAL);
	~CBulletEnemy();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage, float fMovement, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage, float fMovement, float fWidth, float fHeight);
	bool CollisionPlayer(D3DXVECTOR3 pos);

private:
};

#endif // !_BULLET_H_
