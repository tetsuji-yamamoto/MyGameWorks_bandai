//****************************************************************************
// 
// �w�i
// Author tetuji yamamoto
// 
//****************************************************************************
#include "number.h"
#include "renderer.h"
#include "object2D.h"
#include "manager.h"

//****************************************************************************
// ����
//****************************************************************************
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_nNowNumber = 0;
	m_nIdxTexture = 0;
}

//****************************************************************************
// ����
//****************************************************************************
CNumber::~CNumber()
{
}

//****************************************************************************
// ����
//****************************************************************************
void CNumber::Init(D3DXVECTOR3 pos, D3DXCOLOR col,float fWidth, float fHeight, int nNumber)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	HRESULT hr;

	hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CREnderer::InitPoligon > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
	}

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = pos.x - fWidth;
	pVtx[0].pos.y = pos.y - fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + fWidth;
	pVtx[1].pos.y = pos.y - fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x - fWidth;
	pVtx[2].pos.y = pos.y + fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + fWidth;
	pVtx[3].pos.y = pos.y + fHeight;
	pVtx[3].pos.z = 0.0f;

	// �������Z�b�g
	SetNumber(nNumber);

	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	m_nIdxTexture = pTexture->Register(TEXTURE_FILE_PASS_NUMBER);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = col;
		pVtx[nCntVtx].rhw = 1.0f;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//****************************************************************************
// ����
//****************************************************************************
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		MessageBox(NULL, " CNumber::Uninit() > if (m_pVtxBuff != NULL) ��������NULL�ł͂���܂���", "Error", MB_OK);
	}
}

//****************************************************************************
// ����
//****************************************************************************
void CNumber::Update(void)
{

}

//****************************************************************************
// ����
//****************************************************************************
void CNumber::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//****************************************************************************
// ����
//****************************************************************************
CNumber* CNumber::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nNumber)
{
	CNumber* pNumber = NULL;
	int nNumAll = CObject::GetObujectNumAll();

	// �G�t�F�N�g�V���b�N�̐���
	if (pNumber == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pNumber = new CNumber;

		if (pNumber != NULL)
		{
			// ����������
			pNumber->Init(pos, col,fWidth, fHeight,nNumber);	// ����������
		}
		else
		{
			MessageBox(NULL, " CNumber* CNumber::Create() > if ( pNumber != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CNumber* CNumber::Create() > if ( pNumber == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pNumber;
}

//****************************************************************************
// ����
//****************************************************************************
void CNumber::SetNumber(int nNumber)
{
	m_nNowNumber = nNumber;

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fDigitWidth = 1.0f / 10;

	pVtx[0].tex = D3DXVECTOR2(0.0f + fDigitWidth * nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fDigitWidth + fDigitWidth * nNumber, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fDigitWidth * nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fDigitWidth + fDigitWidth * nNumber, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}