//************************************************************************************************
// 
// ���[�V�����Z�b�g�ǂݎ��
// Author Tetsuji Yamamoto
// 
//************************************************************************************************
#include "LoadMotionSet.h"
#include "loadMotionFile.h"
#include "manager.h"

//************************************************************************************************
// ���[�V�����Z�b�g�ǂݎ��
//************************************************************************************************
CLoadMotionSet::CLoadMotionSet()
{
	m_bLoop = false;		// ���[�v�̗L��
	m_nNumKey = 0;			// �L�[��
	m_nNumKeySet = 0;		// �L�[�Z�b�g��
}

//************************************************************************************************
// ���[�V�����Z�b�g�ǂݎ��
//************************************************************************************************
CLoadMotionSet::~CLoadMotionSet()
{

}

//************************************************************************************************
// ���[�V�����Z�b�g�ǂݎ��
//************************************************************************************************
void CLoadMotionSet::Uninit(void)
{
	// �L�[�Z�b�g������Ȃ�Δj������
	for (auto& iter : m_pLoadKeySet)
	{
		iter->Uninit();
	}
	m_pLoadKeySet.clear();
	
	delete this;
}

//************************************************************************************************
// ���[�V�����Z�b�g�ǂݎ��L�[�Z�b�g����
//************************************************************************************************
CLoadKeySet* CLoadMotionSet::CreateLoadkeySet(int nNumLoadKeySet)
{
	//// �L�[�Z�b�g�̐��ۑ�
	//m_nNumKeySet = nNumLoadKeySet;

	//// �k���ł���Ίm�ۂ������������������m�ۂ���
	//if (m_pLoadKeySet == NULL)
	//{
	//	m_pLoadKeySet = new CLoadKeySet[nNumLoadKeySet];
	//}

	//return m_pLoadKeySet;
	return NULL;
}

//************************************************************************************************
// ���[�V�����Z�b�g�ǂݎ��
//************************************************************************************************
void CLoadMotionSet::Load(void)
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

	if (strcmp(pStr, "LOOP") == 0)
	{// ���[�v�̗L��
		// =�ǂݎ��
		nResult = fscanf(pFile, "%s", aData);

		// ���[�v�̗L���ǂݎ��
		int nData = 0;
		nResult = fscanf(pFile, "%d", &nData);
		m_bLoop = (bool)nData;

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "NUM_KEY") == 0)
	{// �L�[��
		// =�ǂݎ��
		nResult = fscanf(pFile, "%s", aData);

		// �L�[���ǂݎ��
		nResult = fscanf(pFile, "%d", &m_nNumKey);

		// �L�[�������������m�ۂ���
		this->CreateLoadkeySet(m_nNumKey);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "KEYSET") == 0)
	{// �L�[�Z�b�g
		// ���f�����擾
		int NumModel = pLoadMotionFile->GetModelNum();

		// �L�[�Z�b�g�̃C���f�b�N�X�擾
		int nIdxKeySet = pLoadMotionFile->GetIdxKeySet();

		// ���f���̐����L�[�𐶐�����
		CLoadKeySet* pLoadKeySet = new CLoadKeySet;

		// �v�f��ǉ�����
		m_pLoadKeySet.push_back(pLoadKeySet);

		// �L�[�Z�b�g�Ǎ��^�C�v�ɐݒ�
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_KEYSET);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "END_MOTIONSET") == 0)
	{// �I��
		// ���[�V�����Z�b�g�C���f�b�N�X���擾
		int nIdx = pLoadMotionFile->GetIdxMotionset();

		// �C���f�b�N�X�J�E���g�A�b�v
		nIdx++;

		// �C���f�b�N�X���Z�b�g
		pLoadMotionFile->SetIdxMotionset(nIdx);

		// �L�[�Z�b�g�ƃL�[�̃C���f�b�N�X�����Z�b�g
		pLoadMotionFile->SetIdxKey(0);
		pLoadMotionFile->SetIdxKeySet(0);

		// �X�N���v�g�Ǎ��^�C�v�ɖ߂�
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_SCRIPT);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
}

//************************************************************************************************
// ���[�V�����Z�b�g�L�[�Z�b�g�ǂݎ��
//************************************************************************************************
void CLoadMotionSet::LoadLoadKeyset(void)
{
	auto iter = m_pLoadKeySet.end() - 1;
	(*iter)->Load();
}