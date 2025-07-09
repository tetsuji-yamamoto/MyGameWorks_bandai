//*************************************
// 
// �I�u�W�F�N�gX
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

// �I�u�W�F�N�gX�N���X
class CObjectX : public CObject // CObject�p��
{
public:
	CObjectX();
	~CObjectX();

	HRESULT Init() { return S_OK; }
	HRESULT Init(const char* pXFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw(D3DXMATRIX *pMtxPearent);
	static CObjectX* Create(const char* pXFileName);

private:
	int *m_apIdxTexture;		// �e�N�X�`���ւ̃C���f�b�N�X�|�C���^�[
	LPD3DXMESH m_pMesh;			// ���b�V��
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A��
	DWORD m_dwNumMat;			// �}�e���A���̐�
	D3DXMATRIX m_mtxWorld;		// �}�g���b�N�X
};

#endif // !_OBJECTX_H_
