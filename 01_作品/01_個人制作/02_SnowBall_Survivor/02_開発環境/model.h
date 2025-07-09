#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

// ���f���\����
typedef struct
{
	LPDIRECT3DTEXTURE9 apTexture[6];	// �e�N�X�`���ւ̃|���^
	LPD3DXMESH pMesh;		// ���b�V��(���_���ւ̃|�C���^)
	LPD3DXBUFFER pBuffMat;	// �}�e���A���ւ̃|�C���^
	DWORD dwNumMat;			// �}�e���A���̐�
	int nIdxModelParent;	// �e���f���̃C���f�b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 offSet;		// �I�t�Z�b�g
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X

}Model;

// ���f���̐F�Ǘ�
typedef struct
{
	float fR;	// ��
	float fG;	// ��
	float fB;	// ��
	float fA;	// �A���t�@�l
}MODELCOLER;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

void SetModel(char astr[], Model* pModel, int nModelNum);
void PartsSet(FILE* pFile, Model* model);
void EndPartsSet(Model* pModel, Model model, int nIndex);

#endif // !_MODEL_H_
