//**************************************
// 
// ��
// Author Tetsuji Yamamoto
// 
//**************************************
#include "sky.h"
#include "texture.h"
#include "manager.h"
#include "myMath.h"

//**************************************
// ��R���X�g���N�^
//**************************************
CSky::CSky() : CObject(CObject::PRIORITY_0)
{
	m_pVtxBuff = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;							// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	ZeroMemory(m_mtxWorld, sizeof(m_mtxWorld));	// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3_NULL;					// �ʒu
	m_nIdxTexture = -1;							// �e�N�X�`���ւ̃C���f�b�N�X
	m_nNumPolygonMeshField = 0;					// ���b�V���̃|���S���̐�
	m_nNumVtx = 0;								// ���_��
	m_nNumVtxFan = 0;							// ���̒��_�̐�
	m_nNumVtxMeshField = 0;						//���b�V���̒��_�̐�
	m_nNumIdx = 0;								// �C���f�b�N�X��
	m_nNumIdxFan = 0;							// �t�@���̃C���f�b�N��
	m_nNumIdxMeshField = 0;						// ���b�V���t�B�[���h�̃C���f�b�N�X��
	m_nDivisionX = 0;							// ������X
	m_nDivisionY = 0;							// ������Y
}

//**************************************
// ��f�X�g���N�^
//**************************************
CSky::~CSky()
{
}

