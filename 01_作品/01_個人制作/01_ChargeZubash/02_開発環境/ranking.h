#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//�}�N����`
#define MAX_RANK (5)					//�\�����ʐ�
#define MAX_RANKSCORE_NUM (3)			//�\���X�R�A����0
#define MAX_RANKSCORE_HEIGHT (100)		//�����L���O�|���S���̍���
#define MAX_RANKSCORE_WIDTH (50)		//�����L���O�|���S���̕�
#define MAX_RANK_WIDTH (50)				//�����N�|���S���̕�
#define MAX_RANK_SCORE_ANIM_TIME (30)	//�_�ŃA�j���[�V�����̎���
#define MAX_BONUS_WIDTH (150)			//�{�[�i�X�̕�
#define MAX_BONUS_HEIGHT (30)			//�{�[�i�X�̍���
//�}�N����`
#define FILE_TXT_SCORE "data\\RANKING\\ranking.txt"	//�X�R�A�̃e�L�X�g�f�[�^�t�@�C��

//�����L���O�{�[�i�X�񋓌^
typedef enum
{
	BONUS_DYING = 0,	//���ɂ����{�[�i�X
	BONUS_JUNPMAN,		//�W�����v�}���{�[�i�X
	BONUS_SHOOTING,		//�ˌ��񐔃{�[�i�X
	BONUS_MAX
}BONUS;
//�����L���O���o
typedef enum
{
	DIRECT_BONUS = 0,	//�{�[�i�X��\��
	DIRECT_RANK,		//�����L���O��\��v
	DIRECT_BRINK,		//�_��
	DIRECT_MAX
}RANKDIRECT;

//�����L���O�X�R�A�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nRank;			//����
	int nScore;			//�X�R�A
}RankScore;
typedef struct
{
	int nSkorDirect;		//���o�p
	int nSkorDirectCounter;	//���o�p�J�E���^�[
}RankDirect;

//�v���g�^�C�v�錾
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(const char* DateScore);
void SetRanking(int nScore);
#endif // !_RANKING_H_
