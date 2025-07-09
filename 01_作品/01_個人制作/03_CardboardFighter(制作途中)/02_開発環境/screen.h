//**********************************************
// 
// �X�N���[������
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "main.h"

// �X�N���[���N���X
class CScreen
{
public:

	CScreen();
	~CScreen();

	void Init(D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(LPDIRECT3DTEXTURE9 pTexture);
	void DrawAlpherTest(LPDIRECT3DTEXTURE9 pTexture);
	void UpdateScale(void);

	// �Z�b�^�[
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	void SetHeight(float fHeight) { m_fHeight = fHeight; }
	void SetColor(D3DXCOLOR col);
	void SetScaleSize(float fScaleValue,int nTimeScale);

	// �Q�b�^�[
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetScaleValue(void) { return m_fScaleValue; }

	static CScreen* Create(D3DXCOLOR col);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_col;					// �F
	float m_fWidth;						// ��
	float m_fHeight;					// ����
	float m_fSize;						// �傫��

	bool m_bScale;			// �g��̗L��
	float m_fScaleValue;	// �g�嗦
	float m_fScaleValueNow;	// ���̊g�嗦
	int m_nFrameScale;		// �g�傷�鎞��
	int m_nCntScale;		// �g��J�E���^�[
};

#endif
