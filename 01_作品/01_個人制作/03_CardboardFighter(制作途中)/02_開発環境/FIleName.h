//*************************************
// 
// �t�@�C����
// Author Tetsuji Yamamoto
// 
//*************************************
#ifndef _FAILENAME_H_
#define _FAILENAME_H_

#include "main.h"

// �t�@�C�����N���X
class CFileName
{
public:
	CFileName() { memset(m_aFIleName, NULL, sizeof(m_aFIleName)); }
	~CFileName() {}

	void Uninit(void) { delete this; }
	void NullOll(void) { memset(m_aFIleName, NULL, sizeof(m_aFIleName)); }

	// �Q�b�^�[
	char* GetFileName(void) { return &m_aFIleName[0]; }

	// �Z�b�^�[
	 void SetFileName(const char* pFileName) { memcpy(m_aFIleName, pFileName,sizeof(m_aFIleName)); }

private:
	char m_aFIleName[128];
};

#endif // !_FAILENAME_H_