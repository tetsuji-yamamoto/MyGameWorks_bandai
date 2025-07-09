//******************************************
// 
// �e�N�X�`��
// Author Tetsuji Yamamoto
// 
//******************************************
#include "texture.h"
#include "renderer.h"
#include "debugproc.h"

// �ÓI�����o�[�ϐ��錾
int CTexture::m_nNumAll = 0;

//******************************************
// �e�N�X�`��
//******************************************
CTexture::CTexture()
{
	memset(m_apTexture, NULL, sizeof(m_apTexture));
}

//******************************************
// �e�N�X�`��
//******************************************
CTexture::~CTexture()
{

}

//******************************************
// �e�N�X�`��
//******************************************
HRESULT CTexture::Load(void)
{
	// �ǂ��ł��g�����ׂẴe�N�X�`���̓Ǎ�
	for (int nCnTex = 0; nCnTex < TEXTURE_MAX; nCnTex++)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
		HRESULT hr = D3DXCreateTextureFromFile(pDevice,
			m_apFileName[nCnTex],
			&m_apTexture[nCnTex]);

		if (FAILED(hr))
		{
			MessageBox(NULL, "CTexture::Load() > �e�N�X�`����ǂݍ��߂܂���ł���", "Error", MB_OK);
			return E_FAIL;
		}

		m_nNumAll++;	// �e�N�X�`���̑����J�E���g�A�b�v
	}

	return S_OK;
}

//******************************************
// �e�N�X�`��
//******************************************
void CTexture::Unload(void)
{
	// ���ׂẴe�N�X�`����j��
	for (int nCnTex = 0; nCnTex < MAX_TEXTURE_NUM; nCnTex++)
	{
		if (m_apTexture[nCnTex] != NULL)
		{
			m_apTexture[nCnTex]->Release();
			m_apTexture[nCnTex] = NULL;
		}

		if (m_apFileName[nCnTex] != NULL)
		{
			m_apFileName[nCnTex] = NULL;
		}

		if (m_apTexture[nCnTex] != NULL)
		{
			MessageBox(NULL, "CTexture::Unload() > �e�N�X�`����NULL�ł͂���܂���", "Error", MB_OK);
		}
	}

	delete this;
}

//******************************************
// �e�N�X�`��
//******************************************
int CTexture::Register(const char* pFileName)
{
	if (pFileName == NULL)
	{
		return -1;
	}

	// ���łɂ��邩�ǂ����𒲂ׂ�
	for (int nCntTex = 0; nCntTex < m_nNumAll; nCntTex++)
	{
		if (strcmp(pFileName, m_apFileName[nCntTex]) == 0)
		{// �������łɃe�N�X�`��������ꍇ
			// ���̃e�N�X�`���̃C���f�b�N�X��Ԃ�
			return nCntTex;
		}
	}

	// ����������V�����ݒ肷��
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	int nIdx = m_nNumAll;
	m_apFileName[nIdx] = pFileName;

	// �e�N�X�`����ǂݍ���
	HRESULT hr = D3DXCreateTextureFromFile(pDevice,
		m_apFileName[nIdx],
		&m_apTexture[nIdx]);

	// �Ǎ����s
	if (FAILED(hr))
	{
		MessageBox(NULL, "CTexture::Register() > �e�N�X�`����ǂݍ��߂܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// �e�N�X�`���̑����J�E���g�A�b�v
	m_nNumAll++;	

	// �ݒ肵���C���f�b�N�X��Ԃ�
	return nIdx;
}

//******************************************
// �e�N�X�`��
//******************************************
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx < 0 || nIdx >= MAX_TEXTURE_NUM)
	{
		return NULL;
	}

	return m_apTexture[nIdx];
}

//******************************************
// �e�N�X�`��
//******************************************
CTexture* CTexture::Create()
{
	CTexture* pTexture = NULL;

	// �I�u�W�F�N�g2D�̐���
	if (pTexture == NULL)
	{
		pTexture = new CTexture;
		if (pTexture == NULL)
		{
#ifdef _DEBUG
			MessageBox(NULL, " CBullet* CBullet::Create() > if ( pBullet != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
#endif
		}
	}

	// ���ʂ�Ԃ�
	return  pTexture;
}

//******************************************
// �e�N�X�`��
//******************************************
void CTexture::DebugTexture()
{
	CDebugprocc::Print("[ CTexture ]\n");
	CDebugprocc::Print("TEXTURE_ADD_NUM : %d\n",TEXTURE_ADD_NUM);
	CDebugprocc::Print("TEXTURE_MAX : %d\n",TEXTURE_MAX);
	CDebugprocc::Print("MAX_TEXTURE_NUM : %d\n",MAX_TEXTURE_NUM);
	CDebugprocc::Print("m_nNumAll : %d\n",m_nNumAll);
	CDebugprocc::Print("\n");
}