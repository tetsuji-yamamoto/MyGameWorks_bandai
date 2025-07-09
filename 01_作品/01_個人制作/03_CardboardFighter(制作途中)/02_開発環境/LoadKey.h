//***************************************
// 
// キー読込
// AuthorTetsujiYamamoto
// 
//***************************************
#ifndef _LOADKEY_H_
#define _LOADKEY_H_

#include "main.h"

// キー読込クラス
class CLoadKey
{
public:
	CLoadKey();
	~CLoadKey();

	void Uninit(void);
	void Load(void);

	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
};

#endif // !_LOADKEY_H_
