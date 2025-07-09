//**********************************************
// 
// �G�l�~�[����
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "enemy.h"
#include "manager.h"
#include "input.h"
#include "particle.h"
#include "texture.h"
#include "object.h"
#include "camera.h"
#include "myMath.h"

//**********************************************
// �G�l�~�[�R���X�g���N�^
//**********************************************
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_pBlendMotion = NULL;			// ���[�V����
	m_pMotion = NULL;				// ���[�V�����u�����h
	m_pCharacter = NULL;			// �L�����N�^-
	m_bMove = false;				// �ړ��̗L��
	m_pColiCyliAttckRange = NULL;	// ���̓����蔻��(�U���͈�)
	m_pColiCyliBody = NULL;			// �~���̓����蔻��(��)
	m_pAttack = NULL;				// �U�����
}

//**********************************************
// �G�l�~�[�f�X�g���N�^
//**********************************************
CEnemy::~CEnemy()
{
}

//**********************************************
// �G�l�~�[����������
//**********************************************
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nAppStateCnt, const char* pFilePass)
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
		m_pCharacter = CCharacter::Create(pos, rot, fRadiusu, fHeight,nLife, fMoveMent, nAppStateCnt);	// �L�����N�^�[���
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
		CCollisionSpher* oColiSpher = CCollisionSpher::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3_NULL, false, 20.0f, 12);
		m_pColiSpherAttack.push_back(oColiSpher);

		CCollisionSpher* oColiSpherB = CCollisionSpher::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), D3DXVECTOR3_NULL, false, 20.0f, 12);
		m_pColiSpherAttack.push_back(oColiSpherB);

		// ���̓����蔻��(�U���͈�)
		m_pColiCyliAttckRange = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, -30.0f),D3DXVECTOR3_NULL,false,fRadiusu, fHeight);
		
		// �~���̓����蔻��(��)
		m_pColiCyliBody = CCollisionCylinder::Create(D3DXVECTOR3_NULL, D3DXVECTOR3_NULL,false,fRadiusu,fHeight);

		// �U�����̐���
		m_pAttack = CAttack::Create();
	}

	return S_OK;
}

//**********************************************
//  �G�l�~�[�I������
//**********************************************
void CEnemy::Uninit()
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
	m_pColiSpherAttack.clear();

	// ���̓����蔻��(�U�����m)
	if (m_pColiCyliAttckRange != NULL)
	{
		m_pColiCyliAttckRange = NULL;
	}

	// �~���̓����蔻��(��)
	if (m_pColiCyliBody != NULL)
	{
		m_pColiCyliBody = NULL;
	}

	// �U���̔j��
	if (m_pAttack != NULL)
	{
		m_pAttack->Uninit();
		m_pAttack = NULL;
	}

	// ���g�̔j��
	Release();
}

//**********************************************
//  �G�l�~�[�X�V����
//**********************************************
void CEnemy::Update()
{
	CInputKeyboard* pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h�擾
	CInputMouse* pInputMouce = CManager::GetInputMouse();			// �}�E�X�擾
	CInputJoypad* pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�h�擾
	CCamera* pCamera = CManager::GetCamera();						// �J�����擾
	CStage* pStage = CManager::GetStage();							// �X�e�[�W�̎擾
	CMeshField* pMeshField = pStage->GetMeshField();				// ���b�V���t�B�[���h�̎擾
	std::vector<CWall*> pWall = pStage->Getwall();					// �ǎ擾
	CPlayer* pPlayer = CManager::GetPlayer();						// �v���C���[�̎擾
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

	// �U���̃A�b�v�f�[�g
	m_pAttack->Update();

	// �U���͈͂Ƀv���C���[�����āA�U�����Ă��Ȃ���Ԃł����
	if (IsAttackPlayer() == true)
	{
		// �U�����[�V�����ɕύX
		m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_ATTACK, 20);
		m_pAttack->Set(5,120,130,5);
	}
	// �U�����Ă��Ȃ���Ԃł����
	else if(m_pAttack->GetIsAttackEnd() == true)
	{
		// ������Ԃł����
		if (m_bMove == true)
		{
			// �ړ��ʂ̌v�Z
			move.x += sinf(fAngleMove) * fMovement;
			move.z += cosf(fAngleMove) * fMovement;

			// �p�x�̍X�V
			m_pCharacter->SetRotationDestY(fAngleMove + D3DX_PI);

			// ���郂�[�V�����ɕύX
			m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_MOVE, 20);
		}
		else
		{
			// �ҋ@���[�V�����ɕύX
			m_pMotion->SetMotionblend(m_pBlendMotion, MOTION_NONE, 60);
		}
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

	if (pInputKeyboard->GetRelease(DIK_W) == true)
	{
		int a = 0;
	}

	// �ǂƂ̓����蔻��
	if (pWall.capacity() > 0)
	{
		for (auto& iter : pWall)
		{
			iter->CollisionWall(&pos, posOld);
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
	case CState::STATE_NONE:
		break;

	case CState::STATE_DAMAGE:
		break;

	default:
		break;
	}

	// �����蔻��X�V(���[�V�����̍X�V�O�ɏ������邱��)
	for (auto& iterColiSpher : m_pColiSpherAttack)
	{
		// ���f���̃}�g���b�N�X���擾����
		int nIdxModel = iterColiSpher->GetIndexModel();
		auto iterModel = m_pModel.begin() + nIdxModel;
		D3DXMATRIX mtxModel = (*iterModel)->GetMatrix();
		iterColiSpher->Update(mtxModel);
	}

	// �����蔻��X�V
	m_pColiCyliAttckRange->Update(pos, rot);
	m_pColiCyliBody->Update(pos, rot);

	// ���[�V�����̃A�b�v�f�[�g
	m_pMotion->UpdateMotionModelBlend(m_pBlendMotion);

	// �U�����肪�o�鎞�ԂȂ���o���Ă����ꍇ�Ȃ�
	if (m_pAttack->GetIsAttackTime() == true)
	{
		// ���g�̍U�����v���C���[�֓������Ă��邩���ׂ�
		if (IsCollisionAttackPlayer() == true)
		{
			// �U�����I�������Ԃɂ���
			m_pAttack->SetIsAttackEnd(false);

			// �v���C���[�̃q�b�g����
			pPlayer->Hit(0,30);
		}
	}
}

