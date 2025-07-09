//**************************************************************
// 
// �����蔻��
// Author Tetsuji Yamamoto
// 
//**************************************************************
#include "collision.h"
#include "manager.h"
#include "input.h"

// �ÓI�����o�[�ϐ��錾
bool CCollision::m_bDraw = false;	// �\���̗L��

//--------------------------------------------------------------
// �����蔻��N���X

//**************************************************************
// �����蔻��R���X�g���N�^
//**************************************************************
CCollision::CCollision()
{
	m_bTrigger = false;								// ���������u�Ԃ��ǂ���
	m_pos = D3DXVECTOR3_NULL;						// �ʒu
	m_posOffset = D3DXVECTOR3_NULL;					// �ʒu�I�t�Z�b�g
	ZeroMemory(&m_mtxWorld,sizeof(D3DXMATRIX)) ;	// �}�g���b�N�X
}

//**************************************************************
// �����蔻��R���X�g���N�^
//**************************************************************
CCollision::~CCollision()
{
}

//**************************************************************
// �����蔻�菈��
//**************************************************************
void CCollision::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger)
{
	m_bTrigger = bTrigger;	// ���������u�Ԃ��ǂ���
	m_posOffset = pos;		// �ʒu�I�t�Z�b�g
}

//**************************************************************
// �����蔻�菈��
//**************************************************************
void CCollision::Uninit(void)
{
	// ���g�̔j��
	CObject::Release();
}

//**************************************************************
// �����蔻�菈��
//**************************************************************
D3DXMATRIX CCollision::Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
	D3DXMATRIX mtxRotParnt, mtxTransParnt, mtxWorldParnt;
	D3DXVECTOR3 rot = D3DXVECTOR3_NULL;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorldParnt);

	// ������ǉ�
	D3DXMatrixRotationYawPitchRoll(&mtxRotParnt, rotParent.y, rotParent.x, rotParent.z);
	D3DXMatrixMultiply(&mtxWorldParnt, &mtxWorldParnt, &mtxRotParnt);

	// �ʒu��ǉ�
	D3DXMatrixTranslation(&mtxTransParnt, posParent.x, posParent.y, posParent.z);
	D3DXMatrixMultiply(&mtxWorldParnt, &mtxWorldParnt, &mtxTransParnt);


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ������ǉ�
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu��ǉ�
	D3DXMatrixTranslation(&mtxTrans, m_posOffset.x, m_posOffset.y, m_posOffset.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// �e�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxWorldParnt);

	// �ʒu���X�V
	m_pos.x = mtxWorld._41;
	m_pos.y = mtxWorld._42;
	m_pos.z = mtxWorld._43;

	// ���ʂ�Ԃ�
	return mtxWorld;
}

//**************************************************************
// �����蔻��X�V����
//**************************************************************
D3DXMATRIX CCollision::Update(D3DXMATRIX mtxParent)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;
	D3DXVECTOR3 rot = D3DXVECTOR3_NULL;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ������ǉ�
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu��ǉ�
	D3DXMatrixTranslation(&mtxTrans, m_posOffset.x, m_posOffset.y, m_posOffset.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// �e�Ɗ|�����킹��s
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

	// �ʒu���X�V
	m_pos.x = mtxWorld._41;
	m_pos.y = mtxWorld._42;
	m_pos.z = mtxWorld._43;

	// ���ʂ�Ԃ�
	return mtxWorld;
}

//**************************************************************
// �����蔻��`�揈��
//**************************************************************
void CCollision::Draw(void)
{

}

//**************************************************************
// ���̓����蔻��
//**************************************************************
void CCollision::IsDraw(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();

	// �\���̗L����؂�ւ���
	if (pInputKeyboard->GetTrigger(DIK_F6) == true)
	{
		m_bDraw = !m_bDraw;
	}
}

//--------------------------------------------------------------
// ���̓����蔻��N���X

//**************************************************************
// ���̓����蔻��R���X�g���N�^
//**************************************************************
CCollisionSpher::CCollisionSpher()
{
	m_pSpher = NULL;	// �\���p�̋�
	m_fRadius = 0.0f;	// ���a
	m_nIdxModel = 0;	// ���f���C���f�b�N�X
}

//**************************************************************
// ���̓����蔻��f�X�g���N�^
//**************************************************************
CCollisionSpher::~CCollisionSpher()
{
}

//**************************************************************
// ���̓����蔻��
//**************************************************************
HRESULT CCollisionSpher::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger,float fRadius, int nIdxModel)
{
	// �f�o�b�O���[�h���̂ݎ��s
#ifdef _DEBUG
	// ���̐���
	m_pSpher = CSphere::Create(8,8,fRadius,D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),NULL);
#endif

	// �����蔻���񏉊���
	CCollision::Init(pos,rot,bTrigger);

	// ���a�ݒ�
	m_fRadius = fRadius;

	// �C���f�b�N�X�ݒ�
	m_nIdxModel = nIdxModel;

	return S_OK;
}

//**************************************************************
// ���̓����蔻��
//**************************************************************
void CCollisionSpher::Uninit(void)
{
	// �f�o�b�O���[�h�����̂ݎ��s
#ifdef _DEBUG
	// ���̔j��
	if (m_pSpher != NULL)
	{
		m_pSpher->Uninit();
		m_pSpher = NULL;
	}
 #endif

	// ���g�̔j��
	CCollision::Uninit();
}

//**************************************************************
// ���̓����蔻��X�V
//**************************************************************
void CCollisionSpher::Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent)
{
	// �}�g���b�N�X�ňʒu�X�V
	D3DXMATRIX mtxWorld = CCollision::Update(posParent, rotParent);

	// �f�o�b�O���[�h���̂ݎ��s
#ifdef _DEBUG
	m_pSpher->SetMatrix(mtxWorld);
#endif
}

