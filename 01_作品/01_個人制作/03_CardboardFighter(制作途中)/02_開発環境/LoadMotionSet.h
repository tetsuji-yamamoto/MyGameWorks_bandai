//**********************************
// 
// ���[�V�����Z�b�g�ǂݎ��
// Author Tetsuji Yamamoto
// 
//**********************************
#ifndef _MOTIONSET_H_
#define _MOTIONSET_H_

#include "main.h"
#include "motion.h"
#include "LoadKeySet.h"
#include <vector>

// ���[�V�����Z�b�g�Ǎ��N���X
class CLoadMotionSet
{
public:
#define MAX_LOAD_MOTION (32)	// ���[�V�����̍ő吔

	CLoadMotionSet();
	~CLoadMotionSet();

	void Uninit(void);
	void Load(void);
	CLoadKeySet* CreateLoadkeySet(int nNumLoadKeySet);
	void LoadLoadKeyset(void);

	// �Q�b�^�[
	bool GetLoop(void) { return m_bLoop; }
	int GetNumKey(void) { return m_nNumKey; }
	std::vector<CLoadKeySet*> GetkeySet(void) { return m_pLoadKeySet; }
	auto GetLoadKeySetBegin(void) { return m_pLoadKeySet.begin(); }
	auto GetLoadKeySetEnd(void) { return m_pLoadKeySet.end(); }
	auto GetLoadKeySetElementEnd(void) { return m_pLoadKeySet.end() - 1; }

	// �Z�b�^�[
	void SetLoop(bool bLoop) { m_bLoop = bLoop; }
	void SetNumKey(int nNumKey) { m_nNumKey = nNumKey; }

private:
	bool m_bLoop;	// ���[�v�̗L��
	int m_nNumKey;	// �L�[��

	std::vector<CLoadKeySet*> m_pLoadKeySet;	// �L�[�Z�b�g�|�C���^
	int m_nNumKeySet;							// �L�[�Z�b�g�̐�
};

#endif // !_MOTIONSET_H_