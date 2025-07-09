/////////////////////////////
//
//ダイレクトX
//Aouthor tetuji yamamoto
//
/////////////////////////////

#ifndef _MAIN_H_ //このマクロ定義がされてなかったら
#define _MAIN_H_ //二重インクルード帽子のマクロ定義

#include<windows.h>
#include <stdio.h>
#include "d3dx9.h"						//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対処用マクロ
#include "dinput.h"						//入力処理に必要
#include "Xinput.h"						//ジョイパッド処理に必要
#include "xaudio2.h"					//サウンド処理に必要
#include <stdio.h>
#include <stdlib.h>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9,lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント(部品)に必要
#pragma comment(lib,"winmm.lib")	//D
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"xinput.lib")	//ジョイパッド処理に必要

//マクロ定義
#define CLASS_NAME "WindowClass"	//ウィンドウクラスの名前
#define WINDOW_NAME "SnowBallSurvivor"	//ウィンドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280)			//ウィンドウの幅
#define SCREEN_HEIGHT (720)			//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //座標.法線.カラー.テクスチャ

#define RGBA_FULLCOLOR 1.0f,1.0f,1.0f,1.0f
#define TEST_WIDTH_CENTER SCREEN_WIDTH * 0.5f
#define TEST_HEIGHT_CENTER SCREEN_HEIGHT * 0.5f
#define WORLD_GRAVITY (0.2f)						// 世界の重力

#define DEBUGFONT_COLERE_R 255
#define DEBUGFONT_COLERE_G 40
#define DEBUGFONT_COLERE_B 126
#define DEBUGFONT_COLERE_A 255
//画面（モード）の種類
typedef enum
{
	MODE_TITLE = 0,		//チュートリアル画面
	MODE_GAME,			//ゲーム画面
	MODE_RESULT,		//リザルト画面
	MODE_RANKING,		//ランキング画面
	MODE_TUTORIAL,		//チュートリアル画面
	MODE_MAX			
}MODE;

//頂点情報[2D]構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換用係数
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;

//頂点情報[3D]構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_3D;

//四頂点構造体
typedef struct
{
	D3DXVECTOR2 TopLeft;
	D3DXVECTOR2 TopRight;
	D3DXVECTOR2 BottomLeft;
	D3DXVECTOR2 BottomRight;
	float fLength;			//対角線
	float fAngle;			//向き
	float fLot;				//角度
}VERTEX;

// デバッグ表示管理
typedef struct
{
	int nDebugLine;		// デバッグ表示行
	int nLineDistance;	// 改行幅
}DEBUGMANAGER;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Updata(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);

void DrawFPS(void);
void DrawGameMode(void);
void DrawCamera(void);
void DrawDebPlayer(void);
void DrawDCamera(void);
void DrawEdit(void);
void DrawDebBlock(void);
void DrawDebEnemy(void);
void DrawDebBoard(void);

void astringAss(char* astrA, char* astrB, int nMaxCnt);
#endif