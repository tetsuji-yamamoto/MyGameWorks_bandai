//**********************************************
// 
// �I�u�W�F�N�g2D����
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "myMath.h"

//**********************************************
// �I�u�W�F�N�g2D�R���X�g���N�^
//**********************************************
CObject2D::CObject2D(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nIdxTexture = -1;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//**********************************************
// �I�u�W�F�N�g2D�f�X�g���N�^
//**********************************************
CObject2D::~CObject2D()
{
}

//**********************************************
// �I�u�W�F�N�g2D����������
//**********************************************
HRESULT CObject2D::Init()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	HRESULT hr;

	hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CREnderer::InitPoligon > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	float fWCenter = SCREEN_WIDTH * 0.5f;
	float fHCenter = SCREEN_HEIGHT * 0.5f;
	float fWidth = 200.0f;

	m_fWidth = OBUJECT2D_WIDTH;
	m_fHeight = OBUJECT2D_WIDTH;
	m_pos = D3DXVECTOR3(fWCenter, fHCenter, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = fWCenter - fWidth;
	pVtx[0].pos.y = fHCenter - fWidth;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fWCenter + fWidth;
	pVtx[1].pos.y = fHCenter - fWidth;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = fWCenter - fWidth;
	pVtx[2].pos.y = fHCenter + fWidth;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fWCenter + fWidth;
	pVtx[3].pos.y = fHCenter + fWidth;
	pVtx[3].pos.z = 0.0f;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
	{
		pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntVtx].rhw = 1.0f;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//**********************************************
// �I�u�W�F�N�g2D����������
//**********************************************
HRESULT CObject2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float fHeight, int nAppStateCnt)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();
	HRESULT hr;

	hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, "CREnderer::InitPoligon > ���_�o�b�t�@���N���G�C�g�ł��܂���ł���", "Error", MB_OK);
		return E_FAIL;
	}

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_pos = pos;
	m_rot = rot;
	m_col = col;

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

	return S_OK;
}

//**********************************************
// �I�u�W�F�N�g2D�I������
//**********************************************
void CObject2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_pVtxBuff != NULL)
	{
		MessageBox(NULL, " CObject2D::Uninit() > if (m_pVtxBuff != NULL) ��������NULL�ł͂���܂���", "Error", MB_OK);
	}


	Release();
}

