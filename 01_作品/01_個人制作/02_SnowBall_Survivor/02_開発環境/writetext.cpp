#include "writetext.h"
#include "block.h"

//**************************************************
// テキストファイルの書き込み
//**************************************************
void WriteText(void)
{
	// ファイル読み込みオープン
	FILE* pFile = fopen("date\\text\\writeStage.txt", "w");
	char astr[256] = {};	// 文字列を格納する変数

	// ステージを書き込む
	WriteStage(pFile);

	fclose(pFile);
}

//**************************************************
// ステージの書き込み
//**************************************************FLENAME_BLOCK_SNOW date\xfile\block\Block_Snow_001.x
void WriteStage(FILE* pFile)
{
	BLOCKMANAGER* pBlockMane = GetBlockManager();	// ブロック管理情報取得

	// 書き込む
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
// ブロックの書きこみ
//**************************************************
void WriteBlockDate(FILE* pFile)
{
	BLOCK* pBlock = GetBlock();	// ブロック情報取得
	BLOCKMANAGER* pBlockMane = GetBlockManager();	// ブロック管理情報取得
	BLOCKCONTROLLER* pBlCont = GetBlockController();// ブロックコントローラー取得

	// 使っているブロック分テキストを読み込む
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++, pBlock++)
	{
		if (pBlock->bUse)
		{
			if (nCnt == pBlCont->nCntNowBlock)
			{// エディットのブロックは書かない
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
