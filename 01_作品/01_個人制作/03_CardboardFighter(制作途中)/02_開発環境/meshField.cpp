//*********************************************
// 
// ���b�V���t�B�[���h
// Author Tetsuji Yamamoto
// 
//*********************************************
#include "meshField.h"
#include "myMath.h"
#include "texture.h"
#include "manager.h"

//*********************************************
// ���b�V���t�B�[���h�R���X�g���N�^
//*********************************************
CMeshField::CMeshField()
{
	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_startPos = D3DXVECTOR3_NULL;	// �n�܂�̈ʒu
	m_nIdxTexture = -1;		// �e�N�X�`���ւ̃C���f�b�N�X
	m_nNumPolygon = 0;		// �|���S����
	m_nNumVtx = 0;			// ���_��
	m_nNumIdx = 0;			// �C���f�b�N�X��
	m_nDivisionX = 0;		// X�̕�����
	m_nDivisionY = 0;		// Y�̕�����
	m_fWidth = 0.0f;		// ��
	m_fHeight = 0.0f;		// ����
}

//*********************************************
// ���b�V���t�B�[���h�f�X�g���N�^
//*********************************************
CMeshField::~CMeshField()
{
}

//*********************************************
// ���b�V���t�B�[���h������
//*********************************************
HRESULT CMeshField::Init(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fWidth, float fHeight, const char* pTexturePass)
{

	// �t�B�[���h�����̃|���S����
	m_nNumPolygon = CMyMath::SeekFieldNumPolygonAll(nDivisionX, nDivisionY);

	// �t�B�[���h�̒��_��
	m_nNumVtx = CMyMath::SeekFieldNumVertexAll(nDivisionX, nDivisionY);

	// �t�B�[���h�̃C���f�b�N�X��
	m_nNumIdx = CMyMath::SeekFieldNumIndexAll(m_nNumPolygon);

	// �������ݒ�
	m_nDivisionX = nDivisionX;
	m_nDivisionY = nDivisionY;

	// ���ƍ���
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	// �n�܂�̈ʒu
	m_startPos = startPos;

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
		MessageBox(NULL, "CMeshField::Init > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
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
		MessageBox(NULL, "CMeshField::Init > �C���f�b�N�X�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	m_nIdxTexture = pTexture->Register(pTexturePass);


	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;

	// Z�̕�������
	for (int nCntY = 0; nCntY <= nDivisionY; nCntY++)
	{
		// X�̕�������
		for (int nCntX = 0; nCntX <= nDivisionX; nCntX++, nCntVtx++)
		{
			float fposX = (fWidth / (float)nDivisionX) * (float)nCntX;	// �ʒu��X���W
			float fposZ = (fHeight / (float)nDivisionY) * (float)nCntY;	// �ʒu��Y���W
			float fTexX = (1.0f / (float)nDivisionX) * (float)nCntX;	// �e�N�X�`�����WX
			float fTexY = 1.0f / (float)nDivisionY * (float)nCntY;		// �e�N�X�`�����WY

			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos.x = startPos.x + fposX;
			pVtx[nCntVtx].pos.y = startPos.y;
			pVtx[nCntVtx].pos.z = startPos.z + (-fposZ);

			// �e���_�̖@���̐ݒ�,�ʂɑ΂��Đ���
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtx].tex.x = fTexX;
			pVtx[nCntVtx].tex.y = fTexY;
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

	// �@���̍Đݒ�
	CMeshField::ResetNormal();

	return S_OK;
}

//*********************************************
// ���b�V���t�B�[���h�I��
//*********************************************
void CMeshField::Uninit(void)
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
		MessageBox(NULL, "  CMeshField::Uninit() > ��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �����̃I�u�W�F�N�g��j��
	Release();
}

//*********************************************
// ���b�V���t�B�[���h�X�V
//*********************************************
void CMeshField::Update(void)
{

}

//*********************************************
// ���b�V���t�B�[���h�`��
//*********************************************
void CMeshField::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

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
}

//**************************************
// ���b�V���t�B�[���h����
//**************************************
CMeshField* CMeshField::Create(D3DXVECTOR3 startPos, int nDivisionX, int nDivisionY, float fWidth, float fheight, const char* pTexturePass)
{
	CMeshField* pMF = NULL;						// ���b�V���t�B�[���h�|�C���^�[
	int nNumAll = CObject::GetObujectNumAll();	// �I�u�W�F�N�g�̑S�̐��擾

	// �I�u�W�F�N�g�̍ő吔�𒴂��Ă��Ȃ���ΐ�������
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// ���b�V���t�B�[���h�̐���
	pMF = new CMeshField;
	if (pMF != NULL)
	{
		// ����������
		pMF->Init(startPos, nDivisionX, nDivisionY, fWidth, fheight, pTexturePass);
	}
	else
	{
		MessageBox(NULL, " CMeshField::Create() > ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pMF;
}

//**************************************
// ���b�V���t�B�[���h����
//**************************************
bool CMeshField::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pNor)
{
	// �����������ǂ����̗L��
	bool bColision = false;

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// �C���f�b�N���ւ̃|�C���^
	WORD* pIdx;

	// ���߂鍂��
	float fHeight = pPos->y;									// ���߂鍂��
	int nCntPolygon = 0;									// �|���S���J�E���^�[
	int nCntIdx = 0;										// �C���f�b�N�X�J�E���^
	float fWidthDiviX = m_fWidth / (float)m_nDivisionX;		// ����������
	float fHeightDiviY = m_fHeight / (float)m_nDivisionY;	// ������������
	float fMovePosX = 0.0f - m_startPos.x;					// ���_�����Ɉړ������邽�߂̈ړ���X
	float fMovePosY = 0.0f - m_startPos.z;					// ���_�����Ɉړ������邽�߂̈ړ���Y

	// �t�B�[���h�͈̔͊O�ł���Ώ������Ȃ�
	if (pPos->x < m_startPos.x ||
		pPos->x > m_startPos.x + m_fWidth ||
		pPos->z > m_startPos.z ||
		pPos->z < m_startPos.z - m_fHeight)
	{
		return bColision;
	}

	// �������Ă��锻��ɂ���
	bColision = true;

	// �ʒu�𕪊����������ňʒu������o��
	int nPosDiviX = (int)((pPos->x + fMovePosX) / fWidthDiviX);
	int nPosDiviY = (int)((pPos->z + fMovePosY) / -fHeightDiviY);

	// �|���S���J�E���^�[���s���i�߂�
	nCntPolygon += (m_nDivisionX * 2) * nPosDiviY;

	// �|���S���J�E���^�[���k�ރ|���S�����i�߂�
	nCntPolygon += 4 * nPosDiviY;

	// �|���S���J�E���^�[��񕪐i�߂�
	nCntPolygon += 2 * nPosDiviX;

	// �C���f�b�N�X�J�E���^�[�����ݒn�̃|���S���֐ݒ�
	nCntIdx = nCntPolygon;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �|���S���񖇕�����
	for (int nCntPoly = 0; nCntPoly < 2; nCntPoly++, nCntIdx++)
	{
		D3DXVECTOR3 posA, posB, posC;							// �|���S���̒��_
		D3DXVECTOR3 vecLineA, vecLineB, vecLineC;				// �|���S���̈�ӂ̃x�N�g��
		D3DXVECTOR3 vecLinePposA, vecLinePposB, vecLinePposC;	// pPos�Ƃ̃x�N�g��
		float fClossA, fClossB, fClossC;						// pPos�x�N�g���ƈ�Ӄx�N�g���̊O�ς�Y����

		posA = pVtx[pIdx[nCntIdx]].pos;
		posB = pVtx[pIdx[nCntIdx + 1]].pos;
		posC = pVtx[pIdx[nCntIdx + 2]].pos;

		// �|���S���̈�ӂ̃x�N�g�������߂�
		vecLineA = posB - posA;
		vecLineB = posC - posB;
		vecLineC = posA - posC;

		// pos�x�N�g�������߂�
		vecLinePposA = *pPos - posA;
		vecLinePposB = *pPos - posB;
		vecLinePposC = *pPos - posC;

		// pPos�x�N�g���ƈ�Ӄx�N�g���̊O�ς����߂�
		fClossA = (vecLineA.z * vecLinePposA.x) - (vecLineA.x * vecLinePposA.z);
		fClossB = (vecLineB.z * vecLinePposB.x) - (vecLineB.x * vecLinePposB.z);
		fClossC = (vecLineC.z * vecLinePposC.x) - (vecLineC.x * vecLinePposC.z);

		D3DXVECTOR3 nor;	// �v�Z�����@����ۑ�����ϐ�
		float fDot;			// ���ς̌��ʂ�ۑ�����ϐ�

		// �@���ƃ|���S���̈꒸�_�̓���
		fDot = ((nor.x * posA.x) +
			(nor.y * posA.y) +
			(nor.z * posA.z));

		// �O�ς����ׂăv���X�܂��̓}�C�i�X�ł����
		if (fClossA >= 0 &&
			fClossB >= 0 &&
			fClossC >= 0)
		{
			// �O�ςɂ���Ė@�������߂�
			D3DXVec3Cross(&nor, &vecLineA, &vecLineB);

			// �@���𐳋K������
			D3DXVec3Normalize(&nor, &nor);

			// �@���ƃ|���S���̈꒸�_�̓���
			float fDot = ((nor.x * posA.x) + (nor.y * posA.y) + (nor.z * posA.z));

			//�v���C���[���|���S����ɂ���Ƃ���y���W�����߂�
			fHeight = (-nor.x * pPos->x - nor.z * pPos->z + fDot) / nor.y;

			// �����ݒ�
			pPos->y = fHeight;

			// �@���ݒ�
			if (pNor != NULL)
			{
				*pNor = nor;
			}

			return bColision;
		}
		else if (fClossA <= 0 &&
			fClossB <= 0 &&
			fClossC <= 0)
		{
			// �O�ςɂ���Ė@�������߂�
			D3DXVec3Cross(&nor, &vecLineB, &vecLineA);

			// �@���𐳋K������
			D3DXVec3Normalize(&nor, &nor);

			// �@���ƃ|���S���̈꒸�_�̓���
			float fDot = ((nor.x * posA.x) + (nor.y * posA.y) + (nor.z * posA.z));

			//�v���C���[���|���S����ɂ���Ƃ���y���W�����߂�
			fHeight = (-nor.x * pPos->x - nor.z * pPos->z + fDot) / nor.y;

			// �����ݒ�
			pPos->y = fHeight;

			// �@���ݒ�
			if (pNor != NULL)
			{
				*pNor = nor;
			}

			return bColision;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return fHeight;
}

//**************************************
// �@���̍Đݒ�
//**************************************
void CMeshField::ResetNormal(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���ׂĂ̒��_����
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		// �@���ϐ�
		D3DXVECTOR3 aNor[6];
		D3DXVECTOR3 nor;

		// �|���S�����x�N�g���ϐ�
		D3DXVECTOR3 vecRight;
		D3DXVECTOR3 vecLeft;
		D3DXVECTOR3 vecUp;
		D3DXVECTOR3 vecDown;
		D3DXVECTOR3 vecRightDown;
		D3DXVECTOR3 vecLeftUp;

		// ���_�ʒu�ϐ�
		D3DXVECTOR3 posCenter;
		D3DXVECTOR3 posRight;
		D3DXVECTOR3 posLeft;
		D3DXVECTOR3 posUp;
		D3DXVECTOR3 posDown;
		D3DXVECTOR3 posRightDown;
		D3DXVECTOR3 posLeftDown;
		D3DXVECTOR3 posRightUp;
		D3DXVECTOR3 posLeftUp;

		// ���_�ԍ������߂�
		int nRightNum = nCntVtx + 1;
		int nLeftNum = nCntVtx - 1;
		int nUpNum = nCntVtx - (m_nDivisionX + 1);
		int nDownNum = nCntVtx + m_nDivisionX + 1;
		int nRightDownNum = nCntVtx + m_nDivisionX + 2;
		int nLeftUpNum = nCntVtx - (m_nDivisionX + 2);

		// ����ł���
		if (nCntVtx == 0)
		{
			// �^�񒆁A�E�A���A�E���̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posRight = pVtx[nRightNum].pos;
			posDown = pVtx[nDownNum].pos;
			posRightDown = pVtx[nRightDownNum].pos;

			// �|���S���̉������߂�
			vecRight = posRight - posCenter;
			vecRightDown = posRightDown - posCenter;
			vecDown = posDown - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&aNor[0], &vecRight, &vecRightDown);
			D3DXVec3Cross(&aNor[1], &vecRightDown, &posDown);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);

			// ���ꂼ��̖@���̕��ϒl�Ŗ@�������߂�
			nor = aNor[0] + aNor[1];
			nor = nor / 2;

		}
		// �E��ł���
		else if (nCntVtx == m_nDivisionX)
		{
			// �^�񒆁A���A���A�����̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posLeft = pVtx[nLeftNum].pos;
			posDown = pVtx[nDownNum].pos;

			// �|���S���̉������߂�
			vecLeft = posLeft - posCenter;
			vecDown = posDown - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&nor, &vecDown, &vecLeft);
			D3DXVec3Normalize(&nor, &nor);
		}
		// �����ł���
		else if (nCntVtx == (m_nDivisionX + 1) * m_nDivisionY)
		{
			// �^�񒆁A��A�E�̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posRight = pVtx[nRightNum].pos;
			posUp = pVtx[nUpNum].pos;

			// �|���S���̉������߂�
			vecRight = posRight - posCenter;
			vecUp = posUp - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&nor, &vecUp, &vecRight);
			D3DXVec3Normalize(&nor, &nor);
		}
		// �E���ł���
		else if (nCntVtx == m_nDivisionX + (m_nDivisionX + 1) * m_nDivisionY)
		{
			// �^�񒆁A��A����A���̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posUp = pVtx[nUpNum].pos;
			posLeftUp = pVtx[nLeftUpNum].pos;
			posLeft = pVtx[nLeftNum].pos;

			// �|���S���̉������߂�
			vecUp = posUp - posCenter;
			vecLeftUp = posLeftUp - posCenter;
			vecLeft = posLeft - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&aNor[0], &vecUp, &vecLeftUp);
			D3DXVec3Cross(&aNor[1], &vecLeftUp, &vecLeft);
			D3DXVec3Normalize(&aNor[0], &nor);
			D3DXVec3Normalize(&aNor[1], &nor);

			// ���ꂼ��̖@���̕��ϒl�Ŗ@�������߂�
			nor = aNor[0] + aNor[1];
			nor = nor / 2;
		}
		// ��ӂł���
		else if (nCntVtx > 0 && nCntVtx < m_nDivisionX)
		{
			// �^�񒆁A���A���A�E��A�E�̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posLeft = pVtx[nLeftNum].pos;
			posDown = pVtx[nDownNum].pos;
			posRightDown = pVtx[nRightDownNum].pos;
			posRight = pVtx[nRightNum].pos;

			// �|���S���̉������߂�
			vecLeft = posLeft - posCenter;
			vecDown = posDown - posCenter;
			vecRightDown = posRightDown - posCenter;
			vecRight = posRight - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&aNor[0], &vecDown, &vecLeft);
			D3DXVec3Cross(&aNor[1], &vecRightDown, &vecDown);
			D3DXVec3Cross(&aNor[2], &vecRight, &vecRightDown);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);

			// ���ꂼ��̖@���̕��ϒl�Ŗ@�������߂�
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}
		// ���ӂł���
		else if (nCntVtx >= m_nNumVtx - m_nDivisionX && nCntVtx < m_nNumVtx)
		{
			// �^�񒆁A���A����A��A�E�̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posLeft = pVtx[nLeftNum].pos;
			posLeftUp = pVtx[nLeftUpNum].pos;
			posUp = pVtx[nUpNum].pos;
			posRight = pVtx[nRightNum].pos;

			// �|���S���̉������߂�
			vecLeft = posLeft - posCenter;
			vecLeftUp = posLeftUp - posCenter;
			vecUp = posUp - posCenter;
			vecRight = posRight - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&aNor[0], &vecLeft, &vecLeftUp);
			D3DXVec3Cross(&aNor[1], &vecLeftUp, &vecUp);
			D3DXVec3Cross(&aNor[2], &vecUp, &vecRight);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);

			// ���ꂼ��̖@���̕��ϒl�Ŗ@�������߂�
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}
		// ���ӂł���
		else if (nCntVtx % (m_nDivisionX + 1) == 0)
		{
			// �^�񒆁A��A�E�A�E���A���̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posUp = pVtx[nUpNum].pos;
			posLeft = pVtx[nLeftNum].pos;
			posRight = pVtx[nRightNum].pos;
			posRightDown = pVtx[nRightDownNum].pos;
			posDown = pVtx[nDownNum].pos;

			// �|���S���̉������߂�
			vecUp = posUp - posCenter;
			vecRight = posRight - posCenter;
			vecRightDown = posRightDown - posCenter;
			vecDown = posDown - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&aNor[0], &vecUp, &vecRight);
			D3DXVec3Cross(&aNor[1], &vecRight, &vecRightDown);
			D3DXVec3Cross(&aNor[2], &vecRightDown, &vecDown);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);

			// ���ꂼ��̖@���̕��ϒl�Ŗ@�������߂�
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}
		// �E�ӂł���
		else if ((nCntVtx - m_nDivisionX) % (m_nDivisionX + 1) == 0)
		{
			// �^�񒆁A���A���A����A��̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posDown = pVtx[nDownNum].pos;
			posLeft = pVtx[nLeftNum].pos;
			posLeftUp = pVtx[nLeftUpNum].pos;
			posUp = pVtx[nUpNum].pos;

			// �|���S���̉������߂�
			vecDown = posDown - posCenter;
			vecLeft = posLeft - posCenter;
			vecLeftUp = posLeftUp - posCenter;
			vecUp = posUp - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&aNor[0], &vecLeftUp, &vecUp);
			D3DXVec3Cross(&aNor[1], &vecLeft, &vecLeftUp);
			D3DXVec3Cross(&aNor[2], &vecDown, &vecLeft);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);

			// ���ꂼ��̖@���̕��ϒl�Ŗ@�������߂�
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}
		// ����ȊO�ł���
		else
		{
			// �^�񒆁A��A�E�A�E���A���A���A����̒��_�̈ʒu�����߂�
			posCenter = pVtx[nCntVtx].pos;
			posUp = pVtx[nUpNum].pos;
			posRight = pVtx[nRightNum].pos;
			posRightDown = pVtx[nRightDownNum].pos;
			posDown = pVtx[nDownNum].pos;
			posLeft = pVtx[nLeftNum].pos;
			posLeftUp = pVtx[nLeftUpNum].pos;

			// �|���S���̉������߂�
			vecUp = posUp - posCenter;
			vecRight = posRight - posCenter;
			vecRightDown = posRightDown - posCenter;
			vecDown = posDown - posCenter;
			vecLeft = posLeft - posCenter;
			vecLeftUp = posLeftUp - posCenter;

			// �O�ςŖ@�����v�Z�A���K��
			D3DXVec3Cross(&aNor[0], &vecLeftUp, &vecUp);
			D3DXVec3Cross(&aNor[1], &vecLeft, &vecLeftUp);
			D3DXVec3Cross(&aNor[2], &vecDown, &vecLeft);
			D3DXVec3Cross(&aNor[3], &vecRightDown, &vecDown);
			D3DXVec3Cross(&aNor[4], &vecRight, &vecRightDown);
			D3DXVec3Cross(&aNor[5], &vecUp, &vecRight);
			D3DXVec3Normalize(&aNor[0], &aNor[0]);
			D3DXVec3Normalize(&aNor[1], &aNor[1]);
			D3DXVec3Normalize(&aNor[2], &aNor[2]);
			D3DXVec3Normalize(&aNor[3], &aNor[3]);
			D3DXVec3Normalize(&aNor[4], &aNor[4]);
			D3DXVec3Normalize(&aNor[5], &aNor[5]);

			// ���ꂼ��̖@���̕��ϒl�Ŗ@�������߂�
			nor = aNor[0] + aNor[1] + aNor[2];
			nor = nor / 3;
		}

		pVtx[nCntVtx].nor = nor;
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//*****************************************************
// ���b�V���t�B�[���h�����ҏW
//*****************************************************
void CMeshField::EditHeight(D3DXVECTOR3 pos, float fHeight, float fRadius)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���ꎞ�ۑ�
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 posVtx;
		posVtx = pVtx[nCntVtx].pos;

		D3DXVECTOR2 posXZ, posXZVtx;
		posXZ.x = pos.x;
		posXZ.y = pos.z;
		posXZVtx.x = posVtx.x;
		posXZVtx.y = posVtx.z;

		// ���_�����a�͈͓̔��ɂ���
		if (CMyMath::ColiisionCircleCircle2D(posXZ, fRadius, posXZVtx, 0.0f) == true)
		{
			pVtx[nCntVtx].pos.y = fHeight;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// �@���̍Đݒ�
	CMeshField::ResetNormal();
}

