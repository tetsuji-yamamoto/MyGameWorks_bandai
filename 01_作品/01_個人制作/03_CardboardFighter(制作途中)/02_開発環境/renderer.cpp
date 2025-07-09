//**********************************************
// 
// �����_���[����
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "renderer.h"
#include "object.h"
#include "object3D.h"
#include "manager.h"
#include "myMath.h"

// �ÓI�����o�[�ϐ��錾
LPDIRECT3DDEVICE9 CRenderer::m_pD3DDevice = NULL;

//**********************************************
// �����_���[�R���X�g���N�^
//**********************************************
CRenderer::CRenderer()
{
	m_pD3D = NULL;										// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	ZeroMemory(m_apTextureMT,sizeof(m_apTextureMT));	// �����_�����O�^�[�Q�b�g�p�e�N�X�`��
	ZeroMemory(m_apRenderMT, sizeof(m_apRenderMT));		// �e�N�X�`�������_�����O�p�C���^�[�[�t�F�[�X
	m_pZBuffMT = NULL;									// �e�N�X�`�������_�����O�pZ�o�b�t�@
	ZeroMemory(&m_viewPortMT,sizeof(D3DVIEWPORT9)) ;	// �e�N�X�`�������_�����O�p�r���[�|�[�g
	ZeroMemory(m_apScreen, sizeof(m_apScreen));			// ��ʗp�|���S��
	m_bBlur = false;									// �ڂ����̗L��
	m_bBlurUp = false;									// �g��ڂ����̗L��
	m_nBlurTime = 0;									// �ڂ�������
	m_nCntBulur = 0;									// �ڂ����J�E���^�[
}

//**********************************************
// �����_���[�f�X�g���N�^
//**********************************************
CRenderer::~CRenderer()
{
}

//**********************************************
// �����_���[����������
//**********************************************
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	// Direc3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^��ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// �p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y��
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y����
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									//
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//
	d3dpp.EnableAutoDepthStencil = TRUE;						//
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//
	d3dpp.Windowed = bWindow;									//
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//

	// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐���(�`�揈�����n�[�h�E�F�A,���_������CPU�ōs��)
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// �J�����O�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// �v���C���[�̒��ɓ����x��������
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���u���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	// �z�񕪉�
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̐���
		m_pD3DDevice->CreateTexture(
			SCREEN_WIDTH,			// �e�N�X�`����
			SCREEN_HEIGHT,			// �e�N�X�`������
			1,						// �~�b�v�}�b�v�����F��
			D3DUSAGE_RENDERTARGET,	// 
			D3DFMT_X8R8G8B8,		// �s�N�Z���t�H�[�}�b�g
			D3DPOOL_DEFAULT,		// �������Ǘ��t���O
			&m_apTextureMT[nCnt],	// 
			NULL					// 
		);

		// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̐���
		m_apTextureMT[nCnt]->GetSurfaceLevel(0, &m_apRenderMT[nCnt]);
	}

	// �e�N�X�`�������_�����O�p��Z�o�b�t�@�̐���
	m_pD3DDevice->CreateDepthStencilSurface(
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffMT,
		NULL
	);

	// �z�񕪉�
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
		m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

		// ���݂�Z�o�b�t�@���擾
		m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

		// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
		m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[nCnt]);

		// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐ���
		m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̃N���A
		m_pD3DDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		// �����_�����O�^�[�Q�b�g�����Ƃɖ߂�
		m_pD3DDevice->SetRenderTarget(0, pRenderDef);

		// Z�o�b�t�@�����Ƃɖ߂�
		m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);
	}

	// �e�N�X�`�������_�����O�p�r���[�|�[�g�̐ݒ�
	m_viewPortMT.X = 0;
	m_viewPortMT.Y = 0;
	m_viewPortMT.Width = SCREEN_WIDTH;
	m_viewPortMT.Height = SCREEN_HEIGHT;
	m_viewPortMT.MinZ = 0.0f;
	m_viewPortMT.MaxZ = 1.0f;

	// ��ʗp�|���S���̐���
	m_apScreen[0] = CScreen::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_apScreen[1] = CScreen::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.85f));

	return S_OK;
}

