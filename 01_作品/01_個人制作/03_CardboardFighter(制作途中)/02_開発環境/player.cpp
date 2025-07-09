//**********************************************
// 
// �v���C���[����
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "player.h"
#include "manager.h"
#include "input.h"
#include "particle.h"
#include "texture.h"
#include "object.h"
#include "camera.h"

//**********************************************
// �v���C���[�R���X�g���N�^
//**********************************************
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_pBlendMotion = NULL;	// ���[�V����
	m_pMotion = NULL;		// ���[�V�����u�����h
	m_pCharacter = NULL;	// �L�����N�^-
	m_bMove = false;		// �ړ��̗L��
	m_pColiCyli = NULL;		// �~���̓����蔻��
}

//**********************************************
// �v���C���[�f�X�g���N�^
//**********************************************
CPlayer::~CPlayer()
{
}

//**********************************************
// �v���C���[����������
//**********************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nAppStateCnt, const char* pFilePass)
{
	// ���[�h���[�V�����t�@�C���|�C���^�擾
	CLoadMotionFile* pLoadMotionFile = CManager::GetLoadMotionFile();

	// ��ސݒ�
	CObject::SetType(CObject::TYPE_PLAYER);

	// �t�@�C���p�X������Ώ�������
	if (pFilePass != NULL)
	{
		// ���[�V�����t�@�C����ǂݍ���
		pLoadMotionFile->Load(pFilePass);

		// �L�����N�^�[�Z�b�g�̎擾
		CCharacterSet* pCharcterSet = pLoadMotionFile->GetCharacterSet();

		// �e��p�����[�^�̎擾
		float fMoveMent = pCharcterSet->GetMovement();
		float fJump = pCharcterSet->GetJump();
		float fRadiusu = pCharcterSet->GetRadius();
		float fHeight = pCharcterSet->GetHeight();
		int nLife = pCharcterSet->GetLife();

		// �e��ϐ�������
		m_pCharacter = CCharacter::Create(pos, rot, fRadiusu,fHeight, nLife, fMoveMent, nAppStateCnt);	// �L�����N�^�[���
		m_bMove = false;		// �ړ��̗L��

		// �L�����N�^�[���擾
		CCharacterSet* pCharacterSet = pLoadMotionFile->GetCharacterSet();

		// �p�[�c���擾
		m_nNumModel = pCharacterSet->GetNumParts();

		// ���f���̓ǂݎ�����������炤
		pLoadMotionFile->CopyModel(&m_pModel);

		// ���[�V�����̓ǂݎ�����������炤
		pLoadMotionFile->CopyMotion(&m_pMotion);
		pLoadMotionFile->CopyMotion(&m_pBlendMotion);

		// ���f����ݒ�
		m_pMotion->SetModel(&m_pModel);

		// ���̓����蔻�萶��
		CCollisionSpher* oColiSpher = CCollisionSpher::Create(D3DXVECTOR3_NULL, D3DXVECTOR3_NULL,false,15.0f,0);
		m_pColiSpher.push_back(oColiSpher);

		CCollisionSpher* oColiSpherB = CCollisionSpher::Create(D3DXVECTOR3(0.0f,30.0f,0.0f), D3DXVECTOR3_NULL,false,15.0f,0);
		m_pColiSpher.push_back(oColiSpherB);

		// �~���̓����蔻�萶��
		m_pColiCyli = CCollisionCylinder::Create(D3DXVECTOR3_NULL, D3DXVECTOR3_NULL, false, fRadiusu,fHeight);
	}

	return S_OK;
}

//**********************************************
//  �v���C���[�I������
//**********************************************
void CPlayer::Uninit()
{
	if (m_pModel.size() > 0)
	{// ���f���p�[�c������̂Ȃ�Δj������NULL�ɂ���
		for (auto& iter : m_pModel)
		{
			iter->Uninit();
		}
		m_pModel.clear();
	}

	if (m_pCharacter != NULL)
	{// �L�����N�^�[���j��
		m_pCharacter->Uninit();
		m_pCharacter = NULL;
	}

	// ���[�V������񂪂���Δj��
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		m_pMotion = NULL;
	}

	// ���[�V������񂪂���Δj��
	if (m_pBlendMotion != NULL)
	{
		m_pBlendMotion->Uninit();
		m_pBlendMotion = NULL;
	}

	// ���̓����蔻��̔j��
	for (auto& iter : m_pColiSpher)
	{
		iter->Uninit();
	}
	m_pColiSpher.clear();

	// �~���̓����蔻��̔j��
	if (m_pColiCyli != NULL)
	{
		m_pColiCyli = NULL;
	}

	// ���g�̔j��
	Release();
}

