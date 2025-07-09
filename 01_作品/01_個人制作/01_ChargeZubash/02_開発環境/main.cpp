#include "main.h"
#include "input.h"
#include "sound.h" 
#include "fade.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h" 
#include "tutorial.h" 
#include "background.h" 
#include "player.h" 
#include "block.h" 
#include "enemy.h" 

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;						//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;						//現在のモード
LPD3DXFONT g_pFont = NULL;						//フォントへのポインタ
int g_nCountFPS = 0;
bool g_isFullscreen = false;					//ウィンドウを切り替えるためのフラグ
RECT g_windowRect;								//ウィンドウを切り替えるための変数

//=======================
//デバイスの取得
//=======================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=======================
//メイン関数
//=======================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
	WNDCLASSEX wcex =					//ウィンドウクラスの構造体
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウィンドウのスタイル
		WindowProc,						//ウィンドウプロシージャ
		0,								//0にする(通常は使用しない)
		0,								//0にする(通常は使用しない)	
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),		//クライアント領域の背景色
		NULL,							//メニューバー
		CLASS_NAME,						//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	//ファイルのアイコン
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//画面サイズの構造体
		
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;//現在時刻
	DWORD dwExecLastTime;//現在時刻
	DWORD dwFrameCount;//フレームカウント
	DWORD dwFPSLastTime;//最後にFPSを計測した時刻

	//ウィンドクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウ左上X座標
		CW_USEDEFAULT,				//ウィンドウ左上Y座標
		(rect.right - rect.left),	//ウィンドウの幅
		(rect.bottom - rect.top),	//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューハンドルまたは子ウィンドウのハンドル
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ生成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗したとき
		return -1;
	}

	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);	//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);			//クライアント領域を更新
	
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windoesの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);	//仮想メッセージを文字メッセージへ変換
				DispatchMessage(&msg);	//ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DilectXの処理
			dwCurrentTime = timeGetTime();//現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;											//FPSを測定したを保存
				dwFrameCount = 0;														//フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))//60フレーム
			{
				dwExecLastTime = dwCurrentTime;
				//更新処理
				Updata();
				//描画処理
				Draw();
				dwFrameCount++;//フレームカウントを加算
			}
		}
	}
	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//==========================================
// ウィンドウをフルスクリーンに変える処理
//==========================================
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

//==========================================
//ウィンドプロシージャ
//==========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY://ウィンド破棄メッセージ

		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:	//ESCが押されたら

			//ウィンドウを破棄する(EM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
			break;

		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//==========================================
//初期化しょり
//==========================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ぢスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;//プレゼンテーションパラメータ

	//Direc3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータを設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;//ゲーム画面サイズ幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ高さ
	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形式
	d3dpp.BackBufferCount = 1;//
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//
	d3dpp.EnableAutoDepthStencil = TRUE;//
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//
	d3dpp.Windowed = bWindow;//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理をハードウェア,頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);//プレイヤーの中に透明度を加える
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//サンブラーステートの設定
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	//キーボード所得処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//背景の初期化
	InitBG();
	//サウンドの初期化処理
	InitSound(hWnd);
	//モードの設定
	SetMode(g_mode);
	//フェードの設定
	InitFade(g_mode);
	//デバッグ用表示フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"terminal", &g_pFont);

	return S_OK;
}

//==========================================
//終了処理
//==========================================
void Uninit(void)
{
	//サウンドの終了処理
	UninitSound();

	//フェードの終了処理
	UninitFade();

	//チュートリアル画面の終了処理
	UninitTutorial();

	//ゲーム画面の終了処理
	UninitGame();

	//リザルト画面の終了処理
	UninitResult();

	//キーボードの終了処理
	UninitKeyboard();

	//ジョイパッドの終了処理
	UninitJoypad();

	//背景の終了
	UninitBG();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクト
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//==========================================
// 更新処理
//==========================================
void Updata(void)
{
	//背景の更新
	UpdateBG();

	//キー入力の更新処理
	UpdataKeyboard();

	//ジョイパッドの更新処理
	UpdataJoypad();

	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面
		UpdateTitle();
		break;
	case MODE_GAME:		//ゲーム画面
		UpdateGame();
		break;
	case MODE_RESULT:	//リザルト画面
		UpdateResult();
		break;
	case MODE_RANKING:	//ランキング画面
		UpdateRanking();
		break;
	case MODE_TUTORIAL:	//チュートリアル画面
		UpdateTutorial();
		break;
	}
	
	//フェードの更新処理
	UpdateFade();
}

