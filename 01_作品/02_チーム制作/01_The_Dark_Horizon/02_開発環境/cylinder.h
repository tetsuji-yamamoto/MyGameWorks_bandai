#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "main.h"

#define FIELD_X (1000)
#define FIELD_Z (1000)
#define MESH_X (300)	// ��
#define MESH_Z (2)	// �c
#define MESH_PLYGON_HID (4 * (MESH_Z - 1))								// �k�ރ|���S��
#define MESH_PLYGON_APP ((MESH_X * MESH_Z) * 2)							// ������|���S��
#define MESH_PLYGON_AII (((MESH_X * MESH_Z) * 2) + (4 * (MESH_Z - 1)))		// ���v�|���S��
#define MESH_VERTEX ((MESH_X + 1) * (MESH_Z + 1))							// ���_��
#define MESH_INDEX (MESH_PLYGON_AII + 2)									// �C���f�b�N�X��

//�v���g�^�C�v�錾
void Initcylinder(void);
void Uninitcylinder(void);
void Updatecylinder(void);
void Drawcylinder(void);

bool CollisionMesh(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove);
#endif // !_POLYGON_H_
