//*************************************
// 
// �I�u�W�F�N�g�X�e�[�W
// Author Tetsuji Yamamoto
// 
//*************************************
#include "objectStage.h"
#include "manager.h"
#include "myMath.h"

//*************************************
// �I�u�W�F�N�g�X�e�[�W����
//*************************************
CObjectStage::CObjectStage()
{
	m_apIdxTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
}

//*************************************
// �I�u�W�F�N�g�X�e�[�W����
//*************************************
CObjectStage::~CObjectStage()
{
}

//*************************************
// �I�u�W�F�N�g�X�e�[�W����
//*************************************
HRESULT CObjectStage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e��ϐ��̏�����
	m_pos = pos;
	m_rot = rot;

	HRESULT hr;
	hr = D3DXLoadMeshFromX(
		pXFileName,
		D3DXMESH_MANAGED,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh
	);

	if (FAILED(hr))
	{// ���s������
		MessageBox(NULL, "CObjectStage::Init() > ���f����ǂݍ��߂܂���ł���", "Error", MB_OK);
	}
	else
	{
		//�}�e���A���ӂ̃|�C���^���擾
		D3DXMATERIAL* pMat;
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		// �e�N�X�`���C���f�b�N�X�̃������m��
		m_apIdxTexture = new int[(int)m_dwNumMat];

		// �}�e���A���̐�����
		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			m_apIdxTexture[nCntMat] = pTexture->Register((const char*)pMat[nCntMat].pTextureFilename);
		}
	}

	// ���ʂ�Ԃ�
	return S_OK;
}

//*************************************
// �I�u�W�F�N�g�X�e�[�W����
//*************************************
void CObjectStage::Uninit(void)
{
	// �}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// ���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �e�N�X�`���C���f�b�N�X�̔j��
	if (m_apIdxTexture != NULL)
	{
		delete[] m_apIdxTexture;
		m_apIdxTexture = NULL;
	}

	// �������g��j��
	delete this;
}

//*************************************
// �I�u�W�F�N�g�X�e�[�W����
//*************************************
void CObjectStage::Update(void)
{

}

//*************************************
// �I�u�W�F�N�g�X�e�[�W����
//*************************************
void CObjectStage::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ������ǉ�
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu��ǉ�
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTexture->GetAddress(m_apIdxTexture[nCntMat]));

		// ���f��(�p�[�c�̕`��)
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//*************************************
// �I�u�W�F�N�g�X�e�[�W����
//*************************************
void CObjectStage::Draw(D3DXMATRIX* pMtxPearent)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (pMtxPearent != NULL)
	{
		m_mtxWorld = *pMtxPearent;
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTexture->GetAddress(m_apIdxTexture[nCntMat]));

		// ���f��(�p�[�c�̕`��)
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}


//*************************************
// �I�u�W�F�N�g�X�e�[�W����
//*************************************
CObjectStage* CObjectStage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName)
{
	CObjectStage* pObjectStage = NULL;

	// �I�u�W�F�N�g�X�e�[�W�̐���
	if (pObjectStage == NULL)
	{
		pObjectStage = new CObjectStage;
		if (pObjectStage != NULL)
		{
			// ����������
			pObjectStage->Init(pos, rot, pXFileName);
		}
		else
		{
			MessageBox(NULL, "CObjectStage::Create() > if ( pObjectStage != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObjectStage::Create() > if ( pObjectStage == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pObjectStage;
}

//************************************************
// �I�u�W�F�N�g�X�e�[�W���}�E�X�ɓ������Ă��邩���ׂ�
//************************************************
bool CObjectStage::CollisionMouse(float fRadius)
{
	// �}�E�X�擾
	CInputMouse* pInputMouse = CManager::GetInputMouse();

	// �ϊ���̈ʒu
	D3DXVECTOR3 pos2D;

	// �}�E�X�̍��W�擾
	D3DXVECTOR3 posMouse = pInputMouse->GetPosition();

	// ���W��2D���ʍ��W�ɕϊ�
	CMyMath::Posision3Dto2D(&pos2D, m_pos);

	D3DXVECTOR2 posA = { pos2D.x, pos2D.y };
	D3DXVECTOR2 posB = { posMouse.x, posMouse.y };

	// �}�E�X��2D�ʒu���d�Ȃ��Ă�����
	if (CMyMath::ColiisionCircleCircle2D(posA, fRadius, posB, 0.0f) == true)
	{
		// �������Ă��锻��
		return true;
	}

	// �������Ă����Ȃ�����
	return false;

}

//*************************************
// �I�u�W�F�N�g�̂̓����x�ύX
//*************************************
void CObjectStage::SetAlphaColor(float fAlphar)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Diffuse.a = fAlphar;
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
	}
}
