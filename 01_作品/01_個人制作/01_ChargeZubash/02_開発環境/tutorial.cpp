#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "background.h"
#include "pause.h"
#include "player.h"
#include "block.h"
#include "effect.h"
#include "particle.h"
#include "thunder.h"
#include "charge.h"
#include "sword.h"
#include "enemy.h"
#include "score.h"
#include "HPbar.h"
#include "timer.h"
#include "background.h"
#include "lain.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//頂点バッファへのポインタ
TUTORIAL g_tutorial;							//チュートリアルポリゴンの情報//チュートリアルポリゴンのテクスチャ
bool g_bPauseTuto = false;

//==============================================
//チュートリアル画面の初期化処理
//==============================================
void InitTutorial(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//情報の初期化

	g_tutorial.pFileName = FILE_TEX_TUTORIAL_MOVE;
	g_tutorial.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	g_tutorial.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_tutorial.nType = TUTORIALTYPE_MOVE;
	g_tutorial.fWidth = 400.0f;
	g_tutorial.fHeight = 200.0f;
	g_tutorial.bDisp = false;
	g_tutorial.bBrink = false;
	g_tutorial.bInput = false;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		g_tutorial.pFileName,
		&g_pTextureTutorial);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	pVtx += 4;

	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();

	InitPlayer();	//プレイヤー
	InitBlock();	//ブロック
	InitPause();	//ポーズ
	InitEffect();	//エフェクト
	InitParticle();	//パーティクル
	InitThunder();	//雷
	InitCharge();	//充電
	InitSword();	//剣
	InitEnemy();	//敵
	InitHPbar();	//HPバー
	InitTimer();	//タイマー
	InitLain();		//雨

	//ブロック設置
	//床一段目
	for (int nCnt = 0; nCnt < 22; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//床2段目
	for (int nCnt = 0; nCnt < 22; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 3.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}
	//------------------------------------
	//床二段目1
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 7.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}

	//床二段目1
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		SetBlock(D3DXVECTOR3(-BLOCK_WIDTH + BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 5.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}
	//------------------------------------
	//床二段目1
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH + BLOCK_WIDTH - BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 7.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
		SetBlock(D3DXVECTOR3(SCREEN_WIDTH + BLOCK_WIDTH - BLOCK_WIDTH * 2.0f * nCnt, SCREEN_HEIGHT - BLOCK_HEIGHT * 5.0f, 0.0f), BLOCKTYPE_NOMAL, BLOCK_WIDTH, BLOCK_HEIGHT);
	}
	//-----------------------------------
	
	//敵設置
	SetEnemy(FILE_TEX_PB, D3DXVECTOR3(1100.0f, 490.0f, 0.0f), ENEMYTYPE_PUNCHINGBAG, 5, PB_WIDTH, PB_HEIGHT);
	
	//背景
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_1, BGTYPE_CLOUDY_0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_2, BGTYPE_CLOUDY_1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}
//==============================================
//チュートリアル画面の終了処理
//==============================================
void UninitTutorial(void)
{

	//テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	UninitPlayer();		//プレイヤー
	UninitBlock();		//ブロック
	UninitPause();		//ポーズ
	UninitEffect();		//エフェクト
	UninitParticle();	//パーティクル
	UninitThunder();	//雷
	UninitCharge();		//充電
	UninitSword();		//剣
	UninitEnemy();		//敵
	UninitHPbar();		//HPバー
	UninitTimer();		//タイマー
	UninitLain();		//雨


	g_bPauseTuto = false;
}

