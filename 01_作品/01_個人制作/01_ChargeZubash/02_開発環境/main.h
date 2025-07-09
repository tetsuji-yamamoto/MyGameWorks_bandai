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

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9,lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント(部品)に必要
#pragma comment(lib,"winmm.lib")	//D
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"xinput.lib")	//ジョイパッド処理に必要

//マクロ定義
#define CLASS_NAME "WindowClass"	//ウィンドウクラスの名前
#define WINDOW_NAME "ChageZubashu"	//ウィンドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280)			//ウィンドウの幅
#define SCREEN_HEIGHT (720)			//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define RGBA_FULLCOLOR 1.0f,1.0f,1.0f,1.0f
#define TEST_WIDTH_CENTER SCREEN_WIDTH * 0.5f
#define TEST_HEIGHT_CENTER SCREEN_HEIGHT * 0.5f

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

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Updata(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawFPS(void);
void DebagDrawPlayer(void);
void DebagDrawBlock(void);
void DebagDrawEnemy(void);
#endif