#include "main.h"
#include "camera.h"
#include "light.h"
#include "keyboard.h"
#include "mouse.h"
#include "joypad.h"
#include "player.h"
#include "shadow.h"
#include "block.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"
#include "readtext.h"
#include "writetext.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "guide.h"
#include "fade.h"
#include "edit.h"
#include "enemy.h"
#include "ranking.h"
#include "tutorial.h"
#include "signboard.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;						//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;						//現在のモード
LPD3DXFONT g_pFont = NULL;						//フォントへのポインタ
int g_nCountFPS = 0;							//fpsカウント用
bool g_isFullscreen = false;					//ウィンドウを切り替えるためのフラグ
RECT g_windowRect;								//ウィンドウを切り替えるための変数
DEBUGMANAGER g_debMane;							// デバッグ表示管理

//***********************************************
// デバイスの取得
//***********************************************
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//***********************************************
// メイン関数
//***********************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{
	WNDCLASSEX wcex =					// ウィンドウクラスの構造体
	{									   
		sizeof(WNDCLASSEX),				// WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						// ウィンドウのスタイル
		WindowProc,						// ウィンドウプロシージャ
		0,								// 0にする(通常は使用しない)
		0,								// 0にする(通常は使用しない)	
		hInstance,						// インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	// タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),		// クライアント領域の背景色
		NULL,							// メニューバー
		CLASS_NAME,						// ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	// ファイルのアイコン
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	// 画面サイズの構造体
		
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;	// 現在時刻
	DWORD dwExecLastTime;	// 現在時刻
	DWORD dwFrameCount;		// フレームカウント
	DWORD dwFPSLastTime;	// 最後にFPSを計測した時刻

	// ウィンドクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,		// 拡張ウィンドウスタイル
		CLASS_NAME,					// ウィンドウクラスの名前
		WINDOW_NAME,				// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		// ウィンドウスタイル
		CW_USEDEFAULT,				// ウィンドウ左上X座標
		CW_USEDEFAULT,				// ウィンドウ左上Y座標
		(rect.right - rect.left),	// ウィンドウの幅
		(rect.bottom - rect.top),	// ウィンドウの高さ
		NULL,						// 親ウィンドウのハンドル
		NULL,						// メニューハンドルまたは子ウィンドウのハンドル
		hInstance,					// インスタンスハンドル
		NULL);						// ウィンドウ生成データ

	// 初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{// 初期化処理が失敗したとき
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);	// ウィンドウの表示状態を設定
	UpdateWindow(hWnd);			// クライアント領域を更新
	
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windoesの処理
			if (msg.message == WM_QUIT)
			{// WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				// メッセージの設定
				TranslateMessage(&msg);	// 仮想メッセージを文字メッセージへ変換
				DispatchMessage(&msg);	// ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{// DilectXの処理
			dwCurrentTime = timeGetTime();	// 現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過
				// FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;											// FPSを測定したを保存
				dwFrameCount = 0;														// フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 60フレーム
			{
				dwExecLastTime = dwCurrentTime;
				// 更新処理
				Updata();

				// 描画処理
				Draw();

				dwFrameCount++;	// フレームカウントを加算
			}
		}
	}
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//***********************************************
// ウィンドウをフルスクリーンに変える処理
//***********************************************
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

