//*************************************
//
// �I�u�W�F�N�g�r���{�[�h�r���{�[�h
// Author Tetsuji Yamamoto
//
//*************************************
#include "objectBillboard.h"
#include "manager.h"
#include "camera.h"

//*************************************
// �I�u�W�F�N�g�r���{�[�h�R���X�g���N�^
//*************************************
CObjectBillboard::CObjectBillboard()
{
	m_pVtxBuff = NULL;
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));
	m_nIdxTexture = -1;
}

//*************************************
// �I�u�W�F�N�g�r���{�[�h�f�X�g���N�^
//*************************************
CObjectBillboard::~CObjectBillboard()
{

}

//*************************************
// �I�u�W�F�N�g�r���{�[�h����������
//*************************************
HRESULT CObjectBillboard::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CObjectBillboard::Init > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	m_nIdxTexture = pTexture->Register("data\\texture\\IMG_4953.JPG");

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = -50.0f;
	pVtx[0].pos.y = 50.0f;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = 50.0f;
	pVtx[1].pos.y = 50.0f;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -50.0f;
	pVtx[2].pos.y = -50.0f;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = 50.0f;
	pVtx[3].pos.y = -50.0f;
	pVtx[3].pos.z = 0.0f;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*************************************
// �I�u�W�F�N�g�r���{�[�h�I������
//*************************************
void CObjectBillboard::Uninit(void)
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
// �I�u�W�F�N�g�r���{�[�h�X�V����
//*************************************
void CObjectBillboard::Update(void)
{

}

//*************************************
// �I�u�W�F�N�g�r���{�[�h�`�揈��
//*************************************
void CObjectBillboard::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxview;
	pDevice->GetTransform(D3DTS_VIEW, &mtxview);

	// �J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxview._11;
	m_mtxWorld._12 = mtxview._21;
	m_mtxWorld._13 = mtxview._31;
	m_mtxWorld._21 = mtxview._12;
	m_mtxWorld._22 = mtxview._22;
	m_mtxWorld._23 = mtxview._32;
	m_mtxWorld._31 = mtxview._13;
	m_mtxWorld._32 = mtxview._23;
	m_mtxWorld._33 = mtxview._33;

	m_mtxWorld._42 = 100.0f;

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
// �I�u�W�F�N�g�r���{�[�h��������
//*************************************
CObjectBillboard* CObjectBillboard::Create(void)
{
	CObjectBillboard* pObjectBill = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�g�r���{�[�h2D�̐���
	if (pObjectBill == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pObjectBill = new CObjectBillboard;
		if (pObjectBill != NULL)
		{
			// ����������
			pObjectBill->Init();
		}
		else
		{
			MessageBox(NULL, " CObjectBillboard::Create() > if ( pObjectBill != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObjectBillboard::Create() > if ( pObjectBill == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pObjectBill;
}