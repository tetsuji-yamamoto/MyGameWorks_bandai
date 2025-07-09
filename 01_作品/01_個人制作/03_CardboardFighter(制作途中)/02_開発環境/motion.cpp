//*************************************
// 
// ���[�V����
// Author Tetsuji Yamamoto
// 
//*************************************
#include "motion.h"
#include "myMath.h"

//-------------------------------------
// �L�[�N���X

//*************************************
// �L�[�N���X�R���X�g���N�^
//*************************************
CKey::CKey()
{
	m_fPosX = NULL;	// �ʒuX
	m_fPosY = NULL;	// �ʒuY
	m_fPosZ = NULL;	// �ʒuZ
	m_fRotX = NULL;	// ����X
	m_fRotY = NULL;	// ����Y
	m_fRotZ = NULL;	// ����Z
}

//*************************************
// �L�[�N���X�f�X�g���N�^
//*************************************
CKey::~CKey()
{
}

//-------------------------------------
// �L�[���N���X

//*************************************
// �L�[���N���X�R���X�g���N�^
//*************************************
CKeyInfo::CKeyInfo()
{
	m_nFrame = NULL;	// �Đ��t���[��
	m_nNumkey = 0;		// �L�[��
}

//*************************************
// �L�[���N���X�f�X�g���N�^
//*************************************
CKeyInfo::~CKeyInfo() 
{
}

//*************************************
// �L�[���[�V������񏉊���
//*************************************
CKey* CKeyInfo::CreateKey(int nNumKey)
{
	//// �L�[����ۑ�
	//m_nNumkey = nNumKey;
	//
	//// �L�[��񕪊m�ۂ���
	//if (m_pKey)
	//{
	//	m_pKey = new CKey[nNumKey];
	//}
	//
	//return m_pKey;
	return NULL;

}

//*************************************
// �L�[���[�V�������I������
//*************************************
void CKeyInfo::Uninit()
{
	// �L�[������Δj������
	for (auto& iter : m_pKey)
	{
		iter->Uninit();
	}
	m_pKey.clear();

	// ���g�̔j��
	delete this;
}

//-------------------------------------
// �L�[���[�V�������

//*************************************
// �L�[���[�V�������
//*************************************
CMotionInfo::CMotionInfo()
{
	m_bLoop = false;	// ���[�v���邩�ǂ���
	m_nNumKey = NULL;	// �L�[�̑���
	m_nNumKeyInfo = 0;	// �L�[���̐�
}

//*************************************
// �L�[���[�V�������f�X�g���N�^
//*************************************
CMotionInfo::~CMotionInfo()
{
}

//*************************************
// �L�[���[�V�������I��
//*************************************
void CMotionInfo::Uninit()
{
	// �L�[��񂪂���Δj������
	for (auto& iter : m_pKeyinfo)
	{
		iter->Uninit();
	}
	m_pKeyinfo.clear();

	// ���g�̔j��
	delete this;
}

//*************************************
// �L�[���[�V������񏉊���
//*************************************
CKeyInfo* CMotionInfo::CreateKeyInfo(int nNumKeyInfo)
{
	// �L�[���̐��ۑ�
	m_nNumKeyInfo = nNumKeyInfo;

	//// �k���ł���΃L�[��񕪊m�ۂ���
	//if (m_pKeyinfo == NULL)
	//{
	//	m_pKeyinfo = new CKeyInfo[nNumKeyInfo];
	//}

	//return m_pKeyinfo;

	return NULL;
}

//-------------------------------------
// ���[�V�����N���X

//*************************************
// ���[�V�����N���X�R���X�g���N�^
//*************************************
CMotion::CMotion()
{
	m_nNumMotion = 0;			// ���[�V�����̑���
	m_nKeySet = 0;				// ���݂̃L�[�Z�b�gNo.
	m_nNextKeySet = 0;			// ���̃L�[�Z�b�g
	m_nCounterMotion = 0;		// ���[�V�����J�E���^�[
	m_nNumModel = 0;			// ���f���̐�
	m_bEndMotion = false;		// ���[�V�������I��������ǂ���
	m_bBlend = false;			// �u�����h�̗L��
	m_nBlendTime = 1;			// �u�����h����
	m_nTypeBlendMotion = 0;		// �u�����h���郂�[�V�����^�C�v
	m_nCntBlend = 0;			// ���[�V�����u�����h�J�E���^�[
}

