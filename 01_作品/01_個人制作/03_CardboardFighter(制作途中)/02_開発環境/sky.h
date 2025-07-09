//**************************************
// 
// ��
// Author Tetsuji Yamamoto
// 
//**************************************
#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
#include "object.h"

// ��N���X
class CSky : public CObject // CObject3D�p��
{
public:
	CSky();
	~CSky();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(int nDivisionX, int nDivisionY, float fRadius);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSky* Create(int nDivisionX, int nDivisionY, float fRadius);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu
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
};


#endif // !_SKY_H_
