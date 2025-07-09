//***********************************************************************
//
// �C�[�W���O����
// Aouther Tetsuji Yamamoto
// 
//***********************************************************************
#ifndef _EASING_H_
#define _EASING_H_

#include "main.h"

// �񋓌^�C�[�W���O�̎��
typedef enum
{
	EASING_TYPE_NONE = 0,		// �Ȃ�
	EASING_TYPE_Liner,			// ���ɕω����Ȃ������̓���
	EASING_TYPE_EaseInExpo,		// �O���͂قƂ�Ǖω����Ȃ�,���Ղɒl���傫���Ȃ�,�㔼�ɋ}���ɑ傫���Ȃ�
	EASING_TYPE_OutExpo,		// �O���͋}���ɑ傫���Ȃ�,���Ղɒl�����₩�ɂȂ�,�㔼�ɂقƂ�Ǖω����Ȃ�
	EASING_TYPE_EaseInOutCirc,	// �O���͉��₩�ɑ������,���Ղɋ}���ɑ�����,�㔼�͉��₩�ɂȂ�
	EASING_TYPE_EaseInOutSine,	// �O���͉��₩�ɑ���,���Ղ͈��̑��x��,�㔼�͉��₩�ɂȂ�
	EASING_TYPE_MAX
}EASING_TYPE;

// �v���g�^�C�v�錾
float SelectEasing(int nType, float fp);	// ���D�݂̃C�[�W���O���������܂�
float Liner(float fp);						// Liner
float EaseInExpo(float fp);					// easeInExpo 0 ? 0 : Math.pow(2, 10 * x - 10)
float OutExpo(float fp);					// outExpo fp ==  1.0f ? 1.0f : 1.0f - (float)pow(2, -10 * (double)fp)
float EaseInOutCirc(float fp);				// easeInOutCirc fp < 0.5 ? (1 - sqrtf(1 - pow(2 * P,2))) / 2 : (sqrtf(1 - pow(-2 * P + 2, 2)) + 1) / 2
float EaseInOutSine(float fp);				// easeInOutSine -(cosf(D3DX_PI * fp) - 1) / 2
#endif // !_EASING_H_
