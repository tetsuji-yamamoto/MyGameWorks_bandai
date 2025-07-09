#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

// �����蔻��̈ʒu
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	float fRadius;		// �����蔻��̑傫��
}COLLISIONPOINT;

// �v���g�^�C�v�錾
bool CollisionSphere(D3DXVECTOR3* pPosA, D3DXVECTOR3* pPosB, float fLadiusA, float fLadiusB, bool bPush);
void CollisionPointUpdate(D3DXVECTOR3* pCollisionPos, D3DXMATRIX parentMtx);

#endif
