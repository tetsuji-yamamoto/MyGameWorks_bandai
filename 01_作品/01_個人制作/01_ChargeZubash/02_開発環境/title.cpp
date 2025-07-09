#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "background.h"
#include "lain.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_aPTextureTitle[TITLETYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�ւ̃|�C���^
TITLE g_aTitle[TITLETYPE_MAX];								//�^�C�g���|���S���̏��//�^�C�g���|���S���̃e�N�X�`��
TITLEDIRECTOR g_TitleDirector;

//==============================================
//�^�C�g����ʂ̏���������
//==============================================
void InitTitle(void)
{

	int nCntTitle;

	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLETYPE_MAX, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//���o�\���̏�����
	g_TitleDirector.titleDirect = TITLEDIRECT_LOGODOWN;
	g_TitleDirector.nTimer = 0;
	g_TitleDirector.bBrink = false;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//���̏�����
	for (nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		g_aTitle[nCntTitle].pFileName = NULL;
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].nType = TITLETYPE_MAX;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	InitLain();	//�J

	//�w�i
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_1, BGTYPE_CLOUDY_0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetBackground(FALE_TEX_BG_TITLE_CLOUDY_2, BGTYPE_CLOUDY_1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//���S
	SetTitle(FILE_TEX_TITLE_LOGO,										//�t�@�C���̃p�X
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -LOGO_HEIGHT, 0.0f),	//�ʒu 
		TITLETYPE_LOGO,													//�^�C�v
		D3DXCOLOR(0.9f, 1.0f, 0.0f, 1.0f),								//�F
		LOGO_WIDTH,														//��
		LOGO_HEIGHT);													//����

	//�X�^�[�g�{�^��
	SetTitle(FILE_TEX_TITLE_START,										//�t�@�C���̃p�X
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f, 0.0f),	//�ʒu 
		TITLETYPE_START,												//�^�C�v
		D3DXCOLOR(0.0f, 0.8f, 1.0f, 0.0f),								//�F
		START_WIDTH,													//��
		START_HEIGHT);													//����
}
//==============================================
//�^�C�g����ʂ̏I������
//==============================================
void UninitTitle(void)
{
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		//�e�N�X�`���̔j��
		if (g_aPTextureTitle[nCntTitle] != NULL)
		{
			g_aPTextureTitle[nCntTitle]->Release();
			g_aPTextureTitle[nCntTitle] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	UninitLain();	//�J


	//�w�i�̏I���
	EndBackground(BGTYPE_CLOUDY_0);
	EndBackground(BGTYPE_CLOUDY_1);
}

//==============================================
//�^�C�g����ʂ̍X�V����
//==============================================
void UpdateTitle(void)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true)
		{
			switch (g_TitleDirector.titleDirect)
			{
			case TITLEDIRECT_LOGODOWN:	//���S�~��Ă���
				UpDateLogo(nCntTitle);
				break;

			case TITLEDIRECT_STARTAPPEAR:	//�X�^�[�g�o������
				UpDateStart(nCntTitle);
				break;

			case TITLEDIRECT_STARTBRINK:	//�X�^�[�g�_�ł���
				UpDateStart(nCntTitle);
				break;

			case TITLEDIRECT_STARTBRINK_QUICKLY:	//�X�^�[�g�f�����_�ł���
			//��ʑJ��
				UpDateStart(nCntTitle);
				break;
			}

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	UpdateLain();	//�J
	
	if (KeyboardTrigger(DIK_G) == true)
	{
		SetFade(MODE_GAME);
	}
}

//==============================================
//�^�C�g����ʂ̕`�揈��
//==============================================
void DrawTitle(void)
{
	DrawLain();	//�J

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aPTextureTitle[nCntTitle]);

			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				4 * nCntTitle,							//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);										//�`�悷��v���~�e�B�u�i�v���C���[�j��
		}
	}


}

//==============================================
//�^�C�g���̐ݒ�
//==============================================
void SetTitle(const char* pFileName, D3DXVECTOR3 pos,TITLETYPE type, D3DXCOLOR col,float fWidth,float fHeight)
{
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D* pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�T��
	for (int nCntTitle = 0; nCntTitle < TITLETYPE_MAX; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].pFileName = pFileName;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].col = col;
			g_aTitle[nCntTitle].nType = type;
			g_aTitle[nCntTitle].fWidth = fWidth;
			g_aTitle[nCntTitle].fHeight = fHeight;
			g_aTitle[nCntTitle].bUse = true;

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				g_aTitle[nCntTitle].pFileName,
				&g_aPTextureTitle[nCntTitle]);

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[0].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[1].pos.y = g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth;
			pVtx[2].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth;
			pVtx[3].pos.y = g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight;
			pVtx[3].pos.z = 0.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aTitle[nCntTitle].col;
			pVtx[1].col = g_aTitle[nCntTitle].col;
			pVtx[2].col = g_aTitle[nCntTitle].col;
			pVtx[3].col = g_aTitle[nCntTitle].col;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//======================================
