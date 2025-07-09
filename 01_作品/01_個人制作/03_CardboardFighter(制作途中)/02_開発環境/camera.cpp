//**********************************************
// 
// カメラ
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "camera.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "math.h"
#include "myMath.h"
#include "manager.h"
#include "debugproc.h"

//**********************************************
// カメラ処理
//**********************************************
CCamera::CCamera()
{
	ZeroMemory(m_mtxProjection, sizeof(m_mtxProjection));// プロジェクションマトリックス
	ZeroMemory(m_mtxView, sizeof(m_mtxView));			// ビューマトリックス
	ZeroMemory(m_posR, sizeof(m_posR));					// 中視点
	ZeroMemory(m_posV, sizeof(m_posV));					// 視点
	ZeroMemory(m_rot, sizeof(m_rot));					// 向き
	m_fDistance = 0.0f;									// 視点と注視点の距離
	m_fAddRotValue = 0.0f;								// 追加の角度の値		 
	m_fLimitAngleValue = 0.0f;							// 角度の限界値
	m_bPosV = false;									// 視点操作の有無
}

//**********************************************
// カメラ処理
//**********************************************
CCamera::~CCamera()
{
}

//**********************************************
// カメラ処理
//**********************************************
HRESULT CCamera::Init(void)
{
	// 視点・中視点・上方向を設定する
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 視点の位置
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 注視点の位置
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							// 固定
	m_rot = D3DXVECTOR3(-D3DX_PI * 0.35f, -D3DX_PI * 0.0f, 0.0f);	// 向き
	m_fDistance = 500.0f;											// 距離
	m_fAddRotValue = D3DX_PI * 0.01f;								// 追加の角度の値
	m_fLimitAngleValue = 0.01f;										// 角度の限界値
	m_bPosV = true;													// 視点操作の有無

	// 球座標計算で初期設定
	m_posV = CMyMath::SphericalCoordinates(m_posR, m_rot, m_fDistance);

	return S_OK;
}

//**********************************************
// カメラ処理
//**********************************************
void CCamera::Uninit(void)
{

}

//**********************************************
// カメラ処理
//**********************************************
void CCamera::Update(void)
{
	//キー操作
	KeyOperation();

}

//**********************************************
// カメラ処理
//**********************************************
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ビューマックスの初期化
	D3DXMatrixIsIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクトマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//**********************************************
// カメラ視点操作
//**********************************************
void CCamera::ViewpointOperation(D3DXVECTOR3 addRot)
{
	// 角度を追加
	m_rot += addRot;

	// 正規化する
	CMyMath::NormalizingAngles(&m_rot);

	// 球座標で視点を求める
	m_posV = CMyMath::SphericalCoordinates(m_posR, m_rot, m_fDistance);
}

//**********************************************
// カメラ処理
//**********************************************
void  CCamera::KeyOperation(void)
{
	// キー入力取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	D3DXVECTOR3 addRot = D3DXVECTOR3_NULL;

	// 上移動
	if (pInput->GetPress(DIK_I) == true)
	{
		addRot.x -= m_fAddRotValue;
	}

	// 下移動
	if (pInput->GetPress(DIK_K) == true)
	{
		addRot.x += m_fAddRotValue;
	}

	// 左移動
	if (pInput->GetPress(DIK_J) == true)
	{
		addRot.y -= m_fAddRotValue;
	}

	// 右移動
	if (pInput->GetPress(DIK_L) == true)
	{
		addRot.y += m_fAddRotValue;
	}

	// 伸ばす
	if (pInput->GetPress(DIK_U) == true)
	{
		m_fDistance += m_fDistance * 0.01f;
	}
	// 縮む
	else if (pInput->GetPress(DIK_O) == true)
	{
		m_fDistance -= m_fDistance * 0.01f;
	}

	// 限界地の設定
	if (m_rot.x + addRot.x >= -D3DX_PI * m_fLimitAngleValue)
	{
		addRot.x = 0.0f;
	}

	if (m_rot.x + addRot.x <= -D3DX_PI * (1.0f - m_fLimitAngleValue))
	{
		addRot.x = 0.0f;
	}

	// 視点旋回
	if (m_bPosV == true)
	{
		CCamera::ViewpointOperation(addRot);
	}
	// 注視点旋回
	else
	{
		CCamera::ViewpointOperation(addRot);
	}
}

//**********************************************
// カメラ処理
//**********************************************
void  CCamera::MouseOperation(void)
{

}

//**********************************************
// カメラ処理
//**********************************************
void  CCamera::JoypadOperation(void)
{

}

//**********************************************
// カメラ処理
//**********************************************
void  CCamera::FollowCamera(D3DXVECTOR3 posR)
{
	D3DXVECTOR3 move = posR - m_posR;
	m_posR += move;
	m_posV += move;
}

//**********************************************
// カメラ処理
//**********************************************
void CCamera::Debug(void)
{
	// デバッグプロック取得
	CDebugprocc* pDebug = CManager::GetDebugprocc();

	pDebug->Print("[ Camera ]\n");
	pDebug->Print("m_posV.x : %0.3f .y : %0.3f .z : %0.3f\n", m_posV.x, m_posV.y, m_posV.z);
	pDebug->Print("m_posR.x : %0.3f .y : %0.3f .z : %0.3f\n", m_posR.x, m_posR.y, m_posR.z);
	pDebug->Print("m_rot.x : %0.3f .y : %0.3f .z : %0.3f\n", m_rot.x, m_rot.y, m_rot.z);
	pDebug->Print("m_fDistance : %0.3f\n", m_fDistance);
	pDebug->Print("\n");
}