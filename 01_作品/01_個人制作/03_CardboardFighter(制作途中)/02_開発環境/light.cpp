//****************************************
// 
// ���C�g
// Author Tetsuji Yamamoto
// 
//****************************************
#include "light.h"
#include "renderer.h"

//****************************************
// ���C�g�R���X�g���N�^
//****************************************
CLight::CLight()
{
	ZeroMemory(m_aLight, sizeof(m_aLight));
}

//****************************************
// ���C�g�f�X�g���N�^
//****************************************
CLight::~CLight()
{

}

//****************************************
// ���C�g����������
//****************************************
HRESULT CLight::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetDevice();

	//���C�g�̕����x�N�g��
	D3DXVECTOR3 vecDir[3];

	for (int nCntLight = 0; nCntLight < 3; nCntLight++)
	{
		//���C�g���N���A����
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		//vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		//vecDir[1] = D3DXVECTOR3(-12.0f, -14.0f, 15.0f);
		//vecDir[2] = D3DXVECTOR3(-5.0f, -5.57f, -3.3f);

		vecDir[0] = D3DXVECTOR3(0.0f, -1.0f, -2.0);
		vecDir[1] = D3DXVECTOR3(2.0f, -1.0f, 2.0);
		vecDir[2] = D3DXVECTOR3(1.0f, -1.0f, 2.0);

		//���K������(�傫���P�̃x�N�g���ɂ���)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		m_aLight[nCntLight].Direction = vecDir[nCntLight];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//****************************************
// ���C�g�I������
//****************************************
void CLight::Uninit(void)
{

}

//****************************************
// ���C�g�X�V����
//****************************************
void CLight::Update(void)
{

}