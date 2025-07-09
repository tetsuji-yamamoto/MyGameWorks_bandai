#ifndef _BACKGROUND_H_ //�}�N����`���ꂦ�ĂȂ�������
#define _BACKGROUND_H_ //��d�C���N���[�h�h�~�}�N����`

#include "main.h"

#define FALE_TEX_BG_TITLE_CLOUDY_1 "data\\BG\\Thunderstorm_001.png"
#define FALE_TEX_BG_TITLE_CLOUDY_2 "data\\BG\\Thunderstorm_002.png"

//�w�i�̎�ޗ񋓌^
typedef enum
{
	BGTYPE_TITLE = 0,		//�^�C�g���̔w�i
	BGTYPE_TUTORIAL,		//�`���[�g���A���̔w�i
	BGTYPE_GAME,			//�Q�[���̔w�i
	BGTYPE_RESULT_GAMEOVER,	//�Q�[���I�[�o�[�̔w�i
	BGTYPE_RESULT_GAMECLER,	//�Q�[���N���A�̔w�i
	BGTYPE_RANKING,			//�����L���O�̔w�i
	BGTYPE_CLOUDY_0,		//�܂�̔w�i
	BGTYPE_CLOUDY_1,		//�����܂�̔w�i
	BGTYPE_MAX
}BGTYPE;

//�v���g�^�C�v�錾
void UninitBG(void);	//�w�i�̏I��
void UpdateBG(void);	//�w�i�̍X�V
void DrawBG(void);		//�w�i�̕`��
void InitBG(void);		//�w�i�̏�����
void SetBackground(const char* pFileName, BGTYPE type, D3DXCOLOR col);				//�w�i
void MoveBackground(D3DXCOLOR col, float texMoveX, float texMoveY, int nCntBG);	//�w�i
void EndBackground(BGTYPE type);	//�w�i�I���

#endif 