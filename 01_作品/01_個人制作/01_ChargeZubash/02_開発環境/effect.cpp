#include "effect.h"
#include "main.h"
#include "player.h"
#include "sword.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureEffect = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];						//�G�t�F�N�g�̏��

//------------------
//�G�t�F�N�g�̏���������
//------------------
void InitEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\EFFECT\\effect000.jpg",
		&g_aPTextureEffect);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//�G�t�F�N�g�̏��̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].vertex.BottomLeft = D3DXVECTOR2(0.0f,0.0f);
		g_aEffect[nCntEffect].vertex.BottomRight = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[nCntEffect].vertex.TopLeft = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[nCntEffect].vertex.TopRight = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].fPullRadius = 0.0f;
		g_aEffect[nCntEffect].fPullmove = 0.0f;
		g_aEffect[nCntEffect].fMultiAlpha = 0.0f;
		g_aEffect[nCntEffect].fLife = 0.0f;
		g_aEffect[nCntEffect].fLength = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].bUse = false;

		pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - 100.0f;
		pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - 25.0f;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + 100.0f;
		pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - 25.0f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - 100.0f;
		pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + 25.0f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + 100.0f;
		pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + 25.0f;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f
			;
		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aEffect[nCntEffect].col;
		pVtx[1].col = g_aEffect[nCntEffect].col;
		pVtx[2].col = g_aEffect[nCntEffect].col;
		pVtx[3].col = g_aEffect[nCntEffect].col;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
//-------------
//�G�t�F�N�g�̏I������
//-------------
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_aPTextureEffect != NULL)
	{
		g_aPTextureEffect->Release();
		g_aPTextureEffect = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//-------------------
//�G�t�F�N�g�̍X�V����
//--------------------
void UpdateEffect(void)
{
	int nCntEffect;

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���

			switch (g_aEffect[nCntEffect].nType)
			{
				//�ʏ�
			case EFFECTTYPE_NOMAL:
				//��������
				g_aEffect[nCntEffect].fLife -= 1.0f;

				//�A���t�@�l����
				g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fMultiAlpha;

				//�ړ��ʂ��X�V
				g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
				g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

				//�|���S���T�C�Y����
				g_aEffect[nCntEffect].fRadius += g_aEffect[nCntEffect].fRadius * -1 * g_aEffect[nCntEffect].fPullRadius;

				//�ړ��ʌ���
				g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullmove;
				g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullmove;

				//���_���W�̐ݒ�
				pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
				pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
				pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
				pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
				pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
				pVtx[3].pos.z = 0.0f;

				//���_�J���[�̐ݒ�
				pVtx[0].col = g_aEffect[nCntEffect].col;
				pVtx[1].col = g_aEffect[nCntEffect].col;
				pVtx[2].col = g_aEffect[nCntEffect].col;
				pVtx[3].col = g_aEffect[nCntEffect].col;
					break;

				//��
			case EFFECTTYPE_THUNDER:
				UpdataThunderEffect(nCntEffect);
				break;

				//�r�[���\�[�h
			case EFFECTTYPE_BEAMSWORD:
				UpdataBeamSwordEffect(nCntEffect);
					break;

				//�r�[��
			case EFFECTTYPE_BEAM:
				UpdataBeamEffect(nCntEffect);
				break;

				//�U�����肠��
			case EFFECTTYPE_ATTACK:
				UpDateAttackEffect(nCntEffect);
				break;

			default:
				break;
			}
			
		}
		
		if (g_aEffect[nCntEffect].fLife <= 0.0f)//�������s����
		{
			g_aEffect[nCntEffect].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
//--------------------
//�G�t�F�N�g�̕`�揈��
//--------------------
void DrawEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//�G�t�F�N�g�̕`��
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���
				//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureEffect);
			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntEffect,							//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);
		}
	}
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//============================================
//�G�t�F�N�g�̐ݒ菈��
//============================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,int nType, float fRadius, float fHeight, float fWidth, float fPullRadius, float fPullmove, float fLife,float fLot, int nDeleetType)
{
	int nCntEffect;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//�G�t�F�N�g���g�p����Ă��Ȃ�
			g_aEffect[nCntEffect].vertex.BottomLeft = D3DXVECTOR2(fWidth, fHeight);
			g_aEffect[nCntEffect].vertex.BottomRight = D3DXVECTOR2(fWidth, fHeight);
			g_aEffect[nCntEffect].vertex.TopLeft = D3DXVECTOR2(fWidth, fHeight);
			g_aEffect[nCntEffect].vertex.TopRight = D3DXVECTOR2(fWidth, fHeight);
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].nType = nType;
			g_aEffect[nCntEffect].nDeleetType = nDeleetType;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].fHeight = fHeight;
			g_aEffect[nCntEffect].fWidth = fWidth;
			g_aEffect[nCntEffect].fPullRadius = fPullRadius;
			g_aEffect[nCntEffect].fPullmove = fPullmove;
			g_aEffect[nCntEffect].fLife = fLife;
			g_aEffect[nCntEffect].fLot = fLot;
			g_aEffect[nCntEffect].bUse = true;//�g�p���Ă����Ԃɂ���

			g_aEffect[nCntEffect].fMultiAlpha = g_aEffect[nCntEffect].col.a * (1 / g_aEffect[nCntEffect].fLife);

			g_aEffect[nCntEffect].fAngle = atan2f(g_aEffect[nCntEffect].fHeight, g_aEffect[nCntEffect].fWidth);
			g_aEffect[nCntEffect].fLength = sqrtf((g_aEffect[nCntEffect].fWidth * g_aEffect[nCntEffect].fWidth) + (g_aEffect[nCntEffect].fHeight * g_aEffect[nCntEffect].fHeight));

			//���_���p�̐ݒ�
			pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius ;
			pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius ;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius ;
			pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius ;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius ;
			pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius ;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius ;
			pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius ;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;
			break;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//============================================
