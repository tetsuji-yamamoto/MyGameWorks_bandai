//****************************************
// 
// �t�H���g
// Author Tetsuji Yamamoto
// 
//****************************************
#ifndef _FONT_H_
#define _FONT_H_

#include "main.h"

#define FONT_TERMNAL "terminal"
#define FONT_JF_DOT_M_10 "JF�h�b�gM+10"
#define FONT_HG_SOUEI_PRESENS_EB "HG�n�p��ھ�ݽEB"
#define FONT_OSIGO "�����S"
#define FONT_MUKASIMUKASI_FONT "�́X�ӂ����"
#define FONT_MOGIHA_PENJIFont "���M�n�E�y����Font"
#define FONT_���ʂ������}�W�b�N "���ʂ������}�W�b�N"

// �t�H���g�N���X
class CFont
{
public:
	CFont();
	~CFont();

	void Init(LPSTR pFileName, int nFontSize);
	void Uninit(void);
	static CFont* Create(LPSTR pFileName, int nFontSize);

	// �Q�b�^�[
	LPD3DXFONT GetFont(void) { return m_pFont; }
	int GetFontSize(void) { return m_nFontSize; }

private:
	LPD3DXFONT m_pFont;	// �t�H���g�ւ̃|�C���^
	int m_nFontSize;	// �t�H���g�T�C�Y
};

#endif // !_FONT_H_
