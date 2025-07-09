//****************************************************************************
// 
// �T�E���h����
// Author tetuji yamamoto
// 
//****************************************************************************
#ifndef _SOUND_H_
#include "main.h"

#include "main.h"

// �T�E���h�N���Xs
class CSound
{
public:

	// �T�E���h�^�C�v
	typedef enum
	{
		SOUND_LABEL_NONE = 0,
		SOUND_LABEL_MAX

	} SOUND_LABEL;

	// �T�E���h���̍\����
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
	} SOUNDINFO;

	CSound();
	~CSound();

	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2* m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data\\sound\\SwoudSlash.wav", -1}	// GM1
	};
};

#endif