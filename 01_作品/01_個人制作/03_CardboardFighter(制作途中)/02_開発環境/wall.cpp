//**********************************************************************
// 
// ��
// Author Tetsuji Yamamoto
// 
//**********************************************************************
#include "wall.h"
#include "debugproc.h"
#include "renderer.h"
#include "manager.h"

//**********************************************************************
// �ǃR���X�g���N�^
//**********************************************************************
CWall::CWall() : CObject3D(CObject::PRIORITY_5)
{
	m_posA = D3DXVECTOR3_NULL;	// �|���S���̒��_
	m_posB = D3DXVECTOR3_NULL;	// �|���S���̒��_
	m_posC = D3DXVECTOR3_NULL;	// �|���S���̒��_
}

//**********************************************************************
// �ǃf�X�g���N�^
//**********************************************************************
CWall::~CWall()
{
}

//**********************************************************************
// �Ǐ�����
//**********************************************************************
HRESULT CWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float fHeight, float fDepth, const char* pTexturePass)
{
	HRESULT hr = CObject3D::Init(pos, rot, col, fWidth, fHeight, fDepth,pTexturePass);

	// �ʒu�擾
	m_posA = CObject3D::GetVtxPos(0);
	m_posB = CObject3D::GetVtxPos(1);
	m_posC = CObject3D::GetVtxPos(2);

	return hr;
}

//**********************************************************************
// �ǏI��
//**********************************************************************
void CWall::Uninit(void)
{
	CObject3D::Uninit();
}

//**********************************************************************
// �ǍX�V
//**********************************************************************
void CWall::Update(void)
{
	CObject3D::Update();
}

//**********************************************************************
// �Ǖ`��
//**********************************************************************
void CWall::Draw(void)
{
	//// �ǂ̕`��
	//CObject3D::Draw();
	
	// �e�N�X�`���̃C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, CManager::GetRenderer()->GetTextureMT(0));

	CObject3D::DrawNoTexture();
}

//**********************************************************************
// �Ǖ`��
//**********************************************************************
bool CWall::CollisionWall(D3DXVECTOR3* pPos,D3DXVECTOR3 posOld)
{
	bool bCollision = false;
	D3DXVECTOR3 edge0, edge1, edge2;
	D3DXVECTOR3 vecPosA, vecPosB,vecPosOld;
	D3DXVECTOR3 crossPos,crossPoaOld;
	float fDotA, fDotB;

	// �|���S���̉��x�N�g���v�Z
	edge0 = m_posB - m_posA;
	edge1 = m_posC - m_posA;
	edge2 = m_posA - m_posB;

	// �ʒu�x�N�g���v�Z
	vecPosA = *pPos - m_posA;
	vecPosB = *pPos - m_posB;

	// ���x�N�g���ƈʒu�x�N�g�����O�όv�Z(�Â��ʒu���v�Z����)
	D3DXVec3Cross(&crossPos, &edge0, &vecPosA);

	// ���x�N�g�����ނƈʒu�x�N�g�����ނ̓��ς��v�Z����
	fDotA = D3DXVec3Dot(&edge0,&vecPosA);
	fDotB = D3DXVec3Dot(&edge2,&vecPosB);

	// �������͈͓��ł�������ǂ̏㉺�ȓ�
	if (pPos->y <= m_posA.y && pPos->y >= m_posC.y)
	{
		// ���ό��ʂ������Ƃ�+�ł���Εǂ͈͓̔�
		if (fDotA >= 0 && fDotB >= 0)
		{
			// �O�ς�Y�������}�C�i�X�ł����ČÂ��ʒu�x�N�g���̊O�ς��v���X�ł���Εǂɂ߂荞�񂾔���
			if (crossPos.y < 0.0f)
			{
				D3DXVECTOR3 vecMove = posOld - *pPos;

				// �@�����O�ςŎZ�o
				D3DXVECTOR3 nor;
				D3DXVec3Cross(&nor, &edge0, &edge1);
				D3DXVec3Normalize(&nor, &nor);

				// �ړ��x�N�g���Ɩ@���̓��ς����
				float fDot = D3DXVec3Dot(&vecMove, &nor);

				// �@���ɓ��ς��|���Ĉړ��ʂ����߂�
				D3DXVECTOR3 move = nor * fDot;

				// �ʒu�Ɉړ��ʂ𑫂��Ă�����
				*pPos += move;

				// ������������ɂ���
				bCollision = true;
			}
		}
	}

	// ���ʂ�Ԃ�
	return bCollision;
}

//**********************************************************************
// �ǐ���
//**********************************************************************
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float fHeight, float fDepth, const char* pTexturePass)
{
	CWall* pWall = NULL;						// �ǃ|�C���^�[
	int nNumAll = CObject::GetObujectNumAll();	// �I�u�W�F�N�g�̑S�̐��擾

	// �I�u�W�F�N�g�̍ő吔�𒴂��Ă��Ȃ���ΐ�������
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// �ǂ̐���
	pWall = new CWall;
	if (pWall != NULL)
	{
		// ����������
		pWall->Init(pos, rot, col, fWidth, fHeight, fDepth, pTexturePass);
	}
	else
	{
		MessageBox(NULL, " CWall::Create() > ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pWall;
}
