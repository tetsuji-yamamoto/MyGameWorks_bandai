//******************************************
// 
// �X�e�[�W
// Author Tetsuji Yamamoto
// 
//******************************************
#include "stage.h"
#include "manager.h"
#include "input.h"

//******************************************
// �X�e�[�W�R���X�g���N�^
//******************************************
CStage::CStage()
{
	m_pSky = NULL;			// ��̃|�C���^�[
	m_pCylinderBG = NULL;	// �V�����_�[�|�C���^�[
	m_pMeshField = NULL;	// ���b�V���t�B�[���h�̃|�C���^�[
}

//******************************************
// �X�e�[�W�f�X�g���N�^
//******************************************
CStage::~CStage()
{
}

//******************************************
// �X�e�[�W������
//******************************************
HRESULT CStage::Init(const char* pFIleName)
{
	// ��
	m_pSky = CSky::Create(10, 10, 5000.0f);

	// �V�����_�[�w�i
	m_pCylinderBG = CCylinderBG::Create(D3DXVECTOR3_NULL, 100, 1, 3000.0f, 1000.0f);

	// �X�e�[�W��ǂݍ���
	Load(pFIleName);
	
	// �ǐ���
	CWall* pWallA = new CWall;
	CWall* pWallB = new CWall;
	CWall* pWallC = new CWall;
	CWall* pWallD = new CWall;
	pWallA = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -64.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), D3DXCOLOR_NULL, 2500.0f, 500.0f, 0.0f, NULL);
	pWallB = CWall::Create(D3DXVECTOR3(1130.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR_NULL, 500.0f, 500.0f, 0.0f, NULL);
	pWallC = CWall::Create(D3DXVECTOR3(-1100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR_NULL, 500.0f, 500.0f, 0.0f, NULL);
	pWallD = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -279.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f), D3DXCOLOR_NULL, 2500.0f, 500.0f, 0.0f, NULL);
	m_pWall.push_back(pWallA);
	m_pWall.push_back(pWallB);
	m_pWall.push_back(pWallC);
	m_pWall.push_back(pWallD);

	return S_OK;
}

//******************************************
// �X�e�[�W�I��
//******************************************
void CStage::Uninit(void)
{
	// ��̔j��
	if (m_pSky != NULL)
	{
		m_pSky = NULL;
	}

	// ���b�V���t�B�[���h�̔j��
	if (m_pMeshField != NULL)
	{
		m_pMeshField = NULL;
	}

	// �V�����_�[�̔j��
	if (m_pCylinderBG != NULL)
	{
		m_pCylinderBG = NULL;
	}

	// �ǂ̔j��
	if (m_pWall.capacity() > 0)
	{
		m_pWall.clear();
	}

	// �X�e�[�W�I�u�W�F�N�g�̔j��
	if (m_pObjStage.capacity() > 0)
	{
		for (auto& iter : m_pObjStage)
		{
			iter->Uninit();
		}
		m_pObjStage.clear();
	}

	// ���g�̔j��
	Release();
}

//******************************************
// �X�e�[�W�X�V
//******************************************
void CStage::Update(void)
{

}

//******************************************
// �X�e�[�W�`��
//******************************************
void CStage::Draw(void)
{
	// �X�e�[�W�I�u�W�F�N�g�̕`��
	for (auto& iter : m_pObjStage)
	{
		iter->Draw();
	}
}

