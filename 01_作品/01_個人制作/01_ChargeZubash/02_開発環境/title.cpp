#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "background.h"
#include "lain.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_aPTextureTitle[TITLETYPE_MAX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファへのポインタ
TITLE g_aTitle[TITLETYPE_MAX];								//タイトルポリゴンの情報//タイトルポリゴンのテクスチャ
TITLEDIRECTOR g_TitleDirector;

//==============================================
//タイトル画面の初期化処理
//==============================================
void InitTitle(void)
{

	int nCntTitle;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLETYPE_MAX, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//演出構造体初期化
	g_TitleDirector.titleDirect = TITLEDIRECT_LOGODOWN;
	g_TitleDirector.nTimer = 0;
	g_TitleDirector.bBrink = false;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//情報の初期化
	for (nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		g_aTitle[nCntTitle].pFileName = NULL;
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].nType = TITLETYPE_MAX;

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
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	InitLain();	//雨

	//背景
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_1, BGTYPE_CLOUDY_0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_2, BGTYPE_CLOUDY_1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//ロゴ
	SetTitle(FILE_TEX_TITLE_LOGO,										//ファイルのパス
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -LOGO_HEIGHT, 0.0f),	//位置 
		TITLETYPE_LOGO,													//タイプ
		D3DXCOLOR(0.9f, 1.0f, 0.0f, 1.0f),								//色
		LOGO_WIDTH,														//幅
		LOGO_HEIGHT);													//高さ

	//スタートボタン
	SetTitle(FILE_TEX_TITLE_START,										//ファイルのパス
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f, 0.0f),	//位置 
		TITLETYPE_START,												//タイプ
		D3DXCOLOR(0.0f, 0.8f, 1.0f, 0.0f),								//色
		START_WIDTH,													//幅
		START_HEIGHT);													//高さ
}
//==============================================
//タイトル画面の終了処理
//==============================================
void UninitTitle(void)
{
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		//テクスチャの破棄
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

	UninitLain();	//雨


	//背景の終わり
	EndBackground(BGTYPE_CLOUDY_0);
	EndBackground(BGTYPE_CLOUDY_1);
}

//==============================================
//タイトル画面の更新処理
//==============================================
void UpdateTitle(void)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true)
		{
			switch (g_TitleDirector.titleDirect)
			{
			case TITLEDIRECT_LOGODOWN:	//ロゴ降りてくる
				UpDateLogo(nCntTitle);
				break;

			case TITLEDIRECT_STARTAPPEAR:	//スタート出現する
				UpDateStart(nCntTitle);
				break;

			case TITLEDIRECT_STARTBRINK:	//スタート点滅する
				UpDateStart(nCntTitle);
				break;

			case TITLEDIRECT_STARTBRINK_QUICKLY:	//スタート素早く点滅する
			//画面遷移
				UpDateStart(nCntTitle);
				break;
			}

			//頂点座標の設定
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
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	UpdateLain();	//雨
	
	if (KeyboardTrigger(DIK_G) == true)
	{
		SetFade(MODE_GAME);
	}
}

//==============================================
//タイトル画面の描画処理
//==============================================
void DrawTitle(void)
{
	DrawLain();	//雨

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_aPTextureTitle[nCntTitle]);

			//プレイヤーの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
				4 * nCntTitle,							//描画する最初の頂点インデックス
				2);										//描画するプリミティブ（プレイヤー）数
		}
	}


}

