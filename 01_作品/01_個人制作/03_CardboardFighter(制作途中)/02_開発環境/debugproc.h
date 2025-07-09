//****************************************************************************
// 
// デバッグ処理
// Author tetuji yamamoto
// 
//****************************************************************************
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"
#include "font.h"

#define MAX_FONT_SIZE (20)
#define MAX_DEBUG_STR_NUM (1024)

// デバッグクラス
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
	static LPD3DXFONT m_pFont;	// フォントへのポインタ
	static char m_aStr[MAX_DEBUG_STR_NUM];	// 文字列を格納するバッファ
	static int m_nNumLine;	// 行数
};

#endif