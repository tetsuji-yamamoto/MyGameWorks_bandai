//**********************************************
// 
// �I�u�W�F�N�g2D����
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

#define STATE_COUNT_NOMAL (60)

// �I�u�W�F�N�g2D�N���X
class CObject2D : public CObject // CObject���p��
{
public:

	CObject2D(int nPriority = PRIORITY_NOMAL);
	~CObject2D();

	HRESULT Init();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float fHeight, int nAppStateCnt = STATE_COUNT_NOMAL);
	void Uninit(void);
	void Update(void);
	void Update(float fPatternWidth, float fPatternHeight, int nNowPattern, int nTexLine);
	void Update(float fFeedRate, float fFeedAngle);
	void Draw(void);
	bool ColisionMouse(float fRadius);

	// �Z�b�^�[
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetIdxTexture(int nIdx) { m_nIdxTexture = nIdx; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }

	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_col;					// �F
	int m_nIdxTexture;					// �e�N�X�`���̃C���f�b�N�X
	float m_fWidth;						// ��
	float m_fHeight;					// ����
};

#endif