//�r�[���\�[�h�G�t�F�N�g�̍X�V
//============================================
void UpdataBeamSwordEffect(int nCntEffect)
{
	//�v���C���[�擾
	Player* pPlayer = GetPlayer();
	//���擾
	SWORD* pSword = GetSword();

	float fAngle = 0.0f;
	float fLength = 0.0f;
	float fLot = 0.0f;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEffect;

	g_aEffect[nCntEffect].pos = pSword->pos;

	fAngle = atan2f(g_aEffect[nCntEffect].fHeight, g_aEffect[nCntEffect].fWidth);
	fLength = sqrtf((g_aEffect[nCntEffect].fWidth * g_aEffect[nCntEffect].fWidth) + (g_aEffect[nCntEffect].fHeight * g_aEffect[nCntEffect].fHeight));

	if (pPlayer->bDirection == false)
	{//������
		pSword->pos.x = pPlayer->pos.x - pSword->fPositionX;	//�ʒuX
		fLot = pSword->fLot * -1.0f;							//����
	}
	else if (pPlayer->bDirection == true)
	{//�E����
		pSword->pos.x = pPlayer->pos.x + pSword->fPositionX;	//�ʒuX
		fLot = pSword->fLot;									//����
	}

	g_aEffect[nCntEffect].vertex.TopLeft.x = sinf(-D3DX_PI * 0.5f + fAngle - fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopLeft.y = cosf(D3DX_PI * 0.5f + fAngle - fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopRight.x = sinf(D3DX_PI * 0.5f + fAngle + fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopRight.y = cosf(D3DX_PI * 0.5f + fAngle + fLot) * fLength;
	g_aEffect[nCntEffect].vertex.BottomLeft.x = sinf(-D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomLeft.y = cosf(-D3DX_PI * 0.5 + fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomRight.x = sinf(D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomRight.y = cosf(-D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.TopLeft.x;;
	pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.TopLeft.y;;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.TopRight.x;
	pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.TopRight.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.BottomLeft.x;
	pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.BottomLeft.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.BottomRight.x;
	pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.BottomRight.y;
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_aEffect[nCntEffect].col;
	pVtx[1].col = g_aEffect[nCntEffect].col;
	pVtx[2].col = g_aEffect[nCntEffect].col;
	pVtx[3].col = g_aEffect[nCntEffect].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//============================================
//�U���G�t�F�N�g�̍X�V
//============================================
void UpDateAttackEffect(int nCntEffect)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEffect;

	//��������
	g_aEffect[nCntEffect].fLife -= 1.0f;

	//�A���t�@�l����
	g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fMultiAlpha;

	//�ړ��ʂ��X�V
	g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
	g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

	//�|���S���T�C�Y����
	g_aEffect[nCntEffect].fRadius += g_aEffect[nCntEffect].fRadius * -1 * g_aEffect[nCntEffect].fPullRadius;

	//�ړ��ʌ���
	g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullmove;
	g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullmove;

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
	pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
	pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
	pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
	pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_aEffect[nCntEffect].col;
	pVtx[1].col = g_aEffect[nCntEffect].col;
	pVtx[2].col = g_aEffect[nCntEffect].col;
	pVtx[3].col = g_aEffect[nCntEffect].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//============================================
//�G�t�F�N�g������
//============================================
void EndEffect(int nType, int nDeleetType)
{
	int nCntEffect;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true && g_aEffect[nCntEffect].nType == nType && g_aEffect[nCntEffect].nDeleetType == nDeleetType)
		{//�G�t�F�N�g���g�p����Ă��Ȃ�
			g_aEffect[nCntEffect].bUse = false;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//============================================
//�r�[���G�t�F�N�g�̍X�V
//============================================
void UpdataBeamEffect(int nCntEffect)
{
	//�v���C���[�擾
	Player* pPlayer = GetPlayer();
	//���擾
	SWORD* pSword = GetSword();

	float fAngle = 0.0f;
	float fLength = 0.0f;
	float fLot = 0.0f;

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEffect;

	//��������
	g_aEffect[nCntEffect].fLife -= 1.0f;

	//�A���t�@�l����
	g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fMultiAlpha;

	//�ړ��ʂ��X�V
	g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
	g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

	//�ړ��ʌ���
	g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullmove;
	g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullmove;

	fAngle = g_aEffect[nCntEffect].fAngle;
	fLength = g_aEffect[nCntEffect].fLength;
	fLot = g_aEffect[nCntEffect].fLot;

	g_aEffect[nCntEffect].vertex.TopLeft.x = sinf(-D3DX_PI * 0.5f + fAngle - fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopLeft.y = cosf(D3DX_PI * 0.5f + fAngle - fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopRight.x = sinf(D3DX_PI * 0.5f + fAngle + fLot) * fLength;
	g_aEffect[nCntEffect].vertex.TopRight.y = cosf(D3DX_PI * 0.5f + fAngle + fLot) * fLength;
	g_aEffect[nCntEffect].vertex.BottomLeft.x = sinf(-D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomLeft.y = cosf(-D3DX_PI * 0.5 + fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomRight.x = sinf(D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;
	g_aEffect[nCntEffect].vertex.BottomRight.y = cosf(-D3DX_PI * 0.5 - fLot) * g_aEffect[nCntEffect].fWidth;

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.TopLeft.x;
	pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.TopLeft.y;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.TopRight.x;
	pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.TopRight.y;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.BottomLeft.x;
	pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.BottomLeft.y;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].vertex.BottomRight.x;
	pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].vertex.BottomRight.y;
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_aEffect[nCntEffect].col;
	pVtx[1].col = g_aEffect[nCntEffect].col;
	pVtx[2].col = g_aEffect[nCntEffect].col;
	pVtx[3].col = g_aEffect[nCntEffect].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//============================================
//���̍X�V
//============================================
void UpdataThunderEffect(int nCntEffect)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEffect;

	//��������
	g_aEffect[nCntEffect].fLife -= 1.0f;

	//�A���t�@�l����
	g_aEffect[nCntEffect].col.a -= g_aEffect[nCntEffect].fMultiAlpha;

	//�ړ��ʂ��X�V
	g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
	g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

	//�|���S���T�C�Y����
	g_aEffect[nCntEffect].fRadius += g_aEffect[nCntEffect].fRadius * -1 * g_aEffect[nCntEffect].fPullRadius;

	//�ړ��ʌ���
	g_aEffect[nCntEffect].move.x += g_aEffect[nCntEffect].move.x * -1 * g_aEffect[nCntEffect].fPullmove;
	g_aEffect[nCntEffect].move.y += g_aEffect[nCntEffect].move.y * -1 * g_aEffect[nCntEffect].fPullmove;

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
	pVtx[0].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
	pVtx[1].pos.y = g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius;
	pVtx[2].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius;
	pVtx[3].pos.y = g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius;
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_aEffect[nCntEffect].col;
	pVtx[1].col = g_aEffect[nCntEffect].col;
	pVtx[2].col = g_aEffect[nCntEffect].col;
	pVtx[3].col = g_aEffect[nCntEffect].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}