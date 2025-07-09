//*****************************************
// 
// �r���{�[�h
// Author Tetsuji Yamamoto
// 
//*****************************************
#ifndef _OBJECTBILLBOARD_H_
#define _OBJECTBILLBOARD_H_

#include "main.h"
#include "object.h"

// �I�u�W�F�N�g�r���{�[�h�N���X
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard();
	~CObjectBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObjectBillboard* Create(void);
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	int m_nIdxTexture;					// �e�N�X�`���ւ̃C���f�b�N�X
};

#endif // !_OBJECTBILLBOARD_H_
