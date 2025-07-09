//**********************************************
// 
// �}�l�[�W���[����
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "manager.h"
#include "object2D.h"
#include "object3D.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "bgManager.h"
#include "effect.h"
#include "number.h"
#include "score.h"
#include "timer.h"
#include "collision.h"

// �ÓI�����o�[�ϐ��錾
CRenderer* CManager::m_pRenderer = NULL ;				// �����_���[
CInputKeyboard* CManager::m_pInputKeyboard = NULL;		// �L�[�{�[�h
CInputMouse* CManager::m_pInputMouse = NULL;			// �}�E�X
CInputJoypad* CManager::m_pInputJoypad = NULL;			// �W���C�p�b�h
CSound* CManager::m_pSound = NULL;						// �T�E���h
CDebugprocc* CManager::m_pDebugprocc = NULL;			// �f�o�b�O
CPause* CManager::m_pPause = NULL;						// �|�[�Y
CTexture* CManager::m_pTexture = NULL;					// �e�N�X�`��
CCamera* CManager::m_pCamera = NULL;					// �J����
CLight* CManager::m_pLight = NULL;						// ���C�g
CFontManager* CManager::m_pFontMane = NULL;				// �t�H���g
CScore* CManager::m_pScore = NULL;						// �X�R�A
CLoadMotionFile* CManager::m_pLoadMotionFile = NULL;	// ���[�V�����t�@�C���ǂݎ��
CStage* CManager::m_pStage = NULL;						// �X�e�[�W�|�C���^
CPlayer* CManager::m_pPlayer = NULL;					// �v���C���[�̃|�C���^�[
std::vector<CEnemy*> CManager::m_pEnemy;				// �G�l�~�[�|�C���^�[

//**********************************************
// �}�l�[�W���[�R���X�g���N�^
//**********************************************
CManager::CManager()
{
}

//**********************************************
// �}�l�[�W���[�f�X�g���N�^
//**********************************************
CManager::~CManager()
{
}

