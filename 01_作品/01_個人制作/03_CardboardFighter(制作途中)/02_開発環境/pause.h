//***********************************************************
// 
// �|�[�Y
// Author Tetsuji Yamamoto
// 
//***********************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "object.h"

// �|�[�Y�N���X
class CPause : public CObject // CObject�p��
{
public:
	CPause(int nPriority = PRIORITY_NOMAL);
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPause* Create(void);

	// �Z�b�^�[
	void SetPause(bool bPause) { m_bPause = bPause; }
	
	// �Q�b�^�[
	bool GetPause(void) { return m_bPause; }

private:
	bool m_bPause;
};

#endif // !_PAUSE_H_
