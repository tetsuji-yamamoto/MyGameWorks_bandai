//***********************************************
// 
// �ۉe
// Author Tetsuji Yamamoto
// 
//***********************************************
#include "shadow.h"
#include "stage.h"
#include "texture.h"
#include "manager.h"
#include "meshField.h"
#include "myMath.h"

//***********************************************
// �ۉe
//***********************************************
CShadow::CShadow() : CObject(CObject::PRIORITY_4)
{
	m_pVtxBuff = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
	memset(m_mtxWorld,0,sizeof(m_mtxWorld)) ;	// ���[���h�}�g���b�N�X
	memset(m_mtxTrans,0,sizeof(m_mtxTrans)) ;	// �g��k���s��
	memset(m_mtxRot,0,sizeof(m_mtxRot)) ;		// ��]�s��
	m_pos = D3DXVECTOR3_NULL ;					// �ʒu
	m_rot = D3DXVECTOR3_NULL ;					// ����
	m_fRadius = 0.0f;							// ���a
}

//***********************************************
// �ۉe
//***********************************************
CShadow::~CShadow()
{
}

//***********************************************
// �ۉe
//***********************************************
HRESULT CShadow::Init(float fRadius)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e��ϐ��̐ݒ�
	m_fRadius = fRadius;
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxTrans);
	D3DXMatrixIdentity(&m_mtxRot);
	 
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
		MessageBox(NULL, "CShadow::Init > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fAddY = 0.5f;

	pVtx[0].pos.x = -fRadius;
	pVtx[0].pos.y = fAddY;
	pVtx[0].pos.z = fRadius;

	pVtx[1].pos.x = fRadius;
	pVtx[1].pos.y = fAddY;
	pVtx[1].pos.z = fRadius;

	pVtx[2].pos.x = -fRadius;
	pVtx[2].pos.y = fAddY;
	pVtx[2].pos.z = -fRadius;

	pVtx[3].pos.x = fRadius;
	pVtx[3].pos.y = fAddY;
	pVtx[3].pos.z = -fRadius;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = D3DXCOLOR_FULL;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//***********************************************
// �ۉe
//***********************************************
void CShadow::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		MessageBox(NULL, " CShadow::Uninit() > ��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//***********************************************
// �ۉe
//***********************************************
void CShadow::Update(void)
{
	// ���b�V���t�B�[���h�擾
	CStage* pStage = CManager::GetStage();
	CMeshField* pMeshField = pStage->GetMeshField();

	// �v�Z�p�x�N�g��
	D3DXVECTOR3 nor;

	// �s�������������
	D3DXMatrixIdentity(&m_mtxRot);

	// ���b�V���Ƃ̔��������
	if (pMeshField->Collision(&m_pos, &nor) == true)
	{
		D3DXVECTOR3 look;
		D3DXVECTOR3 X = {1.0f,0.0f,0.0f};
		D3DXVec3Cross(&look, &nor,&X);
		D3DXVec3Normalize(&look, &look);
		m_mtxRot = CMyMath::ConvertLocalCoordinatesToRotMtx(m_pos, m_pos + look,nor);
	}
}

//***********************************************
// �ۉe
//***********************************************
void CShadow::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXMATRIX mtxTrans;

	// �e�N�X�`���C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	// ������ǉ�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	// �ʒu��ǉ�
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(CTexture::TEXTURE_SHADOW));

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �ݒ�������ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//***********************************************
// �ۉe����
//***********************************************
CShadow* CShadow::Create(float fRadius)
{
	CShadow* pShadow = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�g���ő吔�ɒB���^���������Ȃ�
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	pShadow = new CShadow;
	if (pShadow != NULL)
	{
		// ����������
		pShadow->Init(fRadius);
	}
	else
	{
		MessageBox(NULL, " CShadow::Create() > ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pShadow;
}