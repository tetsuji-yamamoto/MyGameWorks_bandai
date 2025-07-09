#include "effect.h"
#include "particle.h"

// �O���[�o���ϐ��錾
PARTICLE g_aParticle[MAX_PARTICLE];						// �p�[�e�B�N��

//**************************************
// �p�[�e�B�N���̏�����
//**************************************
void InitParticle(void)
{
	for (int nCntPati = 0; nCntPati < MAX_PARTICLE; nCntPati++)
	{
	
	}
}

//**************************************
// �p�[�e�B�N���̍X�V
//**************************************
void UpdateParticle(void)
{

}

//**************************************
// �p�[�e�B�N���̐ݒ�
//**************************************
void SetParticle(EFFECTTYPE type,D3DXVECTOR3 pos, D3DXVECTOR3 gravity, D3DXCOLOR col, int nAmount,int nLife,float fSize,float fSpeed,bool bShadow,bool bSubtractive)
{
	D3DXVECTOR3 move;	// �ړ��ʎZ�o�p
	float fLotA;		// �p�x
	float fLotB;		// �p�x

	for (int nCntPati = 0; nCntPati < nAmount; nCntPati++)
	{
		fLotA = (float)(rand() % 628 - 314) * 0.01f;	// �����_���Ŋp�x�Z�o
		fLotB = (float)(rand() % 628 - 314) * 0.01f;	// �����_���Ŋp�x�Z�o
		move.x = sinf(fLotA) * sinf(fLotB) * fSpeed;
		move.y = cosf(fLotA) * fSpeed;
		move.z = sinf(fLotA) * cosf(fLotB) * fSpeed;

		SetEffect(type,		// �^�C�v
			pos,			// �ʒu
			move,			// �ړ���
			gravity,		// �d��
			col,			// �F
			nLife,			// ����
			fSize,			// �傫��
			bShadow,		// �e�̎d�l�L��
			bSubtractive	// ���Z����
		);
	}
}