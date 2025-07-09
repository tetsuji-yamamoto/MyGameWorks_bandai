//********************************************
// 
// �L�����N�^�[���ǂݎ��
// Author Tetsuji Yamamoto
// 
//********************************************
#ifndef _CHARACTERSET_H_
#define _CHARACTERSET_H_

#include "main.h"

// �L�����N�^�[���ǂݎ��N���X
class CCharacterSet
{
public:
	CCharacterSet();
	~CCharacterSet();

	void Uninit(void);
	void Load(void);

	// �Q�b�^�[
	int GetNumParts(void) { return m_nNumParts; }
	float GetMovement(void) { return m_fMovement; }
	float GetJump(void) { return m_fJump; }
	float GetRadius(void) { return m_fRadius; }
	float GetHeight(void) { return m_fHeight; }
	int GetLife(void) { return m_nLife; }

	// �Z�b�^�[
	void GetNumParts(int nNumParts) { m_nNumParts = nNumParts; }

private:
	int m_nNumParts;	// �p�[�c��
	float m_fMovement;	// �ړ���
	float m_fJump;		// �W�����v��
	float m_fRadius;	// ���a
	float m_fHeight;	// ����
	int m_nLife;		// �̗�
};

// �p�[�c�Z�b�g�ǂݎ��N���X
class CLoadPartsSet
{
public:
	CLoadPartsSet();
	~CLoadPartsSet();

	void Uninit(void);
	void Load(void);

	int GetIndexParrent(void) { return m_nIdxParent; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
private:
	int m_nIdxParent;		// �e���f���̃C���f�b�N�X�ԍ�
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
};

#endif // !_CHARACTERSET_H_
