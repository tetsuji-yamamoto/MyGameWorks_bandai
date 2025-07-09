#ifndef _READTEXT_H_
#define _READTEXT_H_

#include "main.h"
#include "block.h"

typedef struct
{
	LPDIRECT3DTEXTURE9 apTextureBlock[BLOCKTYPE_MAX][6];	// �e�N�X�`���ւ̃|���^
	LPD3DXMESH apMeshBlock[BLOCKTYPE_MAX];					// ���b�V��(���_���ւ̃|�C���^)
	LPD3DXBUFFER apBuffMatBlock[BLOCKTYPE_MAX];				// �}�e���A���ւ̃|�C���^
	DWORD adwNumMatBlock[BLOCKTYPE_MAX];					// �}�e���A���̐�
}READBLOCK;

// �v���g�^�C�v�錾
void ReadText();
void SetStage(FILE* pFile);
void ReadBlockDate(FILE* pFile);
READBLOCK *GetReadBlock();
#endif