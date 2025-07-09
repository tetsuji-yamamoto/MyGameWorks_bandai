//#include "beam.h"
//#include "main.h"
//
////�O���[�o���ϐ��錾
//LPDIRECT3DTEXTURE9 g_pTextureBeam = NULL;//�e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBeam = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//Beam g_aBeam[MAX_BEAM];//�G�t�F�N�g�̏��
//
////============================================
////�G�t�F�N�g�̏���������
////============================================
//void InitBeam(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntBeam;
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\BEAM\\boost.png",
//		&g_pTextureBeam);
//
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BEAM, //�K�v�Ȓ��_��
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffBeam,
//		NULL);
//
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
//	g_pVtxBuffBeam->Lock(0, 0, (void**)&pVtx, 0);
//
//	//�G�t�F�N�g�̏��̏�����
//	for (nCntBeam = 0; nCntBeam < MAX_BEAM; nCntBeam++)
//	{
//		g_aBeam[nCntBeam].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aBeam[nCntBeam].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		g_aBeam[nCntBeam].fWidth = 0.0f;
//		g_aBeam[nCntBeam].fHeight = 0.0f;
//		g_aBeam[nCntBeam].bUse = false;
//
//		pVtx[0].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fWidth;
//		pVtx[0].pos.y = g_aBeam[nCntBeam].pos.y - 25.0f;
//		pVtx[0].pos.z = 0.0f;
//		pVtx[1].pos.x = g_aBeam[nCntBeam].pos.x + 100.0f;
//		pVtx[1].pos.y = g_aBeam[nCntBeam].pos.y - 25.0f;
//		pVtx[1].pos.z = 0.0f;
//		pVtx[2].pos.x = g_aBeam[nCntBeam].pos.x - 100.0f;
//		pVtx[2].pos.y = g_aBeam[nCntBeam].pos.y + 25.0f;
//		pVtx[2].pos.z = 0.0f;
//		pVtx[3].pos.x = g_aBeam[nCntBeam].pos.x + 100.0f;
//		pVtx[3].pos.y = g_aBeam[nCntBeam].pos.y + 25.0f;
//		pVtx[3].pos.z = 0.0f;
//
//		//rhw�̐ݒ�
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = g_aBeam[nCntBeam].col;
//		pVtx[1].col = g_aBeam[nCntBeam].col;
//		pVtx[2].col = g_aBeam[nCntBeam].col;
//		pVtx[3].col = g_aBeam[nCntBeam].col;
//
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffBeam->Unlock();
//}
////============================================
////�G�t�F�N�g�̏I������
////============================================
//void UninitBeam(void)
//{
//	//�e�N�X�`���̔j��
//	if (g_pTextureBeam != NULL)
//	{
//		g_pTextureBeam->Release();
//		g_pTextureBeam = NULL;
//	}
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffBeam != NULL)
//	{
//		g_pVtxBuffBeam->Release();
//		g_pVtxBuffBeam = NULL;
//	}
//}
////============================================
////�G�t�F�N�g�̍X�V����
////============================================
//void UpdateBeam(void)
//{
//	int nCntBeam;
//
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
//	g_pVtxBuffBeam->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntBeam = 0; nCntBeam < MAX_BEAM; nCntBeam++)
//	{
//		if (g_aBeam[nCntBeam].bUse == true)
//		{//�G�t�F�N�g���g�p����Ă���
//
//			//���_���W�̐ݒ�
//			pVtx[0].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fRadius;
//			pVtx[0].pos.y = g_aBeam[nCntBeam].pos.y - g_aBeam[nCntBeam].fRadius;
//			pVtx[0].pos.z = 0.0f;
//			pVtx[1].pos.x = g_aBeam[nCntBeam].pos.x + g_aBeam[nCntBeam].fRadius;
//			pVtx[1].pos.y = g_aBeam[nCntBeam].pos.y - g_aBeam[nCntBeam].fRadius;
//			pVtx[1].pos.z = 0.0f;
//			pVtx[2].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fRadius;
//			pVtx[2].pos.y = g_aBeam[nCntBeam].pos.y + g_aBeam[nCntBeam].fRadius;
//			pVtx[2].pos.z = 0.0f;
//			pVtx[3].pos.x = g_aBeam[nCntBeam].pos.x + g_aBeam[nCntBeam].fRadius;
//			pVtx[3].pos.y = g_aBeam[nCntBeam].pos.y + g_aBeam[nCntBeam].fRadius;
//			pVtx[3].pos.z = 0.0f;
//
//			//���_�J���[�̐ݒ�
//			pVtx[0].col = g_aBeam[nCntBeam].col;
//			pVtx[1].col = g_aBeam[nCntBeam].col;
//			pVtx[2].col = g_aBeam[nCntBeam].col;
//			pVtx[3].col = g_aBeam[nCntBeam].col;
//		}
//
//		if (g_aBeam[nCntBeam].fLife <= 0.0f)//�������s����
//		{
//			g_aBeam[nCntBeam].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
//		}
//		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffBeam->Unlock();
//}
////============================================
////�G�t�F�N�g�̕`�揈��
////============================================
//void DrawBeam(void)
//{
//	int nCntBeam;
//
//	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffBeam, 0, sizeof(VERTEX_2D));
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//	//���u�����f�B���O�����Z�����ɐݒ�
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//	//�G�t�F�N�g�̕`��
//	for (nCntBeam = 0; nCntBeam < MAX_BEAM; nCntBeam++)
//	{
//		if (g_aBeam[nCntBeam].bUse == true)
//		{//�G�t�F�N�g���g�p����Ă���
//				//�e�N�X�`���̐ݒ�
//			pDevice->SetTexture(0, g_pTextureBeam);
//			//�|���S���`��
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
//				4 * nCntBeam,							//�`�悷��ŏ��̒��_�C���f�b�N�X
//				2);
//		}
//	}
//	//���u�����f�B���O�����ɖ߂�
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//}
////============================================
////�G�t�F�N�g�̐ݒ菈��
////============================================
//void SetBeam(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fPullRadius, float fPullmove, float fLife)
//{
//	int nCntBeam;
//
//	VERTEX_2D* pVtx;
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffBeam->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntBeam = 0; nCntBeam < MAX_BEAM; nCntBeam++)
//	{
//		if (g_aBeam[nCntBeam].bUse == false)
//		{//�G�t�F�N�g���g�p����Ă��Ȃ�
//			g_aBeam[nCntBeam].pos = pos;
//			g_aBeam[nCntBeam].move = move;
//			g_aBeam[nCntBeam].col = col;
//			g_aBeam[nCntBeam].fRadius = fRadius;
//			g_aBeam[nCntBeam].fPullRadius = fPullRadius;
//			g_aBeam[nCntBeam].fPullmove = fPullmove;
//			g_aBeam[nCntBeam].fLife = fLife;
//			g_aBeam[nCntBeam].bUse = true;//�g�p���Ă����Ԃɂ���
//
//			g_aBeam[nCntBeam].fMultiAlpha = g_aBeam[nCntBeam].col.a * (1 / g_aBeam[nCntBeam].fLife);
//
//			//���_���p�̐ݒ�
//			pVtx[0].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fRadius;
//			pVtx[0].pos.y = g_aBeam[nCntBeam].pos.y - g_aBeam[nCntBeam].fRadius;
//			pVtx[0].pos.z = 0.0f;
//			pVtx[1].pos.x = g_aBeam[nCntBeam].pos.x + g_aBeam[nCntBeam].fRadius;
//			pVtx[1].pos.y = g_aBeam[nCntBeam].pos.y - g_aBeam[nCntBeam].fRadius;
//			pVtx[1].pos.z = 0.0f;
//			pVtx[2].pos.x = g_aBeam[nCntBeam].pos.x - g_aBeam[nCntBeam].fRadius;
//			pVtx[2].pos.y = g_aBeam[nCntBeam].pos.y + g_aBeam[nCntBeam].fRadius;
//			pVtx[2].pos.z = 0.0f;
//			pVtx[3].pos.x = g_aBeam[nCntBeam].pos.x + g_aBeam[nCntBeam].fRadius;
//			pVtx[3].pos.y = g_aBeam[nCntBeam].pos.y + g_aBeam[nCntBeam].fRadius;
//			pVtx[3].pos.z = 0.0f;
//
//			break;
//		}
//		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffBeam->Unlock();
//}