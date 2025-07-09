//*********************************************
// 
// �V�����_�[
// Author Tetsuji Yamamoto
// 
//*********************************************
#ifndef _SYLINDER_H_
#define _SYLINDER_H_

#include "main.h"
#include "object.h"

// �V�����_�[�N���X
class CCylinder
{
public:
	CCylinder();
	~CCylinder();

	HRESULT Init(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fRadius, float fHeight, D3DXCOLOR col,const char* pTexturePass);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCylinder* Create(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fRadius, float fHeight, D3DXCOLOR col,const char* pTexturePass);

	// �Z�b�^�[
	void SetMatrix(D3DXMATRIX mtx) {m_mtxWorld = mtx;}

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	int m_nIdxTexture;					// �e�N�X�`���ւ̃C���f�b�N�X
	int m_nNumPolygon;					// �|���S����
	int m_nNumVtx;						// ���_��
	int m_nNumIdx;						// �C���f�b�N�X��
};

#endif // !_SYLINDER_H_