//*****************************************************
// ���b�V���t�B�[���h�F�ݒ�
//*****************************************************
void CMeshField::SetColor(D3DXCOLOR col)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �S���_�̐F�ύX
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		pVtx[nCntVtx].col = col;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//*****************************************************
// ���b�V���t�B�[���h�ʒu�ݒ�
//*****************************************************
void CMeshField::SetPosition(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	m_startPos = pos;
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;

	// Z�̕�������
	for (int nCntY = 0; nCntY <= m_nDivisionY; nCntY++)
	{
		// X�̕�������
		for (int nCntX = 0; nCntX <= m_nDivisionX; nCntX++, nCntVtx++)
		{
			float fposX = (m_fWidth / (float)m_nDivisionX) * (float)nCntX;	// �ʒu��X���W
			float fposZ = (m_fHeight / (float)m_nDivisionY) * (float)nCntY;	// �ʒu��Y���W

			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos.x = pos.x + fposX;
			pVtx[nCntVtx].pos.y = pos.y;
			pVtx[nCntVtx].pos.z = pos.z + (-fposZ);
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//*****************************************************
// ���b�V���t�B�[���h�̕ۑ�
//*****************************************************
void CMeshField::Save(const char* pFilePass)
{
	// �������ݗp�Ƃ��ăt�@�C�����J��
	FILE* pFile = fopen(pFilePass, "w");

	// �t�@�C�����J������
	if (pFile != NULL)
	{
		// ���_���ւ̃|�C���^
		VERTEX_3D* pVtx = NULL;

		fprintf(pFile, "#*********************************************************\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# ���b�V���t�B�[���h���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# �e�N�X�`���͂��D�݂̃t�@�C���p�X���L�����Ă����Ă�������\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#*********************************************************\n");
		fprintf(pFile, "START_POS = %0.3f %0.3f %0.3f\n", m_startPos.x, m_startPos.y, m_startPos.z);
		fprintf(pFile, "WIDTH = %0.3f\n", m_fWidth);
		fprintf(pFile, "HEIGHT = %0.3f\n", m_fHeight);
		fprintf(pFile, "POLYGON_NUM = %d\n", m_nNumPolygon);
		fprintf(pFile, "VERTEX_NUM = %d\n", m_nNumVtx);
		fprintf(pFile, "INDEX_NUM = %d\n", m_nNumIdx);
		fprintf(pFile, "DIVISION_X = %d\n", m_nDivisionX);
		fprintf(pFile, "DIVISION_Y = %d\n", m_nDivisionY);
		fprintf(pFile, "TEXTURE_FILE = \n");
		fprintf(pFile, "\n");

		// ���_�o�b�t�@�����b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		fprintf(pFile, "SET_VERTEXBUFF\n");
		// ���_����
		for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 pos = pVtx[nCntVtx].pos;
			D3DXVECTOR3 nor = pVtx[nCntVtx].nor;
			D3DXVECTOR2 tex = pVtx[nCntVtx].tex;
			D3DXCOLOR col = pVtx[nCntVtx].col;

			fprintf(pFile, "SET_VTX\n");
			fprintf(pFile, "POS = %0.3f %0.3f %0.3f\n", pos.x, pos.y, pos.z);
			fprintf(pFile, "NOR = %0.3f %0.3f %0.3f\n", nor.x, nor.y, nor.z);
			fprintf(pFile, "COL = %0.3f %0.3f %0.3f %0.3f\n", col.r, col.g, col.b, col.a);
			fprintf(pFile, "TEX = %0.3f %0.3f\n", tex.x, tex.y);
			fprintf(pFile, "END_VTX\n");
			fprintf(pFile, "\n");
		}
		fprintf(pFile, "END_VERTEXBUFF\n");
		fprintf(pFile, "\n");

		// ���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();

		fprintf(pFile, "END_FILE");

		// �t�@�C�������
		fclose(pFile);
	}
}

//*****************************************************
// ���b�V���t�B�[���h�̕ۑ�
//*****************************************************
void CMeshField::Load(const char* pFilePass)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �ǂݎ��p�Ƃ��ăt�@�C�����J��
	FILE* pFile = fopen(pFilePass, "r");

	// �t�@�C�����J������
	if (pFile != NULL)
	{
		// ���_���ւ̃|�C���^
		VERTEX_3D* pVtx = NULL;

		char aStr[1024] = {};		// ������
		bool bComment = false;		// �R�����g�̗L��
		int nIdxStr = 0;			// ������C���f�b�N�X
		int nIdxFileName = 0;		// �t�@�C�����C���f�b�N�X
		char aData[4] = {};			// =�ǂݎ��p
		char aFileName[128] = {};	// �t�@�C�����p�ϐ�
		int nIdxVtx = 0;			// ���_�C���f�b�N�X
		bool bSetVerBuff = false;	// ���_�o�b�t�@�̐ݒ�̗L��

		while (1)
		{// ���[�v

			// �ꕶ���ǂݎ��
			char cData = fgetc(pFile);

			if (cData == '#')
			{// �R�����g������ǂ񂾂炻�̂��Ƃ̕����͓ǂݔ�΂�
				bComment = true;				// �R�����g�L�̏�Ԃɂ���
				memset(aStr, 0, sizeof(aStr));	// ���������ɂ���
				nIdxStr = 0;					// ������C���f�b�N�X���Z�b�g
				continue;						// while����
			}
			else if (cData == '\n')
			{// ���s��񂾂�
				bComment = false;				// �R�����g���̏�Ԃɂ���
				memset(aStr, 0, sizeof(aStr));	// ���������ɂ���
				nIdxStr = 0;					// ������C���f�b�N�X���Z�b�g
				continue;						// while����
			}
			else if (cData == '\t')
			{// �^�u������񂾂�
				continue;	// while����
			}
			else if (cData == EOF)
			{// �^�u������񂾂�
				break;	// while���甲���o��
			}

			if (bComment == true)
			{// �R�����g�@�\���I��
				continue;	// while����
			}

			aStr[nIdxStr] = cData;	// �ꕶ�����
			nIdxStr++;				// �C���f�b�N�X�J�E���g�A�b�v

			// �X�^�[�g�ʒu�Ǎ�
			if (strcmp(aStr, "START_POSE") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%f", &m_startPos.x);
				fscanf(pFile, "%f", &m_startPos.y);
				fscanf(pFile, "%f", &m_startPos.z);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// ���ǂݎ��
			else if (strcmp(aStr, "WIDTH") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%f", &m_fWidth);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// �����ǂݎ��
			else if (strcmp(aStr, "HEIGHT") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%f", &m_fHeight);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// �|���S�����Ǎ�
			else if (strcmp(aStr, "POLYGON_NUM") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%d", &m_nNumPolygon);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// ���_���Ǎ�
			else if (strcmp(aStr, "VERTEX_NUM") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%d", &m_nNumVtx);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// �C���f�b�N�X���̓Ǎ�
			else if (strcmp(aStr, "INDEX_NUM") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%d", &m_nNumIdx);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// X�̕������Ǎ�
			else if (strcmp(aStr, "DIVISION_X") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%d", &m_nDivisionX);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// Y�̕�����
			else if (strcmp(aStr, "DIVISION_Y") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%d", &m_nDivisionY);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// �e�N�X�`���t�@�C�����Ǎ�
			else if (strcmp(aStr, "TEXTURE_FILE") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// �l�ǂݎ��
				fscanf(pFile, "%s", aFileName);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// �e�N�X�`���t�@�C�����Ǎ�
			else if (strcmp(aStr, "SET_VERTEXBUFF") == 0)
			{
				// �������������s��
				Init(m_startPos, m_nDivisionX, m_nDivisionY, m_fWidth, m_fHeight, aFileName);

				if (m_pVtxBuff != NULL)
				{
					// ���_�o�b�t�@���Z�b�g���Ă����Ԃɂ���
					bSetVerBuff = true;

					// ���_�o�b�t�@�����b�N
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
				}

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}
			// �t�@�C���I��
			else if (strcmp(aStr, "END_FILE") == 0)
			{
				// =��ǂݍ���
				fscanf(pFile, "%s", &aData[0]);

				// ���������ɂ���
				memset(aStr, 0, sizeof(aStr));

				// ������C���f�b�N�X���Z�b�g
				nIdxStr = 0;
			}

			// ���_�Ǎ��\�ł���Βʂ�
			if (bSetVerBuff == true)
			{
				// �ʒu�Ǎ�
				if (strcmp(aStr, "POS") == 0)
				{
					// =��ǂݍ���
					fscanf(pFile, "%s", &aData[0]);

					// �l��ǂݍ���
					fscanf(pFile, "%f", &pVtx[nIdxVtx].pos.x);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].pos.y);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].pos.z);

					// ���������ɂ���
					memset(aStr, 0, sizeof(aStr));

					// ������C���f�b�N�X���Z�b�g
					nIdxStr = 0;
				}
				// �@���Ǎ�
				else if (strcmp(aStr, "NOR") == 0)
				{
					// =��ǂݍ���
					fscanf(pFile, "%s", &aData[0]);

					// �l��ǂݍ���
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.x);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.y);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.z);

					// ���������ɂ���
					memset(aStr, 0, sizeof(aStr));

					// ������C���f�b�N�X���Z�b�g
					nIdxStr = 0;
				}
				// �F�Ǎ�
				else if (strcmp(aStr, "COL") == 0)
				{
					// =��ǂݍ���
					fscanf(pFile, "%s", &aData[0]);

					// �l��ǂݍ���
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.x);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.y);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].nor.z);

					// ���������ɂ���
					memset(aStr, 0, sizeof(aStr));

					// ������C���f�b�N�X���Z�b�g
					nIdxStr = 0;
				}
				// �e�N�X�`�����W�Ǎ�
				else if (strcmp(aStr, "TEX") == 0)
				{
					// =��ǂݍ���
					fscanf(pFile, "%s", &aData[0]);

					// �l��ǂݍ���
					fscanf(pFile, "%f", &pVtx[nIdxVtx].tex.x);
					fscanf(pFile, "%f", &pVtx[nIdxVtx].tex.y);

					// ���������ɂ���
					memset(aStr, 0, sizeof(aStr));

					// ������C���f�b�N�X���Z�b�g
					nIdxStr = 0;
				}
				// ���_�Ǎ��I��
				else if (strcmp(aStr, "END_VTX") == 0)
				{
					// �C���f�b�N�X����i�߂�
					nIdxVtx++;

					// ���������ɂ���
					memset(aStr, 0, sizeof(aStr));

					// ������C���f�b�N�X���Z�b�g
					nIdxStr = 0;
				}
				// ���_�Ǎ��I��
				else if (strcmp(aStr, "END_VERTEXBUFF") == 0)
				{
					bSetVerBuff = false;

					// ���_�o�b�t�@���A�����b�N
					m_pVtxBuff->Unlock();

					// ���������ɂ���
					memset(aStr, 0, sizeof(aStr));

					// ������C���f�b�N�X���Z�b�g
					nIdxStr = 0;
				}
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	// �t�@�C�����J���Ȃ�����
	else
	{
		MessageBox(NULL, "CMeshField::Load() > �t�@�C�����J���܂���ł���", "Error", MB_OK);
		return;
	}
}