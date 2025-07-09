#include "pause.h"
#include "main.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "input.h"
#include "sound.h"
#include "tutorial.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSE_MENU_MAX] = {};	//Direct3Dテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//頂点バッファへのポインタ
PAUSE g_aPause[PAUSE_MENU_MAX];								//ポーズ情報
int g_nSelect;

//======================================
//ポーズの初期化処理
//======================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	int nCntPause;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_MENU_MAX, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	g_nSelect = PAUSE_MENU_CONTINUE;

	//ポーズ情報を初期化
	for (nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		g_aPause[nCntPause].pFileName = NULL;
		g_aPause[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[nCntPause].col = D3DXCOLOR(RGBA_FULLCOLOR);
		g_aPause[nCntPause].nType = PAUSE_MENU_MAX;
		g_aPause[nCntPause].fWidth = 0.0f;
		g_aPause[nCntPause].fHeight = 0.0f;
		g_aPause[nCntPause].bUse = false;

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			g_aPause[nCntPause].pFileName,
			&g_pTexturePause[nCntPause]);

		pVtx[0].pos.x = g_aPause[nCntPause].pos.x - MENU_WIDTH / 2;
		pVtx[0].pos.y = g_aPause[nCntPause].pos.y - MENU_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aPause[nCntPause].pos.x + MENU_WIDTH / 2;
		pVtx[1].pos.y = g_aPause[nCntPause].pos.y - MENU_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aPause[nCntPause].pos.x - MENU_WIDTH / 2;
		pVtx[2].pos.y = g_aPause[nCntPause].pos.y + MENU_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aPause[nCntPause].pos.x + MENU_WIDTH / 2;
		pVtx[3].pos.y = g_aPause[nCntPause].pos.y + MENU_HEIGHT / 2;
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

		pVtx += 4;//頂点データのポインタを四つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	//コンテニュー
	SetPause(FILE_TEX_PAUSE_CONTENUE,													//パス
		D3DXVECTOR3(TEST_WIDTH_CENTER , TEST_HEIGHT_CENTER - MENU_HEIGHT * 2.0f, 0.0f),	//位置
		D3DXCOLOR(RGBA_FULLCOLOR),														//色
		PAUSE_MENU_CONTINUE,															//種類
		MENU_WIDTH,																		//幅
		MENU_HEIGHT);																	//高さ

	//リトライ
	SetPause(FILE_TEX_PAUSE_RETRY,									//パス
		D3DXVECTOR3(TEST_WIDTH_CENTER, TEST_HEIGHT_CENTER, 0.0f),	//位置
		D3DXCOLOR(RGBA_FULLCOLOR),									//色
		PAUSE_MENU_RETRY,											//種類
		MENU_WIDTH,													//幅
		MENU_HEIGHT);												//高さ

	//クイット
	SetPause(FILE_TEX_PAUSE_QUIT,														//パス
		D3DXVECTOR3(TEST_WIDTH_CENTER, TEST_HEIGHT_CENTER + MENU_HEIGHT * 2.0f, 0.0f),	//位置
		D3DXCOLOR(RGBA_FULLCOLOR),														//色
		PAUSE_MENU_QUIT,																//種類
		MENU_WIDTH,																		//幅
		MENU_HEIGHT);																	//高さ
}