//***********************************************
//ウィンドプロシージャ
//***********************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;	// 戻り値を格納
	switch (uMsg)
	{
	case WM_DESTROY:	// ウィンド破棄メッセージ

		// WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:	// ESCが押されたら
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウを破棄する(EM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
			break;

		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//***********************************************
// 初期化しょり
//***********************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	// Direc3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	// デバイスのプレゼンテーションパラメータを設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		// ゲーム画面サイズ幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		// ゲーム画面サイズ高さ
	d3dpp.BackBufferFormat = d3ddm.Format;		// バックバッファの形式
	d3dpp.BackBufferCount = 1;					//
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//
	d3dpp.EnableAutoDepthStencil = TRUE;		//
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//
	d3dpp.Windowed = bWindow;					//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//

	// Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		// Direct3Dデバイスの生成(描画処理をハードウェア,頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
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

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			// プレイヤーの中に透明度を加える
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	// サンブラーステートの設定
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	// ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	// マウス所得処理
	if (FAILED(InitMouse(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// キーボード所得処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	g_debMane.nDebugLine = 0;
	g_debMane.nLineDistance = 15;

	InitSound(hWnd);	//サウンドの初期化処理
	InitFade(g_mode);	// フェード

#ifdef _DEBUG	// デバッグモード時だけ
	InitEdit();			// エディター
#endif

	// デバッグ用表示フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"terminal", &g_pFont);

	return S_OK;
}

//***********************************************
// 終了処理
//***********************************************
void Uninit(void)
{
	UninitSound();		// 音
	UninitKeyboard();	// キーボードの終了処理
	UninitMouse();		// マウス
	UninitJoypad();		// コントローラー
	UninitFade();		// フェード
	
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

//***********************************************
// 更新処理
//***********************************************
void Updata(void)
{
	UpdataKeyboard();	// キー入力の更新処理
	UpdateMouse();		// コントローラー
	UpdataJoypad();		// ジョイパッド
	UpdateFade();		// フェード

	// 今の状態の更新処理
	switch (g_mode)
	{
	case MODE_TITLE:	// タイトル画面
		UpdateTitle();
		break;

	case MODE_GAME:		// ゲーム画面
		UpdateGame();
		break;

	case MODE_TUTORIAL:	// チュートリアル画面
		UpdateTutorial();
		break;

	case MODE_RESULT:	// リザルト画面
		UpdateResult();
		break;

	case MODE_RANKING:	// ランキング画面
		UpdateRanking();
		break;
	}

#ifdef _DEBUG

	if (KeyboardTrigger(DIK_F3))
	{// オブジェクトのテキストへの書き込み
		WriteText();
	}
	else if (KeyboardTrigger(DIK_F4))
	{// エディットモード切替
		if (GetEditMode() == EDITMODE_NONE)
		{// エディターモード解除状態なら
			switch (GetMode())
			{
			case MODE_GAME:	// エディターゲームモード
				SetEditMode(EDITMODE_BLOCK);
				break;

			case MODE_TUTORIAL:	// エディターゲームモード
				SetEditMode(EDITMODE_BLOCK);
				break;
			}
		}
		else
		{
			// エディターモード解除
			SetEditMode(EDITMODE_NONE);
		}
	}

	// モード切替
	if (KeyboardTrigger(DIK_F9))
	{
		// エディターモード解除
		SetEditMode(EDITMODE_NONE);

		// 次のモードに切り替える

		switch (g_mode)
		{
		case MODE_TITLE:	// タイトル画面
			SetMode(MODE_TUTORIAL);
			break;

		case MODE_TUTORIAL:	// チュートリアル画面
			SetMode(MODE_GAME);
			break;

		case MODE_GAME:		// ゲーム画面
			SetMode(MODE_RESULT);
			break;

		case MODE_RESULT:	// リザルト画面
			SetMode(MODE_RANKING);
			break;

		case MODE_RANKING:	// ランキング画面
			SetMode(MODE_TITLE);
			break;
		}
	}

	// モード切替
	if (KeyboardTrigger(DIK_F7))
	{
		// エディターモード解除
		SetEditMode(EDITMODE_NONE);
		SetFade(MODE_RESULT);
		SetResult(RESULTTYPE_GAMECREAR);
	}
	// モード切替
	else if (KeyboardTrigger(DIK_F8))
	{
		// エディターモード解除
		SetEditMode(EDITMODE_NONE);
		SetFade(MODE_RESULT);
		SetResult(RESULTTYPE_GAMEOVER);
	}

#endif
}

//***********************************************
// 描画処理
//***********************************************
void Draw(void)
{
	// 画面クリア(バッファバッファ&のクリア）
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		 D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{// 描画開始が成功した場合


		// 今の状態の描画
		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル画面
			DrawTitle();
			break;

		case MODE_TUTORIAL:	// チュートリアル画面
			DrawTutorial();
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
		}

		DrawFade();	// フェード

#ifdef _DEBUG // デバッグビルド時だけ表示

		DrawFPS();			// FPS表示
		DrawGameMode();		// ゲームモード
		DrawEdit();			// エディター
		DrawCamera();		// カメラ
		//DrawDebPlayer();	// pureiya
		DrawDebBlock();		// ブロック
		DrawDebEnemy();		// 敵

		if (GetMode() == MODE_TUTORIAL)
		{
			DrawDebBoard();	// ボード
		}
		//DrawDCamera();	// ライト

		g_debMane.nDebugLine = 0;

#endif

		// 描画終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//******************************************
// モード切替
//******************************************
void SetMode(MODE mode)
{
	// 今の状態を終了させる
	switch (g_mode)
	{
	case MODE_TITLE:	// タイトル画面
		UninitTitle();
		break;

	case MODE_TUTORIAL:	// チュートリアル画面
		UninitTutorial();
		break;

	case MODE_GAME:		// ゲーム画面
		UninitGame();
		break;

	case MODE_RESULT:	// リザルト画面
		UninitResult();
		break;

	case MODE_RANKING:	//ランキング画面
		UninitRanking();
		break;
	}

	// 次のモードにする
	g_mode = mode;

	// 次のモードに初期化
	switch (mode)
	{
	case MODE_TITLE:	// タイトル画面
		InitTitle();		   
		break;			   
						   
	case MODE_TUTORIAL:	// チュートリアル画面
		InitTutorial();
		break;

	case MODE_GAME:		// ゲーム画面
		InitGame();		   
		break;			   
						   
	case MODE_RESULT:	// リザルト画面
		InitResult();
		break;

	case MODE_RANKING:	//ランキング画面
		InitRanking();
		break;
	}
}

//******************************************
// モード取得
//******************************************
MODE GetMode(void)
{
	return g_mode;
}

//******************************************
// デバッグ表示
//******************************************
void DrawFPS(void)
{
	char aStr[256];

	// 文字に代入
	wsprintf(&aStr[0], "FPS:%0.3d\n", g_nCountFPS);

	RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
	// テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DEBUGFONT_COLERE_R, DEBUGFONT_COLERE_G, DEBUGFONT_COLERE_B, DEBUGFONT_COLERE_A));

	g_debMane.nDebugLine += g_debMane.nLineDistance * 2;
}

//******************************************
// エディターのデバッグ表示
//******************************************
void DrawEdit(void)
{
	char aStr[6][256];
	int nCntA = 0;

	switch (GetEditMode())
	{
	case EDITMODE_BLOCK:	// エディターゲームモード
		// 文字に代入
		wsprintf(&aStr[nCntA][0], "[EDIT_MODE] -F4- <EDITMODE_BLOCK> ---------------------------------------------------------------------------------------------------");
		break;

	case EDITMODE_NONE:	// エディット解除
		// 文字に代入
		wsprintf(&aStr[nCntA][0], "[EDIT_MODE] -F4- <EDITMODE_NONE>");
		break;

	}
	nCntA++;	wsprintf(&aStr[nCntA][0], "-F10- エディットモード解除");
	nCntA++;	wsprintf(&aStr[nCntA][0], "-F4- エディットモード切替");
	nCntA++;	wsprintf(&aStr[nCntA][0], "-F2- テキスト読み込み");
	nCntA++;	wsprintf(&aStr[nCntA][0], "-F3- テキスト書き込み");
	nCntA++;	wsprintf(&aStr[nCntA][0], "-DEL- 配置リセット");

	for (int nCntB = 0; nCntB <= nCntA; nCntB++)
	{
		RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
		// テキストの描画
		g_pFont->DrawText(NULL, &aStr[nCntB][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DEBUGFONT_COLERE_R, DEBUGFONT_COLERE_G, DEBUGFONT_COLERE_B, DEBUGFONT_COLERE_A));
		g_debMane.nDebugLine += g_debMane.nLineDistance;
	}
	g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// ゲームモードのデバッグ表示
//******************************************
void DrawGameMode(void)
{
	MODE mode = GetMode();

	char aStr[256];

	switch (mode)
	{
	case MODE_TITLE:
		// 文字に代入
		wsprintf(&aStr[0], "[MODE]<TITLE>");
		break;

	case MODE_TUTORIAL:
		// 文字に代入
		wsprintf(&aStr[0], "[MODE]<TUTORIAL>");
		break;

	case MODE_GAME:
		// 文字に代入
		wsprintf(&aStr[0], "[MODE]<GAME>");
		break;

	case MODE_RESULT:
		// 文字に代入
		wsprintf(&aStr[0], "[MODE]<RESULT>");
		break;
	}

	
	RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
	// テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DEBUGFONT_COLERE_R, DEBUGFONT_COLERE_G, DEBUGFONT_COLERE_B, DEBUGFONT_COLERE_A));

	g_debMane.nDebugLine += g_debMane.nLineDistance * 2;
}

//******************************************
// カメラのデバッグ表示
//******************************************
void DrawCamera(void)
{
	Camera* pCamera = GetCamera();	// カメラ取得
	char aStr[8][256];
	int nCntA = 0;

	// 文字に代入
	sprintf(&aStr[nCntA][0], "[CAMERA]\n");
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.rot.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posV.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posV.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posR.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posVDest.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posVDest.x, pCamera->posVDest.y, pCamera->posVDest.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.posRDest.x:%0.3fy:%0.3fz:%0.3f\n", pCamera->posRDest.x, pCamera->posRDest.y, pCamera->posRDest.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_camera.fDistance:%0.3f\n", pCamera->fDistance);

	for (int nCntB = 0; nCntB <= nCntA; nCntB++)
	{
		RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
		// テキストの描画
		g_pFont->DrawText(NULL, &aStr[nCntB][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DEBUGFONT_COLERE_R, DEBUGFONT_COLERE_G, DEBUGFONT_COLERE_B, DEBUGFONT_COLERE_A));
		g_debMane.nDebugLine += g_debMane.nLineDistance;
	}
	g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// プレイヤーのデバッグ表示
//******************************************
void DrawDebPlayer(void)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤー取得

	char aStr[18][256];
	int nCntA = 0;

	// 文字に代入
	sprintf(&aStr[nCntA][0], "[PLAYER]\n");
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.pos.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->pos.x, pPlayer->pos.y, pPlayer->pos.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.posOld.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->posOld.x, pPlayer->posOld.y, pPlayer->posOld.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.rot.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->rot.x, pPlayer->rot.y, pPlayer->rot.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.rotDest.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->rotDest.x, pPlayer->rotDest.y, pPlayer->rotDest.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.move.x:%0.3fy:%0.3fz:%0.3f\n", pPlayer->move.x, pPlayer->move.y, pPlayer->move.z);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.nBlockType:%d\n", pPlayer->nBlockType);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.snowBall.nSnowBallWeight:%d\n", pPlayer->snowBall.nSnowBallWeight);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.snowBall.nMakeTimerSnow:%d\n", pPlayer->snowBall.nMakeTimerSnow);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.snowBall.nMakeTimerSnowMidi:%d\n", pPlayer->snowBall.nMakeTimerSnowMidi);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.snowBall.nMakeTimerSnowBig:%d\n", pPlayer->snowBall.nMakeTimerSnowBig);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.snowBall.nMakeTimerIce:%d\n", pPlayer->snowBall.nMakeTimerIce);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.snowBall.nMakeTimerIGravel:%d\n", pPlayer->snowBall.nMakeTimerIGravel);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.snowBall.nGravelOrder:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d\n", pPlayer->snowBall.nGravelOrder[0], pPlayer->snowBall.nGravelOrder[1], pPlayer->snowBall.nGravelOrder[2], pPlayer->snowBall.nGravelOrder[3], pPlayer->snowBall.nGravelOrder[4], pPlayer->snowBall.nGravelOrder[5], pPlayer->snowBall.nGravelOrder[6], pPlayer->snowBall.nGravelOrder[7], pPlayer->snowBall.nGravelOrder[8], pPlayer->snowBall.nGravelOrder[9]);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.charParam.nLife:%d\n", pPlayer->charParam.nLife);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.charParam.nCntOcc:%d\n", pPlayer->charParam.nCntOcc);
	nCntA++; sprintf(&aStr[nCntA][0], "g_player.charParam.nCntState:%d\n", pPlayer->charParam.nCntState);

	switch (pPlayer->charParam.nState)
	{
	case MOTIONTYPE_PLAYER_NEUTRAL:
		nCntA++; sprintf(&aStr[nCntA][0], "g_player.nState:MOTIONTYPE_PLAYER_NEUTRAL\n");
		break;

	case MOTIONTYPE_PLAYER_MOVE:
		nCntA++; sprintf(&aStr[nCntA][0], "g_player.nState:MOTIONTYPE_PLAYER_MOVE\n");
		break;

	case MOTIONTYPE_PLAYER_JUMP:
		nCntA++; sprintf(&aStr[nCntA][0], "g_player.nState:MOTIONTYPE_PLAYER_JUMP\n");
		break;

	case MOTIONTYPE_PLAYER_DAMAGE:
		nCntA++; sprintf(&aStr[nCntA][0], "g_player.nState:MOTIONTYPE_PLAYER_DAMAGE\n");
		break;

	case MOTIONTYPE_PLAYER_DEATH:
		nCntA++; sprintf(&aStr[nCntA][0], "g_player.nState:MOTIONTYPE_PLAYER_DEATH\n");
		break;
	}

	for (int nCnt = 0; nCnt <= nCntA; nCnt++)
	{
		RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
		// テキストの描画
		g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DEBUGFONT_COLERE_R, DEBUGFONT_COLERE_G, DEBUGFONT_COLERE_B, DEBUGFONT_COLERE_A));
		g_debMane.nDebugLine += g_debMane.nLineDistance;
	}
	g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// ブロックのデバッグ表示
