#include "readtext.h"
#include "block.h"

//**************************************************
// �e�L�X�g�t�@�C���̓ǂݍ���
//**************************************************
void ReadText(void)
{
	// �t�@�C���ǂݍ��݃I�[�v��

	FILE* pFile;

	switch (GetMode())
	{
	case MODE_GAME:
		pFile = fopen("date\\text\\stage.txt", "r");
		break;

	case MODE_TUTORIAL:
		pFile = fopen("date\\text\\tutorialStage.txt", "r");
		break;

	default:
		pFile = fopen("date\\text\\stage.txt", "r");
		break;
	}

	 	char astr[256] = {};	// ��������i�[����ϐ�

	// �e�L�X�g��ǂݍ���
	while (1)
	{
		// �e�L�X�g��ǂ�Ō��ʂ���
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "STAGESET") == 0)
		{// �Z�b�g�X�e�[�W���s��
			SetStage(pFile);
		}

		// �ǂݐ؂�����I��
		if (result == EOF)
		{
			break;
		}
	}

	fclose(pFile);
}

//**************************************************
// �X�e�[�W�̓ǂݍ���
//**************************************************
void SetStage(FILE *pFile)
{
	BLOCKMANAGER* pBlMane = GetBlockManager();
	char astr[256] = {};	// ��������i�[����ϐ�

	// �e�L�X�g��ǂݍ���
	while (1)
	{

		// �e�L�X�g��ǂ�Ō��ʂ���
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "SETBLOCK") == 0)
		{// �u���b�N����ǂݍ���
			ReadBlockDate(pFile);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_SNOW") == 0)
		{// �u���b�N����ǂݍ���
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_SNOW][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_ICE") == 0)
		{// �u���b�N����ǂݍ���
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_ICE][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_GRAVEL") == 0)
		{// �u���b�N����ǂݍ���
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_GRAVEL][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_WALL") == 0)
		{// �u���b�N����ǂݍ���
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_WALL][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_WALL_ADULT") == 0)
		{// �u���b�N����ǂݍ���
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_WALL_ADULT][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_TERRITRY_POINT") == 0)
		{// �u���b�N����ǂݍ���
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_TERRITRY_POINT][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_UDD_SNOW") == 0)
		{// �u���b�N����ǂݍ���
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_UDD_SNOW][0]);
		}
		else if (strcmp(&astr[0], "ENDSTAGESET") == 0)
		{// �X�e�[�W�Z�b�g���I������
			break;
		}

		// �ǂݐ؂�����I��
		if (result == EOF)
		{
			break;
		}
	}
}

//**************************************************
// �u���b�N�̓ǂݍ���
//**************************************************
void ReadBlockDate(FILE* pFile)
{
	char astr[256] = {};	// ��������i�[����ϐ�
	char astrOld[256] = {};	// �Â���������i�[����ϐ�
	int result = 0;			// EOF����
	bool bComent = false;	// �ǂ܂Ȃ��Ă�������
	SETBLOCK seBlock;		// �u���b�N���

	// �u���b�N��񏉊���
	seBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock.nType = BLOCKTYPE_MAX;
//	seBlock.pFilename = NULL;

	// �e�L�X�g��ǂݍ���
	while (1)
	{
		// �e�L�X�g��ǂ�Ō��ʂ���
		result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "POS") == 0)
		{// �ʒu��ݒ肷��
			//���l��ǂނ���
			result = fscanf(pFile, "%f", &seBlock.pos.x);
			result = fscanf(pFile, "%f", &seBlock.pos.y);
			result = fscanf(pFile, "%f", &seBlock.pos.z);
		}
		else if (strcmp(&astr[0], "ROT") == 0)
		{// ������ݒ肷��
			result = fscanf(pFile, "%f", &seBlock.rot.x);
			result = fscanf(pFile, "%f", &seBlock.rot.y);
			result = fscanf(pFile, "%f", &seBlock.rot.z);
		}
		else if (strcmp(&astr[0], "BLOCKTYPE") == 0)
		{// �^�C�v��ݒ肷��
			result = fscanf(pFile, "%d", &seBlock.nType);
		}
		else if (strcmp(&astr[0], "BLOCKFILE") == 0)
		{// �^�C�v��ݒ肷��
			result = fscanf(pFile, "%s", &seBlock.astr[0]);
		}
		else if (strcmp(&astr[0], "ENDSETBLOCK") == 0)
		{// �u���b�N��ݒ肵�u���b�N���̓ǂݍ��݂��I������
			SetBlock(seBlock,true);
			break;
		}

		// �ǂݐ؂�����I��
		if (result == EOF)
		{
			break;
		}
	}
}
