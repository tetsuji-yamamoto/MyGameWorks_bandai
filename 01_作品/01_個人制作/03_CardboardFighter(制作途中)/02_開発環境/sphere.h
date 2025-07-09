//**************************************
// 
// ��
// Author Tetsuji Yamamoto
// 
//**************************************
#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "main.h"
#include "object.h"

// ���N���X
class CSphere
{
public:
	CSphere();
	~CSphere();

	HRESULT Init(int nDivisionX, int nDivisionY, float fRadius, D3DXCOLOR col, const char* texturePass);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSphere* Create(int nDivisionX, int nDivisionY, float fRadius, D3DXCOLOR col, const char* texturePass);

	// �Z�b�^�[
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	int m_nIdxTexture;					// �e�N�X�`���ւ̃C���f�b�N�X
	int m_nNumPolygonMeshField;			// ���b�V���̃|���S���̐�
	int m_nNumVtx;						// ���_��
	int m_nNumVtxFan;					// ���̒��_�̐�
	int m_nNumVtxMeshField;				//���b�V���̒��_�̐�
	int m_nNumIdx;						// �C���f�b�N�X��
	int m_nNumIdxFan;					// �t�@���̃C���f�b�N��
	int m_nNumIdxMeshField;				// ���b�V���t�B�[���h�̃C���f�b�N�X��
	int m_nDivisionX;					// ������X
	int m_nDivisionY;					// ������Y
	bool m_bWire;						// ���C���[�\���̗L��
};

#endif // !SPHERE_H_