//****************************************************************************
// 
// �f�o�b�O����
// Author tetuji yamamoto
// 
//****************************************************************************

#include "debugproc.h"
#include "renderer.h"

// �ÓI�����o�[�ϐ��錾
LPD3DXFONT CDebugprocc::m_pFont = NULL;		// �t�H���g�ւ̃|�C���^
char CDebugprocc::m_aStr[MAX_DEBUG_STR_NUM] = {};		// ��������i�[����o�b�t�@
int  CDebugprocc::m_nNumLine = 0;

//****************************************************************************
// �f�o�b�O�R���X�g���N�^
//****************************************************************************
CDebugprocc::CDebugprocc()
{

}

//****************************************************************************
// �f�o�b�O�f�X�g���N�^
//****************************************************************************
CDebugprocc::~CDebugprocc()
{

}

//****************************************************************************
// �f�o�b�O����������
//****************************************************************************
void CDebugprocc::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �f�o�b�O�p�\���t�H���g�̐���
	D3DXCreateFont(pDevice, MAX_FONT_SIZE, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		FONT_JF_DOT_M_10, &m_pFont);

	// �o�b�t�@�̃N���A
	memset(&m_aStr[0],NULL,(sizeof(m_aStr)));

}

//****************************************************************************
// �f�o�b�O�I������
//****************************************************************************
void CDebugprocc::Uninit(void)
{
	//�f�o�b�O�\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//****************************************************************************
// �f�o�b�O����
//****************************************************************************
void CDebugprocc::Print(const char* fmt, ...)
{
	va_list args;
	char aStr[MAX_DEBUG_STR_NUM] = {};
	va_start(args, fmt);

	vsprintf(aStr, fmt, args);

	va_end(args);

	strcat(m_aStr,aStr);
}

//****************************************************************************
// �f�o�b�O�`�揈��
//****************************************************************************
void CDebugprocc::Draw(void)
{
	RECT rect = { 0,MAX_FONT_SIZE,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �e�L�X�g�̕`��
	m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	// �o�b�t�@�̃N���A
	memset(&m_aStr[0], NULL, (sizeof(m_aStr)));

	// �s���J�E���g���Z�b�g
	m_nNumLine = 0;
}