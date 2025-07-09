//*************************************
// 
// ���f��
// Author Tetsuji Yamamoto
// 
//*************************************
#include "model.h"
#include "manager.h"
#include "myMath.h"

//*************************************
// ���f��
//*************************************
CModel::CModel()
{
	m_dwNumMat = 0;
	m_apIdxTexture = NULL;
	m_pBuffMat = NULL;
	m_pMesh = NULL;

	ZeroMemory(m_pos, sizeof(D3DXVECTOR3));
	ZeroMemory(m_rot, sizeof(D3DXVECTOR3));
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
	m_pParent = NULL;
}

//*************************************
// ���f��
//*************************************
CModel::~CModel()
{
}

//*************************************
// ���f��
//*************************************
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName)
{

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e��ϐ��̏�����
	m_pos = pos;	// �ʒu
	m_rot = rot;	// ����

	// X�t�@�C���Ǎ�
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
		MessageBox(NULL, "CModel::Init() > ���f����ǂݍ��߂܂���ł���", "Error", MB_OK);

		// ���ʂ�Ԃ�
		return E_FAIL;
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
// ���f��
//*************************************
void CModel::Uninit(void)
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

	if (m_pParent != NULL)
	{// �e���f���̏�񂪂����
		m_pParent = NULL;	// �Y���
	}

	// ���g�̔j��
	delete this;
}

//*************************************
// ���f��
//*************************************
void CModel::Draw(void)
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
// ���f��
//*************************************
void CModel::DrawParentChild(D3DXCOLOR*pCol)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	D3DXMATRIX mtxParent;// �e�}�g���b�N�X

	// �e�}�g���b�N�X���|�����킹��
	if (m_pParent != NULL)
	{// �e������
		mtxParent = m_pParent->GetMatrix();	// �e�}�g���b�N�X�擾
	}
	else
	{// �e�����Ȃ�
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);	// �e�}�g���b�N�X�擾
	}

	// �e�}�g���b�N���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �F������ꍇ
		if (pCol != NULL)
		{
			// �F��ύX
			D3DXMATERIAL pMatValue = pMat[nCntMat];
			pMatValue.MatD3D.Diffuse.r = pCol->r;
			pMatValue.MatD3D.Diffuse.g = pCol->g;
			pMatValue.MatD3D.Diffuse.b = pCol->b;
			pMatValue.MatD3D.Diffuse.a = pCol->a;

			// �ݒ�
			pDevice->SetMaterial(&pMatValue.MatD3D);
		}
		// �Ȃ��ꍇ
		else
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		}

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTexture->GetAddress(m_apIdxTexture[nCntMat]));

		// ���f��(�p�[�c�̕`��)
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//*************************************
// ���f��
//*************************************
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pXFileName)
{
	CModel* pModel = NULL;

	// �������m��
	pModel = new CModel;
	if (pModel != NULL)
	{
		// ����������
		if (pModel->Init(pos, rot, pXFileName) == E_FAIL)
		{
			delete pModel;
			pModel = NULL;
		}
	}
	else
	{
		MessageBox(NULL, "CModel::Create() > if ( pObjectX != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pModel;
}

//*************************************
// ���f���̓����x�ύX
//*************************************
void CModel::SetAlphaColor(float fAlphar)
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

//************************************************
// ���f�����}�E�X�ɓ������Ă��邩���ׂ�
//************************************************
bool CModel::CollisionMouse(float fRadius)
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