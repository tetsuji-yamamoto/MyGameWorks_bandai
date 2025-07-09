#ifndef _SWORD_H_
#define _SWORD_H_

#include "main.h"

#define SWORD_TEX "data\\SWORD\\LightningSword_001.png"	//剣のテクスチャ
#define SWORD_WIDTH (20)			//幅
#define SWORD_HEIGHT (140)			//高さ
#define MAX_ATTACK_FLAME (25)		//攻撃の全体フレーム
#define SWORD_DAMAGE (1)			//剣の攻撃力
#define BEAMSWORD_HEIGHT (400.0f)	//ビームソードの長さ
#define DISCHARGE_TIMING (40)		//ジャスト放出有余フレーム
#define BEAMSWORD_ANDERCOLOR_RED "D3DXVECTOR3(1.0f,0.3f,0.3f,1.0f)"
#define BEAMSWORD_ANDERCOLOR_BLUE "D3DXVECTOR3(0.3f,0.3f,1.0f,1.0f)"
#define BEAMSWORD_FLONTCOLOR_RED "D3DXVECTOR3(1.0f,0.5f,0.5f,1.0f)"
#define BEAMSWORD_FLONTCOLOR_BLUE "D3DXVECTOR3(0.5f,0.5f,1.0f,1.0f)"

#define BEAMBEAMBEAM (-2)

//剣の攻撃モーション
typedef enum
{
	SWORDATTACK_PREMOVE = 0,	//前動作
	SWORDATTACK_MAINMOVE,		//本動作
	SWORDATTACK_LEARMOVE,		//後動作
	SWORDATTACK_MAX,
	
}SWORDATTACKMOVE;

//剣のモーションの種類列挙型
typedef enum
{
	SWORDANIMTYPE_NONE = 0,			//なし
	SWORDANIMTYPE_ATTACK,			//通常攻撃
	SWORDANIMTYPE_CHARGE,			//チャージ
	SWORDANIMTYPE_DISCHARGE,		//放出
	SWORDANIMTYPE_JUSTDISCHARGE,	//ジャスト放出
	SWORDANIMTYPE_MAX
}SWORDANIMTYPE;

//ビームソード構造体
typedef struct
{
	D3DXCOLOR Andercol;	//色
	D3DXCOLOR Floatcol;	//色
	D3DXCOLOR tracecol;	//色
	bool bBeamSword;	//ビームソードを生成しているかどうか
	float fBSHeight;	//ビームソードの長さ
	float fBSWidth;		//ビームソードの幅
}BEAMSWORD;

//剣構造体
typedef struct
{
	BEAMSWORD beamSword;		//ビームソード情報
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR2 TopLeft;		//0
	D3DXVECTOR2 TopRight;		//1
	D3DXVECTOR2 BottomLeft;		//2
	D3DXVECTOR2 BottomRight;	//3
	D3DXCOLOR col;				//色
	RECT rectHitBox;			//当たり判定の大きさ
	int nState;					//状態
	int nMoveCnt;				//攻撃のフレームカウント
	float fAngle;				//角度
	float fKeepLot;				//キープする角度
	float fLot;					//追加の角度
	float fPositionX;			//剣の位置
	float fTopLeftX;			//0X
	float fLength;				//対角線
	bool bUse;					//使うかどうか
	bool bHit;					//当たるかどうか
	bool bJustDisCharge;		//ジャスト放出かどうか
}SWORD;

//剣アニメーション構造体
typedef struct
{
	int nAnimTurn;				//攻撃の状態
	float fAnimCnt1;			//アニメーションフレーム数1
	float fAnimCnt2;			//アニメーションフレーム数2
	float fAnimCnt3;			//アニメーションフレーム数3
	float fDesiredValueLot1;	//目的の値1
	float fDesiredValueLot2;	//目的の値2
	float fDesiredValueLot3;	//目的の値3
	float fBetweenLot;			//目的の値から今の値の間
	bool bSetAnim;				//計算するかどうか
}SWORDANIM;

//プロトタイプ
void InitSword(void);
void UninitSword(void);
void UpdateSword(void);
void DrawSword(void);
void SetSword(D3DXVECTOR3 pos);
void EquipmentSword(void);//equipment
void SwordAnimation(int nType);
void SetSwordAnim(int type, float fCnt1, float fCnt2, float fCnt3, float fDesValuLot1, float fDesValuLot2, float fDesValuLot3);
bool HitSword(D3DXVECTOR3 pos, float fWidth);
void BeamSwordGeneration(int nTurn);
SWORD* GetSword(void);
SWORDANIM* GetSwordAnim(void);
#endif