//*************************************
// ���[�V�����N���X�f�X�g���N�^
//*************************************
CMotion::~CMotion()
{
}

//*************************************
// ���[�V�����N���X������
//*************************************
void CMotion::Init(int nNumMotion)
{
	
}

//*************************************
// ���[�V�����N���X�I��
//*************************************
void CMotion::Uninit()
{
	// ���[�V������񂪂���Δj������
	for (auto& iter : m_pMotionInfo)
	{
		iter->Uninit();
	}
	m_pMotionInfo.clear();

	// ���g�̔j��
	delete this;
}

//*************************************
// ���[�V�����N���X�Z�b�g
//*************************************
void CMotion::SetModel(std::vector<CModel*>* ppModel)
{
	m_pModel = *ppModel;
}

//*************************************
// ���[�V�����N���X�Z�b�g���[�V����
//*************************************
void CMotion::SetMotion(int nSetMotion)
{
	// ���̃��[�V�����ł͂Ȃ��}�C�i�X��̐��l�ł͖���������
	if (nSetMotion >= 0 && nSetMotion != m_nTypeMotion)
	{
		m_nTypeMotion = nSetMotion;	// ���[�V�����^�C�v�ύX
		m_nCounterMotion = 0;		// ���[�V�����J�E���^�[�[��
		m_nKeySet = 0;				// ���݂̃L�[�Z�b�g�������Z�b�g
	}
}

//*************************************
// ���[�V�����N���X�Z�b�g���[�V�����u�����h
//*************************************
void CMotion::SetMotionblend(CMotion* pBlendMotion,int nSetMotion,int nBlendTime)
{
	// ���[�V������������ΐݒ肵�Ȃ�
	if (nSetMotion < 0)
	{
		return;
	}

	auto iterMotionInfo = GetMotionInfo(m_nTypeMotion);			// ���[�V�������擾
	bool bLoop = (*iterMotionInfo)->GetLoop();					// ���[�v

	// ���̃��[�V�����ł͂Ȃ����̓��[�V�������I����Ă����Ԃł���ΐݒ�
	if (nSetMotion != m_nTypeMotion || m_bEndMotion == true)
	{
		// ���[�V�����u�����h�̃J�E���^�[��ݒ�
		pBlendMotion->SetCounterMotion(m_nCounterMotion);

		// ���[�V�����u�����h�̃L�[�Z�b�g��ݒ�
		pBlendMotion->SetKeySet(m_nKeySet);

		m_nTypeBlendMotion = m_nTypeMotion;	// �u�����h���郂�[�V�����^�C�v
		m_nTypeMotion = nSetMotion;			// ���[�V�����^�C�v�ύX
		m_nCounterMotion = 0;				// ���[�V�����J�E���^�[�[��
		m_nCntBlend = 0;					// �u�����h�J�E���^�[�[��
		m_nKeySet = 0;						// ���݂̃L�[�Z�b�g�������Z�b�g
		m_nBlendTime = nBlendTime;			// �u�����h����
		m_bBlend = true;					// �u�����h�����Ԃɂ���
		m_bEndMotion = false;				// ���[�V�������I����Ă����Ȃ���Ԃɂ���

		// �u�����h���Ԃ͉����𒴂��Ȃ��悤�ɂ���
		if (m_nBlendTime <= 0)
		{
			m_nBlendTime = 1;
		}
	}
}

