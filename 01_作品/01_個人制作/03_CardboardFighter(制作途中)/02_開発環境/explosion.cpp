//****************************************************************************
// 
// ����
// Author tetuji yamamoto
// 
//****************************************************************************
#include "explosion.h"
#include "texture.h"

//****************************************************************************
// �����R���X�g���N�^
//****************************************************************************
CExplosion::CExplosion(int nPriority) : CObject2D(nPriority)
{
	m_nCntTime = 0;				// ���Ԍv���J�E���^�[
	m_nLimitTime = 0;			// ���Ԍv���J�E���^�[
	m_nMaxTexPattern = 0;		// �e�N�X�`���̃p�^�[����
	m_nNowPattern = 0;			// �e�N�X�`���̍��̃p�^�[����
	m_nPatternLine = 0;			// �p�^�[����
	m_fTexPatternWidth = 0.0f;	// �e�N�X�`���p�^�[����
	m_fTexPatternHeight = 0.0f;	// �e�N�X�`���p�^�[������
}

//****************************************************************************
// �����f�X�g���N�^
//****************************************************************************
CExplosion::~CExplosion()
{

}

//****************************************************************************
// ��������������
//****************************************************************************
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nLimitTime, int nMaxTexPattern, int nPatternLine)
{
	// �I�u�W�F�N�g2D������
	CObject2D::Init(pos, D3DXVECTOR3_NULL, col, fWidth, fHeight);
	
	// ��ސݒ�
	CObject2D::SetType(CObject2D::TYPE_EXPLOSION);

	// �e��ϐ�������
	m_nCntTime = 0;						// ���Ԍv���J�E���^�[
	m_nLimitTime = nLimitTime;			// ���E����
	m_nMaxTexPattern = nMaxTexPattern;	// �e�N�X�`���̃p�^�[����
	m_nNowPattern = 0;					// �e�N�X�`���̍��̃p�^�[����
	m_nPatternLine = nPatternLine;		// �p�^�[����
	m_fTexPatternWidth = fWidth;		// �e�N�X�`���p�^�[����
	m_fTexPatternHeight = fHeight;		// �e�N�X�`���p�^�[������

	int nLine = m_nNowPattern / (m_nMaxTexPattern / m_nPatternLine);
	float fTexX = 1.0f / (m_nMaxTexPattern / m_nPatternLine);
	float fTexY = 1.0f / m_nPatternLine;

	// �e�N�X�`�����̃C���f�b�N�X�ݒ�
	CObject2D::SetIdxTexture(CTexture::TEXTURE_EXPROSION);

	// ��x�A�b�v�f�[�g����
	CObject2D::Update(fTexX, fTexY, m_nNowPattern, nLine);

	return S_OK;
}

//****************************************************************************
// �����I������
//****************************************************************************
void CExplosion::Uninit(void)
{
	CObject2D::Uninit();
}

//****************************************************************************
// �����X�V����
//****************************************************************************
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	int nChangeTime = m_nLimitTime / m_nMaxTexPattern;

	m_nCntTime++;	// �J�E���^�[���Z

	if (m_nCntTime >= nChangeTime)
	{
		m_nCntTime = 0;
		m_nNowPattern++;
		if (m_nNowPattern >= m_nMaxTexPattern)
		{
			CObject2D::Uninit();
			return;
		}
	}

	int nLine = m_nNowPattern / (m_nMaxTexPattern / m_nPatternLine);
	float fTexX = 1.0f / (m_nMaxTexPattern / m_nPatternLine);
	float fTexY = 1.0f / m_nPatternLine;

	CObject2D::Update(fTexX, 1.0f, m_nNowPattern, nLine);
}

//****************************************************************************
// �����`�揈��
//****************************************************************************
void CExplosion::Draw(void)
{
	CObject2D::Draw();
}

//****************************************************************************
// �����N���G�C�g����
//****************************************************************************
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nLimitTime, int nMaxTexPattern, int nPatternLine)
{
	CExplosion* pExplosion = NULL;
	int nNumAll = GetObujectNumAll();

	// �I�u�W�F�N�g2D�̐���
	if (pExplosion == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pExplosion = new CExplosion(CObject::PRIORITY_5);
		if (pExplosion != NULL)
		{
			// ����������
			pExplosion->Init(pos,col, fWidth,fHeight,nLimitTime, nMaxTexPattern, nPatternLine);
		}
		else
		{
			MessageBox(NULL, " CExplosion* CExplosion::Create() > if ( pExplosion != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CExplosion* CExplosion::Create() > if ( pExplosion == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return  pExplosion;
}