//**********************************************
//  �v���C���[�X�V����
//**********************************************
void CPlayer::Update()
{
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h�擾
	CInputMouse* pInputMouce = CManager::GetInputMouse();			// �}�E�X�擾
	CInputJoypad* pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�h�擾
	CCamera* pCamera = CManager::GetCamera();						// �J�����擾
	CStage* pStage = CManager::GetStage();							// �X�e�[�W�̎擾
	CMeshField* pMeshField = pStage->GetMeshField();				// ���b�V���t�B�[���h�̎擾
	std::vector<CWall*> pWall = pStage->Getwall();					// �ǎ擾
	D3DXVECTOR3 rotCamera = pCamera->GetRotation();					// �J�����̌���
	CState state = m_pCharacter->GetState();						// ��Ԏ擾
	D3DXVECTOR3 pos = m_pCharacter->GetPosition();					// �ʒu���擾
	D3DXVECTOR3 posOld = m_pCharacter->GetPositionOld();			// �Â��ʒu���擾
	D3DXVECTOR3 rot = m_pCharacter->GetRotation();					// �������擾
	D3DXVECTOR3 rotDest = m_pCharacter->GetRotationDest();			// �ړI�̌������擾
	D3DXVECTOR3 move = m_pCharacter->GetMove();						// �ړ��ʂ��擾
	float fMovement = m_pCharacter->GetMovement();					// �ړ��l���擾

	m_bMove = false;			// �ړ����Ă��Ȃ���Ԃɂ���
	float fAngleMove = 0.0f;	// �ړ�����p�x

	if (pInputKeyboard->GetPress(DIK_W) == true ||
		pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_UP) == true)
	{// ��ړ�
		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_LEFT) == true)
		{// ����ړ�
			fAngleMove = rotCamera.y + ANGLE_UP_LEFT;	// �J�������܂߂��p�x�v�Z
			m_bMove = true;								// �ړ����Ă����Ԃɂ�
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true ||
			pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_RIGHT) == true)
		{// �E��ړ�
			fAngleMove = rotCamera.y + ANGLE_UP_RIGHT;	// �J�������܂߂��p�x�v�Z
			m_bMove = true;								// �ړ����Ă����Ԃɂ�
		}
		else
		{// ��ړ�
			fAngleMove = rotCamera.y + ANGLE_UP;	// �J�������܂߂��p�x�v�Z
			m_bMove = true;							// �ړ����Ă����Ԃɂ�
		}
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true ||
		pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_DOWN) == true)
	{// ���ړ�

		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_LEFT) == true)
		{// �����ړ�
			fAngleMove = rotCamera.y + ANGLE_DOWN_LEFT;	// �J�������܂߂��p�x�v�Z
			m_bMove = true;							// �ړ����Ă����Ԃɂ�
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true ||
			pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_RIGHT) == true)
		{// �E���ړ�
			fAngleMove = rotCamera.y + ANGLE_DOWN_RIGHT;	// �J�������܂߂��p�x�v�Z
			m_bMove = true;									// �ړ����Ă����Ԃɂ�
		}
		else
		{// ���ړ�
			fAngleMove = rotCamera.y + ANGLE_DOWN;	// �J�������܂߂��p�x�v�Z
			m_bMove = true;								// �ړ����Ă����Ԃɂ�
		}
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_LEFT) == true)
	{// ���ړ�
		fAngleMove = rotCamera.y + ANGLE_LEFT;	// �J�������܂߂��p�x�v�Z
		m_bMove = true;							// �ړ����Ă����Ԃɂ�
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputJoypad->GetkeyRepeat(CInputJoypad::JOYKEY_RIGHT) == true)
	{// �E�ړ�
		fAngleMove = rotCamera.y + ANGLE_RIGHT;	// �J�������܂߂��p�x�v�Z
		m_bMove = true;							// �ړ����Ă����Ԃɂ�
	}

	// ������Ԃł����
	if (m_bMove == true)
	{
		// �ړ��ʂ̌v�Z
		move.x += sinf(fAngleMove) * fMovement;
		move.z += cosf(fAngleMove) * fMovement;

		// �p�x�̍X�V
		m_pCharacter->SetRotationDestY(fAngleMove + D3DX_PI);

		// ���郂�[�V�����ɕύX
		//m_pMotion->SetMotion(MOTION_MOVE);
		m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_MOVE, 20);
	}
	else
	{
		// �ҋ@���[�V�����ɕύX
		m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_NONE, 30);
	}

	// �p�x�̍X�V
	m_pCharacter->UpdateRotaition(0.3f);

	// �Â��ʒu�̍X�V
	posOld = pos;

	// �d��
	move.y -= 2.0f;

	// �����̌v�Z
	move.x += -move.x * FRICTION_VALUE;
	move.z += -move.z * FRICTION_VALUE;

	// �ʒu�Ɉړ��ʂ�ǉ�
	pos += move;

	// �����ƕ����擾
	float fHeight = m_pCharacter->GetHeight();
	float fRadius = m_pCharacter->GetRadius();

	// �G�Ƃ̓����蔻��
	for (auto& iter : CManager::GetEnmey())
	{
		iter->CollisionCylinderCylinder(&pos, fHeight,fRadius);
	}


	// �ǂƂ̓����蔻��
	if (pWall.capacity() > 0)
	{
		for (auto& iter : pWall)
		{
			if (iter->CollisionWall(&pos, posOld))
			{

			}
		}
	}

	// ���b�V���t�B�[���h�Ƃ̓����蔻��
	if (pMeshField != NULL)
	{
		pMeshField->Collision(&pos);
	}

	// �����܂ŗ����Ȃ��悤�ɂ���
	if (pos.y <= 0.0f)
	{
		pos.y = 0.0f;
		move.y = 0.0f;
	}

	m_pCharacter->SetPosition(pos);			// �ʒu��ݒ�
	m_pCharacter->SetPositionOld(posOld);	// �Â��ʒu��ݒ�
	m_pCharacter->SetMove(move);			// �ړ��ʂ�ݒ�

	// �L�����N�^�[�A�b�v�f�[�g
	m_pCharacter->Update();

	// ��Ԏ擾
	int nState = state.GetState();

	// ��Ԃɂ�鏈��
	switch (nState)
	{
		// �ʏ���
	case CState::STATE_NONE:
		break;

		// �_���[�W���
	case CState::STATE_DAMAGE:
		break;

	default:
		break;
	}

	// �����蔻��X�V(���[�V�����̍X�V�O�ɏ������邱��)
	for (auto& iterColiSpher : m_pColiSpher)
	{
		// ���f���̃}�g���b�N�X���擾����
		int nIdxModel = iterColiSpher->GetIndexModel();
		auto iterModel = m_pModel.begin() + nIdxModel;
		D3DXMATRIX mtxModel = (*iterModel)->GetMatrix();
		iterColiSpher->Update(mtxModel);
	}
	m_pColiCyli->Update(pos, rot);

	// ���[�V�����̃A�b�v�f�[�g
	m_pMotion->UpdateMotionModelBlend(m_pBlendMotion);

	// �Ǐ]�J�����ɂ���
	pCamera->FollowCamera(pos);
}

