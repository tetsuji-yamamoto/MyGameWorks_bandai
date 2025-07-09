#include "territry.h"

// �v���g�^�C�v�錾

//*******************************************
// �e���g���[�̃Z�b�g
//*******************************************
void SetTerritry(TERRITRY * pTerritry,D3DXVECTOR3 territryPos,float fRadius)
{
	pTerritry->pos = territryPos;	// �ʒu�ݒ�
	pTerritry->fRadius = fRadius;	// ���a�ݒ�
}

//*******************************************
// �e���g���[�̊m�F
//*******************************************
bool TerritryConfirmation(TERRITRY territry, D3DXVECTOR3 nowPos)
{
	bool bOutSide = false;	// �O���ɏo�Ă܂����H

	// �e���g���[�̒��S���獡�̈ʒu�̃x�N�g��
	D3DXVECTOR3 vecA = nowPos - territry.pos;	

	// ������}��
	float fLength = sqrtf((vecA.x * vecA.x) + (vecA.y * vecA.y) + (vecA.z * vecA.z));

	if (fLength >= territry.fRadius)
	{// ���a���f�J��������
		bOutSide = true;	// �o�Ă��
	}

	// ���ʂ�Ԃ�
	return bOutSide;
}