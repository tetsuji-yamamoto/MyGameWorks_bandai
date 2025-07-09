#include "main.h"
#include "particle.h"
#include "effect.h"
#include "sword.h"

//�O���[�o���ϐ��錾
Particle g_aParticle[MAX_PARTICLE];	//�p�[�e�B�N�����
int g_nParticleCounter;

//--------------------------------
//�p�[�e�B�N����
//--------------------------------
void InitParticle(void)
{
	int nCntParticle;

	g_nParticleCounter = 0;
	//�p�[�e�B�N���̏��̏�����
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_aParticle[nCntParticle].nNumAppear = 0;
		g_aParticle[nCntParticle].nRange = 0;
		g_aParticle[nCntParticle].nSpeedRange = 0.0f;
		g_aParticle[nCntParticle].fPullMove = 0.0f;
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].fPullRadius = 0.0f;
		g_aParticle[nCntParticle].fAngle = 0.0f;
		g_aParticle[nCntParticle].fLife = 0.0f;
		g_aParticle[nCntParticle].bUse = false;
	}
}
//--------------------------------
//�p�[�e�B�N����
//--------------------------------
void UninitParticle(void)
{

}
//--------------------------------
//�p�[�e�B�N���̍X�V����
//--------------------------------
void UpdateParticle(void)
{
	SWORD* pSword = GetSword();

	int nCntParticle;
	int nCntAppear;
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�F
	int nType;			//���
	int nDeleetType;
	int nNumAppear;		//�o����
	int nSpeedRange;	//�����͈̔�
	int nRange;			//�o���p�x
	float fPullMove;	//�ړ��ʂ̌����W��
	float fRadius;		//���_���W�̐ݒ�
	float fPullRadius;	//���_���W�̐ݒ�
	float fAngle;		//�p�x
	float fSpeed;		//����
	float fLife;		//����
	float fLowSpeed;	//�Œ�̈ړ���
	float fWidth;		//��
	float fHeight;		//����
	float fAngleEffect = 0.0f;	//�G�t�F�N�g�̊p�x

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			nNumAppear = g_aParticle[nCntParticle].nNumAppear;		//�o����
			nRange = g_aParticle[nCntParticle].nRange;				//�o���p�x
			nSpeedRange = g_aParticle[nCntParticle].nSpeedRange;	//�����͈̔�
			fAngle = g_aParticle[nCntParticle].fAngle;				//�_���̊p�x

			pos = g_aParticle[nCntParticle].pos;					//�ʒu
			col = g_aParticle[nCntParticle].col;					//�F
			nType = g_aParticle[nCntParticle].nType;				//���
			nDeleetType = g_aParticle[nCntParticle].nDeleetType;				//���
			fRadius = g_aParticle[nCntParticle].fRadius;			//�傫���̐ݒ�
			fPullRadius = g_aParticle[nCntParticle].fPullRadius;	//����������W���̐ݒ�
			fPullMove = g_aParticle[nCntParticle].fPullMove;		//�ړ��ʂ̌����W��
			fLife = g_aParticle[nCntParticle].fLife;				//����
			fLowSpeed = g_aParticle[nCntParticle].fLowSpeed;		//�Œ�̈ړ���
			fWidth = g_aParticle[nCntParticle].fWidth;				//��
			fHeight = g_aParticle[nCntParticle].fHeight;			//����

			//�p�[�e�B�N������(��������)
			for (nCntAppear = 0; nCntAppear < nNumAppear; nCntAppear++)
			{
				fAngle += (float)(rand() % ((nRange * 2) + 1) -nRange) / 100.0f;
				fSpeed = (float)(rand() % nSpeedRange) + fLowSpeed;

				fAngleEffect = pSword->fKeepLot;
				fAngleEffect += ((float)(rand() % 14) - 7) / 100.0f;

				//�ړ��ʂ̐ݒ�
				move.x = sinf(fAngle) * (fSpeed);
				move.y = cosf(fAngle) * (fSpeed);

				//�G�t�F�N�g�̐ݒ�
				SetEffect(pos,								//�ʒu
					D3DXVECTOR3(move.x, move.y, move.z),	//�ړ���
					col,			//�F
					nType,			//�ʏ�G�t�F�N�g
					fRadius,		//�|���S���T�C�Y
					fHeight,		//����
					fWidth,			//��
					fPullRadius,	//�|���S���T�C�Y������
					fPullMove,		//�ړ��ʌ�����
					fLife,			//����
					fAngleEffect,	//�|���S�����̂̊p�x
					nDeleetType
				);	
			}

			//�I���
			g_aParticle[nCntParticle].bUse = false;
		}
	}
}

//--------------------------------
//�p�[�e�B�N����
//--------------------------------
void DrawParticle(void)
{
	
}

//--------------------------------
//�p�[�e�B�N����
//--------------------------------
void SetParticle(D3DXVECTOR3 pos,D3DXCOLOR col,int nType,int nNumAppear,int nRange, int nSpeedRange,float fPullMove,float fRadius,  float fPullRadius, float fAngle,float fLife,float fLowSpeed,float fWidth,float fHeight,int nDeleetType)
{
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{//�p�[�e�B�N�����g�p����Ă��Ȃ�
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].col = col;
			g_aParticle[nCntParticle].nType = nType;
			g_aParticle[nCntParticle].nDeleetType = nDeleetType;
			g_aParticle[nCntParticle].nNumAppear = nNumAppear;
			g_aParticle[nCntParticle].nRange = nRange;
			g_aParticle[nCntParticle].nSpeedRange = nSpeedRange;
			g_aParticle[nCntParticle].fPullMove = fPullMove;
			g_aParticle[nCntParticle].fRadius = fRadius;
			g_aParticle[nCntParticle].fPullRadius = fPullRadius;
			g_aParticle[nCntParticle].fAngle = fAngle;
			g_aParticle[nCntParticle].fLife = fLife;
			g_aParticle[nCntParticle].fLowSpeed = fLowSpeed;
			g_aParticle[nCntParticle].fWidth = fWidth;
			g_aParticle[nCntParticle].fHeight = fHeight;
			g_aParticle[nCntParticle].bUse = true;//�g�p���Ă����Ԃɂ���
			break;
		}
	}
}