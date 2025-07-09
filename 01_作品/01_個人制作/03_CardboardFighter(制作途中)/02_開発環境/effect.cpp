#include "effect.h"
#include "easing.h"
#include "texture.h"

//--------------------------------------------------------------------
// �G�t�F�N�g

//********************************************************************
// �G�t�F�N�g
//********************************************************************
CEffect2D::CEffect2D(int nPriority) :CObject2D(nPriority)
{
	m_nLife = 0;
	m_nMaxLife = 0;
	m_fMaxWidth = 0.0f;
	m_fMaxHeight = 0.0f;
	m_MaxCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3_NULL;
}

//********************************************************************
// �G�t�F�N�g
//********************************************************************
CEffect2D::~CEffect2D()
{
}

//********************************************************************
// �G�t�F�N�g
//********************************************************************
HRESULT CEffect2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move,D3DXCOLOR col, int nLife, float fWidth, float fHeight)
{
	CObject2D::Init(pos, rot, col, fWidth, fHeight);
	m_nLife = nLife;
	m_nMaxLife = nLife;
	m_fMaxWidth = fWidth;
	m_fMaxHeight = fHeight;
	m_MaxCol = col;
	m_move = move;
	m_MaxMove = move;

	return S_OK;
}

//********************************************************************
// �G�t�F�N�g
//********************************************************************
void CEffect2D::Uninit(void)
{
	CObject2D::Uninit();
}

//********************************************************************
// �G�t�F�N�g
//********************************************************************
void CEffect2D::Update(void) 
{
	m_nLife--;
}

//********************************************************************
// �G�t�F�N�g
//********************************************************************
void CEffect2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObject2D::Draw();

	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z�̔�r���@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//********************************************************************
// �G�t�F�N�g
//********************************************************************
void CEffect2D::SetEffectType(CEffect2D::TYPE type)
{
	CEffect2D::m_type = type;
}

//--------------------------------------------------------------------
// �G�t�F�N�g�m�[�}��

//********************************************************************
// �G�t�F�N�g�m�[�}��
//********************************************************************
CEffect2DNomal::CEffect2DNomal()
{
}

//********************************************************************
// �G�t�F�N�g�m�[�}��
//********************************************************************
CEffect2DNomal::~CEffect2DNomal()
{
}

//********************************************************************
// �G�t�F�N�g�m�[�}��
//********************************************************************
HRESULT CEffect2DNomal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fWidth, float fHeight)
{
	// �G�t�F�N�g2D�N���X������
	CEffect2D::Init(pos, D3DXVECTOR3_NULL,move, col, nLife, fWidth, fHeight);	
	
	// �I�u�W�F�N�g�^�C�v�ݒ�
	CObject::SetType(CObject::TYPE_EFFECT);

	// �G�t�F�N�g�^�C�v�ݒ�
	CEffect2D::SetEffectType(CEffect2D::TYPE_NOMAL);		

	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	CObject2D::SetIdxTexture(CTexture::TEXTURE_SHADOW);

	return S_OK;
}

//********************************************************************
// �G�t�F�N�g�m�[�}��
//********************************************************************
void CEffect2DNomal::Uninit(void)
{
	CObject2D::Uninit();
}

//********************************************************************
// �G�t�F�N�g�m�[�}��
//********************************************************************
void CEffect2DNomal::Update(void)
{
	CEffect2D::Update();
	
	float fWidth = CObject2D::GetWidth();			// ���擾
	float fHeight = CObject2D::GetHeight();			// �����擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();		// �ʒu�擾
	float fMaxWidth = CEffect2D::GetMaxWidth();		// �ő啝�擾
	float fMaxHeight = CEffect2D::GetMaxHeight();	// �ő卂���擾
	int nNowLife = CEffect2D::GetLife();			// ���̎����擾
	int nMaxLife = CEffect2D::GetMaxLife();			// �ő�����擾
	D3DXCOLOR maxCol = CEffect2D::GetMaxColor();	// �ő�F�擾
	D3DXVECTOR3 maxMove = CEffect2D::GetMaxMove();
	D3DXVECTOR3 move = CEffect2D::GetMove();

	if (nNowLife <= 0)
	{// �������Ȃ��Ȃ���
		// �I��
		CEffect2DNomal::Uninit();
		return;
	}

	float fMugLife = (float)nNowLife / (float)nMaxLife;
	float fNowWidth = fMaxWidth * fMugLife;
	float fNowHeight = fMaxHeight * fMugLife;
	D3DXCOLOR nowCol = maxCol;
	nowCol.a = maxCol.a * SelectEasing(EASING_TYPE_EaseInOutCirc,fMugLife);

	move = maxMove * fMugLife;
	pos += move;

	CObject2D::SetWidth(fNowWidth);		// ���ݒ�
	CObject2D::SetHeight(fNowHeight);	// �����ݒ�
	CObject2D::SetColor(nowCol);		// �F�ݒ�
	CObject2D::SetPosition(pos);		// �ʒu�ݒ�

	CObject2D::Update();				// �|���S���̍X�V
}

//********************************************************************
// �G�t�F�N�g�m�[�}��
//********************************************************************
void CEffect2DNomal::Draw(void)
{
	CEffect2D::Draw();
}

