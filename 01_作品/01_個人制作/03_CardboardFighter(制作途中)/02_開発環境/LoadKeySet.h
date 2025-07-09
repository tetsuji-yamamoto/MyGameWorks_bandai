//************************************
// 
// �L�[�Z�b�g�ǂݎ��
// Author Tetsuji Yamamoto
// 
//************************************
#ifndef _LOADKEYSET_H_
#define _LOADKEYSET_H_

#include "main.h"
#include "LoadKey.h"
#include <vector>

// �L�[�Z�b�g�ǂݎ��N���X
class CLoadKeySet
{
public:
	CLoadKeySet();
	~CLoadKeySet();

	void Uninit(void);
	void Load(void);
	CLoadKey* CreateLoadKey(int nNumLoadKey);


	// �Q�b�^�[
	int GetFlame(void) { return m_nFlame; }
	std::vector<CLoadKey*> GetLoadKey(void) { return m_pLoadkey; }
	auto GetLoadKeyElementEnd(void) { return m_pLoadkey.end() - 1; }
	auto GetLoadKeyBegin(void) { return m_pLoadkey.begin(); }
	auto GetLoadKeyEnd(void) { return m_pLoadkey.end(); }

	// �Z�b�^�[
	void SetFlame(int nFlame) { m_nFlame = nFlame; }

private:
	int m_nFlame;			// �t���[����
	std::vector<CLoadKey*> m_pLoadkey;	// �L�[�|�C���^�[
	int m_nNumKey;			// �L�[��
};

#endif // !_LOADKEYSET_H_