//**********************************************
// �v���C���[�`�揈��
//**********************************************
void CPlayer::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ��Ԏ擾
	CState state = m_pCharacter->GetState();
	
	// ���f���ɓK�p����F
	D3DXCOLOR* pCol = NULL;

	// �_���[�W�F�ϐ�
	D3DXCOLOR colDamage;

	// ��Ԏ擾
	int nState = state.GetState();

	// ��Ԃɂ�鏈��
	switch (nState)
	{
		// �ʏ���
	case CState::STATE_NONE:
		break;

		// �_���[�W���
	case CState::STATE_DAMAGE:
		// �F��ݒ�
		colDamage.r = 1.0f;
		colDamage.g = 0.0f;
		colDamage.b = 0.0f;
		colDamage.a = 1.0f;

		// �_���[�W�F���o��������
		pCol = &colDamage;
		break;

	default:
		break;
	}

	// �L�����N�^�[�`��
	m_pCharacter->Draw();

	if (m_pModel.size() > 0)
	{// ���f���p�[�c������̂Ȃ�Ε`��
		for (auto& iter : m_pModel)
		{
			iter->DrawParentChild(pCol);
		}
	}
}

//**********************************************
// �v���C���[��������
//**********************************************
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife, float fMovement, float fFrictionValue, int nAppStateCnt)
{
	CPlayer* pPlayer = NULL;			// �v���C���[�|�C���^�[
	int nNumAll = GetObujectNumAll();	// �I�u�W�F�N�g�̑S�̐��擾

	// �v���C���[�̐���
	if (pPlayer == NULL)
	{
		if (nNumAll >= MAX_OBJECT)
		{
			return NULL;
		}

		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			// ����������
			pPlayer->Init(pos, rot, nAppStateCnt);
		}
		else
		{
			MessageBox(NULL, " CPlayer::Create() > if (pPlayer != NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, " CObject2D* CObject2D::Create() > if (pObject2D == NULL) ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	return pPlayer;

}

//****************************************************************************
// �v���C���[�q�b�g����
//****************************************************************************
void CPlayer::Hit(int nDamage,int nCntState)
{
	// ���݂̗͎̑擾
	int nLifeNow = m_pCharacter->GetLife();

	// �󂯂��_���[�W��ǉ�
	nLifeNow += nDamage;

	// �̗͂�ݒ�
	m_pCharacter->SetLife(nLifeNow);
	
	// �̗͂��Ȃ��Ȃ��Ă��܂���
	if (nLifeNow < 0)
	{

	}
	// �܂��̗͂�����
	else
	{
		// �_���[�W��Ԃɂ���
		m_pCharacter->SetDamageState(nCntState);
	}
}