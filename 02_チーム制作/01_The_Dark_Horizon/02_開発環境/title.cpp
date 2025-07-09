#include "title.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "snowBall.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "pause.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "player.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "block.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "guide.h"
#include "enemy.h"
#include "snowBall.h"
#include "edit.h"
#include "timer.h"
#include "HPGauge.h"
#include "wave.h"
#include "score.h"
#include "smoke.h"
#include "sound.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureTitle[TITLETYPE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				// 頂点バッファへのポインタ
TITLE g_aTitle[TITLETYPE_MAX];								// タイトルポリゴンの情報
TITLEDIRECTOR g_TitleDirector;

//*********************************************
// タイトル画面の初期化処理
//*********************************************
void InitTitle(void)
{

	int nCntTitle;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLETYPE_MAX, // 必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	// 演出構造体初期化
	g_TitleDirector.titleDirect = TITLEDIRECT_LOGODOWN;
	g_TitleDirector.nTimer = 0;
	g_TitleDirector.bBrink = false;

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 情報の初期化
	for (nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		g_aTitle[nCntTitle].pFileName = NULL;
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitle[nCntTitle].nButtonIdx = -1;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].type = TITLETYPE_MAX;

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	// タイトルロゴ
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.15f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		TITLETYPE_LOGO,
		BUTTONTYPE_MAX,
		FILE_TEX_TITLE_SBS,
		SCREEN_WIDTH * 0.3f,
		SCREEN_HEIGHT * 0.15f);


	// スタートボタン
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),
		TITLETYPE_START,
		BUTTONTYPE_MAX,
		FILE_TEX_STRTBUTTON,
		SCREEN_WIDTH * 0.1f,
		SCREEN_HEIGHT * 0.05f);

	// スタートボタン光
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f, 0.0f),
		D3DXCOLOR(0.0f, 1.0f, 0.9f, 0.0f),
		TITLETYPE_START_SHINE,
		BUTTONTYPE_MAX,
		FILE_TEX_STRTBUTTON_SHINE,
		SCREEN_WIDTH * 0.1f,
		SCREEN_HEIGHT * 0.05f);

	// チュートリアルボタン
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f + SCREEN_HEIGHT * 0.1f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),
		TITLETYPE_TUTORIAL,
		BUTTONTYPE_MAX,
		FILE_TEX_TUTORIALBUTTON,
		SCREEN_WIDTH * 0.1f,
		SCREEN_HEIGHT * 0.05f);

	// チュートリアルボタン光
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f + SCREEN_HEIGHT * 0.1f, 0.0f),
		D3DXCOLOR(0.0f, 1.0f, 0.9f, 0.0f),
		TITLETYPE_TUTORIAL_SHINE,
		BUTTONTYPE_MAX,
		FILE_TEX_TUTORIALBUTTON_SHINE,
		SCREEN_WIDTH * 0.1f,
		SCREEN_HEIGHT * 0.05f);
	// UIの類
	InitCamera();	// カメラ
	InitShadow();	// 影
	InitBlock();	// ブロック
	InitLight();	// ライト
	InitPlayer();	// プレイヤー

	// 草木が揺れる音
	PlaySound(SOUND_LABEL_BGM_PLANTS_SWAY);
}
//*********************************************
// タイトル画面の終了処理
//*********************************************
void UninitTitle(void)
{
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		// テクスチャの破棄
		if (g_aPTextureTitle[nCntTitle] != NULL)
		{
			g_aPTextureTitle[nCntTitle]->Release();
			g_aPTextureTitle[nCntTitle] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// UIの類
	UninitCamera();	// カメラ
	UninitShadow();	// 影
	UninitBlock();	// ブロック
	UninitLight();	// ライト
	UninitPlayer();	// プレイヤー
}

//*********************************************
// タイトル画面の更新処理
//*********************************************
void UpdateTitle(void)
{
	// 許可証
	int nResult = -1;

	if (KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
	{
		if (g_TitleDirector.titleDirect == TITLEDIRECT_STARTBUTTONBRINK)
		{
			// 決定音
			PlaySound(SOUND_LABEL_SE_DESITION);


			g_TitleDirector.bBrink = true;

			SetFade(MODE_GAME);
		}
		else if (g_TitleDirector.titleDirect == TITLEDIRECT_TUTORIALBUTTONBRINK)
		{
			// 決定音
			PlaySound(SOUND_LABEL_SE_DESITION);

			g_TitleDirector.bBrink = true;

			SetFade(MODE_TUTORIAL);
		}

	}

	// タイトル演出
	nResult = TitleManager();


	// UIの類
	UpdateCamera();	// カメラ
	UpdateShadow();	// 影
	UpdateBlock();	// ブロック
	UpdateLight();	// ライト
	UpdatePlayer();	// プレイヤー
}

//*********************************************
// タイトル画面の描画処理
//*********************************************
void DrawTitle(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定00
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureTitle[g_aTitle[nCntTitle].type]);

			// プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				4 * nCntTitle,							// 描画する最初の頂点インデックス
				2);										// 描画するプリミティブ（プレイヤー）数
		}
	}

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// UIの類
	SetCamera();	// カメラ
	DrawShadow();	// 影
	DrawBlock();	// ブロック
	DrawPlayer();	// プレイヤー
}