//******************************************
void DrawDebBlock(void)
{
	PLAYER* pPlayer = GetPlayer();	// プレイヤー取得

	BLOCK* pBlock = GetBlock();// ブロック情報

	BLOCKCONTROLLER*pBlCont = GetBlockController();
	BLOCKMANAGER* pBlMane = GetBlockManager();

	char aStr[6][256];
	int nCntA = 0;

	pBlock += pBlCont->nCntNowBlock;

	// 文字に代入
	sprintf(&aStr[nCntA][0], "[BLOCK]\n");
	nCntA++; sprintf(&aStr[nCntA][0], "g_blockManager.nBlockNum:%d/%d\n", pBlMane->nBlockNum,MAX_BLOCK);
	nCntA++; sprintf(&aStr[nCntA][0], "g_blockCont.nCntNowBlock:%d\n", pBlCont->nCntNowBlock);
	nCntA++; sprintf(&aStr[nCntA][0], "g_aBlock.pos.x:%0.3fy:%0.3fz:%0.3f\n", pBlock->pos.x, pBlock->pos.y, pBlock->pos.z);

	switch (pBlCont->nNextBlType)
	{
	case BLOCKTYPE_SNOW:
		nCntA++; sprintf(&aStr[nCntA][0], "NextBlType:BLOCKTYPE_SNOW\n");
		break;

	case BLOCKTYPE_ICE:
		nCntA++; sprintf(&aStr[nCntA][0], "NextBlType:BLOCKTYPE_ICE\n");
		break;

	case BLOCKTYPE_GRAVEL:
		nCntA++; sprintf(&aStr[nCntA][0], "NextBlType:BLOCKTYPE_GRAVEL\n");
		break;

	case BLOCKTYPE_WALL:
		nCntA++; sprintf(&aStr[nCntA][0], "NextBlType:BLOCKTYPE_WALL\n");
		break;
	}

	switch (pBlock->nType)
	{
	case BLOCKTYPE_SNOW:
		nCntA++; sprintf(&aStr[nCntA][0], "NowBlock:BLOCKTYPE_SNOW\n");
		break;

	case BLOCKTYPE_ICE:
		nCntA++; sprintf(&aStr[nCntA][0], "NowBlock:BLOCKTYPE_ICE\n");
		break;

	case BLOCKTYPE_GRAVEL:
		nCntA++; sprintf(&aStr[nCntA][0], "NowBlock:BLOCKTYPE_GRAVEL\n");
		break;

	case BLOCKTYPE_WALL:
		nCntA++; sprintf(&aStr[nCntA][0], "NowBlock:BLOCKTYPE_WALL\n");
		break;
	}

	for (int nCnt = 0; nCnt <= nCntA; nCnt++)
	{
		RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
		// テキストの描画
		g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DEBUGFONT_COLERE_R, DEBUGFONT_COLERE_G, DEBUGFONT_COLERE_B, DEBUGFONT_COLERE_A));
		g_debMane.nDebugLine += g_debMane.nLineDistance;
	}
	g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// エネミーのデバッグ表示
