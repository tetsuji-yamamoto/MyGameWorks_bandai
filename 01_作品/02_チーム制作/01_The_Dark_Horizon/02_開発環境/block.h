#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

#define MAX_BLOCK (1024)	// �ő�u���b�N��
#define FILE_XFILE_BLOCK_SNOW "date\\xfile\\block\\Block_Snow_001.x"
#define FILE_XFILE_BLOCK_ICE "date\\xfile\\block\\Block_Ice_001.x"
#define FILE_XFILE_BLOCK_GRAVEL "date\\xfile\\block\\Block_Gravel_001.x"
#define FILE_XFILE_BLOCK_WALL "date\\xfile\\block\\Block_Wall_001.x"
#define FILE_XFILE_BLOCK_WALL_ADULT "date\\xfile\\block\\Block_Wall_Adult_001.x"
#define FILE_XFILE_TERRITORYPOINT "date\\xfile\\block\\Block_Territorypoint_001.x"
#define FILE_XFILE_UDD_SNOW "date\\xfile\\block\\Block_Udd_Snow_001.x"

// �u���b�N�^�C�v�񋓌^
typedef enum
{
	BLOCKTYPE_SNOW = 0,		// ��
	BLOCKTYPE_ICE,			// �X
	BLOCKTYPE_GRAVEL,		// ����
	BLOCKTYPE_WALL,			// ��
	BLOCKTYPE_WALL_ADULT,	// ��l�̕�
	BLOCKTYPE_TERRITRY_POINT,	// �s���͈�
	BLOCKTYPE_UDD_SNOW,		// ��̖�
	BLOCKTYPE_MAX
}BLOCKTYPE;

// ����ʗ񋓌^
typedef enum
{
	BLOCKFACETYPE_SIDE = 0,	// ��
	BLOCKFACETYPE_TOP,		// ��
	BLOCKFACETYPE_BOTTOM,	// ����
	BLOCKFACETYPE_MAX
}BLOCKFACETYPE;

// �u���b�N�\����
typedef struct
{
	LPDIRECT3DTEXTURE9 apTextureBlock[6];	// �e�N�X�`���ւ̃|���^
	LPD3DXMESH pMeshBlock;					// ���b�V��(���_���ւ̃|�C���^)
	LPD3DXBUFFER pBuffMatBlock;				// �}�e���A���ւ̃|�C���^
	DWORD dwNumMatBlock;					// �}�e���A���̐�
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 vtxMinBlock, vtxMaxBlock;	// ���f���̍ŏ��l�ő�l
	const char* pFilename;	// �t�@�C����
	char astr[256];			// �����i�[
	int nType;				// �^�C�v
	int nLife;				// ����
	bool bUse;				// �g���Ă���邩�ǂ���
}BLOCK;

// �Z�b�g�u���b�N�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	const char* pFilename;	// �t�@�C����
	char astr[256];			// ������i�[�p
	int nType;				// �^�C�v
}SETBLOCK;

// �u���b�N�R���g���[���[
typedef struct
{
	int nCntNowBlock;	// ���I��ł���u���b�N
	int nNextBlType;	// ���ɔz�u����u���b�N�̃^�C�v
}BLOCKCONTROLLER;

// �u���b�N�̊Ǘ�
typedef struct
{
	char astr[BLOCKTYPE_MAX][256];	// ������i�[�p
	int nBlockNum;
}BLOCKMANAGER;

// �u���b�N����\����
typedef struct
{
	int nType;		// �ǂ̃^�C�v�ɓ������Ă�́H
	int nCnt;		// ���Ԗڂɓ������Ă�́H
	int nHitfase;	// �ǂ̖ʂɓ������Ă��
	bool bHit;		//�@�������Ă܂� 
}BLOCKCOLLISION;

// �v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(SETBLOCK setBlock, bool bFilenameAstr);
BLOCK* GetBlock(void);
BLOCKCONTROLLER* GetBlockController(void);
BLOCKMANAGER* GetBlockManager(void);

BLOCKCOLLISION CollisionBlockCharacter(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, int* pBlockType, float fWidth, float fHeight);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove);
BLOCKCOLLISION CollisionBlockBullet(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fSize);
BLOCKCOLLISION CollisionBlockSpher(D3DXVECTOR3 posA, float fSizeA, int nBreakType, bool bBreak);

BLOCK BlockSearch(BLOCKTYPE type, int nNumber);
void BlockDestroy(int nCnt);

void BlockOllDeliete(void);
void BlockControllre(void);

//BLOCK* GetBlockEX();
#endif // !_MODEL_H_
