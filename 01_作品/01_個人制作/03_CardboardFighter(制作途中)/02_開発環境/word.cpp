//**************************************
// 
// ���[�h
// AouthorTetsuji Yamamoto
// 
//**************************************
#include "word.h"
#include "debugproc.h"
#include "manager.h"

#define WORD_SIZE (100)

// �ÓI�����o�[�ϐ��錾
LPDIRECT3DTEXTURE9 CWord::m_pTextureFont = NULL;	// �t�H���g�p�̃e�N�X�`��
LPDIRECT3DSURFACE9 CWord::m_pSurfaceTexFont = NULL;	// �t�H���g�p�e�N�X�`���̃����_�[�^�[�Q�b�g

//**************************************
// ���[�h
//**************************************
CWord::CWord()
{
	m_pVtxBuff = NULL;
	ZeroMemory(m_cChar, sizeof(m_cChar));
}

//**************************************
// ���[�h
//**************************************
CWord::~CWord()
{
}

//**************************************
// ���[�h
//**************************************
void CWord::Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, const char* pStr)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �l����
	memcpy(m_cChar, pStr, sizeof(m_cChar));

	 HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CWord::Init > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
	}

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = pos.x - fWidth;
	pVtx[0].pos.y = pos.y - fHeight;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + fWidth;
	pVtx[1].pos.y = pos.y - fHeight;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x - fWidth;
	pVtx[2].pos.y = pos.y + fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + fWidth;
	pVtx[3].pos.y = pos.y + fHeight;
	pVtx[3].pos.z = 0.0f;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = col;
		pVtx[nCntVtx].rhw = 1.0f;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	if (m_pTextureFont == NULL)
	{
		// �e�N�X�`���̐���
		hr = pDevice->CreateTexture(
			FONT_SIZE,
			FONT_SIZE,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_pTextureFont,
			NULL);
	}

	if (FAILED(hr))
	{
		MessageBox(NULL, "CWord::Init() > pDevice->CreateTexture() > ���s", "Error", MB_OK);
		return;
	}

	if (m_pSurfaceTexFont == NULL)
	{
		// �e�N�X�`�����烌���_�[�^�[�Q�b�g�p�̃T�[�t�F�X���擾
		hr = m_pTextureFont->GetSurfaceLevel(0, &m_pSurfaceTexFont);
	}

	if (FAILED(hr))
	{
		MessageBox(NULL, "CWord::Init() > GetSurfaceLevel() > ���s", "Error", MB_OK);
		return;
	}
}

//**************************************
// ���[�h
//**************************************
void CWord::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �T�[�t�F�C�X�̔j��
	if (m_pSurfaceTexFont != NULL)
	{
		m_pSurfaceTexFont->Release();
		m_pSurfaceTexFont = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pTextureFont != NULL)
	{
		m_pTextureFont->Release();
		m_pTextureFont = NULL;
	}

	if (m_pVtxBuff != NULL  || m_pSurfaceTexFont != NULL || m_pTextureFont != NULL)
	{
		MessageBox(NULL, " CWord::Uninit() > ��������NULL�ł͂���܂���", "Error", MB_OK);
	}
}

//**************************************
// ���[�h
//**************************************
void CWord::Update(void)
{

}

//**************************************
// ���[�h
//**************************************
void CWord::Draw(LPD3DXFONT pFont)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	RECT rect = { 0,0,FONT_SIZE,FONT_SIZE };

	// �����_�[�^�[�Q�b�g�Ƃ��ăe�N�X�`���ɕ`��
	pDevice->SetRenderTarget(0, m_pSurfaceTexFont);
	
	pDevice->Clear(0, NULL,
	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	
	// �e�L�X�g�̕`��
	pFont->DrawText(NULL, m_cChar, -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 255, 255, 255));
	
	// �o�b�N�o�b�t�@���擾
	LPDIRECT3DSURFACE9 pBuckBuff = NULL;
	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBuckBuff);
	
	// �����_�[�^�[�Q�b�g�Ƃ��ăo�b�N�o�b�t�@�ɕ`��
	pDevice->SetRenderTarget(0, pBuckBuff);
	
	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, m_pTextureFont);
	
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, NULL);

}

//**************************************
// ���[�h
//**************************************
CWord* CWord::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, char cChar)
{
	CWord* pWord = NULL;
	int nNumAll = CObject::GetObujectNumAll();

	// �G�t�F�N�g�V���b�N�̐���
	if (pWord == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pWord = new CWord;

		if (pWord != NULL)
		{
			// ����������
			pWord->Init(pos, col, fWidth, fHeight, &cChar);	// ����������
		}
		else
		{
			MessageBox(NULL, " CWord::Create() > if ( pWord != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CWord::Create() > if ( pWord == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pWord;
}

