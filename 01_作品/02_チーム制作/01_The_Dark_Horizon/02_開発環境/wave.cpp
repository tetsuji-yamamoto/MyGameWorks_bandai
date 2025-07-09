#include "wave.h"
#include "block.h"

// �O���[�o���ϐ��錾
WAVEINFO g_waveInfo;	// �E�F�[�u���

//**************************************************
// �E�F�[�u������
//**************************************************
void InitWave(void)
{
	g_waveInfo.nNowWave = 0;

	for (int nCntWave = 0; nCntWave < WAVETYPE_MAX; nCntWave++)
	{
		g_waveInfo.wave[nCntWave].nEnemy[ENEMYTYPE_NOMAL] = 0;
		g_waveInfo.wave[nCntWave].nEnemy[ENEMYTYPE_REMOATE] = 0;
	}

	// �E�F�[�u�ǂ�
	ReadWave();
}

//**************************************************
// �E�F�[�u�ǂ�
//**************************************************
void ReadWave(void)
{
	// �t�@�C���J��
	FILE* pFile = fopen("date\\text\\EnemyWave.txt", "r");

	char astr[128];	// �K���Ɋi�[����ϐ�
	int result;

	// ��s�ǂݍ���
	result = fscanf(pFile, "%s", &astr[0]);

	for (int nCnt = 0; nCnt < WAVETYPE_MAX; nCnt++)
	{// �E�F�[�u���ǂݍ���
		result = fscanf(pFile, "%d,%[^,],%d",
			&g_waveInfo.wave[nCnt].nEnemy[ENEMYTYPE_NOMAL],
			&astr[0],
			&g_waveInfo.wave[nCnt].nEnemy[ENEMYTYPE_REMOATE]);
	}

	fclose(pFile);
}

//**************************************************
// �E�F�[�u�œG�o��
//**************************************************
void WaveAppEnemy(void)
{
	ENEMY* pEnemy = GetEnemy();						// �G���Q�b�g
	ENEMY_MANAGER EnemyMane = GetEnemyManager();	// �G�Ǘ����Q�b�g
	BLOCK* pBlock = GetBlock();						// �u���b�N���

	int nNumBlWallAdult = 0;
	D3DXVECTOR3 nBlWallAdultposMemo[MAX_BLOCK];

	for (int nCntBl = 0; nCntBl < MAX_BLOCK; nCntBl++, pBlock++)
	{// �u���b�N����
		if (pBlock->bUse && pBlock->nType == BLOCKTYPE_WALL_ADULT)
		{// �g���Ăđ�l�̕ǂ�������
			nNumBlWallAdult++;	// �J�E���g�ǉ�
			nBlWallAdultposMemo[nNumBlWallAdult].x = pBlock->pos.x;	// �ꏊ�o����
			nBlWallAdultposMemo[nNumBlWallAdult].y = pBlock->pos.y + pBlock->vtxMaxBlock.y;	// �ꏊ�o����
			nBlWallAdultposMemo[nNumBlWallAdult].z = pBlock->pos.z;	// �ꏊ�o����
		}
	}

	if (EnemyMane.nNumEnemy <= 0)
	{// �G���Ȃ�������

		for (int nCntEnemy = 0; nCntEnemy < g_waveInfo.wave[g_waveInfo.nNowWave].nEnemy[ENEMYTYPE_NOMAL]; nCntEnemy++)
		{
			int nBl = rand() % nNumBlWallAdult;
			SetEnemy(nBlWallAdultposMemo[nBl], ENEMYTYPE_NOMAL);
		}

		for (int nCntEnemy = 0; nCntEnemy < g_waveInfo.wave[g_waveInfo.nNowWave].nEnemy[ENEMYTYPE_REMOATE]; nCntEnemy++)
		{
			SetEnemy(D3DXVECTOR3(100.0f, 40.0f, 0.0f), ENEMYTYPE_REMOATE);
		}

		// �E�F�[�u�ǉ�
		g_waveInfo.nNowWave++;
	}
}