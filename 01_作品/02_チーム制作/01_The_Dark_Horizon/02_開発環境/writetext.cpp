#include "writetext.h"
#include "block.h"

//**************************************************
// �e�L�X�g�t�@�C���̏�������
//**************************************************
void WriteText(void)
{
	// �t�@�C���ǂݍ��݃I�[�v��
	FILE* pFile = fopen("date\\text\\writeStage.txt", "w");
	char astr[256] = {};	// ��������i�[����ϐ�

	// �X�e�[�W����������
	WriteStage(pFile);

	fclose(pFile);
}

//**************************************************
// �X�e�[�W�̏�������
//**************************************************FLENAME_BLOCK_SNOW date\xfile\block\Block_Snow_001.x
void WriteStage(FILE* pFile)
{
	BLOCKMANAGER* pBlockMane = GetBlockManager();	// �u���b�N�Ǘ����擾

	// ��������
	fprintf(pFile,"%s\n\n","STAGESET");

	fprintf(pFile, "%s %s\n", "FLENAME_BLOCK_SNOW", &pBlockMane->astr[BLOCKTYPE_SNOW][0]);
	fprintf(pFile, "%s %s\n", "FLENAME_BLOCK_ICE", &pBlockMane->astr[BLOCKTYPE_ICE][0]);
	fprintf(pFile, "%s %s\n", "FLENAME_BLOCK_GRAVEL", &pBlockMane->astr[BLOCKTYPE_GRAVEL][0]);
	fprintf(pFile, "%s %s\n", "FLENAME_BLOCK_WALL", &pBlockMane->astr[BLOCKTYPE_WALL][0]);
	fprintf(pFile, "%s %s\n", "FLENAME_BLOCK_WALL_ADULT", &pBlockMane->astr[BLOCKTYPE_WALL_ADULT][0]);
	fprintf(pFile, "%s %s\n", "FLENAME_BLOCK_TERRITRY_POINT", &pBlockMane->astr[BLOCKTYPE_TERRITRY_POINT][0]);
	fprintf(pFile, "%s %s\n\n", "FLENAME_BLOCK_UDD_SNOW", &pBlockMane->astr[BLOCKTYPE_UDD_SNOW][0]);

	WriteBlockDate(pFile);
	fprintf(pFile,"%s\n","ENDSTAGESET");

}

//**************************************************
// �u���b�N�̏�������
//**************************************************
void WriteBlockDate(FILE* pFile)
{
	BLOCK* pBlock = GetBlock();	// �u���b�N���擾
	BLOCKMANAGER* pBlockMane = GetBlockManager();	// �u���b�N�Ǘ����擾
	BLOCKCONTROLLER* pBlCont = GetBlockController();// �u���b�N�R���g���[���[�擾

	// �g���Ă���u���b�N���e�L�X�g��ǂݍ���
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++, pBlock++)
	{
		if (pBlock->bUse)
		{
			if (nCnt == pBlCont->nCntNowBlock)
			{// �G�f�B�b�g�̃u���b�N�͏����Ȃ�
				continue;
			}

			fprintf(pFile, "%s\n", "SETBLOCK");
			fprintf(pFile, "POS %0.1f% 0.1f% 0.1f\n", pBlock->pos.x, pBlock->pos.y, pBlock->pos.z);
			fprintf(pFile, "ROT %0.1f% 0.1f% 0.1f\n", pBlock->rot.x, pBlock->rot.y, pBlock->rot.z);
			fprintf(pFile, "BLOCKTYPE %d\n", pBlock->nType);

			switch (pBlock->nType)
			{
			case BLOCKTYPE_SNOW:
			fprintf(pFile, "BLOCKFILE %s\n", &pBlockMane->astr[BLOCKTYPE_SNOW][0]);
				break;

			case BLOCKTYPE_ICE:
				fprintf(pFile, "BLOCKFILE %s\n", &pBlockMane->astr[BLOCKTYPE_ICE][0]);
				break;

			case BLOCKTYPE_GRAVEL:
				fprintf(pFile, "BLOCKFILE %s\n", &pBlockMane->astr[BLOCKTYPE_GRAVEL][0]);
				break;

			case BLOCKTYPE_WALL:
				fprintf(pFile, "BLOCKFILE %s\n", &pBlockMane->astr[BLOCKTYPE_WALL][0]);
				break;

			case BLOCKTYPE_WALL_ADULT:
				fprintf(pFile, "BLOCKFILE %s\n", &pBlockMane->astr[BLOCKTYPE_WALL_ADULT][0]);
				break;

			case BLOCKTYPE_TERRITRY_POINT:
				fprintf(pFile, "BLOCKFILE %s\n", &pBlockMane->astr[BLOCKTYPE_TERRITRY_POINT][0]);
				break;

			case BLOCKTYPE_UDD_SNOW:
				fprintf(pFile, "BLOCKFILE %s\n", &pBlockMane->astr[BLOCKTYPE_UDD_SNOW][0]);
				break;
			}
			fprintf(pFile, "%s\n\n", "ENDSETBLOCK");
		}
	}
}
