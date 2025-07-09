//**********************************************
// 
// �I�u�W�F�N�g����
// Author Tetsuji Yamamoto
// 
//**********************************************
#include "object.h"
#include "debugproc.h"

// �ÓI�����o�[�ϐ��錾
CObject* CObject::m_aPTop[PRIORITY_MAX] = {};	// �擪�̃A�h���X
CObject* CObject::m_aPCur[PRIORITY_MAX] = {};	// �Ō���̃A�h���X

int CObject::m_nNumAll = 0;						// �I�u�W�F�N�g�̑���

//**********************************************
// �I�u�W�F�N�g�R���X�g���N�^
//**********************************************
CObject::CObject(int nPriority)
{
	// ���M�����X�g�ɒǉ�
	
	// �O�̃I�u�W�F�N�g���Ō���̃A�h���X�ɐݒ�
	m_pPrev = m_aPCur[nPriority];

	// �O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�̃|�C���^�����g�ɐݒ�
	if (m_pPrev != NULL)
	{
		m_pPrev->m_pNext = this;
	}

	// ���̃I�u�W�F�N�g�̃|�C���^��NULL
	m_pNext = NULL;	

	// �擪�̃A�h���X��������Ύ��M��擪�A�h���X�ɂ���
	if (m_aPTop[nPriority] == NULL)
	{
		m_aPTop[nPriority] = this;
	}

	// �Ō���̃I�u�W�F�N�g���������g�ɐݒ�
	m_aPCur[nPriority] = this;

	m_type = TYPE_NONE;			// �^�C�v��ݒ�
	m_nPriority = nPriority;	// �D��x
	m_nNumAll++;				// �������J�E���g�A�b�v

	//for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//{
	//	if (m_apObject[nPriority][nCnt] == NULL)
	//	{
	//		m_apObject[nPriority][nCnt] = this;	// �������g����
	//		m_nID = nCnt;						// �������g��ID��ۑ�
	//		m_type = TYPE_NONE;					// �^�C�v��ݒ�
	//		m_nPriority = nPriority;			// �D��x
	//		m_nNumAll++;						// �������J�E���g�A�b�v
	//		break;
	//	}
	//}
}

//**********************************************
// �I�u�W�F�N�g�f�X�g���N�^
//**********************************************
CObject::~CObject()
{
}

//**********************************************
// �I�u�W�F�N�g�S�j������
//**********************************************
void CObject::ReleaseAll(void)
{
	// �v���C�I���e�B�̐�����
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		// �擪�̃I�u�W�F�N�g���
		CObject* pObject = m_aPTop[nCntPri];

		// ���̃I�u�W�F�N�g��NULL�ɂȂ�܂Ń��[�v����
		while (pObject != NULL)
		{
			// ���̃I�u�W�F�N�g�|�C���^���ꎞ�ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			// �C������
			pObject->Uninit();

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;
		}

		// �擪�ƍŌ���̃|�C���^��NULL�ɂ���
		m_aPTop[nCntPri] = NULL;
		m_aPCur[nCntPri] = NULL;
	}


	//for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPri][nCnt] != NULL)
	//		{
	//			m_apObject[nCntPri][nCnt]->Uninit();
	//		}
	//	}
	//}
	//
	//for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPri][nCnt] != NULL)
	//		{
	//			MessageBox(NULL, " CObject::ReleaseAll() > if (m_apObject[nCntPri][nCnt]) > m_apObject[nCntPri][nCnt]��������NULL�ł͂���܂���", "Error", MB_OK);
	//			return;
	//		}
	//	}
	//}
}

//**********************************************
// �I�u�W�F�N�g�S�X�V����
//**********************************************
void CObject::UpdateAll(void)
{
	// �v���C�I���e�B�̐�����
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		// �擪�̃I�u�W�F�N�g���
		CObject* pObject = m_aPTop[nCntPri];
		
		// ���̃I�u�W�F�N�g��NULL�ɂȂ�܂Ń��[�v����
		while (pObject != NULL)
		{
			// ���̃I�u�W�F�N�g�|�C���^���ꎞ�ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			// �X�V����
			pObject->Update();

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;
		}
	}

	//for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPri][nCnt] != NULL)
	//		{
	//			m_apObject[nCntPri][nCnt]->Update();
	//		}
	//	}
	//}
}

//**********************************************
// �I�u�W�F�N�g�S�`�揈��
//**********************************************
void CObject::DrawAll(void)
{
	// �v���C�I���e�B�̐�����
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		// �擪�̃I�u�W�F�N�g���
		CObject* pObject = m_aPTop[nCntPri];

		// ���̃I�u�W�F�N�g��NULL�ɂȂ�܂Ń��[�v����
		while (pObject != NULL)
		{
			// ���̃I�u�W�F�N�g�|�C���^���ꎞ�ۑ�
			CObject* pObjectNext = pObject->m_pNext;

			// �`�揈��
			pObject->Draw();

			// ���̃I�u�W�F�N�g����
			pObject = pObjectNext;
		}
	}

	//for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	//{
	//	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	//	{
	//		if (m_apObject[nCntPri][nCnt] != NULL)
	//		{
	//			m_apObject[nCntPri][nCnt]->Draw();
	//		}
	//	}
	//}
}

//**********************************************
// �I�u�W�F�N�g�j������
//**********************************************
void CObject::Release(void)
{
	// ���M�����X�g����폜

	// �D��x���擾
	int nPriority = GetPriority();

	// ���X�g���Ȃ���
	// �擪���Ȃ��Ȃ�ꍇ
	if (m_pPrev == NULL && m_pNext != NULL)
	{
		m_pNext->m_pPrev = NULL;
		m_aPTop[nPriority] = m_pNext;
	}
	// �Ō�����Ȃ��Ȃ�ꍇ
	else if (m_pPrev != NULL && m_pNext == NULL)
	{
		m_pPrev->m_pNext = NULL;
		m_aPCur[nPriority] = m_pPrev;
	}
	// ���X�g�̓r���̏ꍇ
	else if (m_pPrev != NULL && m_pNext != NULL)
	{
		m_pNext->m_pPrev = m_pPrev;
		m_pPrev->m_pNext = m_pNext;
	}

	// �����J�E���g�_�E��
	m_nNumAll--;

	// �������M��j��
	delete this;

	//int nIdx = this->m_nID;
	//int nPri = this->m_nPriority;
	//
	//if (m_apObject[nPri][nIdx] != NULL)
	//{
	//	delete m_apObject[nPri][nIdx];
	//	m_apObject[nPri][nIdx] = NULL;
	//	m_nNumAll--;
	//}
	//
	//if (m_apObject[nPri][nIdx] != NULL)
	//{
	//	MessageBox(NULL, " void CObject::Release(void) > if (m_apObject[nIdx] != NULL) > m_apObject[nIdx]��������NULL�ł͂���܂���", "Error", MB_OK);
	//}
}

//**********************************************
// �I�u�W�F�N�g�f�o�b�O�\������
//**********************************************
void CObject::DrawDebug(void)
{
	CDebugprocc::Print("[ s Object ���Ԃ������� �I�u�W�F�N�g �� ]\n");
	CDebugprocc::Print("m_nNumAll : %d\n",m_nNumAll);
	CDebugprocc::Print("\n");
}