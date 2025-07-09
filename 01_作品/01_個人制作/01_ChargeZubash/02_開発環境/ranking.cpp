#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "score.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankingBG = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBonus[BONUS_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBonus = NULL;			//���_�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK];						//�����L���O�X�R�A(5�ʕ�)�\��
RankDirect g_RankDirect;
int g_nRankUpdate = -1;									//�X�V�����NNo.
int g_nTimerRanking;									//�����L���O��ʕ\���^�C�}�[
int g_TransTitleCount;
//==========================================
//�����L���O�̏���������
//==========================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntRank;
	int nRankScore;

	g_nRankUpdate = -1;							//�X�VNo.��������
	g_nTimerRanking = 0;
	g_RankDirect.nSkorDirect = DIRECT_BONUS;	//���o
	g_RankDirect.nSkorDirectCounter = 0;		//���o�J�E���^�[
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\RANKING\\UI_RunkNum_001.png",
		&g_pTextureRank);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\RANKING\\number000.png",
		&g_pTextureRankScore);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\RANKING\\Ranking_Test_001.png",
		&g_pTextureRankingBG);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANKSCORE_NUM, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingBG,
		NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//�����L���O�̏��ʕ���
		g_aRankScore[nCntRank].pos = D3DXVECTOR3(3000.0f - 400 * nCntRank, 200.0f + MAX_RANKSCORE_HEIGHT * nCntRank, 0.0f);
		g_aRankScore[nCntRank].nScore = 0;
		g_aRankScore[nCntRank].nRank = nCntRank + 1;

		for (nRankScore = 0; nRankScore < MAX_RANKSCORE_NUM; nRankScore++)
		{//�X�R�A�̌�������

			pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
			pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
			pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
			pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
			pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
			pVtx[3].pos.z = 0.0f;
			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.9f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.9f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		g_aRankScore[nCntRank].pos = D3DXVECTOR3(3000.0f - MAX_RANK_WIDTH - 400 * nCntRank, 200.0f + MAX_RANKSCORE_HEIGHT * nCntRank, 0.0f);

		pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
		pVtx[3].pos.z = 0.0f;
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + 0.2f * nCntRank, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f + 0.2f * nCntRank, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + 0.2f * nCntRank, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.2f + 0.2f * nCntRank, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();
	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffRankingBG->Lock(0, 0, (void**)&pVtx, 0);
	//�����L���O�̏��̏�����
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = SCREEN_WIDTH;
	pVtx[3].pos.y = SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingBG->Unlock();
	//�����L���O�̃��Z�b�g
	ResetRanking(FILE_TXT_SCORE);
	//�����L���O�̐ݒ�
	SetRanking(GetScore());
}
//==========================================
//�����L���O�̏I������
//==========================================
void UninitRanking(void)
{
	
}
//==========================================
//�����L���O�̍X�V����
//==========================================
void UpdateRanking(void)
{
	int nRankScore;
	int nCntRank;
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;
	//���o��ς���
	if (g_RankDirect.nSkorDirectCounter <= 190)
	{//�ő剉�o�b��
		//���o�J�E���^�[���Z
		g_RankDirect.nSkorDirectCounter++;
		if (g_RankDirect.nSkorDirectCounter <= 60)
		{
			g_RankDirect.nSkorDirect = DIRECT_BONUS;
		}
		else if (g_RankDirect.nSkorDirectCounter > 60 && g_RankDirect.nSkorDirectCounter <= 180)
		{
			g_RankDirect.nSkorDirect = DIRECT_RANK;
		}
		else if (g_RankDirect.nSkorDirectCounter > 180)
		{
			g_RankDirect.nSkorDirect = DIRECT_BRINK;
		}
	}
	
	if (g_RankDirect.nSkorDirect == DIRECT_RANK)
	{
		//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
		g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{//�����L���O�̏��ʕ���
			if (g_aRankScore[nCntRank].pos.x >= 450.0f)
			{
				g_aRankScore[nCntRank].pos.x -= 50.0f;
			}
			else
			{
				g_aRankScore[nCntRank].pos.x = 450.0f;
			}

			for (nRankScore = 0; nRankScore < MAX_RANKSCORE_NUM; nRankScore++)
			{//�X�R�A�̌�������
				pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
				pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
				pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
				pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANKSCORE_WIDTH / 2 + MAX_RANKSCORE_WIDTH * nRankScore;
				pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
				pVtx[3].pos.z = 0.0f;

				pVtx += 4;
			}
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRankScore->Unlock();
		//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
		g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
		//�����L���O�̏��̏�����
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			if (g_aRankScore[nCntRank].pos.x >= 400.0f)
			{
				g_aRankScore[nCntRank].pos.x -= 50.0f;
			}
			else
			{
				g_aRankScore[nCntRank].pos.x = 400.0f;
			}

			pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
			pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
			pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - MAX_RANKSCORE_HEIGHT / 2;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
			pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
			pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + MAX_RANKSCORE_HEIGHT / 2;
			pVtx[3].pos.z = 0.0f;

			pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRank->Unlock();
	}
	else if (g_RankDirect.nSkorDirect == DIRECT_BRINK)
	{
		g_nTimerRanking += 1;				//�_�ŃJ�E���^�[���Z

		//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
		g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

		for (nRankScore = 0; nRankScore < MAX_RANKSCORE_NUM * MAX_RANK; nRankScore++)
		{//�X�R�A�̌�������
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx += 4;
		}
		pVtx -= 4 * MAX_RANKSCORE_NUM * MAX_RANK;
		//�Y���X�R�A�����L���O�X�R�A��_��
		if (g_nRankUpdate != -1 && g_nTimerRanking >= 0)
		{//�����N�C�����ĂāA���A�^�C�}�[���[���ȏゾ������
			pVtx += 4 * MAX_RANKSCORE_NUM * g_nRankUpdate;
			for (nRankScore = 0; nRankScore < MAX_RANKSCORE_NUM; nRankScore++)
			{//�X�R�A�̌�������
			//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);

				pVtx += 4;
			}
		}

		//�^�C�}�[���}�C�i�X�ɂ���
		if (g_nTimerRanking >= 5)
		{
			g_nTimerRanking *= -1;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRankScore->Unlock();
	}

	g_TransTitleCount++;
	if (KeyboardTrigger(DIK_RETURN) == true ||
		GetJoypadTrigger(JOYKEY_START) == true ||
		GetJoypadTrigger(JOYKEY_A) == true ||
		GetJoypadTrigger(JOYKEY_B) == true ||
		g_TransTitleCount >= 600)
	{//���Ԍo�߂܂��̓L�[�����ŉ�ʑJ��
		g_TransTitleCount = 0;
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_TITLE);
	}
}
//==========================================
//�����L���O�̕`�揈��
//==========================================
void DrawRanking(void)
{
	int nCntRank;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingBG, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankingBG);
	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,										//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�����L���O�X�R�A�̕`��
	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_RANKSCORE_NUM; nCntRank++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRankScore);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntRank,							//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);
	}
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�G�t�F�N�g�̕`��
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRank);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntRank,							//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);
	}
}
//==========================================
//�����L���O�̃��Z�b�g
//==========================================
void ResetRanking(const char* DateScore)
{
	int nCnt = 0;
	//�����L���O�X�R�A���̏����ݒ�
	FILE* pFile = fopen(FILE_TXT_SCORE, "r");

	if (pFile == NULL)
	{
		
	}
	else
	{
		//��s�ڂ�ǂݍ���
		char cTmp[125];
		fscanf(pFile, "%s\n", &cTmp[0]);
		//��s�ڈȍ~��ǂݍ���
		for(nCnt = 0; nCnt < MAX_RANK;nCnt++)
		{
			fscanf(pFile,"%d\n",&g_aRankScore[nCnt].nScore);
		}
	}

	fclose(pFile);

}
//==========================================
//�����L���O�̐ݒ�
//==========================================
void SetRanking(int nScore)
{
	int nCntRank;
	int nSelect;
	int nTemp;
	int aPosTexU[3] = {};//�i���̐������i�[
	int nData1, nData2;
	int nCnt;
	//---�����L���O�X�R�A�̕��ёւ�
	//-----�w��X�R�A�������N�C�������� g_nRankUpdate ���X�V
	if (nScore >= g_aRankScore[MAX_RANK - 1].nScore && !(nScore <= 0))//�\�[�g����
	{
		g_aRankScore[MAX_RANK - 1].nScore = nScore;

		for (nCntRank = 0; nCntRank < MAX_RANK - 1; nCntRank++)
		{
			for (nSelect = nCntRank + 1; nSelect < MAX_RANK; nSelect++)
			{
				if (g_aRankScore[nCntRank].nScore <= g_aRankScore[nSelect].nScore)
				{
					nTemp = g_aRankScore[nCntRank].nScore;
					g_aRankScore[nCntRank].nScore = g_aRankScore[nSelect].nScore;
					g_aRankScore[nSelect].nScore = nTemp;
				}
			}
		}
		//���ʂ��Ԃ�����
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			if (g_aRankScore[nCntRank].nScore == nScore)
			{
				g_nRankUpdate = g_aRankScore[nCntRank].nRank - 1;
			}
		}
	}
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		nData1 = 100;
		nData2 = 10;
		//�����Ƃɕ�������
		for (nCnt = 0; nCnt < MAX_RANKSCORE_NUM; nCnt++)
		{
			if (nCnt == 0)
			{
				aPosTexU[0] = g_aRankScore[nCntRank].nScore / nData1;
			}
			else
			{
				aPosTexU[nCnt] = (g_aRankScore[nCntRank].nScore % nData1 / nData2);
				nData1 /= 10;
				nData2 /= 10;
			}
			//-----�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();
	//���ʂ���������
	//�����L���O�X�R�A���̏����ݒ�
	FILE* pFile = fopen(FILE_TXT_SCORE, "w");

	if (pFile == NULL)
	{

	}
	else
	{
		char aScore[10] = "�X�R�A";
		//��s�ڂ���������
		fprintf(pFile, "%s\n", &aScore[0]);
		//��s�ڈȍ~����������
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fprintf(pFile, "%d\n", g_aRankScore[nCntRank].nScore);
		}
	}

	fclose(pFile);
}