//�^�C�g�����S�̍X�V
//======================================
void UpDateLogo(int nCntTitle)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntTitle;//�ݒ肷�镔���܂Ői�߂�

	if (g_aTitle[nCntTitle].nType == TITLETYPE_LOGO)
	{
		if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//����i�߂�
			g_aTitle[nCntTitle].pos.y = SCREEN_HEIGHT * 0.2f;//�ړI�̈ʒu�ɐݒ�
		}

		if (g_aTitle[nCntTitle].pos.y <= SCREEN_HEIGHT * 0.2f)
		{//�ړI�n���ゾ������
			g_aTitle[nCntTitle].pos.y += 5.0f;
		}
		else
		{
			g_TitleDirector.titleDirect = TITLEDIRECT_STARTAPPEAR;//�X�^�[�g�o����Ԃɂ���
		}

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//======================================
//�X�^�[�g�̍X�V
//======================================
void UpDateStart(int nCntTitle)
{
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntTitle;//�ݒ肷�镔���܂Ői�߂�

	if (g_aTitle[nCntTitle].nType == TITLETYPE_START)
	{
		switch (g_TitleDirector.titleDirect)
		{
		case TITLEDIRECT_STARTAPPEAR:	//�X�^�[�g�o������

			if (g_aTitle[nCntTitle].col.a < 1.0f)
			{//���邭�Ȃ�������
				g_aTitle[nCntTitle].col.a += 0.01;
			}
			else
			{
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBRINK;//�X�^�[�g�o����Ԃɂ���
				g_aTitle[nCntTitle].col.a = 1.0f;
			}

			if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true || GetJoypadTrigger(JOYKEY_A) == true)
			{//���o��΂��p
				SetFade(MODE_TUTORIAL);
				PlaySound(SOUND_LABEL_CURSORDICITION_SE);						//���艹
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBRINK_QUICKLY;	//���̉��o�ɂ���
				g_aTitle[nCntTitle].col.a = 1.0f;								//���邳MAX�ɂ���
			}
			break;

		case TITLEDIRECT_STARTBRINK:	//�X�^�[�g�_�ł���

			if (g_TitleDirector.bBrink == true)
			{//�Â�����
				g_aTitle[nCntTitle].col.a -= 0.01;
				if (g_aTitle[nCntTitle].col.a <= 0.0f)
				{
					g_TitleDirector.bBrink = false;
				}
			}
			else if(g_TitleDirector.bBrink == false)
			{//���邭����
				g_aTitle[nCntTitle].col.a += 0.01;
				if (g_aTitle[nCntTitle].col.a >= 1.0f)
				{
					g_TitleDirector.bBrink = true;
				}
			}

			if (KeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true || GetJoypadTrigger(JOYKEY_A) == true)
			{//���o��΂��p
				SetFade(MODE_TUTORIAL);
				PlaySound(SOUND_LABEL_CURSORDICITION_SE);						//���艹
				g_TitleDirector.titleDirect = TITLEDIRECT_STARTBRINK_QUICKLY;	//���̉��o�ɂ���
			}
			break;

		case TITLEDIRECT_STARTBRINK_QUICKLY:	//�X�^�[�g�_�ł���

			if (g_TitleDirector.bBrink == true)
			{//�Â�����
				g_aTitle[nCntTitle].col.a -= 0.5;
				if (g_aTitle[nCntTitle].col.a <= 0.0f)
				{
					g_TitleDirector.bBrink = false;
				}
			}
			else if (g_TitleDirector.bBrink == false)
			{//���邭����
				g_aTitle[nCntTitle].col.a += 0.5;
				if (g_aTitle[nCntTitle].col.a >= 1.0f)
				{
					g_TitleDirector.bBrink = true;
				}
			}
			break;
		}

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aTitle[nCntTitle].col;
		pVtx[1].col = g_aTitle[nCntTitle].col;
		pVtx[2].col = g_aTitle[nCntTitle].col;
		pVtx[3].col = g_aTitle[nCntTitle].col;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}