#include "smoke.h"
#include "effect.h"

// �O���[�o���ϐ��錾
SMOKE g_aSmoke[MAX_SMOKE];	// �����

//************************************************
// ���̏�����
//************************************************
void InitSmoke(void)
{
	for (int nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		g_aSmoke[nCntSmoke].nOccurrenceTimer = 0;				// �����^�C�}�[
		g_aSmoke[nCntSmoke].nOccurrenceInterval = 0;			// �����Ԋu
		g_aSmoke[nCntSmoke].fSize = 0.0f;						// �傫��
		g_aSmoke[nCntSmoke].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);	// �ʒu
		g_aSmoke[nCntSmoke].bUse = false;						// �g���ĂȂ�
		g_aSmoke[nCntSmoke].bAttach = false;					// ���t���Ȃ�
	}
}

//************************************************
// ���̐ݒ�
//************************************************
int SetSmoke(SMOKETYPE type, D3DXVECTOR3 pos,int nOccurrenceInterval,float fSize,bool bAttach)
{
	int nCntSmoke = 0;
	for (nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		if (g_aSmoke[nCntSmoke].bUse == false)
		{
			g_aSmoke[nCntSmoke].type = type;								// ���
			g_aSmoke[nCntSmoke].nOccurrenceTimer = 0;						// �����^�C�}�[
			g_aSmoke[nCntSmoke].nOccurrenceInterval = nOccurrenceInterval;	// �����Ԋu
			g_aSmoke[nCntSmoke].fSize = fSize;								// �����Ԋu
			g_aSmoke[nCntSmoke].pos = pos;									// �ʒu
			g_aSmoke[nCntSmoke].bUse = true;								// �g���Ă�
			g_aSmoke[nCntSmoke].bAttach = bAttach;							// ���t����H
			break;
		}
	}

	// ���ʂ�Ԃ�
	return nCntSmoke;
}

//************************************************
// ���̍X�V
//************************************************
void UpdateSmoke(void)
{
	for (int nCntSmoke = 0; nCntSmoke < MAX_SMOKE; nCntSmoke++)
	{
		if (g_aSmoke[nCntSmoke].bUse)
		{
			switch (g_aSmoke[nCntSmoke].type)
			{
			case SMOKETYPE_NOMAL:
				g_aSmoke[nCntSmoke].nOccurrenceTimer++;	// �����J�E���^�[���Z

				if (g_aSmoke[nCntSmoke].nOccurrenceTimer >= g_aSmoke[nCntSmoke].nOccurrenceInterval)
				{// �����Ԋu����ɂȂ�����,���𔭐�������
					g_aSmoke[nCntSmoke].nOccurrenceTimer = 0;	// �J�E���^�[���Z�b�g

					SetEffect(EFFECTTYPE_SMOKE,				// �^�C�v
						g_aSmoke[nCntSmoke].pos,			// �ʒu
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ړ���
						D3DXVECTOR3(0.0f, 0.01f, 0.0f),		// �d��
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// �F
						120,								// ����
						g_aSmoke[nCntSmoke].fSize,			// �傫��
						false,								// �e�̎d�l�L��
						true								// ���Z����
					);
				}
				break;
			}
			
		}
	}
}

//************************************************
// ���̍X�V
//************************************************
bool UpdateAttachSmoke(int nIdx, D3DXVECTOR3 pos)
{
	bool bResult = false;
	g_aSmoke[nIdx].nOccurrenceTimer++;	// �����J�E���^�[���Z

	if (g_aSmoke[nIdx].nOccurrenceTimer >= g_aSmoke[nIdx].nOccurrenceInterval)
	{// �����Ԋu����ɂȂ�����,���𔭐�������
		g_aSmoke[nIdx].nOccurrenceTimer = 0;	// �J�E���^�[���Z�b�g

		bResult = true;

		SetEffect(EFFECTTYPE_SMOKE,				// �^�C�v
			pos,								// �ʒu
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// �ړ���
			D3DXVECTOR3(0.0f, 0.01f, 0.0f),		// �d��
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),	// �F
			60,									// ����
			g_aSmoke[nIdx].fSize,				// �傫��
			false,								// �e�̎d�l�L��
			true								// ���Z����
		);
	}

	//���ʂ�Ԃ�
	return bResult;
}