//*********************************************
// タイトルの設定
//*********************************************
void SetTitle(D3DXVECTOR3 pos,D3DXCOLOR col,TITLETYPE type,BUTTONTYPE buttonType,const char* pFileName,float fWidth,float fHeight)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].pFileName = pFileName;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].col = col;
			g_aTitle[nCntTitle].type = type;
			g_aTitle[nCntTitle].nButtonIdx = buttonType;
			g_aTitle[nCntTitle].fWidth = fWidth;
			g_aTitle[nCntTitle].fHeight = fHeight;
			g_aTitle[nCntTitle].bUse = true;

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				g_aTitle[nCntTitle].pFileName,
				&g_aPTextureTitle[type]);

			// 頂点座標の設定
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//*********************************************
// タイトル管理
//*********************************************
int TitleManager(void)
{
	int nResult = -1;

	switch (g_TitleDirector.titleDirect)
	{
	case TITLEDIRECT_LOGODOWN:
		TitleLogoAnimation(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f),
			D3DXVECTOR3(0.0f, 5.0f, 0.0f));
		break;

	case TITLEDIRECT_BUTTONAPPEAR:
		TitleStartButtonAnimation();
		TitleTutorialButtonAnimation();
		break;

	case TITLEDIRECT_STARTBUTTONBRINK:
		TitleStartButtonShine();
		break;

	case TITLEDIRECT_TUTORIALBUTTONBRINK:
		TitleTutorialButtonShine();
		break;
	}

	return nResult;
}

//*********************************************
// タイトルロゴのアニメーション
//*********************************************
int TitleLogoAnimation(D3DXVECTOR3 posDest,D3DXVECTOR3 move)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// 結果

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_LOGO)
		{

			g_aTitle[nCntTitle].pos += move;

			if (g_aTitle[nCntTitle].pos.y >= posDest.y || KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
			{// 目的地についたならば
				g_aTitle[nCntTitle].pos = posDest;
				g_TitleDirector.titleDirect = TITLEDIRECT_BUTTONAPPEAR;
				nResult = 1;
			}

			// 頂点座標の設定
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	// 結果を返す
	return nResult;
}

//*********************************************
// ゲームスタートのアニメーション
//*********************************************
int TitleStartButtonAnimation(void)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// 結果

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_START)
		{

			g_aTitle[nCntTitle].col.a += 0.1f;

			if (g_aTitle[nCntTitle].col.a >= 1.0f || KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
			{
				g_aTitle[nCntTitle].col.a = 1.0f;
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBUTTONBRINK;
			}
			nResult = 1;

			// 頂点座標の設定
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	// 結果を返す
	return nResult;
}

//*********************************************
// テュートリアルボタンのアニメーション
//*********************************************
int TitleTutorialButtonAnimation(void)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// 結果

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_TUTORIAL)
		{

			g_aTitle[nCntTitle].col.a += 0.1f;

			if (g_aTitle[nCntTitle].col.a >= 1.0f || KeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
			{
				g_aTitle[nCntTitle].col.a = 1.0f;
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBUTTONBRINK;
			}
			nResult = 1;

			// 頂点座標の設定
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	// 結果を返す
	return nResult;
}

//*********************************************
// スタートボタンが輝く
//*********************************************
int TitleStartButtonShine(void)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// 結果

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_START_SHINE)
		{

			if (g_TitleDirector.bBrink)
			{
				g_TitleDirector.nTimer++;

				if (g_TitleDirector.nTimer >= 0)
				{
					g_aTitle[nCntTitle].col.a = 1.0f;

					if (g_TitleDirector.nTimer >= 2)
					{
						g_TitleDirector.nTimer *= -1;
					}
				}
				else if(g_TitleDirector.nTimer < 0)
				{
					g_aTitle[nCntTitle].col.a = 0.0f;
				}
			}
			else
			{
				g_aTitle[nCntTitle].col.a = 1.0f;

				if (KeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP))
				{
					// 選択音
					PlaySound(SOUND_LABEL_SE_SELECT);

					g_aTitle[nCntTitle].col.a = 0.0f;
					g_TitleDirector.titleDirect = TITLEDIRECT_TUTORIALBUTTONBRINK;
				}
				else if (KeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN))
				{
					// 選択音
					PlaySound(SOUND_LABEL_SE_SELECT);

					g_aTitle[nCntTitle].col.a = 0.0f;
					g_TitleDirector.titleDirect = TITLEDIRECT_TUTORIALBUTTONBRINK;
				}

			}

		

			nResult = 1;

			// 頂点座標の設定
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	// 結果を返す
	return nResult;
}

//*********************************************
// チュートリアルボタンが輝く
//*********************************************
int TitleTutorialButtonShine(void)
{
	VERTEX_2D* pVtx;
	int nResult = -1;	// 結果

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// 探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse && g_aTitle[nCntTitle].type == TITLETYPE_TUTORIAL_SHINE)
		{

			if (g_TitleDirector.bBrink)
			{
				g_TitleDirector.nTimer++;

				if (g_TitleDirector.nTimer >= 0)
				{
					g_aTitle[nCntTitle].col.a = 1.0f;

					if (g_TitleDirector.nTimer >= 2)
					{
						g_TitleDirector.nTimer *= -1;
					}
				}
				else if (g_TitleDirector.nTimer < 0)
				{
					g_aTitle[nCntTitle].col.a = 0.0f;
				}
			}
			else
			{
				g_aTitle[nCntTitle].col.a = 1.0f;

				if (KeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP))
				{
					// 選択音
					PlaySound(SOUND_LABEL_SE_SELECT);

					g_aTitle[nCntTitle].col.a = 0.0f;
					g_TitleDirector.titleDirect = TITLEDIRECT_STARTBUTTONBRINK;
				}
				else if (KeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN))
				{
					// 選択音
					PlaySound(SOUND_LABEL_SE_SELECT);

					g_aTitle[nCntTitle].col.a = 0.0f;
					g_TitleDirector.titleDirect = TITLEDIRECT_STARTBUTTONBRINK;
				}

			}

			nResult = 1;

			// 頂点座標の設定
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			// 頂点カラーの設定
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	// 結果を返す
	return nResult;
}