//==============================================
//タイトルの設定
//==============================================
void SetTitle(const char* pFileName, D3DXVECTOR3 pos,TITLETYPE type, D3DXCOLOR col,float fWidth,float fHeight)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//探す
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].pFileName = pFileName;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].col = col;
			g_aTitle[nCntTitle].nType = type;
			g_aTitle[nCntTitle].fWidth = fWidth;
			g_aTitle[nCntTitle].fHeight = fHeight;
			g_aTitle[nCntTitle].bUse = true;

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				g_aTitle[nCntTitle].pFileName,
				&g_aPTextureTitle[nCntTitle]);

			//頂点座標の設定
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

			//頂点カラーの設定
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//======================================
//タイトルロゴの更新
//======================================
void UpDateLogo(int nCntTitle)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntTitle;//設定する部分まで進める

	if (g_aTitle[nCntTitle].nType == TITLETYPE_LOGO)
	{
		if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//操作進める
			g_aTitle[nCntTitle].pos.y = SCREEN_HEIGHT * 0.2f;//目的の位置に設定
		}

		if (g_aTitle[nCntTitle].pos.y <= SCREEN_HEIGHT * 0.2f)
		{//目的地より上だったら
			g_aTitle[nCntTitle].pos.y += 5.0f;
		}
		else
		{
			g_TitleDirector.titleDirect = TITLEDIRECT_STARTAPPEAR;//スタート出現状態にする
		}

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//======================================
//スタートの更新
//======================================
void UpDateStart(int nCntTitle)
{
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntTitle;//設定する部分まで進める

	if (g_aTitle[nCntTitle].nType == TITLETYPE_START)
	{
		switch (g_TitleDirector.titleDirect)
		{
		case TITLEDIRECT_STARTAPPEAR:	//スタート出現する

			if (g_aTitle[nCntTitle].col.a < 1.0f)
			{//明るくなかったら
				g_aTitle[nCntTitle].col.a += 0.01;
			}
			else
			{
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBRINK;//スタート出現状態にする
				g_aTitle[nCntTitle].col.a = 1.0f;
			}

			if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true || GetJoypadTrigger(JOYKEY_A) == true)
			{//演出飛ばし用
				SetFade(MODE_TUTORIAL);
				PlaySound(SOUND_LABEL_CURSORDICITION_SE);						//決定音
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBRINK_QUICKLY;	//次の演出にする
				g_aTitle[nCntTitle].col.a = 1.0f;								//明るさMAXにする
			}
			break;

		case TITLEDIRECT_STARTBRINK:	//スタート点滅する

			if (g_TitleDirector.bBrink == true)
			{//暗くする
				g_aTitle[nCntTitle].col.a -= 0.01;
				if (g_aTitle[nCntTitle].col.a <= 0.0f)
				{
					g_TitleDirector.bBrink = false;
				}
			}
			else if(g_TitleDirector.bBrink == false)
			{//明るくする
				g_aTitle[nCntTitle].col.a += 0.01;
				if (g_aTitle[nCntTitle].col.a >= 1.0f)
				{
					g_TitleDirector.bBrink = true;
				}
			}

			if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true || GetJoypadTrigger(JOYKEY_A) == true)
			{//演出飛ばし用
				SetFade(MODE_TUTORIAL);
				PlaySound(SOUND_LABEL_CURSORDICITION_SE);						//決定音
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBRINK_QUICKLY;	//次の演出にする
			}
			break;

		case TITLEDIRECT_STARTBRINK_QUICKLY:	//スタート点滅する

			if (g_TitleDirector.bBrink == true)
			{//暗くする
				g_aTitle[nCntTitle].col.a -= 0.5;
				if (g_aTitle[nCntTitle].col.a <= 0.0f)
				{
					g_TitleDirector.bBrink = false;
				}
			}
			else if (g_TitleDirector.bBrink == false)
			{//明るくする
				g_aTitle[nCntTitle].col.a += 0.5;
				if (g_aTitle[nCntTitle].col.a >= 1.0f)
				{
					g_TitleDirector.bBrink = true;
				}
			}
			break;
		}

		//頂点カラーの設定
		pVtx[0].col = g_aTitle[nCntTitle].col;
		pVtx[1].col = g_aTitle[nCntTitle].col;
		pVtx[2].col = g_aTitle[nCntTitle].col;
		pVtx[3].col = g_aTitle[nCntTitle].col;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}