//**********************************************
// �����_���[�I������
//**********************************************
void CRenderer::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	//Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	// �z�񕪉�
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̔j��
		if (m_apTextureMT[nCnt] != NULL)
		{
			m_apTextureMT[nCnt]->Release();
			m_apTextureMT[nCnt] = NULL;
		}

		// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̔j��
		if (m_apRenderMT[nCnt] != NULL)
		{
			m_apRenderMT[nCnt]->Release();
			m_apRenderMT[nCnt] = NULL;
		}
	}

	// �e�N�X�`�������_�����O�pZ�o�b�t�@�̔j��
	if (m_pZBuffMT != NULL)
	{
		m_pZBuffMT->Release();
		m_pZBuffMT = NULL;
	}

	// �z�񕪉�
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// ��ʃ|���S���̔j��
		m_apScreen[nCnt]->Uninit();
		m_apScreen[nCnt] = NULL;
	}
}

//**********************************************
// �����_���[�X�V����
//**********************************************
void CRenderer::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();

	CObject::UpdateAll();

	//// �u���[�̃I���I�t
	//if (pInputKeyboard->GetTrigger(DIK_Z) == true)
	//{
	//	SetBlur(D3DXCOLOR(1.0f,1.0f,1.0f,0.99f));
	//}

	//// �g��u���[
	//if (pInputKeyboard->GetTrigger(DIK_X) == true)
	//{
	//	// �g��u���[�ݒ�
	//	SetBlurUp(180,1.5f,D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.99f));
	//}

	//// �g��u���[�̍X�V
	//UpdateBulrUp();

	// ��ʃ|���S���̕`��
	//m_apScreen[0]->Update();
	/*m_apScreen[1]->Update();*/
}