//******************************************
void DrawDebEnemy(void)
{
	ENEMY* pEnemy = GetEnemy();	// 敵情報
	ENEMY_MANAGER enemyMane = GetEnemyManager();	// 敵管理

	char aStr[2][256];
	int nCntA = 0;

	// 文字に代入
	sprintf(&aStr[nCntA][0], "[ENEMY]\n");
	nCntA++; sprintf(&aStr[nCntA][0], "enemyMane.nNumEnemy:%d\n", enemyMane.nNumEnemy);

	for (int nCnt = 0; nCnt <= nCntA; nCnt++)
	{
		RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
		// テキストの描画
		g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DEBUGFONT_COLERE_R, DEBUGFONT_COLERE_G, DEBUGFONT_COLERE_B, DEBUGFONT_COLERE_A));
		g_debMane.nDebugLine += g_debMane.nLineDistance;
	}
	g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// ボードのデバッグ表示
//******************************************
void DrawDebBoard(void)
{
	SIGNBOARD *pSign = GetSignBoard();
	int pSignCont = GetSignBoardContllore();

	char aStr[3][256];
	int nCntA = 0;

	pSign += pSignCont;

	// 文字に代入
	sprintf(&aStr[nCntA][0], "[SIGNBORD]\n");
	nCntA++; sprintf(&aStr[nCntA][0], "idx%d\n", pSignCont);
	nCntA++; sprintf(&aStr[nCntA][0], "Signboard.pos.x:%fy:%fz:%f\n", pSign->pos.x, pSign->pos.y, pSign->pos.z);

	for (int nCnt = 0; nCnt <= nCntA; nCnt++)
	{
		RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
		// テキストの描画
		g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(DEBUGFONT_COLERE_R, DEBUGFONT_COLERE_G, DEBUGFONT_COLERE_B, DEBUGFONT_COLERE_A));
		g_debMane.nDebugLine += g_debMane.nLineDistance;
	}
	g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// ライトのデバッグ表示