//==============================================
//チュートリアル画面の更新処理
//==============================================
void UpdateTutorial(void)
{
	Player* pPlayer = GetPlayer();	//プレイヤー取得

	VERTEX_2D* pVtx;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	if (pPlayer->fLife <= 0)
	{//体力亡くなたら元に戻してあげる
		pPlayer->pos = D3DXVECTOR3(200.0f, -100.0f,0.0f);
		pPlayer->fLife = MAX_PLAYER_HP;
	}
	
	//透明度を変えていく
	if (g_tutorial.bBrink == false)
	{//暗かったら

		g_tutorial.col.a += 0.01f;//明るさ足していく

		if (g_tutorial.col.a >= 1.0f)
		{//明度MAX
			g_tutorial.col.a = 1.0f;//明度ここまで

			//操作されたか
			if (TutorialInput() == true)
			{//入力したかどうか
				g_tutorial.bBrink = true;//暗くしていいよ
			}
		}
	}

	//暗くして良かったら
	if (g_tutorial.bBrink == true)
	{//明るかったら

		g_tutorial.col.a -= 0.01f;//暗くしていく

		if (g_tutorial.col.a <= 0.0f)
		{//明度0
			g_tutorial.col.a = 0.0f;	//最大明度
			g_tutorial.bDisp = true;	//表示し終わった
			g_tutorial.nType++;			//次の説明へ
		}
	}

	//画面遷移
	if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true)
	{
		if (g_bPauseTuto == false)
		{//	ポーズ中じゃなかったら
			SetFade(MODE_GAME);
		}
	}


	//表示状態によって
	if (g_tutorial.bDisp == false)
	{//表示し終わってなかったら


	}
	else if (g_tutorial.bDisp == true)
	{//表示し終わったら

		//次のテクスチャに変える
		switch (g_tutorial.nType)
		{
		case TUTORIALTYPE_JUMP:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_JUMP;
			break;

		case TUTORIALTYPE_ATTACK:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_ATTACK;
			break;

		case TUTORIALTYPE_THUNDER:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_THUNDER;
			break;

		case TUTORIALTYPE_DISCHARGE:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_DISCHARGE;
			break;

		case TUTORIALTYPE_END:
			g_tutorial.pFileName = FILE_TEX_TUTORIAL_END;
			break;

		}
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			g_tutorial.pFileName,
			&g_pTextureTutorial);

		g_tutorial.bDisp = false;	//表示していない状態
		g_tutorial.bBrink = false;	//暗くする
		g_tutorial.bInput = false;	//入力していない状態
	}

	if (g_bPauseTuto == true)
	{//	ポーズ中
		//	ポーズ中の更新処理
		UpdatePause();
	}
	else
	{//	ポーズ中でなければ
		UpdateBlock();		//	ブロック
		UpdateThunder();	//	雷
		UpdatePlayer();		//	プレイヤー
		UpdateSword();		//	剣
		UpdateCharge();		//	充電
		UpdateEnemy();		//	敵
		UpdateEffect();		//	エフェクト
		UpdateParticle();	//	パーティクル
		UpdateHPbar();		//	HPバー
		UpdateTimer();		//	タイマー
		UpdateLain();		//雨

	}

	if (KeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{//ポーズキー（P）が押された
		g_bPauseTuto = g_bPauseTuto ? false : true;
	}

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = g_tutorial.pos.x - g_tutorial.fWidth;
	pVtx[0].pos.y = g_tutorial.pos.y - g_tutorial.fHeight;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_tutorial.pos.x + g_tutorial.fWidth;
	pVtx[1].pos.y = g_tutorial.pos.y - g_tutorial.fHeight;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_tutorial.pos.x - g_tutorial.fWidth;
	pVtx[2].pos.y = g_tutorial.pos.y + g_tutorial.fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_tutorial.pos.x + g_tutorial.fWidth;
	pVtx[3].pos.y = g_tutorial.pos.y + g_tutorial.fHeight;
	pVtx[3].pos.z = 0.0f;

	//頂点カラーの設定
	pVtx[0].col = g_tutorial.col;
	pVtx[1].col = g_tutorial.col;
	pVtx[2].col = g_tutorial.col;
	pVtx[3].col = g_tutorial.col;


	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();
}

