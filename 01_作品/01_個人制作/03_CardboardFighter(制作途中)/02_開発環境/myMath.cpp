//**********************************************************************************************************************
// 
// ���w
// Author Tetsuji Yamamoto
// 
//**********************************************************************************************************************
#include "myMath.h"
#include "manager.h"

//**********************************************************************************************************************
// ���w�R���X�g���N�^
//**********************************************************************************************************************
CMyMath::CMyMath()
{
}

//**********************************************************************************************************************
// ���w�f�X�g���N�^
//**********************************************************************************************************************
CMyMath::~CMyMath()
{
}

//**********************************************************************************************************************
// ���w�����W�v�Z
//**********************************************************************************************************************
D3DXVECTOR3 CMyMath::SphericalCoordinates(D3DXVECTOR3 centerPos, D3DXVECTOR3 rot, float fDistance)
{
	D3DXVECTOR3 outPos;
	outPos.x = centerPos.x + sinf(rot.x) * sinf(rot.y) * fDistance;
	outPos.y = centerPos.y + cosf(rot.x) * fDistance;
	outPos.z = centerPos.z + sinf(rot.x) * cosf(rot.y) * fDistance;

	return outPos;
}

//**********************************************************************************************************************
// ���w���b�V���t�B�[���h�̏k�ރ|���S���̐������߂鏈��
//**********************************************************************************************************************
int CMyMath::SeekMeshFieldNumPolygonHid(int nDivisionY)
{
	return 4 * (nDivisionY - 1);
}

//**********************************************************************************************************************
// ���w���b�V���t�B�[���h�̌�����|���S���̐������߂鏈��
//**********************************************************************************************************************
int CMyMath::SeekFieldNumPolygonApp(int nDivisionX, int nDivisionY)
{
	return (nDivisionX * nDivisionY) * 2;
}

//**********************************************************************************************************************
// ���w���b�V���t�B�[���h�̂��ׂẴ|���S���������߂鏈��
//**********************************************************************************************************************
int CMyMath::SeekFieldNumPolygonAll(int nDivisionX, int nDivisionY)
{
	return ((nDivisionX * nDivisionY) * 2) + (4 * (nDivisionY - 1));
}

//**********************************************************************************************************************
// ���w���b�V���t�B�[���h�̒��_�������߂鏈��
//**********************************************************************************************************************
int CMyMath::SeekFieldNumVertexAll(int nDivisionX, int nDivisionY)
{
	return (nDivisionX + 1) * (nDivisionY + 1);
}

//**********************************************************************************************************************
// ���w���b�V���t�B�[���h�̃C���f�b�N�X�������߂鏈��
//**********************************************************************************************************************
int CMyMath::SeekFieldNumIndexAll(int nNumPolygonAll)
{
	return nNumPolygonAll + 2;
}

//**********************************************************************************************************************
// ���w�t�@���̃C���f�b�N�X�������߂鏈��
//**********************************************************************************************************************
int CMyMath::SeekFanNumIndexAll(int nDivisionX)
{
	return nDivisionX + 3;
}

//************************************************************************************************************************
// ���[�J�����W�����]�s��ɕϊ����鏈��
//************************************************************************************************************************
D3DXMATRIX CMyMath::ConvertLocalCoordinatesToRotMtx(D3DXVECTOR3 pos, D3DXVECTOR3 look, D3DXVECTOR3 nor)
{
	D3DXMATRIX mtxResult;	// �v�Z���ʕۑ��p�ϐ�
	D3DXVECTOR3 X, Y, Z;	// �v�Z�����x�N�g���ۑ��p�ϐ�

	Z = -(look - pos);										// �ʒu���猩�Ă�������̃x�N�g�������߂�
	D3DXVec3Normalize(&Z, &Z);								// �W��������
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &nor), &Z);		// x�������߂�
	D3DXVec3Normalize(&X, &X);								// �W��������
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));		// y�������߂�

	// ���߂��l����]�s��ɕϊ�����
	mtxResult._11 = X.x; mtxResult._12 = X.y; mtxResult._13 = X.z; mtxResult._14 = 0;
	mtxResult._21 = Y.x; mtxResult._22 = Y.y; mtxResult._23 = Y.z; mtxResult._24 = 0;
	mtxResult._31 = Z.x; mtxResult._32 = Z.y; mtxResult._33 = Z.z; mtxResult._34 = 0;
	mtxResult._41 = 0.0f; mtxResult._42 = 0.0f; mtxResult._43 = 0.0f; mtxResult._44 = 1.0f;

	// ���ʂ�Ԃ�
	return mtxResult;
}

