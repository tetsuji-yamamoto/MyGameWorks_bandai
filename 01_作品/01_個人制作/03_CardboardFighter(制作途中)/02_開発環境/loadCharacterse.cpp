//********************************************
// 
// �L�����N�^�[���ǂݎ��
// Author Tetsuji Yamamoto
// 
//********************************************
#include "loadCharacterse.h"
#include "manager.h"

//*************************************
// ���f���ǂݎ��
//*************************************
CCharacterSet::CCharacterSet()
{
	m_nNumParts = 0;	// �p�[�c��
	m_fMovement = 0.0f;	// �ړ���
	m_fJump = 0.0f;		// �W�����v��
	m_fRadius = 0.0f;	// ���a
	m_fHeight = 0.0f;	// ����
	m_nLife = 0;		// �̗�
}

//*************************************
// ���f���ǂݎ��
//*************************************
CCharacterSet::~CCharacterSet()
{

}

//*************************************
// ���f���ǂݎ��
//*************************************
void CCharacterSet::Uninit(void)
{
	delete this;
}

//*************************************
// ���f���ǂݎ��
//*************************************
void CCharacterSet::Load()
{
	// ���[�h���[�V�����t�@�C���|�C���^�擾
	CLoadMotionFile* pLoadMotionFile = CManager::GetLoadMotionFile();

	// �t�@�C���擾
	FILE* pFile = pLoadMotionFile->GetFile();

	// �ǂݎ����������擾
	char* pStr = pLoadMotionFile->GetStr();

	// ���ǂݎ��ϐ�
	char aData[3] = {};

	if (strcmp(pStr, "END_CHARACTERSET") == 0)
	{// �L�����N�^�[���ǂݎ��I��

		// �X�N���v�g�ǂݎ��^�C�v�ɕύX
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_SCRIPT);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "NUM_PARTS") == 0)
	{
		// ���ǂݎ��
		fscanf(pFile, "%s", aData);

		// �p�[�c���ǂݎ��
		fscanf(pFile, "%d", &m_nNumParts);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "MOVE") == 0)
	{
		// ���ǂݎ��
		fscanf(pFile, "%s", aData);

		// �l�ǂݎ��
		fscanf(pFile, "%f", &m_fMovement);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "JUMP") == 0)
	{
		// ���ǂݎ��
		fscanf(pFile, "%s", aData);

		// �l�ǂݎ��
		fscanf(pFile, "%f", &m_fJump);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "RADIUS") == 0)
	{
		// ���ǂݎ��
		fscanf(pFile, "%s", aData);

		// �l�ݎ��
		fscanf(pFile, "%f", &m_fRadius);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "HEIGHT") == 0)
	{
		// ���ǂݎ��
		fscanf(pFile, "%s", aData);

		// �l�ݎ��
		fscanf(pFile, "%f", &m_fHeight);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "LIFE") == 0)
	{
		// ���ǂݎ��
		fscanf(pFile, "%s", aData);

		// �l�ݎ��
		fscanf(pFile, "%d", &m_nLife);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "PARTSSET") == 0)
	{
		// �p�[�c�Z�b�g�ǂݎ��^�C�v�ɕύX
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_PARTSSET);

		// �p�[�c�Z�b�g�̃C���X�^���X�����A�m��
		CLoadPartsSet* pLoadPartsSet = new CLoadPartsSet;

		// �p�[�c�Z�b�g�̏��𖖔��ɒǉ�
		pLoadMotionFile->SetPushBackLoadPartsSet(&pLoadPartsSet);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
}

//--------------------------------------------------------------------------------
// �p�[�c�Z�b�g

//*************************************
// �p�[�c�ǂݎ��R���X�g���N�^
//*************************************
CLoadPartsSet::CLoadPartsSet()
{
	m_nIdxParent = -1;
	memset(m_pos, NULL, sizeof(m_pos));
	memset(m_rot, NULL, sizeof(m_rot));
}

//*************************************
// �p�[�c�ǂݎ��f�X�g���N�^
//*************************************
CLoadPartsSet::~CLoadPartsSet()
{

}

//*************************************
// �p�[�c�ǂݎ��I������
//*************************************
void CLoadPartsSet::Uninit(void)
{
	delete this;
}

//*************************************
// �p�[�c�ǂݎ��
//*************************************
void CLoadPartsSet::Load()
{
	// ���[�h���[�V�����t�@�C���|�C���^�擾
	CLoadMotionFile* pLoadMotionFile = CManager::GetLoadMotionFile();
	FILE* pFile = pLoadMotionFile->GetFile();

	char* pStr = pLoadMotionFile->GetStr();
	char aData[3] = {};
	int nResult;

	if (strcmp(pStr, "INDEX") == 0)
	{// �C���f�b�N�X
		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "PARENT") == 0)
	{// �e
		nResult = fscanf(pFile, "%s", aData);			// =��ǂݍ���
		nResult = fscanf(pFile, "%d", &m_nIdxParent);	// �e�C���f�b�N�X��ǂݍ���

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "POS") == 0)
	{// �ʒu
		nResult = fscanf(pFile, "%s", aData);		// =��ǂݍ���
		nResult = fscanf(pFile, "%f", &m_pos.x);	// x���W��ǂݍ���
		nResult = fscanf(pFile, "%f", &m_pos.y);	// y���W��ǂݍ���
		nResult = fscanf(pFile, "%f", &m_pos.z);	// z���W��ǂݍ���

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "ROT") == 0)
	{// ����
		nResult = fscanf(pFile, "%s", aData);		// =��ǂݍ���
		nResult = fscanf(pFile, "%f", &m_rot.x);	// x����ǂݍ���
		nResult = fscanf(pFile, "%f", &m_rot.y);	// y����ǂݍ���
		nResult = fscanf(pFile, "%f", &m_rot.z);	// z����ǂݍ���

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
	else if (strcmp(pStr, "END_PARTSSET") == 0)
	{// �I���
		// �p�[�c�Z�b�g�C���f�b�N�X���擾
		int nIdx = pLoadMotionFile->GetIdxLoadPartsSet();

		// �p�[�c�C���f�b�N�X�J�E���g�A�b�v
		nIdx++;

		// �p�[�c�Z�b�g�C���f�b�N�X��ݒ�
		pLoadMotionFile->SetIdxLoadPartsSet(nIdx);

		//	�L�����N�^�[���ǂݎ��^�C�v�ɕύX
		pLoadMotionFile->SetType(CLoadMotionFile::TYPE_CHARCTERSET);

		// ���������ɂ���
		pLoadMotionFile->ClearStr();

		// ������C���f�b�N�X�����Z�b�g
		pLoadMotionFile->ResetIdxStr();
	}
}