#include "light.h"
#include "keyboard.h"

//グローバル変数宣言
D3DLIGHT9 g_light[3];	//ライト情報

//*****************************************
//ライトの初期化
//*****************************************
void InitLight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ライトの方向ベクトル
	D3DXVECTOR3 vecDir[3];

	for (int nCntLight = 0;nCntLight < 3;nCntLight++)
	{
		//ライトをクリアする
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ライトの方向を設定
		vecDir[0] = D3DXVECTOR3(0.2f , -0.8f, -0.4f);
		vecDir[1] = D3DXVECTOR3(-12.0f , -14.0f, 15.0f);
		vecDir[2] = D3DXVECTOR3(-5.0f , -5.57f, -3.3f);

		//正規化する(大きさ１のベクトルにする)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		//ライトを設定する
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//*****************************************
//ライトの終了
//*****************************************
void UninitLight(void)
{
	

}

//*****************************************
//ライトの更新
//*****************************************
void UpdateLight(void)
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////ライトの方向ベクトル
	//D3DXVECTOR3 vecDir[3];

	//vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//vecDir[1] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//vecDir[2] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	//////正規化する(大きさ１のベクトルにする)
	////D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	////g_light[0].Direction = vecDir[0];

	//if (KeyboardRepeat(DIK_R) == true)
	//{
	//	g_light[0].Direction.x += 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_F) == true)
	//{
	//	g_light[0].Direction.x -= 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_V) == true)
	//{
	//	g_light[0].Direction.x = 0.0f;
	//}

	//if (KeyboardRepeat(DIK_T) == true)
	//{
	//	g_light[0].Direction.y += 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_G) == true)
	//{
	//	g_light[0].Direction.y -= 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_B) == true)
	//{
	//	g_light[0].Direction.y = 0.0f;
	//}

	//if (KeyboardRepeat(DIK_Y) == true)
	//{
	//	g_light[0].Direction.z += 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_H) == true)
	//{
	//	g_light[0].Direction.z -= 0.1f;
	//}
	//else if (KeyboardRepeat(DIK_N) == true)
	//{
	//	g_light[0].Direction.z = 0.0f;
	//}
	////ライトを設定する
	//pDevice->SetLight(0, &g_light[0]);
}

D3DLIGHT9* GetLight(void)
{
	return &g_light[0];
}