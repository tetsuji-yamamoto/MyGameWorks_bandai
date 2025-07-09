//***************************************
// 
// �L�[�Ǎ�
// AuthorTetsujiYamamoto
// 
//***************************************
#ifndef _LOADKEY_H_
#define _LOADKEY_H_

#include "main.h"

// �L�[�Ǎ��N���X
class CLoadKey
{
public:
	CLoadKey();
	~CLoadKey();

	void Uninit(void);
	void Load(void);

	// �Q�b�^�[
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
};

#endif // !_LOADKEY_H_
