#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "main.h"

#define FIELD_X (1000)
#define FIELD_Z (1000)
#define MESH_X (300)	// 横
#define MESH_Z (2)	// 縦
#define MESH_PLYGON_HID (4 * (MESH_Z - 1))								// 縮退ポリゴン
#define MESH_PLYGON_APP ((MESH_X * MESH_Z) * 2)							// 見えるポリゴン
#define MESH_PLYGON_AII (((MESH_X * MESH_Z) * 2) + (4 * (MESH_Z - 1)))		// 合計ポリゴン
#define MESH_VERTEX ((MESH_X + 1) * (MESH_Z + 1))							// 頂点数
#define MESH_INDEX (MESH_PLYGON_AII + 2)									// インデックスの

//プロトタイプ宣言
void Initcylinder(void);
void Uninitcylinder(void);
void Updatecylinder(void);
void Drawcylinder(void);

bool CollisionMesh(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove);
#endif // !_POLYGON_H_
