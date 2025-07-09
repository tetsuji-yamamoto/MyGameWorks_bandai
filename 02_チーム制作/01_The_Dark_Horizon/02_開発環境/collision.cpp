#include "collision.h"
#include "effect.h"

//******************************************************
// ���̓����蔻��
//******************************************************
bool CollisionSphere(D3DXVECTOR3 *pPosA, D3DXVECTOR3 *pPosB,float fLadiusA, float fLadiusB,bool bPush)
{
	bool bCollision = false;
	float fRange = fLadiusA + fLadiusB;		// ���a�Ɣ��a�𑫂����l
	D3DXVECTOR3 vecA = *pPosA - *pPosB;		// �x�N�g��A
	D3DXVECTOR3 vecB;						// fRange�̂Ƃ��̃x�N�g���̒l
	D3DXVECTOR3 vecC;						// fRange�̂Ƃ��̃x�N�g���̒l

	// ���������߂�
	float fLength = sqrtf((vecA.x * vecA.x) + (vecA.y * vecA.y) + (vecA.z * vecA.z));

	if (fLength <= 0)
	{
		fLength = 1;
	}

	if (fLength <= fRange)
	{// �Z��������
		bCollision = true;
		vecB = (fRange * vecA) / fLength;
		vecC = vecB - vecA;

		if (bPush)
		{// �����Ԃ��Ă�������
			*pPosA += vecC;
		}

	}

	// ���ʂ�Ԃ�
	return bCollision;
}

//******************************************************
// �����蔻��̈ʒu�X�V
//******************************************************
void CollisionPointUpdate(D3DXVECTOR3* pCollisionPos, D3DXMATRIX parentMtx)
{
	pCollisionPos->x = parentMtx._41;
	pCollisionPos->y = parentMtx._42;
	pCollisionPos->z = parentMtx._43;
}