#include "wave.h"
#include "block.h"

// グローバル変数宣言
WAVEINFO g_waveInfo;	// ウェーブ情報

//**************************************************
// ウェーブ初期化
//**************************************************
void InitWave(void)
{
	g_waveInfo.nNowWave = 0;

	for (int nCntWave = 0; nCntWave < WAVETYPE_MAX; nCntWave++)
	{
		g_waveInfo.wave[nCntWave].nEnemy[ENEMYTYPE_NOMAL] = 0;
		g_waveInfo.wave[nCntWave].nEnemy[ENEMYTYPE_REMOATE] = 0;
	}

	// ウェーブ読む
	ReadWave();
}

//**************************************************
// ウェーブ読む
//**************************************************
void ReadWave(void)
{
	// ファイル開く
	FILE* pFile = fopen("date\\text\\EnemyWave.txt", "r");

	char astr[128];	// 適当に格納する変数
	int result;

	// 一行読み込む
	result = fscanf(pFile, "%s", &astr[0]);

	for (int nCnt = 0; nCnt < WAVETYPE_MAX; nCnt++)
	{// ウェーブ分読み込む
		result = fscanf(pFile, "%d,%[^,],%d",
			&g_waveInfo.wave[nCnt].nEnemy[ENEMYTYPE_NOMAL],
			&astr[0],
			&g_waveInfo.wave[nCnt].nEnemy[ENEMYTYPE_REMOATE]);
	}

	fclose(pFile);
}

//**************************************************
// ウェーブで敵出現
//**************************************************
void WaveAppEnemy(void)
{
	ENEMY* pEnemy = GetEnemy();						// 敵情報ゲット
	ENEMY_MANAGER EnemyMane = GetEnemyManager();	// 敵管理情報ゲット
	BLOCK* pBlock = GetBlock();						// ブロック情報

	int nNumBlWallAdult = 0;
	D3DXVECTOR3 nBlWallAdultposMemo[MAX_BLOCK];

	for (int nCntBl = 0; nCntBl < MAX_BLOCK; nCntBl++, pBlock++)
	{// ブロック分回す
		if (pBlock->bUse && pBlock->nType == BLOCKTYPE_WALL_ADULT)
		{// 使ってて大人の壁だったら
			nNumBlWallAdult++;	// カウント追加
			nBlWallAdultposMemo[nNumBlWallAdult].x = pBlock->pos.x;	// 場所覚える
			nBlWallAdultposMemo[nNumBlWallAdult].y = pBlock->pos.y + pBlock->vtxMaxBlock.y;	// 場所覚える
			nBlWallAdultposMemo[nNumBlWallAdult].z = pBlock->pos.z;	// 場所覚える
		}
	}

	if (EnemyMane.nNumEnemy <= 0)
	{// 敵いなかったら

		for (int nCntEnemy = 0; nCntEnemy < g_waveInfo.wave[g_waveInfo.nNowWave].nEnemy[ENEMYTYPE_NOMAL]; nCntEnemy++)
		{
			int nBl = rand() % nNumBlWallAdult;
			SetEnemy(nBlWallAdultposMemo[nBl], ENEMYTYPE_NOMAL);
		}

		for (int nCntEnemy = 0; nCntEnemy < g_waveInfo.wave[g_waveInfo.nNowWave].nEnemy[ENEMYTYPE_REMOATE]; nCntEnemy++)
		{
			SetEnemy(D3DXVECTOR3(100.0f, 40.0f, 0.0f), ENEMYTYPE_REMOATE);
		}

		// ウェーブ追加
		g_waveInfo.nNowWave++;
	}
}