//************************************************************************************************************************
// �p�x�̐��K��
//************************************************************************************************************************
void CMyMath::NormalizingAngles(D3DXVECTOR3* pRot)
{
	// �p�x�̐��K��
	if (pRot->x > D3DX_PI)
	{
		pRot->x = -D3DX_PI + (pRot->x - D3DX_PI);
	}
	else if (pRot->x < -D3DX_PI)
	{
		pRot->x = D3DX_PI + (pRot->x + D3DX_PI);
	}

	if (pRot->y > D3DX_PI)
	{
		pRot->y = -D3DX_PI + (pRot->y - D3DX_PI);
	}
	else if (pRot->y < -D3DX_PI)
	{
		pRot->y = D3DX_PI + (pRot->y + D3DX_PI);
	}

	if (pRot->z > D3DX_PI)
	{
		pRot->z = -D3DX_PI + (pRot->z - D3DX_PI);
	}
	else if (pRot->y < -D3DX_PI)
	{
		pRot->z = D3DX_PI + (pRot->z + D3DX_PI);
	}
}

//**************************************************
// �ŒZ�̊p�x�ɕϊ����鏈��
//**************************************************
float CMyMath::ShortestAngle(float fAngleDiff)
{
	// �������p�x������𒴂��Ă����獷���������������Ď��ɑ����΂����p�x�����߂�
	if (fAngleDiff > D3DX_PI)
	{
		fAngleDiff = fAngleDiff - D3DX_PI * 2;
	}
	else if (fAngleDiff < -D3DX_PI)
	{
		fAngleDiff = fAngleDiff + D3DX_PI * 2;
	}

	// ���ʂ�Ԃ�
	return fAngleDiff;
}

//**************************************************
// �X�N���[�����W����3D���W�ɕϊ�����
//**************************************************
D3DXVECTOR3 CMyMath::Posision3Dto2D(D3DXVECTOR3* pOutPos2D, D3DXVECTOR3 pos3D)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	D3DXVECTOR3 PosScreen = {};		// �o�͐�
	D3DVIEWPORT9 viewport = {};		// �r���[�|�[�g
	D3DXMATRIX projectionMtx = {};	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX viewMtx = {};		// �r���[�}�g���b�N�X
	D3DXMATRIX worldMtx = {};		// ���[���h�}�g���b�N�X

	pDevice->GetViewport(&viewport);							// �r���[�|�[�g�擾
	pDevice->GetTransform(D3DTS_PROJECTION, &projectionMtx);	// �v���W�F�N�V�����}�g���b�N�X�擾
	pDevice->GetTransform(D3DTS_VIEW, &viewMtx);				// �r���[�}�g���b�N�X�擾
	D3DXMatrixIdentity(&worldMtx);								// ���[���h�}�g���b�N�X�̏�����

	// �ϊ�����
	D3DXVec3Project(
		&PosScreen,		// �o�͐�̃X�N���[�����W
		&pos3D,		// �ϊ����������[���h���W
		&viewport,		// �r���[�|�[�g���
		&projectionMtx,	// �v���W�F�N�V�����}�g���b�N�X
		&viewMtx,		// �r���[�}�g���b�N�X
		&worldMtx		// ���[���h�}�g���b�N�X
	);

	// ���ʂ���
	*pOutPos2D = PosScreen;

	// ���ʂ�Ԃ�
	return PosScreen;
}

