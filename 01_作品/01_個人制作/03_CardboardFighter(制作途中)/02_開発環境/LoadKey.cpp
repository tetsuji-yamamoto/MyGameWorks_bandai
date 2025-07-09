//***************************************
// 
// �L�[�Ǎ�
// AuthorTetsujiYamamoto
// 
//***************************************
#include "LoadKey.h"
#include "loadMotionFile.h"
#include "manager.h"

//***************************************
// �L�[�Ǎ�
//***************************************
CLoadKey::CLoadKey()
{
	m_pos = D3DXVECTOR3_NULL;
	m_rot = D3DXVECTOR3_NULL;
}

//***************************************
// �L�[�Ǎ�
//***************************************
CLoadKey::~CLoadKey()
{
}

//***************************************
// �L�[�Ǎ�
//***************************************
void CLoadKey::Uninit(void)
{
	delete this;
}

//***************************************
// �L�[�Ǎ�
//***************************************
void CLoadKey::Load(void)
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

	if (strcmp(pStr, "POS") == 0)
	{// ���[�v�̗L��
		// =�ǂݎ��
		nResult = fscanf(pFile, "%s", aData);

		// �ʒu�̗L���ǂݎ��
		nResult = fscanf(pFile, "%f", &m_pos.x);
		nResult = fscanf(pFile, "%f", &m_pos.y);
		nResult = fscanf(pFile, "%f", &m_pos.z);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "ROT") == 0)
	{// �L�[��
		// =�ǂݎ��
		nResult = fscanf(pFile, "%s", aData);

		// �����̓ǂݎ��
		nResult = fscanf(pFile, "%f", &m_rot.x);
		nResult = fscanf(pFile, "%f", &m_rot.y);
		nResult = fscanf(pFile, "%f", &m_rot.z);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "END_KEY") == 0)
	{// �L�[�Z�b�g
		// �L�[�̃C���f�b�N�X�擾
		int nIdx = pLoadMotionFile->GetIdxKey();

		// �C���f�b�N�X�J�E���g�A�b�v
		nIdx++;

		// �C���f�b�N�X�ݒ�
		pLoadMotionFile->SetIdxKey(nIdx);

		// �L�[�Z�b�g�Ǎ��^�C�v�ɐݒ�
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_KEYSET);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
}