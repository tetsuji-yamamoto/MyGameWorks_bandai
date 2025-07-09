#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
// カメラタイプ列挙
typedef enum
{
	CAMERATYPE_NOMAL = 0,
	CAMERATYPE_PLAYER,
	CAMERATYPE_MAX,
}CAMERATYPE;

// カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posVDest;		// 目的の視点
	D3DXVECTOR3 posR;			// 中視点
	D3DXVECTOR3 posRDest;		// 目的の注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DXVECTOR3 rot;			// 向き
	float fDistance;			// 視点から注視点までの距離

	int nType;					// カメラタイプ
}Camera;

// プロタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera* GetCamera(void);

void UpdateFollowCamera(void);
void UpdateDebugCamera(void);
#endif // !_CAMERA_H_
