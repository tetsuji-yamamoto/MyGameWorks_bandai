//**********************************************
// 
// �X�N���[������
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "screen.h"
#include "renderer.h"
#include "manager.h"

//**********************************************
// �X�N���[���R���X�g���N�^
//**********************************************
CScreen::CScreen()
{
	m_pVtxBuff = NULL;							// ���_�o�b�t�@
	m_fWidth = 0.0f;							// ��
	m_fHeight = 0.0f;							// ����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
	m_fSize = 0.0f;								// �傫��

	m_bScale = false;		// �g��̗L��
	m_fScaleValue = 0.0f;	// �g�嗦
	m_fScaleValueNow = 0.0f;// ���̊g�嗦
	m_nFrameScale = 0.0f;	// �g�傷�鎞��
	m_nCntScale = 0;		// �g��J�E���^�[
}

//**********************************************
// �X�N���[���f�X�g���N�^
//**********************************************
CScreen::~CScreen()
{
}

//**********************************************
// �X�N���[������������
//**********************************************
void CScreen::Init(D3DXCOLOR col)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	HRESULT hr;

	// ���_�o�b�t�@�̐���
	hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CScreen::Init > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
	}

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	float fWCenter = SCREEN_WIDTH * 0.5f;
	float fHCenter = SCREEN_HEIGHT * 0.5f;

	m_fWidth = fWCenter;
	m_fHeight = fHCenter;
	m_pos = D3DXVECTOR3(fWCenter, fHCenter, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = col;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = fWCenter - fWCenter;
	pVtx[0].pos.y = fHCenter - fHCenter;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fWCenter + fWCenter;
	pVtx[1].pos.y = fHCenter - fHCenter;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = fWCenter - fWCenter;
	pVtx[2].pos.y = fHCenter + fHCenter;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fWCenter + fWCenter;
	pVtx[3].pos.y = fHCenter + fHCenter;
	pVtx[3].pos.z = 0.0f;

	float fShiftX = (0.5f / SCREEN_WIDTH);
	float fShiftY = (0.5f / SCREEN_HEIGHT);

	pVtx[0].tex = D3DXVECTOR2(0.0f + fShiftX, 0.0f + fShiftY);
	pVtx[1].tex = D3DXVECTOR2(1.0f + fShiftX, 0.0f + fShiftY);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fShiftX, 1.0f + fShiftY);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fShiftX, 1.0f + fShiftY);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = m_col;
		pVtx[nCntVtx].rhw = 1.0f;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//**********************************************
// �X�N���[���I������
//**********************************************
void CScreen::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// ���g�̔j��
	delete this;
}

//**********************************************
// �X�N���[���X�V����
//**********************************************
void CScreen::Update()
{
	// �L�[�{�[�h�擾
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();	

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// �g��̍X�V
	UpdateScale();

	// �g�嗦���|�������ƍ��������߂�
	float fWidth = m_fWidth * (m_fScaleValueNow);
	float fHeight = m_fHeight * (m_fScaleValueNow);

	float fLength = sqrtf((fWidth * fWidth) + (fHeight * fHeight));
	float fAngleA = atan2f(fWidth, fHeight);
	float fAngleB = atan2f(fWidth, -fHeight);

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = (m_pos.x + fLength * sinf(m_rot.z - fAngleB));
	pVtx[0].pos.y = (m_pos.y + fLength * cosf(m_rot.z - fAngleB));
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = (m_pos.x + fLength * sinf(m_rot.z + fAngleB));
	pVtx[1].pos.y = (m_pos.y + fLength * cosf(m_rot.z + fAngleB));
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = (m_pos.x + fLength * sinf(m_rot.z - fAngleA));
	pVtx[2].pos.y = (m_pos.y + fLength * cosf(m_rot.z - fAngleA));
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = (m_pos.x + fLength * sinf(m_rot.z + fAngleA));
	pVtx[3].pos.y = (m_pos.y + fLength * cosf(m_rot.z + fAngleA));
	pVtx[3].pos.z = 0.0f;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//**********************************************
// �X�N���[���`�揈��
//**********************************************
void CScreen::Draw(LPDIRECT3DTEXTURE9 pTexture)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, pTexture);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//**********************************************
// �X�N���[���`�揈��
//**********************************************
void CScreen::DrawAlpherTest(LPDIRECT3DTEXTURE9 pTexture)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, pTexture);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//**********************************************
// �X�N���[����������
//**********************************************
CScreen* CScreen::Create(D3DXCOLOR col)
{
	CScreen* pScreen = NULL;

	// �X�N���[���̐���
	if (pScreen == NULL)
	{
		pScreen = new CScreen;
		if (pScreen != NULL)
		{
			// ����������
			pScreen->Init(col);
		}
		else
		{
			MessageBox(NULL, " CScreen* CScreen::Create() >  ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CScreen* CScreen::Create() >  ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pScreen;
}

//**********************************************
// �X�N���[���g��ݒ菈��
//**********************************************
void CScreen::SetScaleSize(float fScaleValue, int nTimeScale)
{
	m_bScale = true;				// �g��̗L��
	m_fScaleValue = fScaleValue;	// �g�嗦
	m_nFrameScale = nTimeScale;		// �g�傷�鎞��
	m_nCntScale = 0;				// �g��J�E���^�[
	m_fScaleValueNow = 1.0f;		// ���̊g�嗦
}

//**********************************************
// �X�N���[���g��X�V����
//**********************************************
void CScreen::UpdateScale(void)
{
	// �g�傷���ԂŖ�����΍X�V���Ȃ�
	if (m_bScale == false)
	{
		return;
	}

	// �g��J�E���^�J�E���g�A�b�v
	m_nCntScale++;

	// ���Ԕ{�����v�Z
	float fMugTime = (float)m_nCntScale / (float)m_nFrameScale;

	// �ړI�̊g�嗦�Ɏ��Ԕ{�����|���Ď��ԂƂƂ��Ɋg�傷��
	float fAddScaleValue = m_fScaleValue * fMugTime;

	// �g�嗦��ǉ�
	m_fScaleValueNow += fAddScaleValue;

	// �J�E���^�[���g�傷�鎞�Ԉȏ�̐��l�ɂȂ�����g����~�߂�
	if (m_nCntScale >= m_nFrameScale)
	{
		m_fScaleValueNow = 1.0f;
		m_bScale = false;
	}
}

//**********************************************
// �X�N���[���F�̐ݒ�
//**********************************************
void CScreen::SetColor(D3DXCOLOR col)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// �F��ݒ�
	m_col = col;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[��ݒ�
	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = m_col;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}