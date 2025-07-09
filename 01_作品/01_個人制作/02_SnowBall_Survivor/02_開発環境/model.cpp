#include "model.h"
#include "motion.h"

// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureModel[6] = {};	// �e�N�X�`���ւ̃|���^


//********************************************
//���f���̏�����
//********************************************
void InitModel(void)
{

}

//********************************************
// ���f���̏I������
//********************************************
void UninitModel(void)
{

}

//********************************************
// ���f���̍X�V
//********************************************
void UpdateModel(void)
{

}

//********************************************
// ���f���̕`��
//********************************************
void DrawModel(void)
{
	
}

//********************************************
// ���f���̐ݒ�
//********************************************
void SetModel(char astr[], Model* pModel, int nModelNum)
{
	const char* pFileName = astr;

	pModel += nModelNum;	// ���f�����i�߂�

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	HRESULT hresult;
	hresult = D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&pModel->pBuffMat,
		NULL,
		&pModel->dwNumMat,
		&pModel->pMesh);

	if (FAILED(hresult))
	{// ���s�����I
		return;
	}

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pModel->dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// �e�N�X�`���t�@�C�������݂���

			// ���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&pModel->apTexture[nCntMat]);
		}
	}
}

//********************************************
// �p�[�c�̐ݒ�
//********************************************
void PartsSet(FILE *pFile,Model* model)
{
	char astrA[256] = {};	// ������i�[�p�ϐ�
	char astrB[256] = {};	// �Â��i�[�p�ϐ�
	char* aResult = 0;
	int nResult = 0;
	int nCnt = 0;
	int nNumParts = 0;// �p�[�c��

	Model SetModel;
	SetModel.nIdxModelParent = -1;// �e
	int nIndex = 0;
	SetModel.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetModel.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	while (1)
	{
		// �ꕶ���ǂݎ��
		aResult = fgets(&astrA[0], 2, pFile);

		// �ꕶ�������
		astrB[nCnt] = astrA[0];

		// �J�E���g��i�߂�,�����������[��
		nCnt = (nCnt + 1) % 256;

		if (strcmp(&astrA[0], "#") == 0)
		{// �R�����g������ǂ񂾂炻�̂��Ƃ̕����͓ǂݔ�΂�
			ReadComment(pFile, aResult);	// �R�����g��ǂݔ�΂�
			StringClear(&astrB[0], 256);	// �ۑ��p������̃N���A
			nCnt = 0;						// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrA[0], "\n") == 0)
		{// ���s��񂾂�

			StringClear(&astrB[0], 256);	// �ۑ��p������̃N���A
			nCnt = 0;						// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrA[0], "\t") == 0)
		{// ���s��񂾂�

			StringClear(&astrB[0], 256);	// �ۑ��p������̃N���A
			nCnt = 0;						// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "INDEX") == 0)
		{// �C���f�b�N�X�ǂݍ���
			nResult = fscanf(pFile,"%s",&astrA[0]);		// =�ǂݍ���
			nResult = fscanf(pFile, "%d", &nIndex);		// �l�ǂݍ���
			StringClear(&astrB[0], 256);	// �ۑ��p������̃N���A
			nCnt = 0;						// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "PARENT") == 0)
		{// �e�ǂݍ���
			nResult = fscanf(pFile, "%s", &astrA[0]);					// =�ǂݍ���
			nResult = fscanf(pFile, "%d", &SetModel.nIdxModelParent);	// �l�ǂݍ���
			StringClear(&astrB[0], 256);	// �ۑ��p������̃N���A
			nCnt = 0;						// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "POS") == 0)
		{// �ʒu�ǂݍ���
			nResult = fscanf(pFile, "%s", &astrA[0]);		// =�ǂݍ���
			nResult = fscanf(pFile, "%f", &SetModel.pos.x);	// �l�ǂݍ���X
			nResult = fscanf(pFile, "%f", &SetModel.pos.y);	// �l�ǂݍ���Y
			nResult = fscanf(pFile, "%f", &SetModel.pos.z);	// �l�ǂݍ���Z
			StringClear(&astrB[0], 256);	// �ۑ��p������̃N���A
			nCnt = 0;						// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "ROT") == 0)
		{// �p�x�ǂݍ���
			nResult = fscanf(pFile, "%s", &astrA[0]);		// =�ǂݍ���
			nResult = fscanf(pFile, "%f", &SetModel.rot.x);	// �l�ǂݍ���X
			nResult = fscanf(pFile, "%f", &SetModel.rot.y);	// �l�ǂݍ���Y
			nResult = fscanf(pFile, "%f", &SetModel.rot.z);	// �l�ǂݍ���Z
			StringClear(&astrB[0], 256);	// �ۑ��p������̃N���A
			nCnt = 0;						// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "END_PARTSSET") == 0)
		{// �ǂݍ��񂾂��̂��Ԃ�����
			EndPartsSet(model,SetModel,nIndex);
			break;
		}

		if (aResult == NULL)
		{// �e�L�X�g�t�@�C���S���ǂݐ؂��������
			break;
		}
		else if (nResult == EOF)
		{// �e�L�X�g�t�@�C���S���ǂݐ؂��������
			break;
		}
	}
}

//********************************************
// �p�[�c�̐ݒ�
//********************************************
void EndPartsSet(Model* pModel, Model model, int nIndex)
{
	pModel += nIndex;	//�@�C���f�b�N�X���i�߂�

	pModel->nIdxModelParent = model.nIdxModelParent;	// �e���
	pModel->pos = model.pos;	// �ʒu���
	pModel->rot = model.rot;	// �p�x���

	pModel->offSet = model.pos;	// �I�t�Z�b�g���

}