//==============================================
//チュートリアル画面の描画処理
//==============================================
void DrawTutorial(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	//プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,										//描画する最初の頂点インデックス
		2);										//描画するプリミティブ（プレイヤー）数

	DrawThunder();	//雷
	DrawBlock();	//ブロック
	DrawEnemy();	//敵
	DrawSword();	//剣
	DrawPlayer();	//プレイヤー
	DrawParticle();	//パーティクル
	DrawEffect();	//エフェクト
	DrawLain();		//雨
	DrawHPbar();	//HPバー
	DrawCharge();	//充電
	DrawTimer();	//タイマー

	//ポーズ中
	if (g_bPauseTuto == true)
	{
		//ポーズの描画
		DrawPause();
	}


}

//===============================
//チュートリアルの設定
//===============================
void SetTutorial(const char* pFileName, D3DXVECTOR3 pos, D3DXCOLOR col, TUTRIALTYPE type, float fWidth, float fHeight)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);


	g_tutorial.pFileName = pFileName;
	g_tutorial.pos = pos;
	g_tutorial.col = col;
	g_tutorial.nType = type;
	g_tutorial.fWidth = fWidth;
	g_tutorial.fHeight = fHeight;
	

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		g_tutorial.pFileName,
		&g_pTextureTutorial);

	//頂点座標の設定
	pVtx[0].pos.x = g_tutorial.pos.x - g_tutorial.fWidth;
	pVtx[0].pos.y = g_tutorial.pos.y - g_tutorial.fHeight;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_tutorial.pos.x + g_tutorial.fWidth;
	pVtx[1].pos.y = g_tutorial.pos.y - g_tutorial.fHeight;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_tutorial.pos.x - g_tutorial.fWidth;
	pVtx[2].pos.y = g_tutorial.pos.y + g_tutorial.fHeight;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_tutorial.pos.x + g_tutorial.fWidth;
	pVtx[3].pos.y = g_tutorial.pos.y + g_tutorial.fHeight;
	pVtx[3].pos.z = 0.0f;

	//頂点カラーの設定
	pVtx[0].col = g_tutorial.col;
	pVtx[1].col = g_tutorial.col;
	pVtx[2].col = g_tutorial.col;
	pVtx[3].col = g_tutorial.col;


	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();
}

//===============================
//チュートリアルの設定
//===============================
bool TutorialInput(void)
{
	bool bInput = false;

	XINPUT_STATE* pStick = GetJoySticAngle();	//スティック取得
	Player* pPlayer = GetPlayer();				//プレイヤー取得

	//操作したら
	switch (g_tutorial.nType)
	{
	case TUTORIALTYPE_MOVE:
		if (KeyboardRepeat(DIK_A) == true || GetJoypadRepeat(JOYKEY_LEFT) == true || pStick->Gamepad.sThumbLX <= -5000)
		{//左移動
			bInput = true;//押した
		}
		else if (KeyboardRepeat(DIK_D) == true || GetJoypadRepeat(JOYKEY_RIGHT) == true || pStick->Gamepad.sThumbLX >= 5000)
		{//右移動
			bInput = true;//押した
		}
		break;

	case TUTORIALTYPE_JUMP:
		if (KeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//ジャンプ
			bInput = true;//押した
		}
		break;

	case TUTORIALTYPE_ATTACK:
		if (KeyboardTrigger(DIK_E) == true || GetJoypadTrigger(JOYKEY_X) == true)
		{//通常攻撃
			bInput = true;//押した
		}
		break;

	case TUTORIALTYPE_THUNDER:
		//当たったら充電
		if (HitThunder(pPlayer->pos, PLAYER_HEIGHT) == true)
		{
			bInput = true;//押した
		}
		break;

	case TUTORIALTYPE_DISCHARGE:
		if (KeyboardTrigger(DIK_F) == true || GetJoypadTrigger(JOYKEY_Y) == true)
		{//放出
			bInput = true;//押した
		}
		break;

	case TUTORIALTYPE_END:
		break;

	}

	//フラグを返す
	return bInput;
}

//===========================================
//ポーズの有効無効設定
//===========================================
void SetEnablePause2(bool bPause)
{
	g_bPauseTuto = bPause;
}