//**********************************************
// �����_���[�`�揈��
//**********************************************
void CRenderer::Draw(void)
{
	CDebugprocc* pDebugproc = CManager::GetDebugprocc();
	CCamera* pCamera = CManager::GetCamera();

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
	LPDIRECT3DSURFACE9 pRenderWK;
	LPDIRECT3DTEXTURE9 pTextureWK;

	// ��ʃN���A(�o�b�t�@�o�b�t�@&�̃N���A�j
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// �`��J�n�����������ꍇ

		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
		pDevice->GetRenderTarget(0, &pRenderDef);

		// ���݂�Z�o�b�t�@���擾
		pDevice->GetDepthStencilSurface(&pZBuffDef);

		// �����_�[�^�[�Q�b�g���e�N�X�`��[0]�ύX����
		CManager::GetRenderer()->ChangeTarget(0,D3DXVECTOR3(0.0f, 50.0f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		// �e�N�X�`���̃N���A
		m_pD3DDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

		// �J�����̃Z�b�g
		pCamera->SetCamera();

		// �I�u�W�F�N�g�̕`��
		CObject::DrawAll();

		// �t�B�[�h�o�b�N�p�|���S���Ƀe�N�X�`��[1]�𒣂�t���ĕ`��
		m_apScreen[1]->DrawAlpherTest(m_apTextureMT[1]);

		// �����_�����O�^�[�Q�b�g�����Ƃɖ߂�
		pDevice->SetRenderTarget(0, pRenderDef);

		// Z�o�b�t�@�����Ƃɖ߂�
		pDevice->SetDepthStencilSurface(pZBuffDef);

		// �|���S���Ƀe�N�X�`��[0]���𒣂���ĕ`��
		m_apScreen[0]->Draw(m_apTextureMT[0]);

		// �f�o�b�O�\���̕`�揈��
		pDebugproc->Draw();

		// �e�N�X�`��[0]�ƃe�N�X�`��[1]�����ւ���
		pTextureWK = m_apTextureMT[0];
		m_apTextureMT[0] = m_apTextureMT[1];
		m_apTextureMT[1] = pTextureWK;

		pRenderWK = m_apRenderMT[0];
		m_apRenderMT[0] = m_apRenderMT[1];
		m_apRenderMT[1] = pRenderWK;

		// �`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//**********************************************
// �����_���[�����_�����O�^�[�Q�b�g�̕ύX
//**********************************************
void CRenderer::ChangeTarget(int nIdxTexture,D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect;

	// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[nIdxTexture]);

	// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐ���
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �e�N�X�`�������_�����O�p�r���[�|�[�g��ݒ�
	m_pD3DDevice->SetViewport(&m_viewPortMT);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	// �v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	fAspect = (float)m_viewPortMT.Width / (float)m_viewPortMT.Height;
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		fAspect,
		10.0f,
		10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//**********************************************
// �����_���[�e�N�X�`���[MT�̃N���A����
//**********************************************
void CRenderer::ClearTextureMT(void)
{
	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	// �z�񕪉�
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{

		// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
		m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

		// ���݂�Z�o�b�t�@���擾
		m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

		// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
		m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[nCnt]);

		// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐ���
		m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̃N���A
		m_pD3DDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(255, 100, 100, 100), 1.0f, 0);

		// �����_�����O�^�[�Q�b�g�����Ƃɖ߂�
		m_pD3DDevice->SetRenderTarget(0, pRenderDef);

		// Z�o�b�t�@�����Ƃɖ߂�
		m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);
	}
}

//**********************************************
// �����_���[�ڂ����̐ݒ�
//**********************************************
void CRenderer::SetBlur(D3DXCOLOR bulrColor)
{
	// ���̏�ԂƋt�̏�Ԃɂ���
	m_bBlur = !m_bBlur;

	// �ڂ�����Ԃł����
	if (m_bBlur == true)
	{
		// �F��ݒ�
		m_apScreen[1]->SetColor(bulrColor);	
	}
	// �łȂ����
	else
	{
		// �F��ݒ�
		m_apScreen[1]->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));	
	}
}

//**********************************************
// �����_���[�ڂ����̐ݒ�
//**********************************************
void CRenderer::SetBlurUp(int nBlurTime, float fScaleValue,D3DXCOLOR bulrColor)
{
	// �g��ڂ�����ԃI��
	m_bBlurUp = true;

	// ���Ԑݒ�
	m_nBlurTime = nBlurTime;

	// �J�E���^�[���Z�b�g
	m_nCntBulur = 0;

	// �|���S���̊g��ݒ�
	m_apScreen[1]->SetScaleSize(fScaleValue,nBlurTime);
	
	// �|���S���̐F��ݒ�
	m_apScreen[1]->SetColor(bulrColor);
}

//**********************************************
// �����_���[�ڂ����̍X�V
//**********************************************
void CRenderer::UpdateBulrUp(void)
{
	// �ڂ����Ȃ���ԏo��Ώ������Ȃ�
	if (m_bBlurUp == false)
	{
		return;
	}

	// �ڂ����J�E���^�J�E���g�A�b�v
	m_nCntBulur++;

	// �g�嗦�擾
	float fScaleValue = m_apScreen[1]->GetScaleValue();

	// �|���S���̊g��ݒ�
	m_apScreen[1]->SetScaleSize(fScaleValue, m_nBlurTime);

	// �J�E���^�[���ő�l�܂ŃJ�E���g���ꂽ��I��
	if (Clamp(m_nCntBulur, 0, m_nBlurTime) == m_nBlurTime)
	{
		// �ڂ����Ȃ���Ԃɂ���
		m_bBlurUp = false;

		// �F��ݒ�
		m_apScreen[1]->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));	
	}
}