//**********************************************
// �G�l�~�[�`�揈��
//**********************************************
void CEnemy::Draw()
{
	// �L�����N�^�[�`��
	m_pCharacter->Draw();

	if (m_pModel.size() > 0)
	{// ���f���p�[�c������̂Ȃ�Ε`��
		for (auto& iter : m_pModel)
		{
			iter->DrawParentChild();
		}
	}
}

//**********************************************
// �G�l�~�[��������
//**********************************************
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife, float fMovement, float fFrictionValue, int nAppStateCnt)
{
	// �I�u�W�F�N�g�̑S�̐��擾
	int nNumAll = GetObujectNumAll();	

	// �I�u�W�F�N�g�̑S�̐�������Ȃ珈�����Ȃ�
	if (nNumAll >= MAX_OBJECT)
	{
		return NULL;
	}

	// �G�l�~�[�̐���
	CEnemy* pEnemy = new CEnemy;
	
	// ���������m�ۂł���
	if (pEnemy != NULL)
	{
		// ����������
		pEnemy->Init(pos, rot, nAppStateCnt);
	}
	// ���������m�ۂł��Ȃ�����
	else
	{
		MessageBox(NULL, " CEnemy::Create() > ���������m�ۂł��܂���ł���", "Error", MB_OK);
	}

	// ���ʂ�Ԃ�
	return pEnemy;
}

//****************************************************************************
// �G�l�~�[
//****************************************************************************
void CEnemy::Hit(int nDamage)
{

}