//======================================
//ポーズの終了処理
//======================================
void UninitPause(void)
{
	int nCntPause;

	for (nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		//テクスチャの破棄
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
//======================================
//ポーズ更新処理
//======================================
void UpdatePause(void)
{
	int nCntPause;

	VERTEX_2D* pVtx;
	XINPUT_STATE* pStick = GetJoySticAngle();	//スティック取得

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{//一度すべてを半透明に
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.6f, 0.8f, 0.6f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.6f, 0.8f, 0.6f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.6f, 0.8f, 0.6f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.6f, 0.8f, 0.6f, 0.5f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	if (KeyboardTrigger(DIK_W) == true || GetJoypadTrigger(JOYKEY_UP) == true)//W、上
	{//Wキーが押された
		g_nSelect--;
		PlaySound(SOUND_LABEL_CURSORMOVE_SE);//カーソル音
	}
	else if (KeyboardTrigger(DIK_S) == true || GetJoypadTrigger(JOYKEY_DOWN) == true)//S、下
	{//Sキーが押された
		g_nSelect++;
		PlaySound(SOUND_LABEL_CURSORMOVE_SE);//カーソル音
	}
	//範囲を超えないようにする
	if (g_nSelect < PAUSE_MENU_CONTINUE)
	{//ゼロより小さい
		g_nSelect = PAUSE_MENU_QUIT;
	}
	else if (g_nSelect >= PAUSE_MENU_MAX)
	{//最大値以上
		g_nSelect = PAUSE_MENU_CONTINUE;
	}

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//g_nSelectを基準にポリゴンを不透明にする
	pVtx += 4 * g_nSelect;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
	{//決定キーが押された
		//メニューに合わせてモードの切り替え
		switch (g_nSelect)
		{
		case PAUSE_MENU_CONTINUE:
			if (GetMode() == MODE_TUTORIAL)
			{
				SetEnablePause2(false);
			}
			else
			{
				SetEnablePause(false);
			}
			break;

		case PAUSE_MENU_RETRY:
			//SetGameState(GAMESTATE_END);
			if (GetMode() == MODE_TUTORIAL)
			{
				SetFade(MODE_TUTORIAL);
			}
			else
			{
				SetFade(MODE_GAME);
			}
			break;

		case PAUSE_MENU_QUIT:
			//SetGameState(GAMESTATE_END);
			SetFade(MODE_TITLE);
			break;
		}

		PlaySound(SOUND_LABEL_CURSORDICITION_SE);//決定音
	}
}
//======================================
//ポーズの描画処理
//======================================
void DrawPause(void)
{
	int nCntPause;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//エフェクトの描画
	for (nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		if (g_aPause[nCntPause].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePause[nCntPause]);
			//ポリゴン描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntPause,							//描画する最初の頂点インデックス
				2);
		}
	}
}

//===============================
//ポーズの設定
//===============================
void SetPause(const char* pFileName, D3DXVECTOR3 pos, D3DXCOLOR col, PAUSE_MENU type, float fWidth, float fHeight)
{

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//探す
	for (int nCntPause = 0; nCntPause < PAUSE_MENU_MAX; nCntPause++)
	{
		if (g_aPause[nCntPause].bUse == false)
		{
			g_aPause[nCntPause].pFileName = pFileName;
			g_aPause[nCntPause].pos = pos;
			g_aPause[nCntPause].col = col;
			g_aPause[nCntPause].nType = type;
			g_aPause[nCntPause].fWidth = fWidth;
			g_aPause[nCntPause].fHeight = fHeight;
			g_aPause[nCntPause].bUse = true;

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				g_aPause[nCntPause].pFileName,
				&g_pTexturePause[nCntPause]);

			//頂点座標の設定
			pVtx[0].pos.x = g_aPause[nCntPause].pos.x - g_aPause[nCntPause].fWidth;
			pVtx[0].pos.y = g_aPause[nCntPause].pos.y - g_aPause[nCntPause].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aPause[nCntPause].pos.x + g_aPause[nCntPause].fWidth;
			pVtx[1].pos.y = g_aPause[nCntPause].pos.y - g_aPause[nCntPause].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aPause[nCntPause].pos.x - g_aPause[nCntPause].fWidth;
			pVtx[2].pos.y = g_aPause[nCntPause].pos.y + g_aPause[nCntPause].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aPause[nCntPause].pos.x + g_aPause[nCntPause].fWidth;
			pVtx[3].pos.y = g_aPause[nCntPause].pos.y + g_aPause[nCntPause].fHeight;
			pVtx[3].pos.z = 0.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aPause[nCntPause].col;
			pVtx[1].col = g_aPause[nCntPause].col;
			pVtx[2].col = g_aPause[nCntPause].col;
			pVtx[3].col = g_aPause[nCntPause].col;

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}