//**********************************************
// �I�u�W�F�N�g2D�X�V����
//**********************************************
void CObject2D::Update(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	float fLength = sqrtf((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight));

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = (m_pos.x + m_fWidth * sinf(m_rot.z - D3DX_PI * 0.75f));
	pVtx[0].pos.y = (m_pos.y + m_fHeight * cosf(m_rot.z - D3DX_PI * 0.75f));
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = (m_pos.x + m_fWidth * sinf(m_rot.z + D3DX_PI * 0.75f));
	pVtx[1].pos.y = (m_pos.y + m_fHeight * cosf(m_rot.z + D3DX_PI * 0.75f));
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = (m_pos.x + m_fWidth * sinf(m_rot.z - D3DX_PI * 0.25f));
	pVtx[2].pos.y = (m_pos.y + m_fHeight * cosf(m_rot.z - D3DX_PI * 0.25f));
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = (m_pos.x + m_fWidth * sinf(m_rot.z + D3DX_PI * 0.25f));
	pVtx[3].pos.y = (m_pos.y + m_fHeight * cosf(m_rot.z + D3DX_PI * 0.25f));
	pVtx[3].pos.z = 0.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//**********************************************
// �I�u�W�F�N�g2D�X�V����
//**********************************************
void CObject2D::Update(float fPatternWidth, float fPatternHeight, int nNowPattern, int nTexLine)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	float fLength = sqrtf((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight));

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = (m_pos.x + m_fWidth * sinf(m_rot.z - D3DX_PI * 0.75f));
	pVtx[0].pos.y = (m_pos.y + m_fHeight * cosf(m_rot.z - D3DX_PI * 0.75f));
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = (m_pos.x + m_fWidth * sinf(m_rot.z + D3DX_PI * 0.75f));
	pVtx[1].pos.y = (m_pos.y + m_fHeight * cosf(m_rot.z + D3DX_PI * 0.75f));
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = (m_pos.x + m_fWidth * sinf(m_rot.z - D3DX_PI * 0.25f));
	pVtx[2].pos.y = (m_pos.y + m_fHeight * cosf(m_rot.z - D3DX_PI * 0.25f));
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = (m_pos.x + m_fWidth * sinf(m_rot.z + D3DX_PI * 0.25f));
	pVtx[3].pos.y = (m_pos.y + m_fHeight * cosf(m_rot.z + D3DX_PI * 0.25f));
	pVtx[3].pos.z = 0.0f;

	pVtx[0].tex.x = 0.0f + fPatternWidth * nNowPattern;
	pVtx[0].tex.y = 0.0f + fPatternHeight * nTexLine;

	pVtx[1].tex.x = fPatternWidth + fPatternWidth * nNowPattern;
	pVtx[1].tex.y = 0.0f + fPatternHeight * nTexLine;

	pVtx[2].tex.x = 0.0f + fPatternWidth * nNowPattern;
	pVtx[2].tex.y = fPatternHeight + fPatternHeight * nTexLine;

	pVtx[3].tex.x = fPatternWidth + fPatternWidth * nNowPattern;
	pVtx[3].tex.y = fPatternHeight + fPatternHeight * nTexLine;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//**********************************************
// �I�u�W�F�N�g2D�X�V����
//**********************************************
void  CObject2D::Update(float fAddTexX, float fAddTexY)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = NULL;

	float fLength = sqrtf((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight));
	float fAngleA = atan2f(m_fWidth, m_fHeight);
	float fAngleB = atan2f(m_fWidth, -m_fHeight);

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

	pVtx[0].tex.x = 0.0f + fAddTexX;
	pVtx[0].tex.y = 0.0f + fAddTexY;

	pVtx[1].tex.x = 1.0f + fAddTexX;
	pVtx[1].tex.y = 0.0f + fAddTexY;

	pVtx[2].tex.x = 0.0f + fAddTexX;
	pVtx[2].tex.y = 1.0f + fAddTexY;

	pVtx[3].tex.x = 1.0f + fAddTexX;
	pVtx[3].tex.y = 1.0f + fAddTexY;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}


//**********************************************
// �I�u�W�F�N�g2D�`�揈��
//**********************************************
void CObject2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	// �e�N�X�`���C���X�^���X�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`����ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

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
// �I�u�W�F�N�g2D��������
//**********************************************
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	CObject2D* pObject2D = NULL;

	// �I�u�W�F�N�g2D�̐���
	if (pObject2D == NULL)
	{
		pObject2D = new CObject2D;
		if (pObject2D != NULL)
		{
			// ����������
			pObject2D->Init(pos, rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWidth, fHeight);
		}
		else
		{
			MessageBox(NULL, " CObject2D* CObject2D::Create() > if (pObject2D != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObject2D* CObject2D::Create() > if (pObject2D == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pObject2D;
}

//**********************************************
// �I�u�W�F�N�g2D��������
//**********************************************
bool CObject2D::ColisionMouse(float fRadius)
{
	// �}�E�X�擾
	CInputMouse* pInputMouse = CManager::GetInputMouse();

	// �}�E�X�̍��W�擾
	D3DXVECTOR3 posMouse = pInputMouse->GetPosition();

	D3DXVECTOR2 posA = { m_pos.x, m_pos.y };
	D3DXVECTOR2 posB = { posMouse.x, posMouse.y };

	// �}�E�X��2D�ʒu���d�Ȃ��Ă�����
	if (CMyMath::ColiisionCircleCircle2D(posA, fRadius, posB, 0.0f) == true)
	{
		// �������Ă��锻��
		return true;
	}

	// �������Ă����Ȃ�����
	return false;
}