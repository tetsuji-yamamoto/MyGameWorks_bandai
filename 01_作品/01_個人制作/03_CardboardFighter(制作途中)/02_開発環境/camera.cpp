//**********************************************
// 
// �J����
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
// �J��������
//**********************************************
CCamera::CCamera()
{
	ZeroMemory(m_mtxProjection, sizeof(m_mtxProjection));// �v���W�F�N�V�����}�g���b�N�X
	ZeroMemory(m_mtxView, sizeof(m_mtxView));			// �r���[�}�g���b�N�X
	ZeroMemory(m_posR, sizeof(m_posR));					// �����_
	ZeroMemory(m_posV, sizeof(m_posV));					// ���_
	ZeroMemory(m_rot, sizeof(m_rot));					// ����
	m_fDistance = 0.0f;									// ���_�ƒ����_�̋���
	m_fAddRotValue = 0.0f;								// �ǉ��̊p�x�̒l		 
	m_fLimitAngleValue = 0.0f;							// �p�x�̌��E�l
	m_bPosV = false;									// ���_����̗L��
}

//**********************************************
// �J��������
//**********************************************
CCamera::~CCamera()
{
}

//**********************************************
// �J��������
//**********************************************
HRESULT CCamera::Init(void)
{
	// ���_�E�����_�E�������ݒ肷��
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ���_�̈ʒu
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// �����_�̈ʒu
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);							// �Œ�
	m_rot = D3DXVECTOR3(-D3DX_PI * 0.35f, -D3DX_PI * 0.0f, 0.0f);	// ����
	m_fDistance = 500.0f;											// ����
	m_fAddRotValue = D3DX_PI * 0.01f;								// �ǉ��̊p�x�̒l
	m_fLimitAngleValue = 0.01f;										// �p�x�̌��E�l
	m_bPosV = true;													// ���_����̗L��

	// �����W�v�Z�ŏ����ݒ�
	m_posV = CMyMath::SphericalCoordinates(m_posR, m_rot, m_fDistance);

	return S_OK;
}

//**********************************************
// �J��������
//**********************************************
void CCamera::Uninit(void)
{

}

//**********************************************
// �J��������
//**********************************************
void CCamera::Update(void)
{
	//�L�[����
	KeyOperation();

}

//**********************************************
// �J��������
//**********************************************
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �r���[�}�b�N�X�̏�����
	D3DXMatrixIsIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//**********************************************
// �J�������_����
//**********************************************
void CCamera::ViewpointOperation(D3DXVECTOR3 addRot)
{
	// �p�x��ǉ�
	m_rot += addRot;

	// ���K������
	CMyMath::NormalizingAngles(&m_rot);

	// �����W�Ŏ��_�����߂�
	m_posV = CMyMath::SphericalCoordinates(m_posR, m_rot, m_fDistance);
}

//**********************************************
// �J��������
//**********************************************
void  CCamera::KeyOperation(void)
{
	// �L�[���͎擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	D3DXVECTOR3 addRot = D3DXVECTOR3_NULL;

	// ��ړ�
	if (pInput->GetPress(DIK_I) == true)
	{
		addRot.x -= m_fAddRotValue;
	}

	// ���ړ�
	if (pInput->GetPress(DIK_K) == true)
	{
		addRot.x += m_fAddRotValue;
	}

	// ���ړ�
	if (pInput->GetPress(DIK_J) == true)
	{
		addRot.y -= m_fAddRotValue;
	}

	// �E�ړ�
	if (pInput->GetPress(DIK_L) == true)
	{
		addRot.y += m_fAddRotValue;
	}

	// �L�΂�
	if (pInput->GetPress(DIK_U) == true)
	{
		m_fDistance += m_fDistance * 0.01f;
	}
	// �k��
	else if (pInput->GetPress(DIK_O) == true)
	{
		m_fDistance -= m_fDistance * 0.01f;
	}

	// ���E�n�̐ݒ�
	if (m_rot.x + addRot.x >= -D3DX_PI * m_fLimitAngleValue)
	{
		addRot.x = 0.0f;
	}

	if (m_rot.x + addRot.x <= -D3DX_PI * (1.0f - m_fLimitAngleValue))
	{
		addRot.x = 0.0f;
	}

	// ���_����
	if (m_bPosV == true)
	{
		CCamera::ViewpointOperation(addRot);
	}
	// �����_����
	else
	{
		CCamera::ViewpointOperation(addRot);
	}
}

//**********************************************
// �J��������
//**********************************************
void  CCamera::MouseOperation(void)
{

}

//**********************************************
// �J��������
//**********************************************
void  CCamera::JoypadOperation(void)
{

}

//**********************************************
// �J��������
//**********************************************
void  CCamera::FollowCamera(D3DXVECTOR3 posR)
{
	D3DXVECTOR3 move = posR - m_posR;
	m_posR += move;
	m_posV += move;
}

//**********************************************
// �J��������
//**********************************************
void CCamera::Debug(void)
{
	// �f�o�b�O�v���b�N�擾
	CDebugprocc* pDebug = CManager::GetDebugprocc();

	pDebug->Print("[ Camera ]\n");
	pDebug->Print("m_posV.x : %0.3f .y : %0.3f .z : %0.3f\n", m_posV.x, m_posV.y, m_posV.z);
	pDebug->Print("m_posR.x : %0.3f .y : %0.3f .z : %0.3f\n", m_posR.x, m_posR.y, m_posR.z);
	pDebug->Print("m_rot.x : %0.3f .y : %0.3f .z : %0.3f\n", m_rot.x, m_rot.y, m_rot.z);
	pDebug->Print("m_fDistance : %0.3f\n", m_fDistance);
	pDebug->Print("\n");
}