#include "motion.h"

// �O���[�o���ϐ��錾
SET_MOTION_MANAGER g_SetMotiMane;	// ���[�V�����J�E���g���

//************************************************
// ���[�V�����̏�����
//************************************************
void InitMotion(void)
{
	g_SetMotiMane.nCntMotionInfo = 0;
	g_SetMotiMane.nCntKeyInfo = 0;
	g_SetMotiMane.nCntKey = 0;
}

//************************************************
// ���[�V�����e�L�X�g�̓ǂݍ���	SCRIPT
//************************************************
void ReadMotionText(const char* pFileName, Model* pModel, MOTION* motion, CHARPARAM* charParam)
{
	char astrA[256] = {};		// ������i�[�p�ϐ�
	char astrB[256] = {};	// �Â��i�[�p�ϐ�
	char* aResult = 0;
	int nResult = 0;
	int nCnt = 0;
	// �t�@�C�����J��
	FILE* pFile = fopen(pFileName, "r");

	if (pFile == NULL)
	{
		return;
	}

	while (1)
	{	
		// �ꕶ���ǂݎ��
		aResult = fgets(&astrA[0],2, pFile);
		
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
		else if (strcmp(&astrB[0], "SCRIPT") == 0)
		{// SCRIPT�ǂݎ��
			ReadScript(pFile,pModel,motion,charParam);	// �X�N���v�g�̓ǂݍ��݂Ɉȍ~
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

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// �X�N���v�g�̓ǂݎ��
//************************************************
void ReadScript(FILE* pFile, Model* pModel, MOTION* motion, CHARPARAM* charParam)
{
	char astrA[256] = {};		// ������i�[�p�ϐ�
	char astrB[256] = {};	// �Â��i�[�p�ϐ�
	char *aResult = 0;
	int nResult = 0;
	int nCnt = 0;
	int nCntModel = 0;

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
		else if (strcmp(&astrB[0], "NUM_MODEL") == 0)
		{// ���f�����̓ǂݍ���
			fgets(&astrA[0],3,pFile);								// =�ǂݍ���
			nResult = fscanf(pFile, "%d", &charParam->nNumModel);	// ���f�����ɑ��
			StringClear(&astrB[0], 256);							// �ۑ��p������̃N���A
			nCnt = 0;												// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "MODEL_FILENAME") == 0)
		{// MODEL_FILENAME�ǂݎ��
			fgets(&astrA[0], 3, pFile);					// =�ǂݍ���
			nResult = fscanf(pFile, "%s", &astrA[0]);	// �t�@�C���p�X�ǂݍ���
			SetModel(&astrA[0],pModel,nCntModel);		// X�t�B���̃p�X�̓ǂݍ���
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
			nCntModel++;								// ���f���J�E���g��i�߂�
		}
		else if (strcmp(&astrB[0], "CHARACTERSET") == 0)
		{// CHARACTERSET�ǂݎ��
			ReadCharacterSet(pFile, pModel, motion, charParam);
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "MOTIONSET") == 0)
		{// MOTIONSET�ǂݎ��
			MostionSet(pFile, motion);		// ���[�V�����Z�b�g�ֈȍ~
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "END_SCRIPT") == 0)
		{// END_SCRIPT�ǂݎ��
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

	// �J�E���g���Ă���ϐ���������
	g_SetMotiMane.nCntMotionInfo = 0;
	g_SetMotiMane.nCntKeyInfo = 0;
	g_SetMotiMane.nCntKey = 0;
}

//************************************************
// �L�����N�^�[�Z�b�g�̓ǂݍ���
//************************************************
void ReadCharacterSet(FILE* pFile, Model* pModel, MOTION* motion, CHARPARAM* charParam)
{
	char astrA[256] = {};	// ������i�[�p�ϐ�
	char astrB[256] = {};	// �Â��i�[�p�ϐ�
	char* aResult = 0;
	int nResult = 0;
	int nCnt = 0;

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
		else if (strcmp(&astrB[0], "NUM_PARTS") == 0)
		{// �p�[�c���̓ǂݍ���
			fgets(&astrA[0], 3, pFile);					// =�ǂݍ���
			nResult = fscanf(pFile, "%d", &charParam->nNumModel);	// ���f�����ɑ��
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "RADIUS") == 0)
		{// ���f�����̓ǂݍ���
			fgets(&astrA[0], 3, pFile);							// =�ǂݍ���
			nResult = fscanf(pFile, "%f", &charParam->fWidth);	// ���f�����ɑ��
			StringClear(&astrB[0], 256);						// �ۑ��p������̃N���A
			nCnt = 0;											// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "HEIGHT") == 0)
		{// ���f�����̓ǂݍ���
			fgets(&astrA[0], 3, pFile);							// =�ǂݍ���
			nResult = fscanf(pFile, "%f", &charParam->fHeigt);	// ���f�����ɑ��
			StringClear(&astrB[0], 256);						// �ۑ��p������̃N���A
			nCnt = 0;											// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "PARTSSET") == 0)
		{// �p�[�c��ݒ�
			PartsSet(pFile,pModel);
			StringClear(&astrB[0], 256);	// �ۑ��p������̃N���A
			nCnt = 0;						// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "END_CHARACTERSET") == 0)
		{// �p�[�c��ݒ�
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

//************************************************
// ���[�V�����Z�b�g
//************************************************
void MostionSet(FILE* pFile, MOTION* motion)
{
	char astrA[256] = {};	// ������i�[�p�ϐ�
	char astrB[256] = {};	// �Â��i�[�p�ϐ�
	char* aResult = 0;
	int nResult = 0;
	int nCnt = 0;

	MOTION_INFO setMotInfo;
	setMotInfo.bLoop = false;
	setMotInfo.nNumKey = 0;

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
		else if (strcmp(&astrB[0], "LOOP") == 0)
		{// ���[�v���̓ǂݍ���
			int nFlag = 0;
			fgets(&astrA[0], 3, pFile);					// =�ǂݍ���
			nResult = fscanf(pFile, "%d", &nFlag);		// ���f�����ɑ��

			if (nFlag > 0)
			{// �[�����ゾ������g�D���[
				setMotInfo.bLoop = true;
			}

			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "NUM_KEY") == 0)
		{// �L�[�����̓ǂݍ���
			fgets(&astrA[0], 3, pFile);					// =�ǂݍ���
			nResult = fscanf(pFile, "%d", &setMotInfo.nNumKey);		// ���f�����ɑ��
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;
		}
		else if (strcmp(&astrB[0], "KEYSET") == 0)
		{// �L�[�Z�b�g�̓ǂݍ���
			KeySet(pFile, motion);	// �L�[�Z�b�g�J�n
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;
		}
		else if (strcmp(&astrB[0], "END_MOTIONSET") == 0)
		{// ���[�V�����Z�b�g�I���
			MostionSet(motion,setMotInfo);	// �擾��������S���Ԃ�����
			g_SetMotiMane.nCntMotionInfo++;	// �L�[�Z�b�g�ԍ��ǉ�

			g_SetMotiMane.nCntKeyInfo = 0;	// �L�[���J�E���g���Z�b�g
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

//************************************************
// ���[�V�����I���[
//************************************************
void MostionSet(MOTION* motion, MOTION_INFO setMotInfo)
{
	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].bLoop = setMotInfo.bLoop;
	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].nNumKey = setMotInfo.nNumKey;
}

//************************************************
// �L�[�Z�b�g�̐ݒ�
//************************************************
void KeySet(FILE* pFile, MOTION* motion)
{
	char astrA[256] = {};	// ������i�[�p�ϐ�
	char astrB[256] = {};	// �Â��i�[�p�ϐ�
	char* aResult = 0;
	int nResult = 0;
	int nCnt = 0;

	KEY_INFO keyInfo;
	keyInfo.nFrame = 1;

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
		else if (strcmp(&astrB[0], "FRAME") == 0)
		{// �t���[�����̓ǂݍ���
			fgets(&astrA[0], 3, pFile);					// =�ǂݍ���
			nResult = fscanf(pFile, "%d", &keyInfo.nFrame);	// ���f�����ɑ��
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "KEY") == 0)
		{// �L�[�̓ǂݍ���
			Key(pFile, motion);
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "END_KEYSET") == 0)
		{// �L�[�̓ǂݍ���
			EndKeySet(motion,keyInfo);		// �擾�����������ׂĂԂ�����
			g_SetMotiMane.nCntKeyInfo++;	// �L�[����i�߂�
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;

			g_SetMotiMane.nCntKey = 0;		// �L�[�J�E���g�����Z�b�g
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

//************************************************
// �L�[�Z�b�g�I���[
//************************************************
void EndKeySet(MOTION* motion, KEY_INFO keyInfo)
{
	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].nFrame = keyInfo.nFrame;
}

//************************************************
// �L�[��ݒ�
//************************************************
void Key(FILE* pFile, MOTION* motion)
{
	char astrA[256] = {};	// ������i�[�p�ϐ�
	char astrB[256] = {};	// �Â��i�[�p�ϐ�
	char* aResult = 0;
	int nResult = 0;
	int nCnt = 0;

	KEY key;
	key.fPosX = 0.0f;
	key.fPosY = 0.0f;
	key.fPosZ = 0.0f;
	key.fRotX = 0.0f;
	key.fRotY = 0.0f;
	key.fRotZ = 0.0f;

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
		else if (strcmp(&astrB[0], "POS") == 0)
		{// POS�̓ǂݍ���
			fgets(&astrA[0], 3, pFile);					// =�ǂݍ���
			nResult = fscanf(pFile, "%f", &key.fPosX);	// �ʒuX
			nResult = fscanf(pFile, "%f", &key.fPosY);	// �ʒuY
			nResult = fscanf(pFile, "%f", &key.fPosZ);	// �ʒuZ
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "ROT") == 0)
		{// ROT�̓ǂݍ���
			fgets(&astrA[0], 3, pFile);					// =�ǂݍ���
			nResult = fscanf(pFile, "%f", &key.fRotX);	// ����X
			nResult = fscanf(pFile, "%f", &key.fRotY);	// ����Y
			nResult = fscanf(pFile, "%f", &key.fRotZ);	// ����Z
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;									// �ۑ��p������̃J�E���g�[��
		}
		else if (strcmp(&astrB[0], "END_KEY") == 0)
		{// �L�[�ǂݍ��݂��[���
			EndKey(motion,key);			// �擾�����������ׂĂԂ�����
			g_SetMotiMane.nCntKey++;	// �L�[�Z�b�g�Ԗڒǉ�
			StringClear(&astrB[0], 256);				// �ۑ��p������̃N���A
			nCnt = 0;
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

//************************************************
// �L�[�̏I���[
//************************************************
void EndKey(MOTION* motion, KEY key)
{
	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fPosX = key.fPosX;
	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fPosY = key.fPosY;
	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fPosZ = key.fPosZ;

	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fRotX = key.fRotX;
	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fRotY = key.fRotY;
	motion->aMotionInfo[g_SetMotiMane.nCntMotionInfo].aKeyinfo[g_SetMotiMane.nCntKeyInfo].aKey[g_SetMotiMane.nCntKey].fRotZ = key.fRotZ;
}

//************************************************
// ������̃N���A
//************************************************
void StringClear(char* astr,int nMaxCunt)
{
	for (int nCntB = 0; nCntB < nMaxCunt; nCntB++)
	{// �ۑ����Ă��镶��������ׂăN���A
		if (astr[nCntB] == '\0')
		{
			break;
		}

		astr[nCntB] = '\0';
	}
}

//************************************************
// �R�����g
//************************************************
void ReadComment(FILE *pFile,char*aResult)
{
	char astr[2];

	while (1)
	{
		// �ꕶ�����ǂ�
		fgets(&astr[0], 2, pFile);

		if (*aResult = strcmp(&astr[0], "\n") == 0)
		{// ���s�����ǂ񂾂�
			break;
		}

		if (*aResult == EOF)
		{// �e�L�X�g�t�@�C���S���ǂݐ؂��������
			break;
		}
	}
}

//************************************************
// ���[�V�����̍X�V
//************************************************
bool UpdateMotion(MOTION* motion,Model* model, int nType, int nNumModel)
{
	bool bMotionEnd = false;

	if (motion->nNowMotiType != nType)
	{// �Ⴄ���[�V�����ɐ؂�ւ���Ă�����
		motion->nNowMotiType = nType;							// �^�C�v��ς���
		motion->nCounterMotion = 0;								// �t���[���J�E���^�[���[��
		motion->nNumKey = motion->aMotionInfo[nType].nNumKey;	// �L�[�̍ő吔����
		motion->nKey = 0;										// �������Ă���L�[��������
		bMotionEnd = true;										// ���[�V�����͏I��������Ƃɂ���

		if (motion->aMotionInfo[nType].nNumKey > 1)
		{// ��L�[�ȏ゠��Ȃ�
			motion->nNextKey = motion->nKey + 1;
		}
		else
		{// �Ȃ��Ȃ��
			motion->nNextKey = motion->nKey;
		}
	}

	motion->nCounterMotion++;	// �t���[�����J�E���g

	if (motion->nNextKey < motion->nNumKey)
	{// ���[�V�����̑S�̃L�[���l���Ⴂ�ꍇ
		// �S���f���p�[�c�̍X�V
		for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++, model++)
		{
			KEY diffKeyPos;
			KEY Hope;

			diffKeyPos.fPosX = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fPosX - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fPosX);
			diffKeyPos.fPosY = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fPosY - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fPosY);
			diffKeyPos.fPosZ = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fPosZ - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fPosZ);

			diffKeyPos.fRotX = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fRotX - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotX);
			diffKeyPos.fRotY = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fRotY - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotY);
			diffKeyPos.fRotZ = (motion->aMotionInfo[nType].aKeyinfo[motion->nNextKey].aKey[nCntModel].fRotZ - motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotZ);

			Hope.fPosX = diffKeyPos.fPosX / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame;
			Hope.fPosY = diffKeyPos.fPosY / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame;
			Hope.fPosZ = diffKeyPos.fPosZ / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame;

			Hope.fRotX = motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotX + diffKeyPos.fRotX * ((float)motion->nCounterMotion / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame);
			Hope.fRotY = motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotY + diffKeyPos.fRotY * ((float)motion->nCounterMotion / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame);
			Hope.fRotZ = motion->aMotionInfo[nType].aKeyinfo[motion->nKey].aKey[nCntModel].fRotZ + diffKeyPos.fRotZ * ((float)motion->nCounterMotion / (float)motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame);

			model->pos = model->offSet + D3DXVECTOR3(Hope.fPosX, Hope.fPosY, Hope.fPosZ);
			model->rot = D3DXVECTOR3(Hope.fRotX, Hope.fRotY, Hope.fRotZ);

			if (model->nIdxModelParent == -1)
			{// �v���C���[�̃|�X�����т��Ă���������
				model->rot.y += D3DX_PI;
			}
		}


		if (motion->nCounterMotion >= motion->aMotionInfo[nType].aKeyinfo[motion->nKey].nFrame)
		{// �t���[���S�������I�������
			motion->nCounterMotion = 0;	// �t���[�����J�E���g�[��

			if (motion->nNextKey - motion->nKey > 0)
			{// ���[�v�̊Ԃ̃L�[����Ȃ�
				motion->nNextKey++;	// ���̃L�[�փJ�E���g
				motion->nKey++;		// ���̃L�[�փJ�E���g
				bMotionEnd = true;	// ���[�V�����I�������

				if (motion->nKey >= motion->aMotionInfo[nType].nNumKey - 1)
				{// �L�[�̑����ȏ�ɂȂ�����
					if (motion->aMotionInfo[nType].bLoop)
					{// ���[�v����̂�������
						motion->nNextKey = 0;	// ���̃L�[���ŏ��̃L�[�ɂ���
					}
					else
					{
						motion->nNextKey = motion->nNumKey;	// �v�Z�̏������ɓ���Ȃ��悤�ɂ���
					}
				}
			}
			else
			{// ���[�v�̊Ԃ̒l��������
				motion->nKey = 0;				// �L�[�O
				motion->nNextKey = motion->nKey + 1;	// ���̃L�[�̒l�ɐݒ�
			}
		}
	}

	return bMotionEnd;
}