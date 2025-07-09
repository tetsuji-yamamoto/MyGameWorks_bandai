//********************************************
// 
// ���[�V�����t�@�C���Ǎ�
// Author Tetsuji Yamamoto
// 
//********************************************
#ifndef _LOADMOTIONFILE_H_
#define _LOADMOTIONFILE_H_

#include "main.h"
#include "loadCharacterse.h"
#include "FIleName.h"
#include "LoadMotionSet.h"
#include "model.h"
#include "motion.h"
#include <vector>

// �Ǎ��N���X
class CLoadMotionFile
{
public:
#define MAX_PARTS_NUM (32)
#define MAX_XFILE_NUM (32)

	// �t�@�C���ǂݎ��^�C�v
	typedef enum
	{
		TYPE_SCRIPT = 0,
		TYPE_CHARCTERSET,
		TYPE_PARTSSET,
		TYPE_MOTIONSET,
		TYPE_KEYSET,
		TYPE_KEY,
		TYPE_MAX
	}TYPE;

	CLoadMotionFile();
	~CLoadMotionFile();

	void Uninit(void);
	void Load(const char* pFileName);
	void ClearStr(void) { memset(m_aStr, NULL, sizeof(m_aStr)); }
	void ResetIdxStr(void) { m_nIdxStr = 0; }
	static CLoadMotionFile* Create(void);
	void CopyMotion(CMotion** ppMotion);
	void CopyModel(std::vector<CModel*>* ppVectorModel);
	void Reset(void);

	// �Q�b�^�[
	FILE* GetFile(void) { return m_pFile; }
	CCharacterSet* GetCharacterSet(void) { return m_pLoadCharacterSet; }
	auto GetPartsSet(int nElementNum) { return m_pLoadPartsSet.begin() + nElementNum; }
	auto GetXFileName(int nElementNum) { return m_pXFileName.begin() + nElementNum; }
	CLoadMotionSet* GetLoadMotionSet(int nIdx) { return m_apLoadMotionSet[nIdx]; }
	char* GetStr(void) { return &m_aStr[0]; }
	bool GetIsComment(void) { return m_bComment; }
	int GetIdxStr(void) { return m_nIdxStr; }
	int GetIdxFIleName(void) { return m_nIdxFileName; }
	int GetResult(void) { return m_nResult; }
	int GetIdxLoadPartsSet(void) { return m_nIdxLoadPartsSet; }
	int GetIdxMotionset(void) { return m_nIdxMotionset; }
	int GetIdxKey(void) { return m_nIdxKey; }
	int GetModelNum(void) { return m_nModelNum; }
	int GetIdxKeySet(void) { return m_nIdxKeySet; }
	int GetNumMotion(void) { return m_nNumMotion; }

	// �Z�b�^�[
	void SetType(TYPE type) { m_type = type; }													// �t�@�C���ǂݎ��^�C�v
	void SetPartsSet(CLoadPartsSet* pLoadPartsSet) { /*m_pLoadPartsSet = pLoadPartsSet;*/ }
	void SetIdxLoadPartsSet(int nIdxLoadPartsSet) { m_nIdxLoadPartsSet = nIdxLoadPartsSet; }
	void SetIdxMotionset(int nIdxMotionset) { m_nIdxMotionset = nIdxMotionset; }
	void SetIdxKey(int nIdxKey) { m_nIdxKey = nIdxKey; }
	void SetModelNum(int nMmodelNum) { m_nModelNum = nMmodelNum; }
	void SetIdxKeySet(int nIdxKeySet) { m_nIdxKeySet = nIdxKeySet; }
	void SetNumMotion(int nNumMotion) { m_nNumMotion = nNumMotion; }
	void SetPushBackLoadPartsSet(CLoadPartsSet** ppLoadPartsSet) { m_pLoadPartsSet.push_back(*ppLoadPartsSet); }

private:
	FILE* m_pFile;										// �t�@�C���|�C���^
	TYPE m_type;										// �ǂݎ��^�C�v
	CCharacterSet* m_pLoadCharacterSet;					// �L�����N�^�[���|�C���^�[
	std::vector< CFileName*> m_pXFileName;				// �t�@�C����
	std::vector<CLoadPartsSet*> m_pLoadPartsSet;		// �p�[�c�Z�b�g�|�C���^�[
	std::vector<CLoadMotionSet*> m_apLoadMotionSet;		// ���[�V�����Z�b�g�|�C���^�[
	char m_aStr[1024];									// ������
	bool m_bComment;									// �R�����g�̗L��
	int m_nIdxStr;										// ������C���f�b�N�X
	int m_nIdxFileName;									// �t�@�C�����C���f�b�N�X
	int m_nIdxLoadPartsSet;								// �p�[�c�Z�b�g�C���f�b�N�X
	int m_nIdxMotionset;								// ���[�V�����Z�b�g�C���f�b�N�X
	int m_nIdxKeySet;									// �L�[�Z�b�g�̃C���f�b�N�X
	int m_nIdxKey;										// �L�[�̃C���f�b�N�X
	int m_nResult;										// �ǂݎ�茋�ʗp
	int m_nModelNum;									// ���f���̐�
	int m_nNumMotion;									// ���[�V�����̐�
};

#endif // !_LOADFILE_H_
