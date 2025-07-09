//*************************************
// 
// �I�u�W�F�N�gX
// Author Tetsuji Yamamoto
// 
//*************************************
#include "objectX.h"
#include "manager.h"

//*************************************
// �I�u�W�F�N�gX����
//*************************************
CObjectX::CObjectX()
{
	m_apIdxTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
}

//*************************************
// �I�u�W�F�N�gX����
//*************************************
CObjectX::~CObjectX()
{
}

//*************************************
// �I�u�W�F�N�gX����
//*************************************
HRESULT CObjectX::Init(const char *pXFileName)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �I�u�W�F�N�g�^�C�v�ݒ�
	CObject::SetType(CObject::TYPE_MODEL_X);

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
		MessageBox(NULL, "InitModel() > ���fWS����ǂݍ��߂܂���ł���", "Error", MB_OK);
	}

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

	// ���ʂ�Ԃ�
	return S_OK;
}

//*************************************
// �I�u�W�F�N�gX����
//*************************************
void CObjectX::Uninit(void)
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

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}

//*************************************
// �I�u�W�F�N�gX����
//*************************************
void CObjectX::Update(void)
{

}

//*************************************
// �I�u�W�F�N�gX����
//*************************************
void CObjectX::Draw(void)
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
// �I�u�W�F�N�gX����
//*************************************
void CObjectX::Draw(D3DXMATRIX* pMtxPearent)
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
// �I�u�W�F�N�gX����
//*************************************
CObjectX* CObjectX::Create(const char* pXFileName)
{
	CObjectX* pObjectX = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�gX�̐���
	if (pObjectX == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pObjectX = new CObjectX;
		if (pObjectX != NULL)
		{
			// ����������
			pObjectX->Init(pXFileName);
		}
		else
		{
			MessageBox(NULL, "CObjectX::Create() > if ( pObjectX != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObjectX::Create() > if ( pObjectX == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pObjectX;
}
