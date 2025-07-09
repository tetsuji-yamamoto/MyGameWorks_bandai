#ifndef _TERRITRY_H_
#define _TERRITRY_H_

#include "main.h"

// �e���g���[�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	float fRadius;		// ���a(�͈�)
	float fAngle;		// �s������
	int nTimer;			// ���Ԍv���p
	int nBreakTimer;	// �x�e���Ԍv���p
	int nPatrolTimer;	// �p�g���[���^�C�}�[
	int nAngerTimer;	// �{��^�C�}�[
	int nPatrolRimit;	// ������E����
}TERRITRY;

void SetTerritry(TERRITRY* pTerritry, D3DXVECTOR3 territryPos, float fRadius);
bool TerritryConfirmation(TERRITRY territry, D3DXVECTOR3 nowPos);

#endif // !_TERRITRY_H_