//==========================================
//描画処理
//==========================================
void Draw(void)
{
	//画面クリア(バッファバッファ&のクリア）
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		 D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//背景の描画
		DrawBG();		

		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル画面
			DrawTitle();
			break;
		case MODE_GAME:		//ゲーム画面
			DrawGame();
			break;
		case MODE_RESULT:	//リザルト画面
			DrawResult();
			break;
		case MODE_RANKING:	//ランキング画面
			DrawRanking();
			break;

		case MODE_TUTORIAL:	//チュートリアル画面
			DrawTutorial();
			break;
		}

		//フェードの描画処理
		DrawFade();
#ifdef _DEBUG //デバッグビルド時だけ表示

		//FPS表示
		DrawFPS();

		//プレイヤーの座標
		DebagDrawPlayer();

		//ブロックの順番
		DebagDrawBlock();

		//エネミー
		DebagDrawEnemy();
#endif

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==========================================
//モードの設定
//==========================================
void SetMode(MODE mode)
{
	//現在の画面(モード)の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル画面
		UninitTitle();
		break;
	case MODE_GAME:		//ゲーム画面
		UninitGame();
		break;
	case MODE_RESULT:	//リザルト画面
		UninitResult();
		break;
	case MODE_RANKING:	//ランキング画面
		UninitRanking();
		break;

	case MODE_TUTORIAL:	//チュートリアル画面
		UninitTutorial();
		break;
	}

	//新しい画面画面(モード)の初期化処理
	switch (mode)
	{
	case MODE_TITLE:	//タイトル画面
		InitTitle();
		break;

	case MODE_GAME:		//ゲーム画面
		InitGame();
		break;

	case MODE_RESULT:	//リザルト画面
		InitResult();
		break;

	case MODE_RANKING:	//ランキング画面
		InitRanking();
		break;

	case MODE_TUTORIAL:	//チュートリアル画面
		InitTutorial();
		break;
	}

	g_mode = mode;//現在の画面(モード)を切り替える

}

//==========================================
//モードの取得
//==========================================
MODE GetMode(void)
{
	return g_mode;
}

//==========================================
//デバッグ表示
//==========================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	//文字に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==========================================
//プレイヤーデバッグ表示
//==========================================
void DebagDrawPlayer(void)
{
	Player* pPlayer = GetPlayer();

	RECT rectPosx = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectPosy = { 0,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStrPosx[128];
	char aStrPosy[128];

	//文字に代入
	sprintf(&aStrPosx[0], "PLAYER_POS_X:%.2f\n", pPlayer->pos.x);
	sprintf(&aStrPosy[0], "PLAYER_POS_Y:%.2f\n", pPlayer->pos.y);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrPosy[0], -1, &rectPosy, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//=============================
//ブロックのデバッグ表示
//=============================
void DebagDrawBlock(void)
{
	//ブロック情報を取得
	BLOCK* pBlock = GetBlock();

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++, pBlock++)
	{
		if (pBlock->bUse == true)
		{
			RECT rectPosx = { pBlock->pos.x,pBlock->pos.y,SCREEN_WIDTH,SCREEN_HEIGHT };

			char aStrPosx[64];

			//文字に代入
			sprintf(&aStrPosx[0],"%d\n", nCnt);

			//テキストの描画
			g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}
}

//=============================
//エネミーのデバッグ表示
//=============================
void DebagDrawEnemy(void)
{
	int nNumEnemy = GetNumEnemy();	//エネミーの総数を取得
	ENEMY* pEnemy = GetEnemy();		//エネミー情報を取得

	RECT rectPosx = {0,45,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStrPosx[64];

	//文字に代入
	sprintf(&aStrPosx[0], "NUMENEMY:%d\n", nNumEnemy);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));



	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			RECT rectPosx = { pEnemy->pos.x,pEnemy->pos.y,SCREEN_WIDTH,SCREEN_HEIGHT };

			char aStrPosx[64];

			//文字に代入
			sprintf(&aStrPosx[0], "%d\n", nCnt);

			//テキストの描画
			g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}
}