//**********************************************
// 
// �J����
// Author Tetsuji Yamamoto
// 
//**********************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

// �J�����N���X
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

	// �Q�b�^�[
	D3DXVECTOR3 GetPositionV(void) { return m_posV; }
	D3DXVECTOR3 GetPositionR(void) { return m_posR; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	float GetDistance(void) { return m_fDistance; }

	// �Z�b�^�[
	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; }
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetDistance(float fDistance) { m_fDistance = fDistance; }

private:
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// ����
	float m_fDistance;			// ���_�ƒ����_�̋���
	float m_fAddRotValue;		// �ǉ��̊p�x�̒l
	float m_fLimitAngleValue;	// �p�x�̌��E�l
	bool m_bPosV;				// ���_����̗L��
};


#endif // !_CAMERA_H_
