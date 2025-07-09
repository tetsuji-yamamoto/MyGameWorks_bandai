//*********************************************
// 
// �V�����_�[�w�i
// Author Tetsuji Yamamoto
// 
//*********************************************
#include "cylinderBG.h"
#include "myMath.h"
#include "texture.h"
#include "manager.h"

//*********************************************
// �V�����_�[�R���X�g���N�^
//*********************************************
CCylinderBG::CCylinderBG()
{
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_nIdxTexture = -1;		// �e�N�X�`���ւ̃C���f�b�N�X
	m_nNumPolygon = 0;		// �|���S����
	m_nNumVtx = 0;			// ���_��
	m_nNumIdx = 0;			// �C���f�b�N�X��
}

//*********************************************
// �V�����_�[�f�X�g���N�^
//*********************************************
CCylinderBG::~CCylinderBG()
{
}

//*********************************************
// �V�����_�[������
//*********************************************
HRESULT CCylinderBG::Init(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fRadius, float fheight)
{
	// ���������[���ȉ��ɂȂ�Ȃ��悤�ɂ���
	if (nDivisionX <= 0)
	{
		nDivisionX = 1;
	}

	if (nDivisionY <= 0)
	{
		nDivisionY = 1;
	}

	// �t�B�[���h�����̃|���S����
	m_nNumPolygon = CMyMath::SeekFieldNumPolygonAll(nDivisionX, nDivisionY);

	// �t�B�[���h�̒��_��
	m_nNumVtx = CMyMath::SeekFieldNumVertexAll(nDivisionX, nDivisionY);

	// �t�B�[���h�̃C���f�b�N�X��
	m_nNumIdx = CMyMath::SeekFieldNumIndexAll(m_nNumPolygon);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���_�𐶐�
	HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CCylinderBG::Init > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_pIdxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CCylinderBG::Init > �C���f�b�N�X�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	m_nIdxTexture = pTexture->Register("data\\texture\\mountain002.png");


	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fAngleX = (D3DX_PI * 2.0f) / nDivisionX;
	float fAngleY = D3DX_PI / nDivisionY;
	int nCntVtx = 0;

	float fStartPosY = (startPos.y + fheight * 0.5f);

	for (int nCntY = 0; nCntY <= nDivisionY; nCntY++)
	{
		for (int nCntX = 0; nCntX <= nDivisionX; nCntX++, nCntVtx++)
		{
			float fPosY = (fheight / (float)nDivisionY + 1) * nCntY;	// Y���W
			float fTexX = (1.0f / (float)nDivisionX) * (float)nCntX;	// �e�N�X�`�����WX
			float fTexY = 1.0f / (float)nDivisionY * (float)nCntY;		// �e�N�X�`�����WY

			pVtx[nCntVtx].pos.x = startPos.x + sinf(fAngleX * nCntX) * fRadius;
			pVtx[nCntVtx].pos.y = -fPosY + fStartPosY;
			pVtx[nCntVtx].pos.z = startPos.z + cosf(fAngleX * nCntX) * fRadius;
			pVtx[nCntVtx].tex.x = fTexX;
			pVtx[nCntVtx].tex.y = fTexY;

			// �e���_�̖@���̐ݒ�,�ʂɑ΂��Đ���
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// �C���f�b�N���ւ̃|�C���^
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nIdxA = nDivisionX + 1;	// �����C���f�b�N�X
	int nIdxB = 0;				// �E���C���f�b�N�X
	int nCntIdx = 0;			// �C���f�b�N�X�J�E���^�[

	// �C���f�b�N�X�����߂�
	for (int nCntA = 0; nCntA < nDivisionY; nCntA++)
	{// Z�̕���������
		for (int nCntB = 0; nCntB <= nDivisionX; nCntB++)
		{// X�̕���������
			pIdx[nCntIdx] = nIdxA;
			pIdx[nCntIdx + 1] = nIdxB;
			nCntIdx += 2;
			nIdxA++;
			nIdxB++;
		}

		if (nCntA < nDivisionY - 1)
		{// ���S���u
			pIdx[nCntIdx] = nIdxB - 1;
			pIdx[nCntIdx + 1] = nIdxA;
			nCntIdx += 2;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//*********************************************
// �V�����_�[�I��
//*********************************************
void CCylinderBG::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// ���_�C���f�b�N�X�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �j���Ɏ��s���Ă���
	if (m_pVtxBuff != NULL || m_pIdxBuff != NULL)
	{
		MessageBox(NULL, "  CCylinderBG::Uninit() > ��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �����̃I�u�W�F�N�g��j��
	Release();
}

//*********************************************
// �V�����_�[�X�V
//*********************************************
void CCylinderBG::Update(void)
{

}

//*********************************************
// �V�����_�[�`��
//*********************************************
void CCylinderBG::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���}�g���b�N�X
	D3DXMATRIX mtxWorld;

	// �}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_nNumVtx,
		0,
		m_nNumPolygon
	);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//**************************************
// �V�����_�[����
//**************************************
CCylinderBG* CCylinderBG::Create(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fRadius, float fheight)
{
	CCylinderBG* pCylinder = NULL;						// �V�����_�[�|�C���^�[
	int nNumAll = CObject::GetObujectNumAll();	// �I�u�W�F�N�g�̑S�̐��擾

	// �I�u�W�F�N�g�̍ő吔�𒴂��Ă��Ȃ���ΐ�������
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// �V�����_�[�̐���
	pCylinder = new CCylinderBG;
	if (pCylinder != NULL)
	{
		// ����������
		pCylinder->Init(startPos, nDivisionX, nDivisionY, fRadius, fheight);
	}
	else
	{
		MessageBox(NULL, " CCylinderBG::Create() > ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pCylinder;
}