//*************************************
//
// �I�u�W�F�N�g3D
// Author Tetsuji Yamamoto
//
//*************************************
#include "object3D.h"
#include "manager.h"
#include "camera.h"

//*************************************
// �I�u�W�F�N�g�R���X�g���N�^
//*************************************
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;
	ZeroMemory(m_mtxWorld,sizeof(m_mtxWorld));
	m_nIdxTexture = -1;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//*************************************
// �I�u�W�F�N�g�f�X�g���N�^
//*************************************
CObject3D::~CObject3D()
{

}

//*************************************
// �I�u�W�F�N�g����������
//*************************************
HRESULT CObject3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,float fWidth,float fHeight,float fDepth,const char *pTexturePass)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	
	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e��ϐ��̐ݒ�
	m_pos = pos;
	m_rot = rot;
	m_col = col;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fDepth = fDepth;

	// ���_�o�b�t�@�̐���
	HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CObject3D::Init > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	m_nIdxTexture = pTexture->Register(pTexturePass);

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = -fWidth;
	pVtx[0].pos.y = fHeight;
	pVtx[0].pos.z = fDepth;

	pVtx[1].pos.x = fWidth;
	pVtx[1].pos.y = fHeight;
	pVtx[1].pos.z = fDepth;

	pVtx[2].pos.x = -fWidth;
	pVtx[2].pos.y = -fHeight;
	pVtx[2].pos.z = -fDepth;

	pVtx[3].pos.x = fWidth;
	pVtx[3].pos.y = -fHeight;
	pVtx[3].pos.z = -fDepth;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �|���S���̉������߂�
	D3DXVECTOR3 nor,edge0, edge1;
	edge0 = pVtx[1].pos - pVtx[0].pos;
	edge1 = pVtx[2].pos - pVtx[0].pos;

	// �O�ςŖ@�������߂�
	D3DXVec3Cross(&nor, &edge0, &edge1);

	pVtx[0].nor = nor;
	pVtx[1].nor = nor;
	pVtx[2].nor = nor;
	pVtx[3].nor = nor;
	
	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = col;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*************************************
// �I�u�W�F�N�g�I������
//*************************************
void CObject3D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		MessageBox(NULL, " CObject2D::Uninit() > if (m_pVtxBuff != NULL) ��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	Release();
}

//*************************************
// �I�u�W�F�N�g�X�V����
//*************************************
void CObject3D::Update(void)
{

}

//*************************************
// �I�u�W�F�N�g�`�揈��
//*************************************
void CObject3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

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

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//*************************************
// �I�u�W�F�N�g�`�揈��
//*************************************
void CObject3D::DrawNoTexture(void)
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

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}


//*************************************
// �I�u�W�F�N�g��������
//*************************************
void CObject3D::SetColor(D3DXCOLOR col)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = col;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//*************************************
// �I�u�W�F�N�g���_�擾����
//*************************************
D3DXVECTOR3 CObject3D::GetVtxPos(int nNumVtx)
{
	// �߂�l�p�ϐ�
	D3DXVECTOR3 posReturn = D3DXVECTOR3_NULL;

	// ���_�ԍ����͈͊O�ł���Ώ������Ȃ�
	if (nNumVtx < 0 || nNumVtx >= 4)
	{
		return posReturn;
	}

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

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 posVtx = pVtx[nNumVtx].pos;

	// �ʒu�ݒ�
	posReturn.x = (posVtx.x * m_mtxWorld._11) + (posVtx.y * m_mtxWorld._21) + (posVtx.z * m_mtxWorld._31) + (1.0f * m_mtxWorld._41);
	posReturn.y = (posVtx.x * m_mtxWorld._12) + (posVtx.y * m_mtxWorld._22) + (posVtx.z * m_mtxWorld._32) + (1.0f * m_mtxWorld._42);
	posReturn.z = (posVtx.x * m_mtxWorld._13) + (posVtx.y * m_mtxWorld._23) + (posVtx.z * m_mtxWorld._33) + (1.0f * m_mtxWorld._43);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return posReturn;
}

//*************************************
// �I�u�W�F�N�g��������
//*************************************
CObject3D* CObject3D::Create(void)
{
	CObject3D* pObject3D = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�g2D�̐���
	if (pObject3D == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pObject3D = new CObject3D;
		if (pObject3D != NULL)
		{
			// ����������
			pObject3D->Init();
		}
		else
		{
			MessageBox(NULL, " CObject3D::Create() > if ( pObject3D != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObject3D::Create() > if ( pObject3D == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pObject3D;
}