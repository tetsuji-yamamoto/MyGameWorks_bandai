//**********************************************
// 
// �����_���[����
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"
#include "screen.h"

// �����_���[�N���X
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd,BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
	void ChangeTarget(int nIdxTexture, D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureMT(int nIdx) { return m_apTextureMT[nIdx]; }
	LPDIRECT3DSURFACE9 GetZBuffMT(void) { return m_pZBuffMT; }
	void ClearTextureMT(void);
	void SetBlur(D3DXCOLOR bulrColor);
	void SetBlurUp(int nBlurTime, float fScaleValue, D3DXCOLOR bulrColor);
	void UpdateBulrUp(void);

private:
	LPDIRECT3D9 m_pD3D;						// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	static LPDIRECT3DDEVICE9 m_pD3DDevice;	// Direct3D�f�o�C�X�ւ̃|�C���^

	bool m_bBlur;		// �ڂ����̗L��
	bool m_bBlurUp;		// �g��ڂ����̗L��
	int m_nBlurTime;	// �ڂ�������
	int m_nCntBulur;	// �ڂ����J�E���^�[
	LPDIRECT3DTEXTURE9 m_apTextureMT[2];	// �����_�����O�^�[�Q�b�g�p�e�N�X�`��
	LPDIRECT3DSURFACE9 m_apRenderMT[2];		// �e�N�X�`�������_�����O�p�C���^�[�[�t�F�[�X
	LPDIRECT3DSURFACE9 m_pZBuffMT;			// �e�N�X�`�������_�����O�pZ�o�b�t�@
	D3DVIEWPORT9 m_viewPortMT;				// �e�N�X�`�������_�����O�p�r���[�|�[�g

	CScreen* m_apScreen[2];	// ��ʗp�|���S��
};
#endif