//******************************************
// �X�e�[�W�Ǎ�
//******************************************
void CStage::Load(const char* pFileName)
{
	// �ǂݎ��p�Ƃ��ăt�@�C�����J��
	FILE* pFile = fopen(pFileName, "r");

	// �t�@�C�����J���Ȃ�����
	if (pFile == NULL)
	{
		MessageBox(NULL, "CStage::Load() > �t�@�C�����J���܂���ł���", "Error", MB_OK);
		return;
	}

	// �t�@�C�����J������
	char aStr[1024] = {};	// ������
	bool bComment = false;	// �R�����g�̗L��
	int nIdxStr = 0;		// ������C���f�b�N�X
	int nIdxFileName = 0;	// �t�@�C�����C���f�b�N�X
	char aData[4] = {};		// =�ǂݎ��p
	int nType = TYPE_MAX;	// �ǂݎ��^�C�v

	// �ǂݎ��p�ϐ�
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����
	char aFileName[128] = {};	// �t�@�C����

	while (1)
	{// ���[�v

		// �ꕶ���ǂݎ��
		char cData = fgetc(pFile);

		if (cData == '#')
		{// �R�����g������ǂ񂾂炻�̂��Ƃ̕����͓ǂݔ�΂�
			bComment = true;				// �R�����g�L�̏�Ԃɂ���
			memset(aStr, 0, sizeof(aStr));	// ���������ɂ���
			nIdxStr = 0;					// ������C���f�b�N�X���Z�b�g
			continue;						// while����
		}
		else if (cData == '\n')
		{// ���s��񂾂�
			bComment = false;				// �R�����g���̏�Ԃɂ���
			memset(aStr, 0, sizeof(aStr));	// ���������ɂ���
			nIdxStr = 0;					// ������C���f�b�N�X���Z�b�g
			continue;						// while����
		}
		else if (cData == '\t')
		{// �^�u������񂾂�
			continue;	// while����
		}
		else if (cData == EOF)
		{// �^�u������񂾂�
			break;	// while���甲���o��
		}

		if (bComment == true)
		{// �R�����g�@�\���I��
			continue;	// while����
		}

		aStr[nIdxStr] = cData;	// �ꕶ�����
		nIdxStr++;				// �C���f�b�N�X�J�E���g�A�b�v

		// ���f���Ǎ�
		if (strcmp(aStr, "MODEL_SET") == 0)
		{
			// �ǂݎ��^�C�v�����f���ɕύX
			nType = TYPE_MODEL;
		}
		// ���b�V���t�B�[���h�Ǎ�
		else if (strcmp(aStr, "MESHFIELD_SET") == 0)
		{
			// �ǂݎ��^�C�v�����f���ɕύX
			nType = TYPE_MESHFIELD;
		}

		// �^�C�v�ʂœǂݎ��
		switch (nType)
		{
			// ���f��
		case TYPE_MODEL:
			// �ʒu��ǂݍ���
			if (strcmp(aStr, "POS") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// ���l��ǂݍ���
				fscanf(pFile, "%f", &pos.x);
				fscanf(pFile, "%f", &pos.y);
				fscanf(pFile, "%f", &pos.z);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// ������ǂݍ���
			else if (strcmp(aStr, "ROT") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// ���l��ǂݍ���
				fscanf(pFile, "%f", &rot.x);
				fscanf(pFile, "%f", &rot.y);
				fscanf(pFile, "%f", &rot.z);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// �t�@�C������ǂݍ���
			else if (strcmp(aStr, "FILE_NAME") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �t�@�C������ǂݍ���
				fscanf(pFile, "%s", aFileName);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// ���f���𐶐�
			else if (strcmp(aStr, "MODEL_SET_END") == 0)
			{
				// ���f���̃C���X�^���X�����A������
				CObjectStage* pStage = new CObjectStage;
				pStage->Init(pos,rot, aFileName);

				// �v�f��ǉ�����
				m_pObjStage.push_back(pStage);

				// �^�C�v��߂�
				nType = TYPE_MAX;

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			break;

			// ���b�V���t�B�[���h
		case TYPE_MESHFIELD:
			// �t�@�C������ǂݍ���
			if (strcmp(aStr, "FILE_NAME") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l��ǂݍ���
				fscanf(pFile, "%s", aFileName);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// ���b�V���t�B�[���h�̐���
			if (strcmp(aStr, "MESHFIELD_SET_END") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// ���b�V���t�B�[���h�̃������m��
				m_pMeshField = new CMeshField;

				// ���b�V���t�B�[���h�̓Ǎ�����������
				m_pMeshField->Load(aFileName);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			break;
		}
	}

	// �t�@�C�������
	fclose(pFile);
}
