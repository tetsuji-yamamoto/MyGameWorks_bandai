//**********************************************
// 
// カメラ
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

// カメラクラス
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	void ViewpointOperation(D3DXVECTOR3 addRot);
	void KeyOperation(void);
	void MouseOperation(void);
	void JoypadOperation(void);
	void FollowCamera(D3DXVECTOR3 posR);

	void Debug(void);

	// ゲッター
	D3DXVECTOR3 GetPositionV(void) { return m_posV; }
	D3DXVECTOR3 GetPositionR(void) { return m_posR; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	float GetDistance(void) { return m_fDistance; }

	// セッター
	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; }
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetDistance(float fDistance) { m_fDistance = fDistance; }

private:
	D3DXMATRIX m_mtxView;		// ビューマトリックス
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 中視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXVECTOR3 m_rot;			// 向き
	float m_fDistance;			// 視点と注視点の距離
	float m_fAddRotValue;		// 追加の角度の値
	float m_fLimitAngleValue;	// 角度の限界値
	bool m_bPosV;				// 視点操作の有無
};


#endif // !_CAMERA_H_
