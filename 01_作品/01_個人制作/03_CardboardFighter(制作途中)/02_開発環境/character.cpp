//*****************************************
// 
// �L�����N�^�[
// Author Tetsuji Yamamoto
// 
//*****************************************
#include "character.h"

//*****************************************
// �L�����N�^�[
//*****************************************
CCharacter::CCharacter()
{
	m_nLife = 0;								// ����
	m_pos = D3DXVECTOR3_NULL;					// �ʒu
	m_posOld = D3DXVECTOR3_NULL;				// �Â��ʒu
	m_rot = D3DXVECTOR3_NULL;					// ����
	m_rotDest = D3DXVECTOR3_NULL;				// �ړI�̌���
	m_move = D3DXVECTOR3_NULL;					// �ړ���
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));	// ���[���h�}�g���b�N�X
	m_pState = NULL;							// ���
}

//*****************************************
// �L�����N�^�[
//*****************************************
CCharacter::~CCharacter()
{
}

//*****************************************
// �L�����N�^�[
//*****************************************
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight,int nLife, float fMovement, int nAppStateCnt)
{
	// �e��ϐ��̏�����
	m_fRadius = fRadius;						// ���a
	m_fHeight = fHeight;						// ����
	m_fMovement = fMovement;					// �ړ���
	m_nLife = nLife;							// ����
	m_pos = pos;								// �ʒu
	m_rot = rot;								// ����
	m_rotDest = D3DXVECTOR3_NULL;				// �ړI�̌���
	ZeroMemory(m_move, sizeof(D3DXVECTOR3));	// �ړ���
	D3DXMatrixIdentity(&m_mtxWorld);			// �}�g���b�N�X

	// ��Ԑ���
	m_pState = CState::Create();

	// �ۉe����
	m_pShadow = CShadow::Create(fRadius);
	return S_OK;
}

//*****************************************
// �L�����N�^�[
//*****************************************
void CCharacter::Uninit(void)
{
	if (m_pState != NULL)
	{
		m_pState->Uninit();
		m_pState = NULL;
	}

	delete this;
}

//*****************************************
// �L�����N�^�[
//*****************************************
void CCharacter::Update(void)
{
	// ��ԏ���
	m_pState->StateCountDown();

	// �e�̈ʒu�ݒ�
	m_pShadow->SetPosition(m_pos);
}

//*****************************************
// �L�����N�^�[
//*****************************************
void CCharacter::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	// ������ǉ�
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu��ǉ�
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

}

//*****************************************
// �L�����N�^�[
//*****************************************
CCharacter* CCharacter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight, int nLife, float fMovement, int nAppStateCnt)
{
	// �v���C���[�|�C���^�[
	CCharacter* pCharacter = NULL;	

	// ���������m��
	pCharacter = new CCharacter;

	if (pCharacter != NULL)
	{// �k���`�F�b�N
		// ����������
		pCharacter->Init(pos, rot, fRadius,fHeight, nLife, fMovement, nAppStateCnt);
	}
	else
	{
		MessageBox(NULL, " CObject2D* CObject2D::Create() > if (pObject2D != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pCharacter;
}

//*****************************************
// �L�����N�^�[
//*****************************************
void CCharacter::UpdateRotaition(float fX)
{
	// �p�x�̐��K��
	if (m_rotDest.y > D3DX_PI)
	{
		m_rotDest.y = -D3DX_PI + (m_rotDest.y - D3DX_PI);
	}
	else if (m_rotDest.y < -D3DX_PI)
	{
		m_rotDest.y = D3DX_PI + (m_rotDest.y + D3DX_PI);
	}

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI + (m_rot.y - D3DX_PI);
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI + (m_rot.y + D3DX_PI);
	}

	// ���f���̊p�x��ړI�̊p�x�ɋ߂Â���
	float fDiff = m_rotDest.y - m_rot.y;

	if (fDiff > D3DX_PI)
	{
		fDiff = fDiff - D3DX_PI * 2;
	}
	else if (fDiff < -D3DX_PI)
	{
		fDiff = fDiff + D3DX_PI * 2;
	}

	m_rot.y += (fDiff)*fX;
}

//*****************************************
// �L�����N�^�[�_���[�W��Ԃɂ���
//*****************************************
void CCharacter::SetDamageState(int nCntState)
{
	// �_���[�W��Ԃɂ���
	m_pState->SetState(CState::STATE_DAMAGE);

	// �J�E���^�[�ݒ�
	m_pState->SetStateCnt(nCntState);
}