//****************************************************************************
// �G�t�F�N�g�m�[�}���N���G�C�g����
//****************************************************************************
CEffect2DNomal* CEffect2DNomal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fWidth, float fHeight)
{
	CEffect2DNomal* pEffectN = NULL;

	// �G�t�F�N�g�m�[�}���̐���
	if (pEffectN == NULL)
	{
		pEffectN = new CEffect2DNomal;
		if (pEffectN != NULL)
		{
			// ����������
			pEffectN->Init(pos, move,col, nLife, fWidth, fHeight);						// ����������
		}
		else
		{
			MessageBox(NULL, " CEffect2DNomal* CEffect2DNomal::Create() > if ( pEffectN != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CEffect2DNomal* CEffect2DNomal::Create() > if ( pEffectN == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pEffectN;
}

//--------------------------------------------------------------------
// �G�t�F�N�g�V���b�N

//********************************************************************
// �G�t�F�N�g�V���b�N
//********************************************************************
CEffect2DShaking::CEffect2DShaking()
{
	m_fAddRot = 0.0f;
	m_fStartRot = 0.0f;
	m_fShakRadius = 0.0f;
}

//********************************************************************
// �G�t�F�N�g�V���b�N
//********************************************************************
CEffect2DShaking::~CEffect2DShaking()
{
}

//********************************************************************
// �G�t�F�N�g�V���b�N
//********************************************************************
HRESULT CEffect2DShaking::Init(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fWidth, float fHeight, float fShakRadius, float fAddRot)
{
	D3DXVECTOR3 rot = D3DXVECTOR3_NULL;
	D3DXVECTOR3 move = D3DXVECTOR3_NULL;
	CEffect2D::Init(pos, rot, move, col, nLife, fWidth, fHeight);	// ������
	CObject::SetType(CObject::TYPE_EFFECT);							// �I�u�W�F�N�g�^�C�v�ݒ�
	CEffect2D::SetEffectType(CEffect2D::TYPE_SHAKING);				// �G�t�F�N�g�^�C�v�ݒ�

	int addrot = (int)(fAddRot * 100.0f);
	int nShakRadius = (int)(fShakRadius * 100.0f);

	m_fAddRot = (float)(rand() % addrot) * 0.001f;
	m_fStartRot = (float)(rand() % 628 - 314) * 0.001f;
	m_fShakRadius = (float)(rand() % nShakRadius) * 0.001f;

	return S_OK;
}

//********************************************************************
// �G�t�F�N�g�V���b�N
//********************************************************************
void CEffect2DShaking::Uninit(void)
{
	CObject2D::Uninit();
}

//********************************************************************
// �G�t�F�N�g�V���b�N
//********************************************************************
void CEffect2DShaking::Update(void)
{
	CEffect2D::Update();

	float fWidth = CObject2D::GetWidth();			// ���擾
	float fHeight = CObject2D::GetHeight();			// �����擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();		// �ʒu�擾
	D3DXVECTOR3 rot = CObject2D::GetRotation();		// �����擾
	float fMaxWidth = CEffect2D::GetMaxWidth();		// �ő啝�擾
	float fMaxHeight = CEffect2D::GetMaxHeight();	// �ő卂���擾
	int nNowLife = CEffect2D::GetLife();			// ���̎����擾
	int nMaxLife = CEffect2D::GetMaxLife();			// �ő�����擾
	D3DXCOLOR maxCol = CEffect2D::GetMaxColor();	// �ő�F�擾

	if (nNowLife <= 0)
	{// �������Ȃ��Ȃ���
		// �I��
		CEffect2DShaking::Uninit();
		return;
	}

	float fMugLife = (float)nNowLife / (float)nMaxLife;
	float fNowWidth = fMaxWidth * fMugLife;
	float fNowHeight = fMaxHeight * fMugLife;
	D3DXCOLOR nowCol = maxCol;
	nowCol.a = maxCol.a * SelectEasing(EASING_TYPE_EaseInOutCirc, fMugLife);

	D3DXVECTOR3 move = D3DXVECTOR3_NULL;

	CObject2D::SetWidth(fNowWidth);		// ���ݒ�
	CObject2D::SetHeight(fNowHeight);	// �����ݒ�
	CObject2D::SetPosition(pos);		// �ʒu�ݒ�
	CObject2D::SetColor(nowCol);		// �F�ݒ�
	CObject2D::Update();				// �|���S���̍X�V
}

//********************************************************************
// �G�t�F�N�g�V���b�N
//********************************************************************
void CEffect2DShaking::Draw(void)
{
	CEffect2D::Draw();
}

//****************************************************************************
// �G�t�F�N�g�V���b�N�N���G�C�g����
//****************************************************************************
CEffect2DShaking* CEffect2DShaking::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fWidth, float fHeight, float fShakRadius, float fAddRot)
{
	CEffect2DShaking* pEffectS = NULL;
	int nNumAll = GetObujectNumAll();

	// �G�t�F�N�g�V���b�N�̐���
	if (pEffectS == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pEffectS = new CEffect2DShaking;
		if (pEffectS != NULL)
		{
			// ����������
			pEffectS->Init(pos, col, nLife, fWidth, fHeight, fShakRadius, fAddRot);			// ����������
		}
		else
		{
			MessageBox(NULL, " CEffect2DShaking* CEffect2DShaking::Create() > if ( pEffectS != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CEffect2DShaking* CEffect2DShaking::Create() > if ( pEffectS == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pEffectS;
}