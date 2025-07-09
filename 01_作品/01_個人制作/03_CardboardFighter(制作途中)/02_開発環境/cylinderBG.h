//*********************************************
// 
// �V�����_�[�̔w�i
// Author Tetsuji Yamamoto
// 
//*********************************************
#ifndef _SYLINDERBG_H_
#define _SYLINDERBG_H_

#include "main.h"
#include "object.h"
#include "cylinder.h"

// �V�����_�[�N���X
class CCylinderBG : public CObject	// CObject�p��
{
public:
	CCylinderBG();
	~CCylinderBG();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fRadius, float fheight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCylinderBG* Create(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fRadius, float fheight);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int m_nIdxTexture;					// �e�N�X�`���ւ̃C���f�b�N�X
	int m_nNumPolygon;					// �|���S����
	int m_nNumVtx;						// ���_��
	int m_nNumIdx;						// �C���f�b�N�X��
};

#endif // !_SYLINDER_H_