//*************************************
// ���[�V�����N���X�X�V
//*************************************
void CMotion::UpdateMotionGetKey(D3DXVECTOR3* pOutPos, D3DXVECTOR3* pOutRot, int nMotion,int nKey)
{
	auto iterMotionInfo = GetMotionInfo(nMotion);					// ���[�V�������擾
	auto iterKeyInfo = (*iterMotionInfo)->GetKeyInfo(m_nKeySet);	// �L�[���擾
	bool bLoop = (*iterMotionInfo)->GetLoop();						// ���[�v
	int nNumKey = (*iterMotionInfo)->GetNumKey();					// �L�[�̑���
	int nFrame = (*iterKeyInfo)->GetFrame();						// �t���[����
	m_nNextKeySet = m_nKeySet + 1;									// ���̃L�[
	float fMugFlame = (float)m_nCounterMotion / (float)nFrame;		// �t���[���{�������߂�
	D3DXVECTOR3 posKey,rotKey;										// ���̃L�[�̈ʒu
	D3DXVECTOR3 posKeyNext,rotKeyNext;								// ���̃L�[�̈ʒu
	D3DXVECTOR3 posDiff, rotDiff;									// �L�[�̍���

	// �L�[�̌��E���z������
	if (m_nNextKeySet >= nNumKey)
	{
		// �[���ɂ���
		m_nNextKeySet = 0;

		// ���[�v���Ȃ��ꍇ
		if (bLoop == false)
		{
			// ���̃��[�V�����͍��Ɠ������[�V�����ɂ���
			m_nNextKeySet = m_nKeySet;
		}
	}

	// ���[�V�����J�E���^�[���t���[�����𒴂����玟�̃L�[�ɂ���
	if (m_nCounterMotion > nFrame)
	{
		// ���[�v���Ȃ��āA���̃��[�V���������̃��[�V�����Ɠ����ꍇ
		if (bLoop == false && m_nNextKeySet == m_nKeySet)
		{
			// ���[�V�����J�E���^�[��ς��Ȃ�
			m_nCounterMotion = nFrame;

			// ���[�V�������I�������Ԃɂ���
			m_bEndMotion = true;
		}
		else
		{
			// ���[�V�����J�E���^�[�����Z�b�g
			m_nCounterMotion = 0;

			// ���̃��[�V������ݒ�
			m_nKeySet = m_nNextKeySet;
		}
	}

	// ���Ɛ�̃L�[���擾
	auto iterKeyInfoNow = (*iterMotionInfo)->GetKeyInfo(m_nKeySet);
	auto iterKeyInfoNext = (*iterMotionInfo)->GetKeyInfo(m_nNextKeySet);
	auto iterKeyNow = (*iterKeyInfoNow)->GetKey(nKey);
	auto iterKeyNext = (*iterKeyInfoNext)->GetKey(nKey);

	posKey.x = (*iterKeyNow)->GetPositionX();	// ���̈ʒuX�擾
	posKey.y = (*iterKeyNow)->GetPositionY();	// ���̈ʒuY�擾
	posKey.z = (*iterKeyNow)->GetPositionZ();	// ���̈ʒuZ�擾
	rotKey.x = (*iterKeyNow)->GetRotationX();	// ���̌���X�擾
	rotKey.y = (*iterKeyNow)->GetRotationY();	// ���̌���Y�擾
	rotKey.z = (*iterKeyNow)->GetRotationZ();	// ���̌���Z�擾

	posKeyNext.x = (*iterKeyNext)->GetPositionX();	// ���̈ʒuX�擾
	posKeyNext.y = (*iterKeyNext)->GetPositionY();	// ���̈ʒuY�擾
	posKeyNext.z = (*iterKeyNext)->GetPositionZ();	// ���̈ʒuZ�擾
	rotKeyNext.x = (*iterKeyNext)->GetRotationX();	// ���̌���X�擾
	rotKeyNext.y = (*iterKeyNext)->GetRotationY();	// ���̌���Y�擾
	rotKeyNext.z = (*iterKeyNext)->GetRotationZ();	// ���̌���Z�擾

	// ���[�V�������I����Ă���ꍇ�͒l�����̂܂ܕԂ�
	if (m_bEndMotion == true)
	{
		*pOutPos = posKey * fMugFlame;
		*pOutRot = rotKey * fMugFlame;
	}

	posDiff = posKeyNext - posKey;	// �ʒu�̍��������߂�
	rotDiff = rotKeyNext - rotKey;	// �����̍��������߂�

	// �ŒZ�̊p�x�ɒ���
	rotDiff.x = CMyMath::ShortestAngle(rotDiff.x);
	rotDiff.y = CMyMath::ShortestAngle(rotDiff.y);
	rotDiff.z = CMyMath::ShortestAngle(rotDiff.z);

	*pOutPos = posKey + (posDiff * fMugFlame);	// �ʒu�̍����Ƀt���[���{�����|������𑫂��ʒu�����߂�
	*pOutRot = rotKey + (rotDiff * fMugFlame);	// �����̍����Ƀt���[���{�����|������𑫂����������߂�
}

