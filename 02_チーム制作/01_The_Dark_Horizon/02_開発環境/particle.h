#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "effect.h"

#define MAX_PARTICLE (256)	// �ő�p�[�e�B�N����

// �p�[�e�B�N���^�C�v
typedef enum
{
	PATITYPE_NOMAL = 0,// �ʏ�
	PATITYPE_MAX
}PATITIPE;

// �p�[�e�B�N���\����
typedef struct
{
	int nAmount;	// �o����
	bool bUse;
}PARTICLE;

// �v���g�^�C�v�錾
void InitParticle(void);
void UpdateParticle(void);
void SetParticle(EFFECTTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 gravity, D3DXCOLOR col, int nAmount, int nLife, float fSize, float fSpeed, bool bShadow, bool bSubtractive);

#endif // !_PARTICLE_H_
