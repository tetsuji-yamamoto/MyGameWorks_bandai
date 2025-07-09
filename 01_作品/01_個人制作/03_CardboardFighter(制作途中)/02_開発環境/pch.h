//****************************************
// 
// プリコンパイルヘッダー
// Author Tetsuji Yamamoto
// 
//****************************************
#ifndef _PCH_H_
#define _PCH_H_

#include<windows.h>
#include <stdio.h>
#include "d3dx9.h"						//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対処用マクロ
#include "dinput.h"						//入力処理に必要
#include "Xinput.h"						//ジョイパッド処理に必要
#include "xaudio2.h"					//サウンド処理に必要
#include <stdlib.h>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9,lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント(部品)に必要
#pragma comment(lib,"winmm.lib")	//D
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"xinput.lib")	//ジョイパッド処理に必要

#define SCREEN_WIDTH (1280)			//ウィンドウの幅
#define SCREEN_HEIGHT (720)			//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //座標.法線.カラー.テクスチャ

#define RGBA_FULLCOLOR 1.0f,1.0f,1.0f,1.0f
#define BACKCOLOR D3DCOLOR_RGBA(100,100,255,100)
#define TEST_WIDTH_CENTER SCREEN_WIDTH * 0.5f
#define TEST_HEIGHT_CENTER SCREEN_HEIGHT * 0.5f
#define D3DXVECTOR3_NULL (D3DXVECTOR3(NULL , NULL , NULL))
#define D3DXCOLOR_FULL (D3DXCOLOR(1.0f , 1.0f , 1.0f,1.0f))
#define D3DXCOLOR_NULL (D3DXCOLOR(0.0f , 0.0f , 0.0f,0.0f))

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

#endif // !_PCH_H_