//*************************************
// ���[�V�����N���X�u�����h�X�V
//*************************************
void CMotion::UpdateMotionGetKeyBlend(D3DXVECTOR3* pOutPos, D3DXVECTOR3* pOutRot, int nMotion, int nKey)
{
	auto iterMotionInfo = GetMotionInfo(nMotion);					// ���[�V�������擾
	auto iterKeyInfo = (*iterMotionInfo)->GetKeyInfo(m_nKeySet);	// �L�[���擾
	bool bLoop = (*iterMotionInfo)->GetLoop();						// ���[�v
	int nFrame = (*iterKeyInfo)->GetFrame();						// �t���[����
	float fMugFlame = (float)m_nCounterMotion / (float)nFrame;		// �t���[���{�������߂�
	D3DXVECTOR3 posKey, rotKey;										// ���̃L�[�̈ʒu
	D3DXVECTOR3 posKeyNext, rotKeyNext;								// ���̃L�[�̈ʒu
	D3DXVECTOR3 posDiff, rotDiff;									// �L�[�̍���

	if (m_nKeySet == -1)
	{// �L�[��������Ώ������Ȃ�
		*pOutPos = D3DXVECTOR3_NULL;
		*pOutRot = D3DXVECTOR3_NULL;
		return;
	}

	// ���Ɛ�̃L�[���擾
	auto iterKeyInfoNow = (*iterMotionInfo)->GetKeyInfo(m_nKeySet);
	auto iterKeyInfoNext = (*iterMotionInfo)->GetKeyInfo(m_nNextKeySet);
	auto iterKeyNow = (*iterKeyInfoNow)->GetKey(nKey);
	auto iterKeyNext = (*iterKeyInfoNext)->GetKey(nKey);

	posKey.x = (*iterKeyNow)->GetPositionX();	// ���̈ʒuX�擾
	posKey.y = (*iterKeyNow)->GetPositionY();	// ���̈ʒuY�擾
	posKey.z = (*iterKeyNow)->GetPositionZ();	// ���̈ʒuZ�擾
	rotKey.x = (*iterKeyNow)->GetRotationX();	// ���̌���X�擾
	rotKey.y = (*iterKeyNow)->GetRotationY();	// ���̌���Y�擾
	rotKey.z = (*iterKeyNow)->GetRotationZ();	// ���̌���Z�擾

	posKeyNext.x = (*iterKeyNext)->GetPositionX();	// ���̈ʒuX�擾
	posKeyNext.y = (*iterKeyNext)->GetPositionY();	// ���̈ʒuY�擾
	posKeyNext.z = (*iterKeyNext)->GetPositionZ();	// ���̈ʒuZ�擾
	rotKeyNext.x = (*iterKeyNext)->GetRotationX();	// ���̌���X�擾
	rotKeyNext.y = (*iterKeyNext)->GetRotationY();	// ���̌���Y�擾
	rotKeyNext.z = (*iterKeyNext)->GetRotationZ();	// ���̌���Z�擾

	posDiff = posKeyNext - posKey;	// �ʒu�̍��������߂�
	rotDiff = rotKeyNext - rotKey;	// �����̍��������߂�

	*pOutPos = posKey + (posDiff * fMugFlame);	// �ʒu�̍����Ƀt���[���{�����|������𑫂��ʒu�����߂�
	*pOutRot = rotKey + (rotDiff * fMugFlame);	// �����̍����Ƀt���[���{�����|������𑫂����������߂�
}

