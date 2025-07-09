//*************************************
// 
// �t�H���g�}�l�[�W���[
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include "main.h"
#include "font.h"

// �t�H���g�}�l�[�W���[
class CFontManager
{
public:

	// ���
	typedef enum
	{
		TYPE_DEBUG = 0,
		TYPE_SCORE,
		TYPE_MAX
	}TYPE;

	CFontManager();
	~CFontManager();

	void Init(void);
	void Uninit(void);
	static CFontManager* Create(void);
	
	// �Q�b�^�[
	CFont* GetFont(TYPE type) { return m_apFont[type]; }

private:
	CFont* m_apFont[TYPE_MAX];	// �t�H���g�ւ̃|�C���^�[

	const char* m_apFileName[TYPE_MAX] = 
	{
		FONT_JF_DOT_M_10,
		FONT_���ʂ������}�W�b�N,
	};

	int m_aFontSize[TYPE_MAX] =
	{
		18,
		200,
	};
};

#endif // !_FONTMANAGER_H_
