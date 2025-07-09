//*********************************************
// 
// ���b�V���t�B�[���h
// Author Tetsuji Yamamoto
// 
//*********************************************
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "object.h"

// ���b�V���t�B�[���h�N���X
class CMeshField : public CObject	// CObject�p��
{
public:
	CMeshField();
	~CMeshField();

	HRESULT Init(void) { return S_OK; }
	HRESULT Init(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fWidth, float fheight, const char* pTexturePass = NULL);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ResetNormal(void);
	static CMeshField* Create(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fWidth, float fheight, const char* pTexturePass = NULL);
	bool Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pNor = NULL);
	void EditHeight(D3DXVECTOR3 pos, float fHeight, float fRadius);
	void Save(const char* pFilePass);
	void Load(const char* pFilePass);

	// �Z�b�^�[
	void SetColor(D3DXCOLOR col);
	void SetPosition(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_startPos;				// �n�܂�̈ʒu
	int m_nIdxTexture;					// �e�N�X�`���ւ̃C���f�b�N�X
	int m_nNumPolygon;					// �|���S����
	int m_nNumVtx;						// ���_��
	int m_nNumIdx;						// �C���f�b�N�X��
	int m_nDivisionX;					// X�̕�����
	int m_nDivisionY;					// Y�̕�����
	float m_fWidth;						// ��
	float m_fHeight;					// ����
};

#endif // !_MESHFIELD_H_