//**************************************************************
// ���̓����蔻��X�V
//**************************************************************
void CCollisionSpher::Update(D3DXMATRIX mtxParent)
{
	// �}�g���b�N�X�ňʒu�X�V
	D3DXMATRIX mtxWorld = CCollision::Update(mtxParent);

	// �f�o�b�O���[�h���̂ݎ��s
#ifdef _DEBUG
	m_pSpher->SetMatrix(mtxWorld);
#endif
}


//**************************************************************
// ���̓����蔻��
//**************************************************************
void CCollisionSpher::Draw(void)
{
	// �f�o�b�O���[�h���̂ݎ��s
#ifdef _DEBUG

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �`�悵�ėǂ���ԂȂ��
	if (CCollision::GetIsDraw() == true)
	{
		// ���C���[�t���[���I��
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		// ���̕`��
		m_pSpher->Draw();

		// ���C���[�t���[���I�t
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
#endif
}

//**************************************************************
// ���̓����蔻�萶��
//**************************************************************
CCollisionSpher* CCollisionSpher::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, int nIdxModel)
{
	// ���̓����蔻��|�C���^�[
	CCollisionSpher* pColiSpher = NULL;

	// �I�u�W�F�N�g�̑S�̐��擾
	int nNumAll = CObject::GetObujectNumAll();

	// �I�u�W�F�N�g�̍ő吔�����炢�Ȃ��悤�ɂ���
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// ���̓����蔻��C���X�^���X����
	pColiSpher = new CCollisionSpher;

	// �������̊m�ۂ��ł����Ȃ�
	if (pColiSpher != NULL)
	{
		// ����������
		pColiSpher->Init(pos,rot,bTrigger,fRadius, nIdxModel);
	}
	// �ł��Ȃ�����
	else
	{
		// ���b�Z�[�W�\��
		MessageBox(NULL, " CCollisionSpher::Create() > ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// ���ʂ�Ԃ�
	return pColiSpher;
}

//-----------------------------------------------------------------
// �~���̓����蔻��

//**************************************************************
// �~���̓����蔻��R���X�g���N�^
//**************************************************************
CCollisionCylinder::CCollisionCylinder()
{
	m_pCylinder = NULL;	// �\���p�̉~��
	m_fRadius = 0.0f;	// ���a
	m_fHeight = 0.0f;	// ����
}

//**************************************************************
// �~���̓����蔻��f�X�g���N�^
//**************************************************************
CCollisionCylinder::~CCollisionCylinder()
{
}

//**************************************************************
// �~���̓����蔻�菉����
//**************************************************************
HRESULT CCollisionCylinder::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, float fHeight)
{
	// �f�o�b�O���[�h���̂ݎ��s
#ifdef _DEBUG
	// �~���̐���
	m_pCylinder = CCylinder::Create(D3DXVECTOR3_NULL,8, 1, fRadius,fHeight, D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), NULL);
#endif

	// �����蔻���񏉊���
	CCollision::Init(pos, rot, bTrigger);

	// ���a�ƍ����ݒ�
	m_fRadius = fRadius;
	m_fHeight = fHeight;

	return S_OK;
}

//**************************************************************
// �~���̓����蔻��I��
//**************************************************************
void CCollisionCylinder::Uninit(void)
{
	// �f�o�b�O���[�h���̂ݎ��s
#ifdef _DEBUG
	// ���̔j��
	if (m_pCylinder != NULL)
	{
		m_pCylinder->Uninit();
		m_pCylinder = NULL;
	}
#endif

	// ���g�̔j��
	CCollision::Uninit();
}

//**************************************************************
// �~���̓����蔻��X�V
//**************************************************************
void CCollisionCylinder::Update(D3DXVECTOR3 posParent, D3DXVECTOR3 rotParent)
{
	// �}�g���b�N�X�ňʒu�X�V
	D3DXMATRIX mtxWorld = CCollision::Update(posParent, rotParent);

	// �f�o�b�O���[�h���̂ݎ��s
#ifdef _DEBUG
	m_pCylinder->SetMatrix(mtxWorld);
#endif
}

//**************************************************************
// �~���̓����蔻��`��
//**************************************************************
void CCollisionCylinder::Draw(void)
{
	// �f�o�b�O���[�h���̂ݎ��s
#ifdef _DEBUG

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �`�悵�ėǂ���ԂȂ��
	if (CCollision::GetIsDraw() == true)
	{
		// ���C���[�t���[���I��
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		// ���̕`��
		m_pCylinder->Draw();

		// ���C���[�t���[���I�t
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
#endif
}

//**************************************************************
// �~���̓����蔻�萶��
//**************************************************************
CCollisionCylinder* CCollisionCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bTrigger, float fRadius, float fHeight)
{
	// �~���̓����蔻��|�C���^�[
	CCollisionCylinder* pColiCyli = NULL;

	// �I�u�W�F�N�g�̑S�̐��擾
	int nNumAll = CObject::GetObujectNumAll();

	// �I�u�W�F�N�g�̍ő吔�����炢�Ȃ��悤�ɂ���
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// �~���̓����蔻��C���X�^���X����
	pColiCyli = new CCollisionCylinder;

	// �������̊m�ۂ��ł����Ȃ�
	if (pColiCyli != NULL)
	{
		// ����������
		pColiCyli->Init(pos, rot, bTrigger, fRadius, fHeight);
	}
	// �ł��Ȃ�����
	else
	{
		// ���b�Z�[�W�\��
		MessageBox(NULL, " CCollisionCylinder::Create() > ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// ���ʂ�Ԃ�
	return pColiCyli;
}