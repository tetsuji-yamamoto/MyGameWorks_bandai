#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "score.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankingBG = NULL;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBonus[BONUS_MAX] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingBG = NULL;		//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBonus = NULL;			//頂点バッファへのポインタ
RankScore g_aRankScore[MAX_RANK];						//ランキングスコア(5位分)表示
RankDirect g_RankDirect;
int g_nRankUpdate = -1;									//更新ランクNo.
int g_nTimerRanking;									//ランキング画面表示タイマー
int g_TransTitleCount;
//==========================================
//ランキングの初期化処理
//==========================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntRank;
	int nRankScore;

	g_nRankUpdate = -1;							//更新No.を初期化
	g_nTimerRanking = 0;
	g_RankDirect.nSkorDirect = DIRECT_BONUS;	//演出
	g_RankDirect.nSkorDirectCounter = 0;		//演出カウンター
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\RANKING\\UI_RunkNum_001.png",
		&g_pTextureRank);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\RANKING\\number000.png",
		&g_pTextureRankScore);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\RANKING\\Ranking_Test_001.png",
		&g_pTextureRankingBG);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANKSCORE_NUM, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingBG,
		NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//ランキングの順位分回す
		g_aRankScore[nCntRank].pos = D3DXVECTOR3(3000.0f - 400 * nCntRank, 200.0f + MAX_RANKSCORE_HEIGHT * nCntRank, 0.0f);
		g_aRankScore[nCntRank].nScore = 0;
		g_aRankScore[nCntRank].nRank = nCntRank + 1;

		for (nRankScore = 0; nRankScore < MAX_RANKSCORE_NUM; nRankScore++)
		{//スコアの桁数分回す

			pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
			pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
			pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
			pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
			pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
			pVtx[3].pos.z = 0.0f;
			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.9f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.9f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;//頂点データのポインタを四つ分進める
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		g_aRankScore[nCntRank].pos = D3DXVECTOR3(3000.0f - MAX_RANK_WIDTH - 400 * nCntRank, 200.0f + MAX_RANKSCORE_HEIGHT * nCntRank, 0.0f);

		pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
		pVtx[3].pos.z = 0.0f;
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + 0.2f * nCntRank, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f + 0.2f * nCntRank, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + 0.2f * nCntRank, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.2f + 0.2f * nCntRank, 1.0f);

		pVtx += 4;//頂点データのポインタを四つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();
	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffRankingBG->Lock(0, 0, (void**)&pVtx, 0);
	//ランキングの情報の初期化
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = SCREEN_WIDTH;
	pVtx[3].pos.y = SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffRankingBG->Unlock();
	//ランキングのリセット
	ResetRanking(FILE_TXT_SCORE);
	//ランキングの設定
	SetRanking(GetScore());
}
//==========================================
//ランキングの終了処理
//==========================================
void UninitRanking(void)
{
	
}
//==========================================
//ランキングの更新処理
//==========================================
void UpdateRanking(void)
{
	int nRankScore;
	int nCntRank;
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;
	//演出を変える
	if (g_RankDirect.nSkorDirectCounter <= 190)
	{//最大演出秒数
		//演出カウンター加算
		g_RankDirect.nSkorDirectCounter++;
		if (g_RankDirect.nSkorDirectCounter <= 60)
		{
			g_RankDirect.nSkorDirect = DIRECT_BONUS;
		}
		else if (g_RankDirect.nSkorDirectCounter > 60 && g_RankDirect.nSkorDirectCounter <= 180)
		{
			g_RankDirect.nSkorDirect = DIRECT_RANK;
		}
		else if (g_RankDirect.nSkorDirectCounter > 180)
		{
			g_RankDirect.nSkorDirect = DIRECT_BRINK;
		}
	}
	
	if (g_RankDirect.nSkorDirect == DIRECT_RANK)
	{
		//頂点バッファをロックし、ちょうてん情報へのポインタを取得
		g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{//ランキングの順位分回す
			if (g_aRankScore[nCntRank].pos.x >= 450.0f)
			{
				g_aRankScore[nCntRank].pos.x -= 50.0f;
			}
			else
			{
				g_aRankScore[nCntRank].pos.x = 450.0f;
			}

			for (nRankScore = 0; nRankScore < MAX_RANKSCORE_NUM; nRankScore++)
			{//スコアの桁数分回す
				pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
				pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
				pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
				pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
				pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
				pVtx[3].pos.z = 0.0f;

				pVtx += 4;
			}
		}
		//頂点バッファをアンロックする
		g_pVtxBuffRankScore->Unlock();
		//頂点バッファをロックし、ちょうてん情報へのポインタを取得
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
		//ランキングの情報の初期化
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			if (g_aRankScore[nCntRank].pos.x >= 400.0f)
			{
				g_aRankScore[nCntRank].pos.x -= 50.0f;
			}
			else
			{
				g_aRankScore[nCntRank].pos.x = 400.0f;
			}

			pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
			pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
			pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
			pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
			pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
			pVtx[3].pos.z = 0.0f;

			pVtx += 4;//頂点データのポインタを四つ分進める
		}
		//頂点バッファをアンロックする
		g_pVtxBuffRank->Unlock();
	}
	else if (g_RankDirect.nSkorDirect == DIRECT_BRINK)
	{
		g_nTimerRanking += 1;				//点滅カウンター加算

		//頂点バッファをロックし、ちょうてん情報へのポインタを取得
		g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

		for (nRankScore = 0; nRankScore < MAX_RANKSCORE_NUM * MAX_RANK; nRankScore++)
		{//スコアの桁数分回す
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx += 4;
		}
		pVtx -= 4 * MAX_RANKSCORE_NUM * MAX_RANK;
		//該当スコアランキングスコアを点滅
		if (g_nRankUpdate != -1 && g_nTimerRanking >= 0)
		{//ランクインしてて、かつ、タイマーがゼロ以上だったら
			pVtx += 4 * MAX_RANKSCORE_NUM * g_nRankUpdate;
			for (nRankScore = 0; nRankScore < MAX_RANKSCORE_NUM; nRankScore++)
			{//スコアの桁数分回す
			//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);

				pVtx += 4;
			}
		}

		//タイマーをマイナスにする
		if (g_nTimerRanking >= 5)
		{
			g_nTimerRanking *= -1;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffRankScore->Unlock();
	}

	g_TransTitleCount++;
	if (KeyboardTrigger(DIK_RETURN) == true ||
		GetJoypadTrigger(JOYKEY_START) == true ||
		GetJoypadTrigger(JOYKEY_A) == true ||
		GetJoypadTrigger(JOYKEY_B) == true ||
		g_TransTitleCount >= 600)
	{//時間経過またはキー押下で画面遷移
		g_TransTitleCount = 0;
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_TITLE);
	}
}
//==========================================
//ランキングの描画処理
//==========================================
void DrawRanking(void)
{
	int nCntRank;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingBG, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingBG);
	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,										//描画する最初の頂点インデックス
		2);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//ランキングスコアの描画
	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_RANKSCORE_NUM; nCntRank++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRankScore);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntRank,							//描画する最初の頂点インデックス
			2);
	}
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//エフェクトの描画
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRank);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntRank,							//描画する最初の頂点インデックス
			2);
	}
}
//==========================================
//ランキングのリセット
//==========================================
void ResetRanking(const char* DateScore)
{
	int nCnt = 0;
	//ランキングスコア情報の初期設定
	FILE* pFile = fopen(FILE_TXT_SCORE, "r");

	if (pFile == NULL)
	{
		
	}
	else
	{
		//一行目を読み込む
		char cTmp[125];
		fscanf(pFile, "%s\n", &cTmp[0]);
		//二行目以降を読み込む
		for(nCnt = 0; nCnt < MAX_RANK;nCnt++)
		{
			fscanf(pFile,"%d\n",&g_aRankScore[nCnt].nScore);
		}
	}

	fclose(pFile);

}
//==========================================
//ランキングの設定
//==========================================
void SetRanking(int nScore)
{
	int nCntRank;
	int nSelect;
	int nTemp;
	int aPosTexU[3] = {};//格桁の数字を格納
	int nData1, nData2;
	int nCnt;
	//---ランキングスコアの並び替え
	//-----指定スコアがランクインしたら g_nRankUpdate を更新
	if (nScore >= g_aRankScore[MAX_RANK - 1].nScore && !(nScore <= 0))//ソート処理
	{
		g_aRankScore[MAX_RANK - 1].nScore = nScore;

		for (nCntRank = 0; nCntRank < MAX_RANK - 1; nCntRank++)
		{
			for (nSelect = nCntRank + 1; nSelect < MAX_RANK; nSelect++)
			{
				if (g_aRankScore[nCntRank].nScore <= g_aRankScore[nSelect].nScore)
				{
					nTemp = g_aRankScore[nCntRank].nScore;
					g_aRankScore[nCntRank].nScore = g_aRankScore[nSelect].nScore;
					g_aRankScore[nSelect].nScore = nTemp;
				}
			}
		}
		//順位をぶち込む
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			if (g_aRankScore[nCntRank].nScore == nScore)
			{
				g_nRankUpdate = g_aRankScore[nCntRank].nRank - 1;
			}
		}
	}
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		nData1 = 100;
		nData2 = 10;
		//桁ごとに分割する
		for (nCnt = 0; nCnt < MAX_RANKSCORE_NUM; nCnt++)
		{
			if (nCnt == 0)
			{
				aPosTexU[0] = g_aRankScore[nCntRank].nScore / nData1;
			}
			else
			{
				aPosTexU[nCnt] = (g_aRankScore[nCntRank].nScore % nData1 / nData2);
				nData1 /= 10;
				nData2 /= 10;
			}
			//-----テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
	//順位を書き込む
	//ランキングスコア情報の初期設定
	FILE* pFile = fopen(FILE_TXT_SCORE, "w");

	if (pFile == NULL)
	{

	}
	else
	{
		char aScore[10] = "スコア";
		//一行目を書き込む
		fprintf(pFile, "%s\n", &aScore[0]);
		//二行目以降を書き込む
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fprintf(pFile, "%d\n", g_aRankScore[nCntRank].nScore);
		}
	}

	fclose(pFile);
}