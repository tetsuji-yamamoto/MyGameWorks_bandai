//****************************************************************************
// 
// �w�i
// Author tetuji yamamoto
// 
//****************************************************************************
#include "bg.h"
#include "texture.h"

//****************************************************************************
// �w�i�R���X�g���N�^
//****************************************************************************
CBG::CBG(int nPriority) : CObject2D(nPriority)
{
	m_type = TYPE_00;		// ���
	m_fFeedAngle = 0.0f;	// ����p�x
	m_fFeedRate = 0.0f;		// ���葬�x
	m_fAddTexX= 0.0f;		// ���蕝
	m_fAddTexY= 0.0f;		// ���荂��
}

//****************************************************************************
// �w�i�f�X�g���N�^
//****************************************************************************
CBG::~CBG()
{
}

//****************************************************************************
// �w�i������
//****************************************************************************
HRESULT CBG::Init(float fFeedRate, float fFeedAngle, TYPE type)
{
	CObject2D::Init();
	CObject2D::SetWidth(SCREEN_WIDTH * 0.5f);
	CObject2D::SetHeight(SCREEN_HEIGHT * 0.5f);

	// ��ސݒ�
	CObject2D::SetType(CObject2D::TYPE_BG);

	switch (type)
	{
	case TYPE_00:
	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	CObject2D::SetIdxTexture(CTexture::TEXTURE_BG_0);
		break;

	case TYPE_01:
		// �e�N�X�`�����̃C���f�b�N�X�ݒ�
		CObject2D::SetIdxTexture(CTexture::TEXTURE_BG_1);
		break;

	case TYPE_02:
		// �e�N�X�`�����̃C���f�b�N�X�ݒ�
		CObject2D::SetIdxTexture(CTexture::TEXTURE_BG_2);
		break;
	}

	m_type = type;
	m_fFeedAngle = fFeedAngle;
	m_fFeedRate = fFeedRate;
	m_fAddTexX = 0.0f;
	m_fAddTexY = 0.0f;

	return S_OK;
}

//****************************************************************************
// �w�i�I��
//****************************************************************************
void CBG::Uninit(void)
{
	m_fFeedAngle = 0.0f;
	m_fFeedRate = 0.0f;
	m_fAddTexX = 0.0f;
	m_fAddTexY = 0.0f;
	CObject2D::Uninit();
}

//****************************************************************************
// �w�i�X�V
//****************************************************************************
void CBG::Update(void)
{
	m_fAddTexX += sinf(m_fFeedAngle) * m_fFeedRate;
	m_fAddTexY += cosf(m_fFeedAngle) * m_fFeedRate;

	CObject2D::Update(m_fAddTexX, m_fAddTexY);
}

//****************************************************************************
// �w�i�`��
//****************************************************************************
void CBG::Draw(void)
{
	CObject2D::Draw();
}

//****************************************************************************
// �w�i�쐬
//****************************************************************************
CBG* CBG::Create(float fFeedRate, float fFeedAngle, TYPE type)
{
	CBG* pBG = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�g2D�̐���
	if (pBG == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pBG = new CBG(CObject::PRIORITY_0);
		if (pBG != NULL)
		{
			// ����������
			pBG->Init(fFeedRate, fFeedAngle,type);
		}
		else
		{
			MessageBox(NULL, " CBG* CBG::Create() > if ( pBG != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CBG* CBG::Create() > if ( pBG == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pBG;
}