//**********************************************
// �}�l�[�W���[����������
//**********************************************
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	// �������m��
	m_pRenderer = new CRenderer;

	if (m_pRenderer != NULL)
	{// �m�ۂł��Ă����
		// �����_���[�̏�����
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{
			MessageBox(NULL, " CManager::Init() > if(FAILED(m_pRenderer->Init(hWnd, TRUE))) > �������ł��܂���ł���", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pRenderer != NULL) > m_pRenderer���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// �������m��
	m_pInputKeyboard = new CInputKeyboard;

	if (m_pInputKeyboard != NULL)
	{// �m�ۂł��Ă����
		// �L�[�{�[�h�̏�����
		if (FAILED(m_pInputKeyboard->Init(hinstance, hWnd)))
		{
			MessageBox(NULL, " CManager::Init() > if (FAILED(m_pInputKeyboard->Init(hinstance,hWnd))) > �������ł��܂���ł���", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pInputKeyboard != NULL) > m_pInputKeyboard���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// �������m��
	m_pInputMouse = new CInputMouse;

	if (m_pInputMouse != NULL)
	{// �m�ۂł��Ă����
		// �}�E�X�̏�����
		if (FAILED(m_pInputMouse->Init(hinstance, hWnd)))
		{
			MessageBox(NULL, " CManager::Init() > if (FAILED(m_pInputMouse->Init(hinstance,hWnd))) > �������ł��܂���ł���", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pInputMouse != NULL) > m_pInputKeyboard���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// �������m��
	m_pInputJoypad = new CInputJoypad;

	if (m_pInputJoypad != NULL)
	{// �m�ۂł��Ă����
		// �W���C�p�b�h�̏�����
		if (FAILED(m_pInputJoypad->Init(hinstance, hWnd)))
		{
			MessageBox(NULL, " CManager::Init() > if (FAILED(m_pInputJoypad->Init(hinstance,hWnd))) > �������ł��܂���ł���", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pInputJoypad != NULL) > m_pInputJoypad���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// �������m��
	m_pSound = new CSound;

	if (m_pSound != NULL)
	{// �m�ۂł��Ă����
		// �T�E���h�̏�����
		if (FAILED(m_pSound->InitSound(hWnd)))
		{
			MessageBox(NULL, " CManager::Init() > if (FAILED(m_pSound->Init(hinstance,hWnd))) > �������ł��܂���ł���", "Error", MB_OK);
			return -1;
		}
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pSound != NULL) > m_pSound���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// �������m��
	m_pDebugprocc = new CDebugprocc;

	if (m_pDebugprocc != NULL)
	{// �m�ۂł��Ă����
		// �f�o�b�O�̏�����
		m_pDebugprocc->Init();
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pDebugprocc != NULL) > m_pDebugprocc���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// �������m��
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{// �m�ۂł��Ă����
		// �f�o�b�O�̏�����
		m_pCamera->Init();
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pCamera != NULL) > m_pCamera���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// �������m��
	m_pLight = new CLight;
	if (m_pLight != NULL)
	{// �m�ۂł��Ă����
		// �f�o�b�O�̏�����
		m_pLight->Init();
	}
	else
	{
		MessageBox(NULL, " CManager::Init() > if (m_pLight != NULL) > m_pLight���������m�ۂł��܂���ł���", "Error", MB_OK);
	}


	// �k���ł����
	if (m_pLoadMotionFile == NULL)
	{
		// ���[�V�����t�@�C���ǂݎ��N���X�̃������m��
		m_pLoadMotionFile = CLoadMotionFile::Create();
	}

	// �v���C���[�̐���
	if (m_pPlayer == NULL)
	{
		m_pPlayer = new CPlayer;
	}

	// �X�e�[�W�̃C���X�^���X����
	if (m_pStage == NULL)
	{
		m_pStage = new CStage;
	}

	// �v���C���[�̐���
	m_pFontMane = CFontManager::Create();	// �t�H���g�}�l�[�W���[
	m_pTexture = CTexture::Create();		// �e�N�X�`��
	m_pPause = CPause::Create();			// �|�[�Y
	m_pTexture->Load();						// �e�N�X�`���̃��[�h

	m_pStage->Init("data\\text\\stage_load\\stage_000.txt");

	
	CEnemy* pEnemy = new CEnemy;
	pEnemy->Init(D3DXVECTOR3(0.0f, 0.0f, -80.0f), D3DXVECTOR3_NULL, 60, "data\\motion\\motion_enemy_armor.txt");
	m_pEnemy.push_back(pEnemy);

	m_pPlayer->Init(D3DXVECTOR3(0.0f,0.0f,-80.0f), D3DXVECTOR3_NULL,60, "data\\motion\\motion_player_001.txt");

	/*CEnemy* pEnemy2 = new CEnemy;
	pEnemy2->Init(D3DXVECTOR3(0.0f, 0.0f, -80.0f), D3DXVECTOR3_NULL, 60, "data\\motion\\motion_enemy_armor.txt");
	m_pEnemy.push_back(pEnemy2);*/
	return S_OK;
}

//**********************************************
// �}�l�[�W���[�I������
//**********************************************
void CManager::Uninit(void)
{
	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{// �k���łȂ�������
		// �����_���[�̏I������
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pRenderer != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pRenderer != NULL) > m_pRenderer��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{// �k���łȂ�������
		// �L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pInputKeyboard != NULL) > m_pInputKeyboard��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �}�E�X�̔j��
	if (m_pInputMouse != NULL)
	{// �k���łȂ�������
		// �}�E�X�̏I������
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	if (m_pInputMouse != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pInputMouse != NULL) > m_pInputMouse��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �W���C�p�b�h�̔j��
	if (m_pInputJoypad != NULL)
	{// �k���łȂ�������
		// �W���C�p�b�h�̏I������
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	if (m_pInputJoypad != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pInputJoypad != NULL) > m_pInputJoypad��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{// �k���łȂ�������
		// �T�E���h�̏I������
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pSound != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pSound != NULL) > m_pSound��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �f�o�b�O�̔j��
	if (m_pDebugprocc != NULL)
	{// �k���łȂ�������
		// �f�o�b�O�̏I������
		m_pDebugprocc->Uninit();
		delete m_pDebugprocc;
		m_pDebugprocc = NULL;
	}

	if (m_pDebugprocc != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pDebugprocc != NULL) > m_pDebugprocc��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// �J�����̔j��
	if (m_pCamera != NULL)
	{// �k���łȂ�������
		// �f�o�b�O�̏I������
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if (m_pCamera != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pDebugprocc != NULL) > m_pDebugprocc��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// ���C�g�̔j��
	if (m_pLight != NULL)
	{// �k���łȂ�������
		// �f�o�b�O�̏I������
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// ���C�g���j������Ă��Ȃ�
	if (m_pLight != NULL)
	{
		MessageBox(NULL, " void CManager::Uninit() > if (m_pDebugprocc != NULL) > m_pDebugprocc��������NULL�ł͂���܂���", "Error", MB_OK);
	}

	// ���[�V�����t�@�C���ǂݎ��N���X�̃�����������Δj��
	if (m_pLoadMotionFile != NULL)
	{
		// ��������j����NULL�ɂ���
		m_pLoadMotionFile->Uninit();
		m_pLoadMotionFile = NULL;
	}

	// �t�H���g�̔j��
	if (m_pFontMane != NULL)
	{
		m_pFontMane->Uninit();
		delete m_pFontMane;
		m_pFontMane = NULL;
	}

	// �|�[�Y�̔j��
	if (m_pPause != NULL)
	{
		m_pPause = NULL;	// �|�[�Y�̃�������Y���
	}

	//	�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();	// �e�N�X�`���ƃ������j��
		m_pTexture = NULL;		// �Y���
	}

	// �X�e�[�W�̔j��
	if (m_pStage != NULL)
	{
		m_pStage = NULL;
	}

	// �v���C���[�̔j��
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;
	}

	// �G�l�~�[�̔j��
	m_pEnemy.clear();
}

//**********************************************
// �}�l�[�W���[�X�V����
//**********************************************
void CManager::Update(void)
{
	m_pInputKeyboard->Update();	// �L�[�{�[�h
	m_pInputMouse->Update();	// �}�E�X
	m_pInputJoypad->Update();	// �W���C�p�b�h
	m_pCamera->Update();		// �J����

	// ���݂̃|�[�Y�̗L�����擾
	bool bNowPause = m_pPause->GetPause();	
	
	if (m_pInputKeyboard->GetTrigger(DIK_P) == true)
	{// P�L�[����������
		// ���݂Ƃ͋t�̃|�[�Y�ɂ���
		m_pPause->SetPause(!bNowPause);
	}

	// �f�o�b�O���[�h���̂ݗL��
#ifdef _DEBUG
	// �����蔻��p���f���̕`�摀��
	CCollision::IsDraw();
#endif

	// �|�[�Y��ԂŖ������
	if (m_pPause->GetPause() == false)
	{
		// �����_���[�̍X�V����
		m_pRenderer->Update();		
	}
}

//**********************************************
// �}�l�[�W���[�`�揈��
//**********************************************
void CManager::Draw(void)
{
	m_pCamera->Debug();			// �J�����̃f�o�b�O�\��
	CObject::DrawDebug();		// �I�u�W�F�N�g�̃f�o�b�O�\��
	CTexture::DebugTexture();	// �e�N�X�`�����̃f�o�b�O�\��

	m_pRenderer->Draw();		// �����_���[�̕`�揈��
}