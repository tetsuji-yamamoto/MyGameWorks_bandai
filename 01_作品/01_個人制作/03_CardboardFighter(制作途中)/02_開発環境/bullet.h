//****************************************************************************
// 
// �e
// Author tetuji yamamoto
// 
//****************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "object2D.h"

// �e�N���X
class CBullet : public CObject2D	// CObject2D�p��
{
public:
	CBullet(int nPriority = PRIORITY_NOMAL);
	~CBullet();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nDamage,float fMovement, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Q�b�^�[
	D3DXVECTOR3 GetMove(void) { return m_move; }
	int GetLife() { return m_nLife; }
	int GetMaxLife() { return m_nMaxLife; }
	float GetMovement() { return m_fMovement; }

	// �Z�b�^�[
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	D3DXVECTOR3 m_move;							// �ړ���
	float m_fMovement;							// �ړ��l
	int m_nLife;								// ����
	int m_nMaxLife;								// �ő����
	int m_nDamage;								// �U����
};

// �e�N���X
class CBulletPlayer : public CBullet	// CObject2D�p��
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

// �e�N���X
class CBulletEnemy : public CBullet	// CObject2D�p��
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
