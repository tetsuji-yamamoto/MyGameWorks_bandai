//*************************************
// 
// �I�u�W�F�N�g�X�e�[�W
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _OBJECTSTAGE_H_
#define _OBJECTSTAGE_H_

#include "main.h"
#include "object.h"

// �I�u�W�F�N�gX�N���X
class CObjectStage
{
public:
	CObjectStage();
	~CObjectStage();

	HRESULT Init() { return S_OK; }
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Draw(D3DXMATRIX* pMtxPearent);
	static CObjectStage* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName);
	bool CollisionMouse(float fRadius);

	// �Q�b�^�[
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXMATRIX SetMatrix(void) { return m_mtxWorld; }
	LPD3DXMESH GetMesh(void) { return m_pMesh; }
	int* GetIndexTexture(void) { return m_apIdxTexture; }

	// �Z�b�^�[
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }
	void SetIndexTexture(int* pIdx) { m_apIdxTexture = pIdx; }
	void SetAlphaColor(float fAlphar);

private:
	int* m_apIdxTexture;		// �e�N�X�`���ւ̃C���f�b�N�X�|�C���^�[
	LPD3DXMESH m_pMesh;			// ���b�V��
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A��
	DWORD m_dwNumMat;			// �}�e���A���̐�
	D3DXMATRIX m_mtxWorld;		// �}�g���b�N�X

	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
};

#endif // !_OBJECTX_H_
