//****************************************
// 
// ���C�g
// Author Tetsuji Yamamoto
// 
//****************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

// ���C�g�N���X
class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DLIGHT9 m_aLight[3];
};

#endif // !_LIGHT_H_
