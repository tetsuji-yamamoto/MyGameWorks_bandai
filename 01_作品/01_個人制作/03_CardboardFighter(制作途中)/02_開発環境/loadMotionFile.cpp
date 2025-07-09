//********************************************
// 
// �t�@�C���Ǎ�
// Author Tetsuji Yamamoto
// 
//********************************************
#include "loadMotionFile.h"

//********************************************
// �t�@�C���Ǎ��R���X�g���N�^
//********************************************
CLoadMotionFile::CLoadMotionFile()
{
	memset(m_aStr, NULL, sizeof(m_aStr));	// ������
	m_pFile = NULL;							// �t�@�C���|�C���^�[
	m_type = CLoadMotionFile::TYPE_SCRIPT;	// �ǂݎ��^�C�v
	m_bComment = false;						// �R�����g�̗L��
	m_nIdxStr = 0;							// ������C���f�b�N�X
	m_nIdxFileName = 0;						// �t�@�C�����C���f�b�N�X
	m_nResult = 0;							// �ǂݎ�茋�ʗp
	m_nModelNum = 0;						// ���f���̐�
	m_nNumMotion = 0;						// ���[�V������
	m_nIdxMotionset = 0;					// ���[�V�����Z�b�g�C���f�b�N�X
	m_nIdxKey = 0;							// �L�[�̃C���f�b�N�X
	m_nIdxKeySet = 0;						// �L�[�Z�b�g�̃C���f�b�N�X
}

//********************************************
// �t�@�C���Ǎ��f�X�g���N�^
//********************************************
CLoadMotionFile::~CLoadMotionFile()
{
}

//********************************************
// �t�@�C���Ǎ��I������
//********************************************
void CLoadMotionFile::Uninit()
{
	// �L�����N�^�[���j��
	if (m_pLoadCharacterSet != NULL)
	{
		m_pLoadCharacterSet->Uninit();
		m_pLoadCharacterSet = NULL;
	}

	// �p�[�c�Z�b�g�Ǎ����j��
	for (auto& iter : m_pLoadPartsSet)
	{
		iter->Uninit();
	}
	m_pLoadPartsSet.clear();
	
	// �t�@�C�������j��
	for (auto& iter : m_pXFileName)
	{
		iter->Uninit();
	}
	m_pXFileName.clear();


	// ���[�V�����Z�b�g�̔j��
	for (auto& iter : m_apLoadMotionSet)
	{	
		iter->Uninit();
	}
	m_apLoadMotionSet.clear();

	// �������g��j��
	delete this;
}

