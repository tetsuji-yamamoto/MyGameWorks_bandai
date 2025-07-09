//**************************************
// 
// ���[�h
// AouthorTetsuji Yamamoto
// 
//**************************************
#ifndef _WORD_H_
#define _WORD_H_

#include "main.h"
#include "object2D.h"

// ���[�h�N���X
class CWord
{
public:
#define FONT_SIZE (200)

	CWord();
	~CWord();

	void Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, const char* pStr);
	void Uninit(void);
	void Update(void);
	void Draw(LPD3DXFONT pFont);

	static CWord* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, char cChar);
private:
	static LPDIRECT3DTEXTURE9 m_pTextureFont;		// �t�H���g�p�̃e�N�X�`��
	static LPDIRECT3DSURFACE9 m_pSurfaceTexFont;	// �t�H���g�p�e�N�X�`���̃����_�[�^�[�Q�b�g
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@
	char m_cChar[3];									// ���̕���
};

#endif // !_WORD_H_
