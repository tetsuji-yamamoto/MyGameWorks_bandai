#include "readtext.h"
#include "block.h"

//**************************************************
// テキストファイルの読み込み
//**************************************************
void ReadText(void)
{
	// ファイル読み込みオープン

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

	 	char astr[256] = {};	// 文字列を格納する変数

	// テキストを読み込む
	while (1)
	{
		// テキストを読んで結果を代入
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "STAGESET") == 0)
		{// セットステージを行う
			SetStage(pFile);
		}

		// 読み切ったら終了
		if (result == EOF)
		{
			break;
		}
	}

	fclose(pFile);
}

//**************************************************
// ステージの読み込み
//**************************************************
void SetStage(FILE *pFile)
{
	BLOCKMANAGER* pBlMane = GetBlockManager();
	char astr[256] = {};	// 文字列を格納する変数

	// テキストを読み込む
	while (1)
	{

		// テキストを読んで結果を代入
		int result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "SETBLOCK") == 0)
		{// ブロック情報を読み込む
			ReadBlockDate(pFile);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_SNOW") == 0)
		{// ブロック情報を読み込む
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_SNOW][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_ICE") == 0)
		{// ブロック情報を読み込む
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_ICE][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_GRAVEL") == 0)
		{// ブロック情報を読み込む
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_GRAVEL][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_WALL") == 0)
		{// ブロック情報を読み込む
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_WALL][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_WALL_ADULT") == 0)
		{// ブロック情報を読み込む
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_WALL_ADULT][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_TERRITRY_POINT") == 0)
		{// ブロック情報を読み込む
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_TERRITRY_POINT][0]);
		}
		else if (strcmp(&astr[0], "FLENAME_BLOCK_UDD_SNOW") == 0)
		{// ブロック情報を読み込む
			result = fscanf(pFile, "%s", &pBlMane->astr[BLOCKTYPE_UDD_SNOW][0]);
		}
		else if (strcmp(&astr[0], "ENDSTAGESET") == 0)
		{// ステージセットを終了する
			break;
		}

		// 読み切ったら終了
		if (result == EOF)
		{
			break;
		}
	}
}

//**************************************************
// ブロックの読み込み
//**************************************************
void ReadBlockDate(FILE* pFile)
{
	char astr[256] = {};	// 文字列を格納する変数
	char astrOld[256] = {};	// 古い文字列を格納する変数
	int result = 0;			// EOF判定
	bool bComent = false;	// 読まなくていいもの
	SETBLOCK seBlock;		// ブロック情報

	// ブロック情報初期化
	seBlock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	seBlock.nType = BLOCKTYPE_MAX;
//	seBlock.pFilename = NULL;

	// テキストを読み込む
	while (1)
	{
		// テキストを読んで結果を代入
		result = fscanf(pFile, "%s", &astr[0]);

		if (strcmp(&astr[0], "POS") == 0)
		{// 位置を設定する
			//数値を読むこむ
			result = fscanf(pFile, "%f", &seBlock.pos.x);
			result = fscanf(pFile, "%f", &seBlock.pos.y);
			result = fscanf(pFile, "%f", &seBlock.pos.z);
		}
		else if (strcmp(&astr[0], "ROT") == 0)
		{// 向きを設定する
			result = fscanf(pFile, "%f", &seBlock.rot.x);
			result = fscanf(pFile, "%f", &seBlock.rot.y);
			result = fscanf(pFile, "%f", &seBlock.rot.z);
		}
		else if (strcmp(&astr[0], "BLOCKTYPE") == 0)
		{// タイプを設定する
			result = fscanf(pFile, "%d", &seBlock.nType);
		}
		else if (strcmp(&astr[0], "BLOCKFILE") == 0)
		{// タイプを設定する
			result = fscanf(pFile, "%s", &seBlock.astr[0]);
		}
		else if (strcmp(&astr[0], "ENDSETBLOCK") == 0)
		{// ブロックを設定しブロック情報の読み込みを終了する
			SetBlock(seBlock,true);
			break;
		}

		// 読み切ったら終了
		if (result == EOF)
		{
			break;
		}
	}
}