//********************************************
// �t�@�C���Ǎ�
//********************************************
void CLoadMotionFile::Load(const char* pFileName)
{
	// ��������������
	Reset();

	// �ǂݎ��p�Ƃ��ăt�@�C�����J��
	m_pFile = fopen(pFileName, "r");

	// �t�@�C�����J������
	if (m_pFile != NULL)
	{
		while (1)
		{// ���[�v

			// �ꕶ���ǂݎ��
			char cData = fgetc(m_pFile);

			if (cData == '#')
			{// �R�����g������ǂ񂾂炻�̂��Ƃ̕����͓ǂݔ�΂�
				m_bComment = true;	// �R�����g�L�̏�Ԃɂ���
				ClearStr();			// ���������ɂ���
				m_nIdxStr = 0;
				continue;			// while����
			}
			else if (cData == '\n')
			{// ���s��񂾂�
				m_bComment = false;	// �R�����g���̏�Ԃɂ���
				ClearStr();			// ���������ɂ���
				m_nIdxStr = 0;		// �C���f�b�N�X���Z�b�g
				continue;			// while����
			}
			else if (cData == '\t')
			{// �^�u������񂾂�
				continue;	// while����
			}
			else if (cData == EOF)
			{// �^�u������񂾂�
				break;	// while���甲���o��
			}


			if (m_bComment == true)
			{// �R�����g�@�\���I��
				continue;	// while����
			}

			m_aStr[m_nIdxStr] = cData;	// �ꕶ�����
			m_nIdxStr++;				// �C���f�b�N�X�J�E���g�A�b�v

			switch (m_type)
			{
				// �X�N���v�g
			case TYPE_SCRIPT:
				if (strcmp(m_aStr, "NUM_MODEL") == 0)
				{// ���f����
					char aData[4] = {};

					// =��ǂݍ���
					m_nResult = fscanf(m_pFile, "%s", &aData[0]);		
					
					// ���l��ǂݍ���
					m_nResult = fscanf(m_pFile, "%d", &m_nModelNum);	

					// ���������ɂ���
					ClearStr();

					// ������C���f�b�N�X�����Z�b�g
					m_nIdxStr = 0;

					// while����
					continue;
				}
				else if (strcmp(m_aStr, "MODEL_FILENAME") == 0)
				{// x�t�@�C����
					// = ��ǂݎ�邽�߂̕ϐ�
					char aData[4] = {};

					// =��ǂݍ���
					m_nResult = fscanf(m_pFile, "%s", aData);

					// �t�@�C�������C���X�^���X�����A�m��
					CFileName* pXFileName = new CFileName;

					// �t�@�C������ǂݍ���
					m_nResult = fscanf(m_pFile, "%s", pXFileName->GetFileName());

					// �t�@�C�����𖖔��ɒǉ�	
					m_pXFileName.push_back(pXFileName);

					// �t�@�C�����C���f�b�N�X�J�E���g�A�b�v
					m_nIdxFileName++;

					// ���������ɂ���
					ClearStr();

					// ������C���f�b�N�X�����Z�b�g
					m_nIdxStr = 0;

					// while����
					continue;
				}
				else if (strcmp(m_aStr, "CHARACTERSET") == 0)
				{// �L�����N�^�[���
					SetType(TYPE_CHARCTERSET);

					// �L�����N�^�[�Z�b�g�C���X�^���X�����A�m��
					m_pLoadCharacterSet = new CCharacterSet;

					// ���������ɂ���
					ClearStr();	

					// ������C���f�b�N�X�����Z�b�g
					m_nIdxStr = 0;
				}
				else if (strcmp(m_aStr, "MOTIONSET") == 0)
				{// ���[�V�����Z�b�g
					// ���������m��
					CLoadMotionSet* pLoadMotionSet = new CLoadMotionSet;
					
					// �v�f��ǉ�
					m_apLoadMotionSet.push_back(pLoadMotionSet);

					// ���[�V�������J�E���g�A�b�v
					m_nNumMotion++;

					// ���[�V�����Z�b�g�^�C�v�ɕύX
					SetType(TYPE_MOTIONSET);

					// ���������ɂ���
					ClearStr();

					// ������C���f�b�N�X�����Z�b�g
					m_nIdxStr = 0;
				}
				break;

					// �L�����N�^�[�Z�b�g
			case TYPE_CHARCTERSET:
				if (m_pLoadCharacterSet != NULL)
				{// �k���Ŗ������
					// �L�����N�^�[���ǂݎ��
					m_pLoadCharacterSet->Load();
				}
				break;

				//	�p�[�c�Z�b�g
			case TYPE_PARTSSET:
				// NULL�Ŗ������
				if (m_pLoadPartsSet.size() > 0)
				{
					auto iter = m_pLoadPartsSet.end() - 1;
					(*iter)->Load();
				}
				break;

			case TYPE_MOTIONSET:
				// NULL�Ŗ������
				if (m_apLoadMotionSet.size() > 0)
				{
					auto iter = m_apLoadMotionSet.end() - 1;
					(*iter)->Load();
				}
				break;

			case TYPE_KEYSET:
				// �v�f�������
				if (m_apLoadMotionSet.capacity() > 0)
				{
					auto iterLoadMotinSet = m_apLoadMotionSet.end() - 1;
					auto iterLoadKeyset = (*iterLoadMotinSet)->GetLoadKeySetElementEnd();
					(*iterLoadKeyset)->Load();
				}
				break;

			case TYPE_KEY:
				// NULL�Ŗ������
				if (m_apLoadMotionSet.capacity() > 0)
				{
					auto iterLoadMotinSet = m_apLoadMotionSet.end() - 1;
					auto iterLoadKeyset = (*iterLoadMotinSet)->GetLoadKeySetElementEnd();
					auto iterLoadKey = (*iterLoadKeyset)->GetLoadKeyElementEnd();
					(*iterLoadKey)->Load();
				}
				break;
			}
		}

		// �t�@�C�������
		fclose(m_pFile);
	}
	// �t�@�C�����J���Ȃ�����
	else
	{
		MessageBox(NULL, "CLoadMotionFile::Load() > if (pFile != NULL) �t�@�C�����J���܂���ł���", "Error", MB_OK);
		return;
	}
}