//**************************************************
// �O�p�֐��œ_�Ɠ_�̒�����}�鏈��2D
//**************************************************
float CMyMath::LengthTrigonometric2D(D3DXVECTOR2 posA, D3DXVECTOR2 posB)
{
	float fX = posA.x - posB.x;
	float fY = posA.y - posB.y;
	return sqrtf((fX * fX) + (fY * fY));
}

//**************************************************
// �O�p�֐��œ_�Ɠ_�̒�����}�鏈��3D
//**************************************************
float CMyMath::LengthTrigonometric3D(D3DXVECTOR3 posA, D3DXVECTOR3 posB)
{
	float fX = posA.x - posB.x;
	float fY = posA.y - posB.y;
	float fZ = posA.z - posB.z;
	return sqrtf((fX * fX) + (fY * fY) + (fZ * fZ));
}

//**************************************************
// �~�Ɖ~�̓����蔻��2D
//**************************************************
bool CMyMath::ColiisionCircleCircle2D(D3DXVECTOR2 posA, float fRadiusA, D3DXVECTOR2 posB, float fRadiusB)
{
	// ���E�̒���
	float fLimitLength = fRadiusA + fRadiusB;

	// �_�Ɠ_�̒�����}��
	float fLength = CMyMath::LengthTrigonometric2D(posA, posB);

	// ���E�̒������Z�����
	if (fLength <= fLimitLength)
	{
		// �������Ă��锻��
		return true;
	}

	// �������Ă��Ȃ�
	return false;
}

//**************************************************
// ���Ƌ��̓����蔻��
//**************************************************
bool CMyMath::ColiisionSpherSpher(D3DXVECTOR3 posA, float fRadiusA, D3DXVECTOR3 posB, float fRadiusB)
{
	// ���E�̒���
	float fLimitLength = fRadiusA + fRadiusB;

	// �_�Ɠ_�̒�����}��
	float fLength = CMyMath::LengthTrigonometric3D(posA, posB);

	// ���E�̒������Z�����
	if (fLength <= fLimitLength)
	{
		// �������Ă��锻��
		return true;
	}

	// �������Ă��Ȃ�
	return false;
}

//**************************************************
// �~���Ɖ~���̓����蔻��
//**************************************************
bool CMyMath::ColiisionCylinderCylinder(D3DXVECTOR3 posA, float fRadiusA, float fHeightA, D3DXVECTOR3 posB, float fRadiusB, float fHeightB)
{
	/*
			 |---|		|---|
			 |   |		|   |
		|---||   |		|   ||---|
		|   ||---|		|---||   |
		|   |				 |   |
		|---|				 |---|
		my   par		 my   par
	*/

	// ���g�̒�ӂ�����̒�ӂ�菬�����A�����g�̏�ӂ�����̒�ӂ�荂��
	if (posA.y <= posB.y && posA.y + fHeightA >= posB.y)
	{

	}
	// ���g�̒�ӂ�����̒�ӂ��傫���A�����g�̒�ӂ�����̏�ӂ��Ⴂ
	else if (posA.y >= posB.y && posA.y <= posB.y + fHeightB)
	{

	}
	// �ǂ�ɂ����Ă͂܂�Ȃ�
	else
	{
		return false;
	}

	// D3DXVECTOR3����D3DXVECTOR2�ֈڂ��ւ���
	D3DXVECTOR2 pos2D, pos2DPar;
	pos2D.x = posA.x;
	pos2D.y = posA.z;
	pos2DPar.x = posB.x;
	pos2DPar.y = posB.z;

	// ���E�̒���
	float fLimitLength = fRadiusA + fRadiusB;

	// �_�Ɠ_�̒�����}��
	float fLength = CMyMath::LengthTrigonometric2D(pos2D, pos2DPar);

	// ���E�̒������Z����Γ������Ă��锻��
	if (fLength <= fLimitLength)
	{
		return true;
	}

	// �������Ă��Ȃ�����
	return false;
}