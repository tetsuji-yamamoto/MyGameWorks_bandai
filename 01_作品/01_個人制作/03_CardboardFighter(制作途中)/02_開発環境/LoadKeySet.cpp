//************************************
// 
// �L�[�Z�b�g�ǂݎ��
// Author Tetsuji Yamamoto
// 
//************************************

#include "LoadKeySet.h"
#include "loadMotionFile.h"
#include "manager.h"

//************************************
// �L�[�Z�b�g�ǂݎ��
//************************************
CLoadKeySet::CLoadKeySet() 
{
	m_nFlame = 0;		// �t���[����
	m_nNumKey = 0;		// �L�[��
}

//************************************
// �L�[�Z�b�g�ǂݎ��
//************************************
CLoadKeySet::~CLoadKeySet()
{
}

//************************************
// �L�[�Z�b�g�ǂݎ��
//************************************
void CLoadKeySet::Uninit(void)
{
	// �L�[������̂Ȃ�Δj������
	for (auto& iter : m_pLoadkey)
	{
		iter->Uninit();
	}
	m_pLoadkey.clear();

	delete this;
}

//************************************
// �L�[�Z�b�g�ǂݎ�萶��
//************************************
CLoadKey* CLoadKeySet::CreateLoadKey(int nNumLoadKey)
{
	//// �L�[���ۑ�
	//m_nNumKey = nNumLoadKey;
	//
	//// �k���ł���Ίm�ۂ������������������m�ۂ���
	//if (m_pLoadkey == NULL)
	//{
	//	m_pLoadkey = new CLoadKey[nNumLoadKey];
	//}
	//
	//return m_pLoadkey;

	return NULL;
}

//************************************
// �L�[�Z�b�g�ǂݎ�菉����
//************************************
void CLoadKeySet::Load(void)
{
	// ���[�h���[�V�����t�@�C���|�C���^�擾
	CLoadMotionFile* pLoadMotionFile = CManager::GetLoadMotionFile();

	// �t�@�C���擾
	FILE* pFile = pLoadMotionFile->GetFile();

	// �ǂݎ����������擾
	char* pStr = pLoadMotionFile->GetStr();

	// ���ǂݎ��p�ϐ�
	char aData[3] = {};

	// �Ǎ����ʗp�ϐ�
	int nResult;

	if (strcmp(pStr, "FRAME") == 0)
	{// ���[�v�̗L��
		// =�ǂݎ��
		nResult = fscanf(pFile, "%s", aData);

		// �t���[�����ǂݎ��
		nResult = fscanf(pFile, "%d", &m_nFlame);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "KEY") == 0)
	{// ���[�v�̗L��
		// �L�[�Z�b�g�Ǎ��^�C�v�ɐݒ�
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_KEY);

		// �L�[�̃������m��
		CLoadKey* pLoadKey = new CLoadKey;

		// �v�f�ǉ�
		m_pLoadkey.push_back(pLoadKey);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "END_KEYSET") == 0)
	{// �L�[�Z�b�g

		// �L�[�Z�b�g�̃C���f�b�N�X�擾
		int nIdxKeySet = pLoadMotionFile->GetIdxKeySet();

		// �C���f�b�N�X�J�E���g�A�b�v
		nIdxKeySet++;

		// �C���f�b�N�X�ݒ�
		pLoadMotionFile->SetIdxKeySet(nIdxKeySet);

		// �L�[�C���f�b�N�X������
		pLoadMotionFile->SetIdxKey(0);

		// �L�[�Z�b�g�Ǎ��^�C�v�ɐݒ�
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_MOTIONSET);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
}
