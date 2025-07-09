//**************************************************************
// 
// �����蔻��
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
// �����蔻��N���X
class CCollision : public CObject // CObject�p��
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

	// �Z�b�^�[
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	static bool m_bDraw;		// �\���̗L��
	bool m_bTrigger;			// ���������u�Ԃ��ǂ���
	D3DXVECTOR3 m_posOffset;	// �ʒu�I�t�Z�b�g
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXMATRIX m_mtxWorld;		// �}�g���b�N�X
};

//-----------------------------------------------------------------------
// ���̓����蔻��N���X
class CCollisionSpher : public CCollision // CCollision�p��
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

	// �Q�b�^�[
	float GetRadius(void) { return m_fRadius; }
	int GetIndexModel(void) { return m_nIdxModel; }

private:
	int m_nIdxModel;		// ���f���̃C���f�b�N�X�ԍ�
	CSphere* m_pSpher;	// �\���p�̋�
	float m_fRadius;	// ���a
};

//-----------------------------------------------------------------------
// �~���̓����蔻��N���X
class CCollisionCylinder : public CCollision // CCollision�p��
{
public:
	CCollisionCylinder();
	~CCollisionCylinder();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius,float fHeight);
	void Uninit(void);
	void Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent);
	void Draw(void);
	static CCollisionCylinder* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, float fHeight);

	// �Q�b�^�[
	float GetRadius(void) { return m_fRadius; }
	float GetHeight(void) { return m_fHeight; }


private:
	CCylinder* m_pCylinder;	// �\���p�̉~��
	float m_fRadius;		// ���a
	float m_fHeight;		// ����
};
#endif // !_COLLISION_H_