//****************************************************************************
// �G�l�~�[�̉~���Ɖ~���̓����蔻��
//****************************************************************************
void CEnemy::CollisionCylinderCylinder(D3DXVECTOR3 * pPosPartner, float fHeightPartner, float fRadiusPartner)
{
	// �ʒu�ƌÂ��ʒu�̎擾
	D3DXVECTOR3 pos = m_pCharacter->GetPosition();
	D3DXVECTOR3 posOld = m_pCharacter->GetPositionOld();

	// ���a�擾
	float fRadius = m_pColiCyliBody->GetRadius();
	
	// �����擾
	float fHeight = m_pColiCyliBody->GetHeight();

	// �������Ă��Ȃ������珈�����~�߂�
	if (CMyMath::ColiisionCylinderCylinder(pos,fRadius,fHeight,*pPosPartner,fRadiusPartner,fHeightPartner) == false)
	{
		return;
	}
	
	// D3DXVECTOR3����D3DXVECTOR2�ֈڂ��ւ���
	D3DXVECTOR2 pos2D, pos2DPar;
	pos2D.x = pos.x;
	pos2D.y = pos.z;
	pos2DPar.x = pPosPartner->x;
	pos2DPar.y = pPosPartner->z;

	// ���E�̒���
	float fLimitLength = fRadius + fRadiusPartner;

	// �_�Ɠ_�̒�����}��
	float fLength = CMyMath::LengthTrigonometric2D(pos2D, pos2DPar);

	// ���E�̒������Z����Γ������Ă��锻��
	if (fLength <= fLimitLength)
	{
		CStage* pStage = CManager::GetStage();							// �X�e�[�W�̎擾
		std::vector<CWall*> pWall = pStage->Getwall();					// �ǎ擾

		// �~�Ɖ~�̏d�Ȃ��������̊Ԃ̒����̔��������
		float fSpaceLength = (fLimitLength - fLength) * 0.5f;

		// ���g���瑊��ւ̌����x�N�g�������
		D3DXVECTOR3 vecPos;
		vecPos.x = pos.x - pPosPartner->x;
		vecPos.y = 0.0f;
		vecPos.z = pos.z - pPosPartner->z;

		// ���K������
		D3DXVec3Normalize(&vecPos, &vecPos);

		// �����Ԃ��x�N�g�������߂�
		D3DXVECTOR3 vecPush = vecPos * fSpaceLength;

		// �����Ԃ�
		pos += vecPush;
		*pPosPartner -= vecPush;

		// �ǂƂ̓����蔻��
		if (pWall.capacity() > 0)
		{
			for (auto& iter : pWall)
			{
				iter->CollisionWall(&pos, posOld);
			}
		}

		// �ʒu��ݒ�
		m_pCharacter->SetPosition(pos);
	}
}

//****************************************************************************
// �G�l�~�[�v���C���[�ւ̃A�^�b�N�̔��f����
//****************************************************************************
bool CEnemy::IsAttackPlayer(void)
{
	// �v���C���[�̎擾
	CPlayer*pPlayer = CManager::GetPlayer();

	// �v���C���[�̑̂̓����蔻��擾
	CCollisionCylinder* pColiCyliPlayer = pPlayer->GetCollisionCylinder();

	// �v���C���[�̓����蔻��ʒu�Ɣ��a�ƍ������擾
	D3DXVECTOR3 posPlayer = pColiCyliPlayer->GetPosition();
	float fRadiusPlayer = pColiCyliPlayer->GetRadius();
 	float fHeightPlayer = pColiCyliPlayer->GetHeight();

	// ���g�̍U���͈͂̈ʒu�Ɣ��a�ƍ����̎擾s
	D3DXVECTOR3 pos = m_pColiCyliAttckRange->GetPosition();
	float fRadius = m_pColiCyliAttckRange->GetRadius();
	float fHeight = m_pColiCyliAttckRange->GetHeight();

	// �������Ă��Ȃ������珈�����~�߂�
	if (CMyMath::ColiisionCylinderCylinder(pos, fRadius, fHeight, posPlayer, fRadiusPlayer, fHeightPlayer) == false)
	{
		// �U���͈͂ɓ����Ă��Ȃ��Ɣ��f����
		return false;
	}

	// �U���͈͂ɓ����Ă���Ɣ��f����
	return true;
}

//****************************************************************************
// �G�l�~�[�v���C���[�֍U���̔���𒲂ׂ鏈��
//****************************************************************************
bool CEnemy::IsCollisionAttackPlayer(void)
{
	// �v���C���[�̎擾
	CPlayer* pPlayer = CManager::GetPlayer();

	// �v���C���[�̑̂̓����蔻��擾
	std::vector<CCollisionSpher*> pColiSpherPlayer = pPlayer->GetCollisionSpher();

	// ���g�̍U������̐�����
	for (auto& iterColiSpherAttack : m_pColiSpherAttack)
	{
		// �G�l�~�[�̓����蔻��ʒu�Ɣ��a���擾
		D3DXVECTOR3 posEnemy = iterColiSpherAttack->GetPosition();
		float fRadiusEnemy = iterColiSpherAttack->GetRadius();

		// �v���C���[�̎󂯂锻�蕪��
		for (auto& iterColiSpherPlayer : pColiSpherPlayer)
		{
			// �v���C���[�̓����蔻��ʒu�Ɣ��a���擾
			D3DXVECTOR3 posPlayer = iterColiSpherPlayer->GetPosition();
			float fRadiusPlayer = iterColiSpherPlayer->GetRadius();

			// ���Ƌ��̓����蔻��Œ��ׂ�
			if (CMyMath::ColiisionSpherSpher(posEnemy, fRadiusEnemy, posPlayer, fRadiusPlayer) == true)
			{
				// �������Ă���Ɣ��肵�������~�߂�
				return true;
			}
		}
	}

	// �������Ă��Ȃ�����
	return false;
}