//*******************************************************
// �t�@�C���Ǎ��ǂݍ��񂾃��f���̏���n������
//*******************************************************
void CLoadMotionFile::CopyModel(std::vector<CModel*>* ppVectorModel)
{
	// ���f���J�E���^�[
	int nCntModel = 0;

	// �ǂݎ�����p�[�c�Z�b�g�̗v�f����
	for (auto iter = m_pLoadPartsSet.begin(); iter != m_pLoadPartsSet.end();iter++, nCntModel++)
	{
		// ���f���̃������m��
		CModel* pModel = new CModel;

		// x�t�@�C�����̏��(�C�e���[�^�[)���擾
		auto iterXFileName = m_pXFileName.begin() + nCntModel;

		// ���f���̏�����
		D3DXVECTOR3 pos = (*iter)->GetPosition();
		D3DXVECTOR3 rot = (*iter)->GetRotation();
		char* pXFilename = (*iterXFileName)->GetFileName();
		pModel->Init(pos, rot, pXFilename);

		// �v�f�ǉ�
		ppVectorModel->push_back(pModel);
	}

	// ���f���J�E���g���Z�b�g
	nCntModel = 0;

	// �e���f���̐ݒ�
	for (auto iter = ppVectorModel->begin(); iter != ppVectorModel->end(); iter++, nCntModel++)
	{
		auto iterPartsSet = m_pLoadPartsSet.begin() + nCntModel;
		int nIdx = (*iterPartsSet)->GetIndexParrent();

		// �e������̂ł���ΐݒ肷��
		if (nIdx >= 0)
		{
			(*iter)->SetParent(*(ppVectorModel->begin() + nIdx));
		}
	}
}