//******************************************
void DrawDCamera(void)
{
	//D3DLIGHT9* pLight = GetLight();	// ライト取得

	//char aStr[5][256];
	//int nCntA = 0;

	//// 文字に代入
	//sprintf(&aStr[nCntA][0], "[LIGHT]\n");
	//nCntA++; sprintf(&aStr[nCntA][0], "g_player.pos.x:%0.3fy:%0.3fz:%0.3f\n", pLight->pos.x, pPlayer->pos.y, pPlayer->pos.z);

	//for (int nCnt = 0; nCnt < nCntA; nCnt++)
	//{
	//	RECT rect = { 0,g_debMane.nDebugLine,SCREEN_WIDTH,SCREEN_HEIGHT };
	//	// テキストの描画
	//	g_pFont->DrawText(NULL, &aStr[nCnt][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 255, 0, 255));
	//	g_debMane.nDebugLine += g_debMane.nLineDistance;
	//}
	//g_debMane.nDebugLine += g_debMane.nLineDistance;
}

//******************************************
// 文字列代入
//******************************************
void astringAss(char *astrA, char* astrB,int nMaxCnt)
{
	for (int nCnt = 0; nCnt < nMaxCnt; nCnt++, astrA++, astrB++)
	{
		astrA = astrB;
	}
}
