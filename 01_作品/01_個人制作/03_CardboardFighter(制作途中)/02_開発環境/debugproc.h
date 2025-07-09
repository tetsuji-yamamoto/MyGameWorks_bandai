//****************************************************************************
// 
// �f�o�b�O����
// Author tetuji yamamoto
// 
//****************************************************************************
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"
#include "font.h"

#define MAX_FONT_SIZE (20)
#define MAX_DEBUG_STR_NUM (1024)

// �f�o�b�O�N���X
class CDebugprocc
{
public:
	CDebugprocc();
	~CDebugprocc();

	void Init(void);
	void Uninit(void);
	static void Print(const char *fmt,...);
	static void Draw(void);

	static LPD3DXFONT GetFont() { return m_pFont; }

private:
	static LPD3DXFONT m_pFont;	// �t�H���g�ւ̃|�C���^
	static char m_aStr[MAX_DEBUG_STR_NUM];	// ��������i�[����o�b�t�@
	static int m_nNumLine;	// �s��
};

#endif