//**************************************
// �󏉊���
//**************************************
HRESULT CSky::Init(int nDivisionX, int nDivisionY, float fRadius)
{

	// �����𒴂��Ȃ��悤����
	if (nDivisionX < 3)
	{
		nDivisionX = 1;
	}

	// �����𒴂��Ȃ��悤����
	if (nDivisionY < 3)
	{
		nDivisionY = 1;
	}

	m_nDivisionX = nDivisionX;
	m_nDivisionY = nDivisionY;

	// �t�B�[���h�����̃|���S����
	m_nNumPolygonMeshField = CMyMath::SeekFieldNumPolygonAll(nDivisionX, nDivisionY - 2);

	// �t�B�[���h�����̃C���f�b�N�X��
	m_nNumIdxMeshField = CMyMath::SeekFieldNumIndexAll(m_nNumPolygonMeshField);

	// �t�@���̃C���f�b�N�X��
	m_nNumIdxFan = CMyMath::SeekFanNumIndexAll(nDivisionX);

	// ���ׂẴC���f�b�N�X��
	m_nNumIdx = m_nNumIdxMeshField + (m_nNumIdxFan * 2);

	// ���_�������߂�
	m_nNumVtxMeshField = CMyMath::SeekFieldNumVertexAll(nDivisionX, nDivisionY - 2);
	m_nNumVtxFan = nDivisionX + 2;
	m_nNumVtx = m_nNumVtxMeshField + 2;


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
		MessageBox(NULL, "CSky::Init > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
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
		MessageBox(NULL, "CSky::Init > �C���f�b�N�X�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	m_nIdxTexture = pTexture->Register("data\\texture\\sky001.jpg");

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fAngleX = (D3DX_PI * 2.0f) / nDivisionX;
	float fAngleY = D3DX_PI / nDivisionY;
	int nIdxVtx = 1;

	pVtx[0].pos = D3DXVECTOR3(0.0f, fRadius, 0.0f);
	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);


	for (int nCntY = 1; nCntY < nDivisionY; nCntY++)
	{
		float fRadiusXZ = sinf(fAngleY * nCntY) * fRadius;
		for (int nCntX = 0; nCntX <= nDivisionX; nCntX++, nIdxVtx++)
		{
			float fTexX = (1.0f / (float)nDivisionX) * (float)nCntX;	// �e�N�X�`�����WX
			float fTexY = 1.0f / (float)nDivisionY * (float)nCntY;		// �e�N�X�`�����WY
			pVtx[nIdxVtx].pos.x = sinf(fAngleX * nCntX) * fRadiusXZ;
			pVtx[nIdxVtx].pos.y = cosf(fAngleY * nCntY) * fRadius;
			pVtx[nIdxVtx].pos.z = cosf(fAngleX * nCntX) * fRadiusXZ;
			pVtx[nIdxVtx].tex.x = fTexX;
			pVtx[nIdxVtx].tex.y = fTexY;
		}
	}

	// ��ԉ��̓_
	pVtx[m_nNumVtx - 1].pos = D3DXVECTOR3(0.0f, -fRadius, 0.0f);
	pVtx[m_nNumVtx - 1].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�̐�����
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		pVtx[nCntVtx].nor = D3DXVECTOR3_NULL;
		pVtx[nCntVtx].col = D3DXCOLOR_FULL;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// �C���f�b�N���ւ̃|�C���^
	WORD* pIdx;

	int nIdxA = nDivisionX + 2;	// �����C���f�b�N�X
	int nIdxB = 1;				// �E���C���f�b�N�X
	int nCntIdx = 1;			// �ۑ��p�C���f�b�N�X�̃J�E���^�[

	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �Ă��؂�t�@���C���f�b�N�X
	pIdx[0] = 0;

	// �t�@���̃C���f�b�N�X������
	for (int nCntIdxA = m_nNumIdxFan - 2; nCntIdxA > 0; nCntIdxA--, nCntIdx++)
	{
		pIdx[nCntIdx] = nCntIdxA;
	}

	pIdx[m_nNumIdxFan - 1] = 0;

	for (int nCntY = 1; nCntY < nDivisionY - 1; nCntY++)
	{// Z�̕���������
		for (int nCntX = 0; nCntX <= nDivisionX; nCntX++)
		{// X�̕���������
			pIdx[nCntIdx] = nIdxA;
			pIdx[nCntIdx + 1] = nIdxB;
			nCntIdx += 2;
			nIdxA++;
			nIdxB++;
		}

		if (nCntY < nDivisionY - 1)
		{// ���S���u
			pIdx[nCntIdx] = nIdxB - 1;
			pIdx[nCntIdx + 1] = nIdxA;
			nCntIdx += 2;
		}
	}

	// �Ō�t�@���C���f�b�N�X
	nCntIdx--;
	pIdx[nCntIdx] = m_nNumVtx - 1;
	nCntIdx++;

	// �t�@���̃C���f�b�N�X������
	for (int nCntIdxB = m_nNumVtxMeshField - m_nDivisionX; nCntIdxB < m_nNumVtx - 1; nCntIdxB++, nCntIdx++)
	{
		pIdx[nCntIdx] = nCntIdxB;
	}

	pIdx[nCntIdx] = m_nNumVtx - 1;

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//**************************************
// ��I��
//**************************************
void CSky::Uninit(void)
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
		MessageBox(NULL, " CObject2D::Uninit() > ��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �����̃I�u�W�F�N�g��j��
	Release();
}

//**************************************
// ��X�V
//**************************************
void CSky::Update(void)
{

}

//**************************************
// ��`��
//**************************************
void CSky::Draw(void)
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

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��(�Ă��؂�)
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLEFAN,
		0,
		0,
		m_nNumVtxFan,
		0,
		m_nDivisionX
	);

	// �|���S���̕`��(��)
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_nNumVtxMeshField,
		m_nNumIdxFan - 1,
		m_nNumPolygonMeshField
	);

	// �|���S���̕`��(��)
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLEFAN,
		0,
		0,
		m_nNumVtxFan,
		m_nNumIdxFan + m_nNumIdxMeshField,
		m_nDivisionX
	);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//**************************************
// �󐶐�
//**************************************
CSky* CSky::Create(int nDivisionX, int nDivisionY, float fRadius)
{
	CSky* pSphere = NULL;			// ��|�C���^�[
	int nNumAll = GetObujectNumAll();	// �I�u�W�F�N�g�̑S�̐��擾

	// ��̐���
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	pSphere = new CSky;
	if (pSphere != NULL)
	{
		// ����������
		pSphere->Init(nDivisionX, nDivisionY, fRadius);
	}
	else
	{
		MessageBox(NULL, " CSky::Create() > if (pPlayer != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pSphere;
}