//*******************************************************
// �t�@�C���Ǎ��ǂݍ��񂾃��[�V�����̏���n������
//*******************************************************
void CLoadMotionFile::CopyMotion(CMotion** ppMotion)
{
	// �L�����N�^�[���擾
	CCharacterSet* pCharacterSet = this->GetCharacterSet();

	// �k���ł���΃��������m�ۂ���
	if (*ppMotion == NULL)
	{
		*ppMotion = new CMotion;
	}

	// ���[�V�������ݒ�
	ppMotion[0]->SetNumMotion(m_nNumMotion);

	// �ǂݎ�������[�V�����̐����ݒ肷��
	for (auto iterLoadtMotinSet = m_apLoadMotionSet.begin(); iterLoadtMotinSet != m_apLoadMotionSet.end();iterLoadtMotinSet++)
	{
		// ���[�V�����̃C���X�^���X�����A�m��
		CMotionInfo* pMyMotionInfo = new CMotionInfo;

		// ���[�V�����C���t�H�̖����ɗv�f��ǉ�
		ppMotion[0]->SetPushBackMotionInfo(&pMyMotionInfo);

		// ���[�v�̗L���ƃL�[���̎擾
		bool bLoop = (*iterLoadtMotinSet)->GetLoop();
		int nNumkey = (*iterLoadtMotinSet)->GetNumKey();

		// ���[�v�̗L���ƃL�[���̐ݒ�
		pMyMotionInfo->SetLoop(bLoop);
		pMyMotionInfo->SetNumKey(nNumkey);

		// �ǂݎ�����L�[�̐�����
		for (auto iterLoadKeyset = (*iterLoadtMotinSet)->GetLoadKeySetBegin(); iterLoadKeyset != (*iterLoadtMotinSet)->GetLoadKeySetEnd(); iterLoadKeyset++)
		{
			// �L�[�C���t�H�̃C���X�^���X����
			CKeyInfo* pMyKeyInfo = new CKeyInfo;;

			// ���[�V�������̖����ɃL�[�C���t�H�̗v�f��ǉ�
			pMyMotionInfo->SetPushBackKeyInfo(&pMyKeyInfo);

			// �L�[�̃t���[�����擾
			int nFlame = (*iterLoadKeyset)->GetFlame();

			// �t���[�����ݒ�
 			pMyKeyInfo->SetFrame(nFlame);

			// �L�[(���f��)�̐�����
			for (auto iterKeySet = (*iterLoadKeyset)->GetLoadKeyBegin(); iterKeySet != (*iterLoadKeyset)->GetLoadKeyEnd(); iterKeySet++)
			{
				// �L�[�̃C���X�^���X�����A�m��
				CKey* pMyKey = new CKey;

				// �L�[�C���t�H�̖����ɃL�[�̗v�f�ǉ�
				pMyKeyInfo->SetPushBackKey(&pMyKey);

				// �����n���p�ϐ�
				D3DXVECTOR3 pos, rot;

				// �ǂݎ�����ʒu�ƌ������擾
				pos = (*iterKeySet)->GetPosition();
				rot = (*iterKeySet)->GetRotation();

				// ���g�̃L�[�ɓǂݎ�����ʒu�ƌ�����ݒ�
				pMyKey->SetPositionX(pos.x);
				pMyKey->SetPositionY(pos.y);
				pMyKey->SetPositionZ(pos.z);
				pMyKey->SetRotationX(rot.x);
				pMyKey->SetRotationY(rot.y);
				pMyKey->SetRotationZ(rot.z);
			}
		}
	}
}

//********************************************
// �t�@�C���Ǎ���������
//********************************************
CLoadMotionFile* CLoadMotionFile::Create(void)
{
	CLoadMotionFile* pLoadMotionFile = NULL;

	// �I�u�W�F�N�g2D�̐���
	if (pLoadMotionFile == NULL)
	{

		pLoadMotionFile = new CLoadMotionFile;
		if (pLoadMotionFile == NULL)
		{
			MessageBox(NULL, " CLoadMotionFile::Create() > if ( pBullet != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}

	return  pLoadMotionFile;
}
 
//********************************************
// �t�@�C���Ǎ��������������鏈��
//********************************************
void CLoadMotionFile::Reset(void)
{
	// �p�[�c�Z�b�g�Ǎ����j��
	for (auto& iter : m_pLoadPartsSet)
	{
		iter->Uninit();
	}
	m_pLoadPartsSet.clear();

	// �t�@�C�������j��
	for (auto& iter : m_pXFileName)
	{
		iter->Uninit();
	}
	m_pXFileName.clear();

	// �L�����N�^�[���j��
	m_pLoadCharacterSet->Uninit();

	// ���[�V�����Z�b�g�̔j��
	for (auto& iter : m_apLoadMotionSet)
	{
		iter->Uninit();
	}
	m_apLoadMotionSet.clear();

	memset(m_aStr, NULL, sizeof(m_aStr));	// ������
	m_pFile = NULL;							// �t�@�C���|�C���^�[
	m_type = CLoadMotionFile::TYPE_SCRIPT;	// �ǂݎ��^�C�v
	m_bComment = false;						// �R�����g�̗L��
	m_nIdxStr = 0;							// ������C���f�b�N�X
	m_nIdxFileName = 0;						// �t�@�C�����C���f�b�N�X
	m_nResult = 0;							// �ǂݎ�茋�ʗp
	m_nModelNum = 0;						// ���f���̐�
	m_nNumMotion = 0;						// ���[�V������
	m_nIdxMotionset = 0;					// ���[�V�����Z�b�g�C���f�b�N�X
	m_nIdxKey = 0;							// �L�[�̃C���f�b�N�X
	m_nIdxKeySet = 0;						// �L�[�Z�b�g�̃C���f�b�N�X
}