//*************************************
// ���[�V�����N���X�X�V
//*************************************
void CMotion::UpdateMotionModel()
{
	// ���f���J�E���^�[
	int nCntModel = 0;

	for (auto iter = m_pModel.begin(); iter != m_pModel.end(); iter++, nCntModel++)
	{
		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxWorld, mtxRot, mtxTrans;

		// ���[�V�����p�x�N�g��
		D3DXVECTOR3 outPos, outRot;

		// ���f���̈ʒu�ƌ������擾
		D3DXVECTOR3 pos = (*iter)->GetPosition();
		D3DXVECTOR3 rot = (*iter)->GetRotation();

		// ���[�V�����̃A�b�v�f�[�g
		CMotion::UpdateMotionGetKey(&outPos, &outRot, m_nTypeMotion, nCntModel);

		// �o�͂��ꂽ�l��ǉ�
		pos += outPos;
		rot += outRot;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// ������ǉ�
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ʒu��ǉ�
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// �}�g���b�N�X��ݒ�
		(*iter)->SetMatrix(mtxWorld);
	}

	// ���[�V�����J�E���^�[���J�E���g�A�b�v
	m_nCounterMotion++;
}

//*************************************
// ���[�V�����N���X�X�V
//*************************************
void CMotion::UpdateMotionModelBlend(CMotion* pBlendMotion)
{
	// ���f���J�E���^�[
	int nCntModel = 0;

	for (auto iter = m_pModel.begin(); iter != m_pModel.end(); iter++, nCntModel++)
	{
		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxWorld, mtxRot, mtxTrans;

		// ���[�V�����p�x�N�g��
		D3DXVECTOR3 outPos, outRot;

		// �u�����h���[�V�����p�x�N�g��
		D3DXVECTOR3 blendPos, blendRot;

		// ���f���̈ʒu�ƌ������擾
		D3DXVECTOR3 pos = (*iter)->GetPosition();
		D3DXVECTOR3 rot = (*iter)->GetRotation();

		// ���[�V�����̃A�b�v�f�[�g
		CMotion::UpdateMotionGetKey(&outPos, &outRot, m_nTypeMotion, nCntModel);
		pBlendMotion->UpdateMotionGetKey(&blendPos, &blendRot, m_nTypeBlendMotion, nCntModel);

		// ���[�V�����u�����h�������Ԃł����
		if (m_bBlend == true)
		{
			// �u�����h���Ԃ̔{�����o��
			float fMugBlendTime = (float)m_nCntBlend / (float)m_nBlendTime;

			outPos *= fMugBlendTime;
			outRot *= fMugBlendTime;
			blendPos *= 1.0f - fMugBlendTime;
			blendRot *= 1.0f - fMugBlendTime;

			// �Z�o���ꂽ�l��ǉ�
			pos += outPos + blendPos;
			rot += outRot + blendRot;
		}
		else
		{
			// �擾�����l��ǉ�
			pos += outPos;
			rot += outRot;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// ������ǉ�
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ʒu��ǉ�
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// �}�g���b�N�X��ݒ�
		(*iter)->SetMatrix(mtxWorld);
	}

	// ���[�V�����J�E���^�[���J�E���g�A�b�v
	this->CountUpMotionCounter();

	// ���[�V�����J�E���^�[���J�E���g�A�b�v
	pBlendMotion->CountUpMotionCounter();

	// �u�����h���[�V�����J�E���^���u�����h���Ԃ��傫�����
	if (m_nCntBlend > m_nBlendTime)
	{
		// ���[�V�����u�����h�����Ȃ���Ԃɂ���
		m_bBlend = false;
	}
	// �u�����h���[�V�����J�E���^�������
	else
	{
		// ���[�V�����u�����h�J�E���g�A�b�v
		m_nCntBlend++;
	}
}