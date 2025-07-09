//*************************************
// 
// �I�u�W�F�N�g3D
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

// �I�u�W�F�N�g3D�N���X
class CObject3D : public CObject // CObject�p��
{
public:
	CObject3D(int nPriority = CObject::PRIORITY_3);
	~CObject3D();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float fHeight, float fDepth, const char* pTexturePass);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawNoTexture(void);
	static CObject3D* Create(void);

	// �Z�b�^�[
	void SetColor(D3DXCOLOR col);
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }

	// �Q�b�^�[
	int GetIdxTexture(void) { return m_nIdxTexture; }
	D3DXVECTOR3 GetVtxPos(int nNumVtx);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotasion(void) { return m_rot; }
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }


private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_col;					// �F
	float m_fWidth;						// ��
	float m_fHeight;					// ����
	float m_fDepth;						// ���s��
	int m_nIdxTexture;					// �e�N�X�`���ւ̃C���f�b�N�X
};

#endif // !_OBJECT3D_H_
